/* The contents of this file was automatically generated by dump_modes.c
   with arguments: 48000 960
   It contains static definitions for some pre-defined modes. */
#include "modes.h"
#include "rate.h"

#ifndef DEF_WINDOW120
#define DEF_WINDOW120
static const opus_val16 window120[120] = {
2, 20, 55, 108, 178,
266, 372, 494, 635, 792,
966, 1157, 1365, 1590, 1831,
2089, 2362, 2651, 2956, 3276,
3611, 3961, 4325, 4703, 5094,
5499, 5916, 6346, 6788, 7241,
7705, 8179, 8663, 9156, 9657,
10167, 10684, 11207, 11736, 12271,
12810, 13353, 13899, 14447, 14997,
15547, 16098, 16648, 17197, 17744,
18287, 18827, 19363, 19893, 20418,
20936, 21447, 21950, 22445, 22931,
23407, 23874, 24330, 24774, 25208,
25629, 26039, 26435, 26819, 27190,
27548, 27893, 28224, 28541, 28845,
29135, 29411, 29674, 29924, 30160,
30384, 30594, 30792, 30977, 31151,
31313, 31463, 31602, 31731, 31849,
31958, 32057, 32148, 32229, 32303,
32370, 32429, 32481, 32528, 32568,
32604, 32634, 32661, 32683, 32701,
32717, 32729, 32740, 32748, 32754,
32758, 32762, 32764, 32766, 32767,
32767, 32767, 32767, 32767, 32767,
};
#endif

#ifndef DEF_LOGN400
#define DEF_LOGN400
static const opus_int16 logN400[21] = {
0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 16, 16, 16, 21, 21, 24, 29, 34, 36, };
#endif

