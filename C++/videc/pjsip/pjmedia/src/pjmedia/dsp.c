//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdint.h>
#include <math.h>

#include "dsp.h"

#define M_PI  (3.141592653589793238462643383279f)
static int SAMPLE_RATE = 48000;//8000;

#define MIN_SAMPLE 612//102


static float dtmf_row[] =
{
	697.0,  770.0,  852.0,  941.0
};
static float dtmf_col[] =
{
	1209.0, 1336.0, 1477.0, 1633.0
};


static char dtmf_positions[] = "123A" "456B" "789C" "*0#D";

static void goertzel_sample(goertzel_state_t *s, short sample)
{
	int v1;

	v1 = s->v2;
	s->v2 = s->v3;

	s->v3 = (s->fac * s->v2) >> 15;
	s->v3 = s->v3 - v1 + (sample >> s->chunky);
	if (abs(s->v3) > 32768) {
		s->chunky++;
		s->v3 = s->v3 >> 1;
		s->v2 = s->v2 >> 1;
		v1 = v1 >> 1;
	}
}

static void goertzel_update(goertzel_state_t *s, short *samps, int count)
{
	int i;

	for (i=0;i<count;i++) 
		goertzel_sample(s, samps[i]);
}

static float goertzel_result(goertzel_state_t *s)
{
	goertzel_result_t r;
	r.value = (s->v3 * s->v3) + (s->v2 * s->v2);
	r.value -= ((s->v2 * s->v3) >> 15) * s->fac;
	r.power = s->chunky * 2;
	return (float)r.value * (float)(1 << r.power);
}

static void goertzel_init(goertzel_state_t *s, float freq, int samples, int nSamplerate)
{
	s->v2 = s->v3 = s->chunky = 0.0;
	s->fac = (int)(32768.0 * 2.0 * cos(2.0 * M_PI * freq / nSamplerate));
	s->samples = samples;
}

static void goertzel_reset(goertzel_state_t *s)
{
	s->v2 = s->v3 = s->chunky = 0.0;
}

static void ast_dtmf_detect_init (dtmf_detect_state_t *s, int nMinSamples, int nSamplerate)
{
	int i;
	s->lasthit = 0;
	s->current_hit = 0;

	for (i = 0;  i < 4;  i++) {
		goertzel_init (&s->row_out[i], dtmf_row[i], nMinSamples, nSamplerate);
		goertzel_init (&s->col_out[i], dtmf_col[i], nMinSamples, nSamplerate);
		s->energy = 0.0;
	}
	s->current_sample = 0;
}

void ast_digit_detect_init(digit_detect_state_t *s, int new_detect, int nSamplerate)
{
	s->current_digits = 0;
	s->detected_digits = 0;
	s->lost_digits = 0;
	s->digits[0] = '\0';

	s->m_nSamplerate = nSamplerate; //liurui

	//#define MIN_SAMPLE 612//102
	if( nSamplerate == 8000 )
		s->m_nMinSamples = 102;
	else if( nSamplerate == 16000 )
		s->m_nMinSamples = 102*2;
	else if( nSamplerate == 32000 )
		s->m_nMinSamples = 102*4;
	else if( nSamplerate == 48000 )
		s->m_nMinSamples = 102*6;

	if (new_detect)
		ast_dtmf_detect_init(&s->td.dtmf, s->m_nMinSamples, nSamplerate);
}

static void store_digit(digit_detect_state_t *s, char digit)
{
	s->digits[0] = digit;
	s->detected_digits = 1;
	s->digits[1] = '\0';
	return;

	s->detected_digits++;
	if (s->current_digits < MAX_DTMF_DIGITS) {
		s->digits[s->current_digits++] = digit;
		s->digits[s->current_digits] = '\0';
	} else {
		/* ast_log(LOG_WARNING, "Digit lost due to full buffer\n"); */
		//s->lost_digits++;

		// Reset data
		s->current_digits = 0;
		s->detected_digits = 0;
		s->lost_digits = 0;
		s->digits[0] = '\0';

		s->detected_digits++;
		if (s->current_digits < MAX_DTMF_DIGITS) {
			s->digits[s->current_digits++] = digit;
			s->digits[s->current_digits] = '\0';
		}
	}
}