#ifndef DEF_PULSE_CACHE50
#define DEF_PULSE_CACHE50
static const opus_int16 cache_index50[105] = {
-1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 41, 41, 41,
82, 82, 123, 164, 200, 222, 0, 0, 0, 0, 0, 0, 0, 0, 41,
41, 41, 41, 123, 123, 123, 164, 164, 240, 266, 283, 295, 41, 41, 41,
41, 41, 41, 41, 41, 123, 123, 123, 123, 240, 240, 240, 266, 266, 305,
318, 328, 336, 123, 123, 123, 123, 123, 123, 123, 123, 240, 240, 240, 240,
305, 305, 305, 318, 318, 343, 351, 358, 364, 240, 240, 240, 240, 240, 240,
240, 240, 305, 305, 305, 305, 343, 343, 343, 351, 351, 370, 376, 382, 387,
};
static const unsigned char cache_bits50[392] = {
40, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 40, 15, 23, 28,
31, 34, 36, 38, 39, 41, 42, 43, 44, 45, 46, 47, 47, 49, 50,
51, 52, 53, 54, 55, 55, 57, 58, 59, 60, 61, 62, 63, 63, 65,
66, 67, 68, 69, 70, 71, 71, 40, 20, 33, 41, 48, 53, 57, 61,
64, 66, 69, 71, 73, 75, 76, 78, 80, 82, 85, 87, 89, 91, 92,
94, 96, 98, 101, 103, 105, 107, 108, 110, 112, 114, 117, 119, 121, 123,
124, 126, 128, 40, 23, 39, 51, 60, 67, 73, 79, 83, 87, 91, 94,
97, 100, 102, 105, 107, 111, 115, 118, 121, 124, 126, 129, 131, 135, 139,
142, 145, 148, 150, 153, 155, 159, 163, 166, 169, 172, 174, 177, 179, 35,
28, 49, 65, 78, 89, 99, 107, 114, 120, 126, 132, 136, 141, 145, 149,
153, 159, 165, 171, 176, 180, 185, 189, 192, 199, 205, 211, 216, 220, 225,
229, 232, 239, 245, 251, 21, 33, 58, 79, 97, 112, 125, 137, 148, 157,
166, 174, 182, 189, 195, 201, 207, 217, 227, 235, 243, 251, 17, 35, 63,
86, 106, 123, 139, 152, 165, 177, 187, 197, 206, 214, 222, 230, 237, 250,
25, 31, 55, 75, 91, 105, 117, 128, 138, 146, 154, 161, 168, 174, 180,
185, 190, 200, 208, 215, 222, 229, 235, 240, 245, 255, 16, 36, 65, 89,
110, 128, 144, 159, 173, 185, 196, 207, 217, 226, 234, 242, 250, 11, 41,
74, 103, 128, 151, 172, 191, 209, 225, 241, 255, 9, 43, 79, 110, 138,
163, 186, 207, 227, 246, 12, 39, 71, 99, 123, 144, 164, 182, 198, 214,
228, 241, 253, 9, 44, 81, 113, 142, 168, 192, 214, 235, 255, 7, 49,
90, 127, 160, 191, 220, 247, 6, 51, 95, 134, 170, 203, 234, 7, 47,
87, 123, 155, 184, 212, 237, 6, 52, 97, 137, 174, 208, 240, 5, 57,
106, 151, 192, 231, 5, 59, 111, 158, 202, 243, 5, 55, 103, 147, 187,
224, 5, 60, 113, 161, 206, 248, 4, 65, 122, 175, 224, 4, 67, 127,
182, 234, };
static const unsigned char cache_caps50[168] = {
224, 224, 224, 224, 224, 224, 224, 224, 160, 160, 160, 160, 185, 185, 185,
178, 178, 168, 134, 61, 37, 224, 224, 224, 224, 224, 224, 224, 224, 240,
240, 240, 240, 207, 207, 207, 198, 198, 183, 144, 66, 40, 160, 160, 160,
160, 160, 160, 160, 160, 185, 185, 185, 185, 193, 193, 193, 183, 183, 172,
138, 64, 38, 240, 240, 240, 240, 240, 240, 240, 240, 207, 207, 207, 207,
204, 204, 204, 193, 193, 180, 143, 66, 40, 185, 185, 185, 185, 185, 185,
185, 185, 193, 193, 193, 193, 193, 193, 193, 183, 183, 172, 138, 65, 39,
207, 207, 207, 207, 207, 207, 207, 207, 204, 204, 204, 204, 201, 201, 201,
188, 188, 176, 141, 66, 40, 193, 193, 193, 193, 193, 193, 193, 193, 193,
193, 193, 193, 194, 194, 194, 184, 184, 173, 139, 65, 39, 204, 204, 204,
204, 204, 204, 204, 204, 201, 201, 201, 201, 198, 198, 198, 187, 187, 175,
140, 66, 40, };
#endif

#ifndef FFT_TWIDDLES48000_960
#define FFT_TWIDDLES48000_960
static const kiss_twiddle_cpx fft_twiddles48000_960[480] = {
{32767, 0}, {32766, -429},
{32757, -858}, {32743, -1287},
{32724, -1715}, {32698, -2143},
{32667, -2570}, {32631, -2998},
{32588, -3425}, {32541, -3851},
{32488, -4277}, {32429, -4701},
{32364, -5125}, {32295, -5548},
{32219, -5971}, {32138, -6393},
{32051, -6813}, {31960, -7231},
{31863, -7650}, {31760, -8067},
{31652, -8481}, {31539, -8895},
{31419, -9306}, {31294, -9716},
{31165, -10126}, {31030, -10532},
{30889, -10937}, {30743, -11340},
{30592, -11741}, {30436, -12141},
{30274, -12540}, {30107, -12935},
{29936, -13328}, {29758, -13718},
{29577, -14107}, {29390, -14493},
{29197, -14875}, {29000, -15257},
{28797, -15635}, {28590, -16010},
{28379, -16384}, {28162, -16753},
{27940, -17119}, {27714, -17484},
{27482, -17845}, {27246, -18205},
{27006, -18560}, {26760, -18911},
{26510, -19260}, {26257, -19606},
{25997, -19947}, {25734, -20286},
{25466, -20621}, {25194, -20952},
{24918, -21281}, {24637, -21605},
{24353, -21926}, {24063, -22242},
{23770, -22555}, {23473, -22865},
{23171, -23171}, {22866, -23472},
{22557, -23769}, {22244, -24063},
{21927, -24352}, {21606, -24636},
{21282, -24917}, {20954, -25194},
{20622, -25465}, {20288, -25733},
{19949, -25997}, {19607, -26255},
{19261, -26509}, {18914, -26760},
{18561, -27004}, {18205, -27246},
{17846, -27481}, {17485, -27713},
{17122, -27940}, {16755, -28162},
{16385, -28378}, {16012, -28590},
{15636, -28797}, {15258, -28999},
{14878, -29197}, {14494, -29389},
{14108, -29576}, {13720, -29757},
{13329, -29934}, {12937, -30107},
{12540, -30274}, {12142, -30435},
{11744, -30592}, {11342, -30743},
{10939, -30889}, {10534, -31030},
{10127, -31164}, {9718, -31294},
{9307, -31418}, {8895, -31537},
{8482, -31652}, {8067, -31759},
{7650, -31862}, {7233, -31960},
{6815, -32051}, {6393, -32138},
{5973, -32219}, {5549, -32294},
{5127, -32364}, {4703, -32429},
{4278, -32487}, {3852, -32541},
{3426, -32588}, {2999, -32630},
{2572, -32667}, {2144, -32698},
{1716, -32724}, {1287, -32742},
{860, -32757}, {430, -32766},
{0, -32767}, {-429, -32766},
{-858, -32757}, {-1287, -32743},
{-1715, -32724}, {-2143, -32698},
{-2570, -32667}, {-2998, -32631},
{-3425, -32588}, {-3851, -32541},
{-4277, -32488}, {-4701, -32429},
{-5125, -32364}, {-5548, -32295},
{-5971, -32219}, {-6393, -32138},
{-6813, -32051}, {-7231, -31960},
{-7650, -31863}, {-8067, -31760},
{-8481, -31652}, {-8895, -31539},
{-9306, -31419}, {-9716, -31294},
{-10126, -31165}, {-10532, -31030},
{-10937, -30889}, {-11340, -30743},
{-11741, -30592}, {-12141, -30436},
{-12540, -30274}, {-12935, -30107},
{-13328, -29936}, {-13718, -29758},
{-14107, -29577}, {-14493, -29390},
{-14875, -29197}, {-15257, -29000},
{-15635, -28797}, {-16010, -28590},
{-16384, -28379}, {-16753, -28162},
{-17119, -27940}, {-17484, -27714},
{-17845, -27482}, {-18205, -27246},
{-18560, -27006}, {-18911, -26760},
{-19260, -26510}, {-19606, -26257},
{-19947, -25997}, {-20286, -25734},
{-20621, -25466}, {-20952, -25194},
{-21281, -24918}, {-21605, -24637},
{-21926, -24353}, {-22242, -24063},
{-22555, -23770}, {-22865, -23473},
{-23171, -23171}, {-23472, -22866},
{-23769, -22557}, {-24063, -22244},
{-24352, -21927}, {-24636, -21606},
{-24917, -21282}, {-25194, -20954},
{-25465, -20622}, {-25733, -20288},
{-25997, -19949}, {-26255, -19607},
{-26509, -19261}, {-26760, -18914},
{-27004, -18561}, {-27246, -18205},
{-27481, -17846}, {-27713, -17485},
{-27940, -17122}, {-28162, -16755},
{-28378, -16385}, {-28590, -16012},
{-28797, -15636}, {-28999, -15258},
{-29197, -14878}, {-29389, -14494},
{-29576, -14108}, {-29757, -13720},
{-29934, -13329}, {-30107, -12937},
{-30274, -12540}, {-30435, -12142},
{-30592, -11744}, {-30743, -11342},
{-30889, -10939}, {-31030, -10534},
{-31164, -10127}, {-31294, -9718},
{-31418, -9307}, {-31537, -8895},
{-31652, -8482}, {-31759, -8067},
{-31862, -7650}, {-31960, -7233},
{-32051, -6815}, {-32138, -6393},
{-32219, -5973}, {-32294, -5549},
{-32364, -5127}, {-32429, -4703},
{-32487, -4278}, {-32541, -3852},
{-32588, -3426}, {-32630, -2999},
{-32667, -2572}, {-32698, -2144},
{-32724, -1716}, {-32742, -1287},
{-32757, -860}, {-32766, -430},
{-32767, 0}, {-32766, 429},
{-32757, 858}, {-32743, 1287},
{-32724, 1715}, {-32698, 2143},
{-32667, 2570}, {-32631, 2998},
{-32588, 3425}, {-32541, 3851},
{-32488, 4277}, {-32429, 4701},
{-32364, 5125}, {-32295, 5548},
{-32219, 5971}, {-32138, 6393},
{-32051, 6813}, {-31960, 7231},
{-31863, 7650}, {-31760, 8067},
{-31652, 8481}, {-31539, 8895},
{-31419, 9306}, {-31294, 9716},
{-31165, 10126}, {-31030, 10532},
{-30889, 10937}, {-30743, 11340},
{-30592, 11741}, {-30436, 12141},
{-30274, 12540}, {-30107, 12935},
{-29936, 13328}, {-29758, 13718},
{-29577, 14107}, {-29390, 14493},
{-29197, 14875}, {-29000, 15257},
{-28797, 15635}, {-28590, 16010},
{-28379, 16384}, {-28162, 16753},
{-27940, 17119}, {-27714, 17484},
{-27482, 17845}, {-27246, 18205},
{-27006, 18560}, {-26760, 18911},
{-26510, 19260}, {-26257, 19606},
{-25997, 19947}, {-25734, 20286},
{-25466, 20621}, {-25194, 20952},
{-24918, 21281}, {-24637, 21605},
{-24353, 21926}, {-24063, 22242},
{-23770, 22555}, {-23473, 22865},
{-23171, 23171}, {-22866, 23472},
{-22557, 23769}, {-22244, 24063},
{-21927, 24352}, {-21606, 24636},
{-21282, 24917}, {-20954, 25194},
{-20622, 25465}, {-20288, 25733},
{-19949, 25997}, {-19607, 26255},
{-19261, 26509}, {-18914, 26760},
{-18561, 27004}, {-18205, 27246},
{-17846, 27481}, {-17485, 27713},
{-17122, 27940}, {-16755, 28162},
{-16385, 28378}, {-16012, 28590},
{-15636, 28797}, {-15258, 28999},
{-14878, 29197}, {-14494, 29389},
{-14108, 29576}, {-13720, 29757},
{-13329, 29934}, {-12937, 30107},
{-12540, 30274}, {-12142, 30435},
{-11744, 30592}, {-11342, 30743},
{-10939, 30889}, {-10534, 31030},
{-10127, 31164}, {-9718, 31294},
{-9307, 31418}, {-8895, 31537},
{-8482, 31652}, {-8067, 31759},
{-7650, 31862}, {-7233, 31960},
{-6815, 32051}, {-6393, 32138},
{-5973, 32219}, {-5549, 32294},
{-5127, 32364}, {-4703, 32429},
{-4278, 32487}, {-3852, 32541},
{-3426, 32588}, {-2999, 32630},
{-2572, 32667}, {-2144, 32698},
{-1716, 32724}, {-1287, 32742},
{-860, 32757}, {-430, 32766},
{0, 32767}, {429, 32766},
{858, 32757}, {1287, 32743},
{1715, 32724}, {2143, 32698},
{2570, 32667}, {2998, 32631},
{3425, 32588}, {3851, 32541},
{4277, 32488}, {4701, 32429},
{5125, 32364}, {5548, 32295},
{5971, 32219}, {6393, 32138},
{6813, 32051}, {7231, 31960},
{7650, 31863}, {8067, 31760},
{8481, 31652}, {8895, 31539},
{9306, 31419}, {9716, 31294},
{10126, 31165}, {10532, 31030},
{10937, 30889}, {11340, 30743},
{11741, 30592}, {12141, 30436},
{12540, 30274}, {12935, 30107},
{13328, 29936}, {13718, 29758},
{14107, 29577}, {14493, 29390},
{14875, 29197}, {15257, 29000},
{15635, 28797}, {16010, 28590},
{16384, 28379}, {16753, 28162},
{17119, 27940}, {17484, 27714},
{17845, 27482}, {18205, 27246},
{18560, 27006}, {18911, 26760},
{19260, 26510}, {19606, 26257},
{19947, 25997}, {20286, 25734},
{20621, 25466}, {20952, 25194},
{21281, 24918}, {21605, 24637},
{21926, 24353}, {22242, 24063},
{22555, 23770}, {22865, 23473},
{23171, 23171}, {23472, 22866},
{23769, 22557}, {24063, 22244},
{24352, 21927}, {24636, 21606},
{24917, 21282}, {25194, 20954},
{25465, 20622}, {25733, 20288},
{25997, 19949}, {26255, 19607},
{26509, 19261}, {26760, 18914},
{27004, 18561}, {27246, 18205},
{27481, 17846}, {27713, 17485},
{27940, 17122}, {28162, 16755},
{28378, 16385}, {28590, 16012},
{28797, 15636}, {28999, 15258},
{29197, 14878}, {29389, 14494},
{29576, 14108}, {29757, 13720},
{29934, 13329}, {30107, 12937},
{30274, 12540}, {30435, 12142},
{30592, 11744}, {30743, 11342},
{30889, 10939}, {31030, 10534},
{31164, 10127}, {31294, 9718},
{31418, 9307}, {31537, 8895},
{31652, 8482}, {31759, 8067},
{31862, 7650}, {31960, 7233},
{32051, 6815}, {32138, 6393},
{32219, 5973}, {32294, 5549},
{32364, 5127}, {32429, 4703},
{32487, 4278}, {32541, 3852},
{32588, 3426}, {32630, 2999},
{32667, 2572}, {32698, 2144},
{32724, 1716}, {32742, 1287},
{32757, 860}, {32766, 430},
};
#ifndef FFT_BITREV480
#define FFT_BITREV480
static const opus_int16 fft_bitrev480[480] = {
0, 120, 240, 360, 30, 150, 270, 390, 60, 180, 300, 420, 90, 210, 330,
450, 15, 135, 255, 375, 45, 165, 285, 405, 75, 195, 315, 435, 105, 225,
345, 465, 5, 125, 245, 365, 35, 155, 275, 395, 65, 185, 305, 425, 95,
215, 335, 455, 20, 140, 260, 380, 50, 170, 290, 410, 80, 200, 320, 440,
110, 230, 350, 470, 10, 130, 250, 370, 40, 160, 280, 400, 70, 190, 310,
430, 100, 220, 340, 460, 25, 145, 265, 385, 55, 175, 295, 415, 85, 205,
325, 445, 115, 235, 355, 475, 1, 121, 241, 361, 31, 151, 271, 391, 61,
181, 301, 421, 91, 211, 331, 451, 16, 136, 256, 376, 46, 166, 286, 406,
76, 196, 316, 436, 106, 226, 346, 466, 6, 126, 246, 366, 36, 156, 276,
396, 66, 186, 306, 426, 96, 216, 336, 456, 21, 141, 261, 381, 51, 171,
291, 411, 81, 201, 321, 441, 111, 231, 351, 471, 11, 131, 251, 371, 41,
161, 281, 401, 71, 191, 311, 431, 101, 221, 341, 461, 26, 146, 266, 386,
56, 176, 296, 416, 86, 206, 326, 446, 116, 236, 356, 476, 2, 122, 242,
362, 32, 152, 272, 392, 62, 182, 302, 422, 92, 212, 332, 452, 17, 137,
257, 377, 47, 167, 287, 407, 77, 197, 317, 437, 107, 227, 347, 467, 7,
127, 247, 367, 37, 157, 277, 397, 67, 187, 307, 427, 97, 217, 337, 457,
22, 142, 262, 382, 52, 172, 292, 412, 82, 202, 322, 442, 112, 232, 352,
472, 12, 132, 252, 372, 42, 162, 282, 402, 72, 192, 312, 432, 102, 222,
342, 462, 27, 147, 267, 387, 57, 177, 297, 417, 87, 207, 327, 447, 117,
237, 357, 477, 3, 123, 243, 363, 33, 153, 273, 393, 63, 183, 303, 423,
93, 213, 333, 453, 18, 138, 258, 378, 48, 168, 288, 408, 78, 198, 318,
438, 108, 228, 348, 468, 8, 128, 248, 368, 38, 158, 278, 398, 68, 188,
308, 428, 98, 218, 338, 458, 23, 143, 263, 383, 53, 173, 293, 413, 83,
203, 323, 443, 113, 233, 353, 473, 13, 133, 253, 373, 43, 163, 283, 403,
73, 193, 313, 433, 103, 223, 343, 463, 28, 148, 268, 388, 58, 178, 298,
418, 88, 208, 328, 448, 118, 238, 358, 478, 4, 124, 244, 364, 34, 154,
274, 394, 64, 184, 304, 424, 94, 214, 334, 454, 19, 139, 259, 379, 49,
169, 289, 409, 79, 199, 319, 439, 109, 229, 349, 469, 9, 129, 249, 369,
39, 159, 279, 399, 69, 189, 309, 429, 99, 219, 339, 459, 24, 144, 264,
384, 54, 174, 294, 414, 84, 204, 324, 444, 114, 234, 354, 474, 14, 134,
254, 374, 44, 164, 284, 404, 74, 194, 314, 434, 104, 224, 344, 464, 29,
149, 269, 389, 59, 179, 299, 419, 89, 209, 329, 449, 119, 239, 359, 479,
};
#endif