int dtmf_detect(digit_detect_state_t *s, short amp[], int samples, int digitmode)
{
	float row_energy[4];
	float col_energy[4];
	float famp;
	int i;
	int j;
	int sample;
	int best_row;
	int best_col;
	int hit;
	int limit;

	hit = 0;
	for (sample = 0;  sample < samples;  sample = limit) 
	{
		/* 102 is optimised to meet the DTMF specs. */
		if ((samples - sample) >= (s->m_nMinSamples - s->td.dtmf.current_sample))
			limit = sample + (s->m_nMinSamples - s->td.dtmf.current_sample);
		else
			limit = samples;
		/* The following unrolled loop takes only 35% (rough estimate) of the 
		time of a rolled loop on the machine on which it was developed */
		for (j = sample; j < limit; j++) {
			famp = amp[j];
			s->td.dtmf.energy += famp*famp;
			/* With GCC 2.95, the following unrolled code seems to take about 35%
			(rough estimate) as long as a neat little 0-3 loop */
			goertzel_sample(s->td.dtmf.row_out, amp[j]);
			goertzel_sample(s->td.dtmf.col_out, amp[j]);
			goertzel_sample(s->td.dtmf.row_out + 1, amp[j]);
			goertzel_sample(s->td.dtmf.col_out + 1, amp[j]);
			goertzel_sample(s->td.dtmf.row_out + 2, amp[j]);
			goertzel_sample(s->td.dtmf.col_out + 2, amp[j]);
			goertzel_sample(s->td.dtmf.row_out + 3, amp[j]);
			goertzel_sample(s->td.dtmf.col_out + 3, amp[j]);
		}
		s->td.dtmf.current_sample += (limit - sample);
		if (s->td.dtmf.current_sample < s->m_nMinSamples) {
			if (hit && !((digitmode & DSP_DIGITMODE_NOQUELCH))) {
				/* If we had a hit last time, go ahead and clear this out since likely it
				will be another hit */
				for (i=sample;i<limit;i++) 
					amp[i] = 0;
			}
			continue;
		}
		/* We are at the end of a DTMF detection block */
		/* Find the peak row and the peak column */
		row_energy[0] = goertzel_result (&s->td.dtmf.row_out[0]);
		col_energy[0] = goertzel_result (&s->td.dtmf.col_out[0]);

		for (best_row = best_col = 0, i = 1;  i < 4;  i++) {
			row_energy[i] = goertzel_result (&s->td.dtmf.row_out[i]);
			if (row_energy[i] > row_energy[best_row])
				best_row = i;
			col_energy[i] = goertzel_result (&s->td.dtmf.col_out[i]);
			if (col_energy[i] > col_energy[best_col])
				best_col = i;
		}
		hit = 0;

		/* Basic signal level test and the twist test */
		if (row_energy[best_row] >= DTMF_THRESHOLD && 
			col_energy[best_col] >= DTMF_THRESHOLD &&
			/* 			col_energy[best_col] < row_energy[best_row] *DTMF_REVERSE_TWIST &&		  aluigi work-around */
			col_energy[best_col]*DTMF_NORMAL_TWIST > row_energy[best_row]) {
				/* Relative peak test */
				for (i = 0;  i < 4;  i++) 
				{
					if ((i != best_col &&
						col_energy[i]*DTMF_RELATIVE_PEAK_COL > col_energy[best_col]) ||
						(i != best_row 
						&& row_energy[i]*DTMF_RELATIVE_PEAK_ROW > row_energy[best_row])) {
							break;
					}
				}
				/* ... and fraction of total energy test */
				if (i >= 4 /*&&
						   (row_energy[best_row] + col_energy[best_col]) > DTMF_TO_TOTAL_ENERGY*s->td.dtmf.energy*/) 
				{	 /*  aluigi work-around */
							   /* Got a hit */
							   hit = dtmf_positions[(best_row << 2) + best_col];
							   if (!(digitmode & DSP_DIGITMODE_NOQUELCH)) {
								   /* Zero out frame data if this is part DTMF */
								   for (i=sample;i<limit;i++) 
									   amp[i] = 0;
							   }
				}
		} 

		/* The logic in the next test is:
		For digits we need two successive identical clean detects, with
		something different preceeding it. This can work with
		back to back differing digits. More importantly, it
		can work with nasty phones that give a very wobbly start
		to a digit */
		if (hit != s->td.dtmf.current_hit) {
			if (hit && s->td.dtmf.lasthit == hit) {
				s->td.dtmf.current_hit = hit;
				store_digit(s, hit);
			} else if (s->td.dtmf.lasthit != s->td.dtmf.current_hit) {
				s->td.dtmf.current_hit = 0;
				//liurui
				s->detected_digits = 0;
			}
		}
		s->td.dtmf.lasthit = hit;

		/* Reinitialise the detector for the next block */
		for (i = 0;  i < 4;  i++) 
		{
			goertzel_reset(&s->td.dtmf.row_out[i]);
			goertzel_reset(&s->td.dtmf.col_out[i]);
		}
		s->td.dtmf.energy = 0.0;
		s->td.dtmf.current_sample = 0;
	}
	return (s->td.dtmf.current_hit);	/* return the debounced hit */
}