#ifndef FFT_BITREV240
#define FFT_BITREV240
static const opus_int16 fft_bitrev240[240] = {
0, 60, 120, 180, 15, 75, 135, 195, 30, 90, 150, 210, 45, 105, 165,
225, 5, 65, 125, 185, 20, 80, 140, 200, 35, 95, 155, 215, 50, 110,
170, 230, 10, 70, 130, 190, 25, 85, 145, 205, 40, 100, 160, 220, 55,
115, 175, 235, 1, 61, 121, 181, 16, 76, 136, 196, 31, 91, 151, 211,
46, 106, 166, 226, 6, 66, 126, 186, 21, 81, 141, 201, 36, 96, 156,
216, 51, 111, 171, 231, 11, 71, 131, 191, 26, 86, 146, 206, 41, 101,
161, 221, 56, 116, 176, 236, 2, 62, 122, 182, 17, 77, 137, 197, 32,
92, 152, 212, 47, 107, 167, 227, 7, 67, 127, 187, 22, 82, 142, 202,
37, 97, 157, 217, 52, 112, 172, 232, 12, 72, 132, 192, 27, 87, 147,
207, 42, 102, 162, 222, 57, 117, 177, 237, 3, 63, 123, 183, 18, 78,
138, 198, 33, 93, 153, 213, 48, 108, 168, 228, 8, 68, 128, 188, 23,
83, 143, 203, 38, 98, 158, 218, 53, 113, 173, 233, 13, 73, 133, 193,
28, 88, 148, 208, 43, 103, 163, 223, 58, 118, 178, 238, 4, 64, 124,
184, 19, 79, 139, 199, 34, 94, 154, 214, 49, 109, 169, 229, 9, 69,
129, 189, 24, 84, 144, 204, 39, 99, 159, 219, 54, 114, 174, 234, 14,
74, 134, 194, 29, 89, 149, 209, 44, 104, 164, 224, 59, 119, 179, 239,
};
#endif

#ifndef FFT_BITREV120
#define FFT_BITREV120
static const opus_int16 fft_bitrev120[120] = {
0, 30, 60, 90, 15, 45, 75, 105, 5, 35, 65, 95, 20, 50, 80,
110, 10, 40, 70, 100, 25, 55, 85, 115, 1, 31, 61, 91, 16, 46,
76, 106, 6, 36, 66, 96, 21, 51, 81, 111, 11, 41, 71, 101, 26,
56, 86, 116, 2, 32, 62, 92, 17, 47, 77, 107, 7, 37, 67, 97,
22, 52, 82, 112, 12, 42, 72, 102, 27, 57, 87, 117, 3, 33, 63,
93, 18, 48, 78, 108, 8, 38, 68, 98, 23, 53, 83, 113, 13, 43,
73, 103, 28, 58, 88, 118, 4, 34, 64, 94, 19, 49, 79, 109, 9,
39, 69, 99, 24, 54, 84, 114, 14, 44, 74, 104, 29, 59, 89, 119,
};
#endif

#ifndef FFT_BITREV60
#define FFT_BITREV60
static const opus_int16 fft_bitrev60[60] = {
0, 15, 30, 45, 5, 20, 35, 50, 10, 25, 40, 55, 1, 16, 31,
46, 6, 21, 36, 51, 11, 26, 41, 56, 2, 17, 32, 47, 7, 22,
37, 52, 12, 27, 42, 57, 3, 18, 33, 48, 8, 23, 38, 53, 13,
28, 43, 58, 4, 19, 34, 49, 9, 24, 39, 54, 14, 29, 44, 59,
};
#endif

#ifndef FFT_STATE48000_960_0
#define FFT_STATE48000_960_0
static const kiss_fft_state fft_state48000_960_0 = {
480,	/* nfft */
-1,	/* shift */
{4, 120, 4, 30, 2, 15, 3, 5, 5, 1, 0, 0, 0, 0, 0, 0, },	/* factors */
fft_bitrev480,	/* bitrev */
fft_twiddles48000_960,	/* bitrev */
};
#endif

#ifndef FFT_STATE48000_960_1
#define FFT_STATE48000_960_1
static const kiss_fft_state fft_state48000_960_1 = {
240,	/* nfft */
1,	/* shift */
{4, 60, 4, 15, 3, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, },	/* factors */
fft_bitrev240,	/* bitrev */
fft_twiddles48000_960,	/* bitrev */
};
#endif

#ifndef FFT_STATE48000_960_2
#define FFT_STATE48000_960_2
static const kiss_fft_state fft_state48000_960_2 = {
120,	/* nfft */
2,	/* shift */
{4, 30, 2, 15, 3, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, },	/* factors */
fft_bitrev120,	/* bitrev */
fft_twiddles48000_960,	/* bitrev */
};
#endif

#ifndef FFT_STATE48000_960_3
#define FFT_STATE48000_960_3
static const kiss_fft_state fft_state48000_960_3 = {
60,	/* nfft */
3,	/* shift */
{4, 15, 3, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },	/* factors */
fft_bitrev60,	/* bitrev */
fft_twiddles48000_960,	/* bitrev */
};
#endif

#endif

#ifndef MDCT_TWIDDLES960
#define MDCT_TWIDDLES960
static const opus_val16 mdct_twiddles960[481] = {
32767, 32767, 32767, 32767, 32766,
32763, 32762, 32759, 32757, 32753,
32751, 32747, 32743, 32738, 32733,
32729, 32724, 32717, 32711, 32705,
32698, 32690, 32683, 32676, 32667,
32658, 32650, 32640, 32631, 32620,
32610, 32599, 32588, 32577, 32566,
32554, 32541, 32528, 32515, 32502,
32487, 32474, 32459, 32444, 32429,
32413, 32397, 32381, 32364, 32348,
32331, 32313, 32294, 32277, 32257,
32239, 32219, 32200, 32180, 32159,
32138, 32118, 32096, 32074, 32051,
32029, 32006, 31984, 31960, 31936,
31912, 31888, 31863, 31837, 31812,
31786, 31760, 31734, 31707, 31679,
31652, 31624, 31596, 31567, 31539,
31508, 31479, 31450, 31419, 31388,
31357, 31326, 31294, 31262, 31230,
31198, 31164, 31131, 31097, 31063,
31030, 30994, 30959, 30924, 30889,
30853, 30816, 30779, 30743, 30705,
30668, 30629, 30592, 30553, 30515,
30475, 30435, 30396, 30356, 30315,
30274, 30233, 30191, 30149, 30107,
30065, 30022, 29979, 29936, 29891,
29847, 29803, 29758, 29713, 29668,
29622, 29577, 29529, 29483, 29436,
29390, 29341, 29293, 29246, 29197,
29148, 29098, 29050, 29000, 28949,
28899, 28848, 28797, 28746, 28694,
28642, 28590, 28537, 28485, 28432,
28378, 28324, 28271, 28217, 28162,
28106, 28051, 27995, 27940, 27884,
27827, 27770, 27713, 27657, 27598,
27540, 27481, 27423, 27365, 27305,
27246, 27187, 27126, 27066, 27006,
26945, 26883, 26822, 26760, 26698,
26636, 26574, 26510, 26448, 26383,
26320, 26257, 26191, 26127, 26062,
25997, 25931, 25866, 25800, 25734,
25667, 25601, 25533, 25466, 25398,
25330, 25262, 25194, 25125, 25056,
24987, 24917, 24848, 24778, 24707,
24636, 24566, 24495, 24424, 24352,
24280, 24208, 24135, 24063, 23990,
23917, 23842, 23769, 23695, 23622,
23546, 23472, 23398, 23322, 23246,
23171, 23095, 23018, 22942, 22866,
22788, 22711, 22634, 22557, 22478,
22400, 22322, 22244, 22165, 22085,
22006, 21927, 21846, 21766, 21687,
21606, 21524, 21443, 21363, 21282,
21199, 21118, 21035, 20954, 20870,
20788, 20705, 20621, 20538, 20455,
20371, 20286, 20202, 20118, 20034,
19947, 19863, 19777, 19692, 19606,
19520, 19434, 19347, 19260, 19174,
19088, 18999, 18911, 18825, 18737,
18648, 18560, 18472, 18384, 18294,
18205, 18116, 18025, 17936, 17846,
17757, 17666, 17576, 17485, 17395,
17303, 17212, 17122, 17030, 16937,
16846, 16755, 16662, 16569, 16477,
16385, 16291, 16198, 16105, 16012,
15917, 15824, 15730, 15636, 15541,
15447, 15352, 15257, 15162, 15067,
14973, 14875, 14781, 14685, 14589,
14493, 14396, 14300, 14204, 14107,
14010, 13914, 13815, 13718, 13621,
13524, 13425, 13328, 13230, 13133,
13033, 12935, 12836, 12738, 12638,
12540, 12441, 12341, 12241, 12142,
12044, 11943, 11843, 11744, 11643,
11542, 11442, 11342, 11241, 11139,
11039, 10939, 10836, 10736, 10635,
10534, 10431, 10330, 10228, 10127,
10024, 9921, 9820, 9718, 9614,
9512, 9410, 9306, 9204, 9101,
8998, 8895, 8791, 8689, 8585,
8481, 8377, 8274, 8171, 8067,
7962, 7858, 7753, 7650, 7545,
7441, 7336, 7231, 7129, 7023,
6917, 6813, 6709, 6604, 6498,
6393, 6288, 6182, 6077, 5973,
5867, 5760, 5656, 5549, 5445,
5339, 5232, 5127, 5022, 4914,
4809, 4703, 4596, 4490, 4384,
4278, 4171, 4065, 3958, 3852,
3745, 3640, 3532, 3426, 3318,
3212, 3106, 2998, 2891, 2786,
2679, 2570, 2465, 2358, 2251,
2143, 2037, 1929, 1823, 1715,
1609, 1501, 1393, 1287, 1180,
1073, 964, 858, 751, 644,
535, 429, 322, 214, 107,
0, };
#endif

static const CELTMode mode48000_960_120 = {
48000,	/* Fs */
120,	/* overlap */
21,	/* nbEBands */
21,	/* effEBands */
{27853, 0, 4096, 8192, },	/* preemph */
eband5ms,	/* eBands */
3,	/* maxLM */
8,	/* nbShortMdcts */
120,	/* shortMdctSize */
11,	/* nbAllocVectors */
band_allocation,	/* allocVectors */
logN400,	/* logN */
window120,	/* window */
{1920, 3, {&fft_state48000_960_0, &fft_state48000_960_1, &fft_state48000_960_2, &fft_state48000_960_3, }, mdct_twiddles960},	/* mdct */
{392, cache_index50, cache_bits50, cache_caps50},	/* cache */
};

/* List of all the available modes */
#define TOTAL_MODES 1
static const CELTMode * const static_mode_list[TOTAL_MODES] = {
&mode48000_960_120,
};
