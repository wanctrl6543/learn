#include "stdafx.h"
#include "SubTitle.h"
#include "resource.h"
#include "LoadHex.h"
#include <VIDEC/VIDEC.h>


SubTitle::SubTitle(void)
{
}

SubTitle::~SubTitle()
{
}

unsigned char*	SubTitle::m_pHZK=NULL;
int				SubTitle::m_nHZKSize=0;


unsigned char SubTitle::Ascii[]=
{
	/*0x00*/  
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	/*0x10*/  
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

	/*0x20*/  
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/* */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x3c,0x3c,0x3c,0x18,0x18,/*!*/
	0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,
	0x00,0x66,0x66,0x66,0x24,0x00,0x00,0x00,/*"*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x6c,0x6c,0xfe,0x6c,0x6c,
	0x6c,0xfe,0x6c,0x6c,0x00,0x00,0x00,0x00,
	0x18,0x18,0x7c,0xc6,0xc2,0xc0,0x7c,0x06,
	0x86,0xc6,0x7c,0x18,0x18,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xc2,0xc6,0x0c,0x18,
	0x30,0x60,0xc6,0x86,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x6c,0x6c,0x38,0x76,0xdc,
	0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
	0x00,0x30,0x30,0x30,0x60,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0c,0x18,0x30,0x30,0x30,0x30,
	0x30,0x30,0x18,0x0c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x30,0x18,0x0c,0x0c,0x0c,0x0c,
	0x0c,0x0c,0x18,0x30,0x00,0x00,0x00,0x00,



	0x00,0x00,0x00,0x00,0x00,0x66,0x3c,0xff,
	0x3c,0x66,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x7e,
	0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x18,0x18,0x18,0x30,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x02,0x06,0x0c,0x18,
	0x30,0x60,0xc0,0x80,0x00,0x00,0x00,0x00,



	0x00,0x00,0x7c,0xc6,0xc6,0xce,0xd6,0xd6,
	0xe6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x38,0x78,0x18,0x18,0x18,/*1*/
	0x18,0x18,0x18,0x7e,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0x06,0x0c,0x18,0x30,
	0x60,0xc0,0xc6,0xfe,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0x06,0x06,0x3c,0x06,
	0x06,0x06,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x0c,0x1c,0x3c,0x6c,0xcc,0xfe,
	0x0c,0x0c,0x0c,0x1e,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0xc0,0xc0,0xc0,0xfc,0x0e,
	0x06,0x06,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x60,0xc0,0xc0,0xfc,0xc6,
	0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0xc6,0x06,0x06,0x0c,0x18,
	0x30,0x30,0x30,0x30,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0xc6,0xc6,0x7c,0xc6,
	0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0xc6,0xc6,0x7e,0x06,
	0x06,0x06,0x0c,0x78,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
	0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
	0x00,0x18,0x18,0x30,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x06,0x0c,0x18,0x30,0x60,
	0x30,0x18,0x0c,0x06,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,
	0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x60,0x30,0x18,0x0c,0x06,
	0x0c,0x18,0x30,0x60,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0xc6,0x0c,0x18,0x18,
	0x18,0x00,0x18,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x7c,0xc6,0xc6,0xde,0xde,
	0xde,0xdc,0xc0,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x10,0x38,0x6c,0xc6,0xc6,0xfe,
	0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfc,0x66,0x66,0x66,0x7c,0x66,
	0x66,0x66,0x66,0xfc,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x66,0xc2,0xc0,0xc0,0xc0,
	0xc0,0xc2,0x66,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xf8,0x6c,0x66,0x66,0x66,0x66,
	0x66,0x66,0x6c,0xf8,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0x66,0x62,0x68,0x78,0x68,
	0x60,0x62,0x66,0xfe,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0x66,0x62,0x68,0x78,0x68,
	0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x66,0xc2,0xc0,0xc0,0xde,
	0xc6,0xc6,0x66,0x3a,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xfe,0xc6,
	0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x18,0x18,0x18,0x18,0x18,
	0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1e,0x0c,0x0c,0x0c,0x0c,0x0c,
	0xcc,0xcc,0xcc,0x78,0x00,0x00,0x00,0x00,
	0x00,0x00,0xe6,0x66,0x6c,0x6c,0x78,0x78,
	0x6c,0x66,0x66,0xe6,0x00,0x00,0x00,0x00,
	0x00,0x00,0xf0,0x60,0x60,0x60,0x60,0x60,
	0x60,0x62,0x66,0xfe,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xee,0xfe,0xfe,0xd6,0xc6,
	0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xe6,0xf6,0xfe,0xde,0xce,
	0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x6c,0xc6,0xc6,0xc6,0xc6,
	0xc6,0xc6,0x6c,0x38,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfc,0x66,0x66,0x66,0x7c,0x60,
	0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,
	0xc6,0xd6,0xde,0x7c,0x0c,0x0e,0x00,0x00,
	0x00,0x00,0xfc,0x66,0x66,0x66,0x7c,0x6c,
	0x66,0x66,0x66,0xe6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7c,0xc6,0xc6,0x60,0x38,0x0c,
	0x06,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x7e,0x7e,0x5a,0x18,0x18,0x18,
	0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,
	0xc6,0x6c,0x38,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xc6,0xd6,
	0xd6,0xfe,0x6c,0x6c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xc6,0xc6,0x6c,0x6c,0x38,0x38,
	0x6c,0x6c,0xc6,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x66,0x66,0x66,0x66,0x3c,0x18,
	0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0xfe,0xc6,0x86,0x0c,0x18,0x30,
	0x60,0xc2,0xc6,0xfe,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x80,0xc0,0xe0,0x70,0x38,
	0x1c,0x0e,0x06,0x02,0x00,0x00,0x00,0x00,
	0x00,0x00,0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,
	0x0c,0x0c,0x0c,0x3c,0x00,0x00,0x00,0x00,
	0x10,0x38,0x6c,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,
	0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x78,0x0c,0x7c,
	0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
	0x00,0x00,0xe0,0x60,0x60,0x78,0x6c,0x66,
	0x66,0x66,0x66,0xdc,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xc0,
	0xc0,0xc0,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x1c,0x0c,0x0c,0x3c,0x6c,0xcc,
	0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xfe,
	0xc0,0xc0,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x6c,0x64,0x60,0xf0,0x60,
	0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x76,0xcc,0xcc,
	0xcc,0xcc,0xcc,0x7c,0x0c,0xcc,0x78,0x00,
	0x00,0x00,0xe0,0x60,0x60,0x6c,0x76,0x66,
	0x66,0x66,0x66,0xe6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x18,0x00,0x38,0x18,0x18,
	0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x06,0x06,0x00,0x0e,0x06,0x06,
	0x06,0x06,0x06,0x06,0x66,0x66,0x3c,0x00,
	0x00,0x00,0xe0,0x60,0x60,0x66,0x6c,0x78,
	0x78,0x6c,0x66,0xe6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x18,0x18,0x18,0x18,0x18,
	0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xec,0xfe,0xd6,
	0xd6,0xd6,0xd6,0xd6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xdc,0x66,0x66,
	0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xdc,0x66,0x66,
	0x66,0x66,0x66,0x7c,0x60,0x60,0xf0,0x00,
	0x00,0x00,0x00,0x00,0x00,0x76,0xcc,0xcc,
	0xcc,0xcc,0xcc,0x7c,0x0c,0x0c,0x1e,0x00,
	0x00,0x00,0x00,0x00,0x00,0xdc,0x76,0x62,
	0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0x60,
	0x38,0x0c,0xc6,0x7c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x10,0x30,0x30,0xfc,0x30,0x30,
	0x30,0x30,0x36,0x1c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xcc,0xcc,0xcc,
	0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,
	0x66,0x66,0x3c,0x18,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xc6,0xc6,0xc6,
	0xd6,0xd6,0xfe,0x6c,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xc6,0x6c,0x38,
	0x38,0x38,0x6c,0xc6,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xc6,0xc6,0xc6,
	0xc6,0xc6,0xc6,0x7e,0x06,0x0c,0xf8,0x00,
	0x00,0x00,0x00,0x00,0x00,0xfe,0xcc,0x18,
	0x30,0x60,0xc6,0xfe,0x00,0x00,0x00,0x00,
	0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,
	0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,
	0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
	0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe
};


void SubTitle::LoadHZK(void)
{
	PBYTE pBuf = NULL;
	DWORD nLen = 0;

	if (LoadHex(g_hInstance, IDR_HEX_HZK, &pBuf, nLen))
	{
		m_pHZK=pBuf;
		m_nHZKSize=nLen;
	}
}


/* YUV420ͼ��������Ļ
 * <����˵��>
 * pY:	yuv����
 * nStride:	�������ͬ
 * nWidth:	��
 * nHeight:		��
 * nSubTitle: 0:TOP_LEFT 1:BOTOM_LEFT,2:TOP_CENTER,3:BOTTOM_CENTER,4:TOP_RIGHT,5:BOTTOM_RIGHT
 * cszSubTitle:	��Ļ��Ϣ
 * invert: ��Ϊ0����
 */
void SubTitle::DrawTitle(unsigned char *pY,int nStride,int nWidth,int nHeight,int nSubTitle,const char*cszSubTitle)
{//4 1 2 1 2 1 2 1 2 1 2 = 19
// 16 = 16  nSubTitle
// 16*8 + 19*8 + 6 = 128 + 152 + 6 = 286

	if (m_pHZK==NULL)
	{
		LoadHZK();
		if (m_pHZK==NULL)
		{
			return ;
		}
	}

	int x,y;
	int ld = 1;
	int nSubTitleWidth = strlen(cszSubTitle);

	nSubTitleWidth = nSubTitleWidth*8;
	if (nSubTitleWidth>(nWidth-4))
	{
		nSubTitleWidth=(nWidth-4);
		nSubTitleWidth-=(nSubTitleWidth%8);
	}

	switch (nSubTitle)
	{
	case VIDEC_OSD_ALIGN_TOP_LEFT:
		{
			x = 2;
			y = 2;
		}
		break;
	case VIDEC_OSD_ALIGN_TOP_CENTER:
		{
			if(nWidth >= 286)
				x = (nWidth - nSubTitleWidth - 2)>>1;
			else
				x = (286 - nSubTitleWidth - 2)>>1;
			y = 2;
		}
		break;
	case VIDEC_OSD_ALIGN_TOP_RIGHT:
		{
			if(nWidth >= 286)
				x = nWidth - nSubTitleWidth - 2;
			else
				x = 286 - nSubTitleWidth - 2;
			y = 2;
		}
		break;
	case VIDEC_OSD_ALIGN_BOTTOM_CENTER:
		{
			if(nWidth >= 286)
				x = (nWidth - nSubTitleWidth - 2)>>1;
			else
				x = (286 - nSubTitleWidth - 2)>>1;
			y = nHeight-18;
		}
		break;
	case VIDEC_OSD_ALIGN_BOTTOM_RIGHT:
		{
			if(nWidth >= 286)
				x = nWidth - nSubTitleWidth - 2;
			else
				x = 286 - nSubTitleWidth - 2;
			y = nHeight-18;
		}
		break;
	case VIDEC_OSD_ALIGN_BOTOM_LEFT:
	default:
		{
			x = 2;
			y = nHeight-18;
		}
		break;
	}

	int h1;

	
	if(nWidth >= 286)
	{//����Ҫ����С����	
		unsigned char *p;		
		const unsigned char *pstr = (unsigned char*)cszSubTitle;
		int x1;
		int n = 0;
		
		{
			for(int y1 = y; y1 < y + 16;y1++)
			{				
				p = pY + y1*nStride + x;
				for(int i = 0; i < nSubTitleWidth+1; i++)
				{			
					*p = (*p >> 1) + 52;
					p++;		
				}		
			}
		}
		x1 = x;	
		while(x1 < x + nSubTitleWidth)
		{	
			if(*pstr & 0x80)
			{
				//n = *pstr * 32;				
				int i,j;
				i=pstr[0]-0xa0;j=pstr[1]-0xa0; /*���������λ��*/
				n = (94*(i-1)+(j-1))*32;
				if(m_pHZK == NULL || n < 0 || n >= m_nHZKSize)
				{
					pstr +=2;
					x1 += 16;
					continue;
				}
					
				for( i = 0; i < 16; i++)
				{
					p = pY + ((int)(y + i))*nStride + x1;				
					
					if(m_pHZK[n] & 0x080)
						*p = 255;
					
					p++;
				
					if(m_pHZK[n] & 0x040)
						*p = 255;
				
					p++;
					
					if(m_pHZK[n] & 0x020)
						*p = 255;
				
					p++;
					
					if(m_pHZK[n] & 0x010)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x08)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x04)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x02)
						*p = 255;
					
					p++;
				
					if(m_pHZK[n] & 0x01)
						*p = 255;
				
					p++;

					n++;

					if(m_pHZK[n] & 0x080)
						*p = 255;
					
					p++;
				
					if(m_pHZK[n] & 0x040)
						*p = 255;
				
					p++;
					
					if(m_pHZK[n] & 0x020)
						*p = 255;
				
					p++;
					
					if(m_pHZK[n] & 0x010)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x08)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x04)
						*p = 255;
				
					p++;
				
					if(m_pHZK[n] & 0x02)
						*p = 255;
					
					p++;
				
					if(m_pHZK[n] & 0x01)
						*p = 255;
				
					p++;

					n++;
				}
				x1+=16;
				pstr+=2;
			}
			else if(*pstr == '\0')
				break;
			else
			{
				n = *pstr * 16;

				for(int i = 0; i < 16; i++)
				{
					p = pY + (y + i)*nStride + x1;			

					if(Ascii[n] & 0x080)
						*p = 255;
					
					p++;
				
					if(Ascii[n] & 0x040)
						*p = 255;
				
					p++;
					
					if(Ascii[n] & 0x020)
						*p = 255;
				
					p++;
					
					if(Ascii[n] & 0x010)
						*p = 255;
				
					p++;
				
					if(Ascii[n] & 0x08)
						*p = 255;
				
					p++;
				
					if(Ascii[n] & 0x04)
						*p = 255;
				
					p++;
				
					if(Ascii[n] & 0x02)
						*p = 255;
					
					p++;
				
					if(Ascii[n] & 0x01)
						*p = 255;				
		
					n++;
				}
				x1+=8;
				pstr++;
			}
		}
	}
	else
	{
		float delta = nWidth/(float)286.0;
		unsigned char *p;
		float dx = 0;
		float xx = x*delta;
		float yy = y*delta;	
		const unsigned char *pstr = (unsigned char*)cszSubTitle;
		float x1;
		int n = 0;
		int ww = (int)(nSubTitleWidth*delta);
	
		h1 = (int)(16*delta);
		
		{
			for(int y1 = (int)yy; y1 < (int)yy + h1;y1++)
			{				
				p = pY + y1*nStride + (int)(xx);
				for(int i = 0; i < ww+1; i++)
				{			
					*p = (*p >> 1) + 52;
					p++;
				}		
			}
		}
		x1 = xx;
	
		while(x1 < xx + ww)
		{		
		
			if(*pstr & 0x80)
			{
				//n = *pstr * 32;				
				int i,j;
				i=pstr[0]-0xa0;j=pstr[1]-0xa0; /*���������λ��*/
				n = (94*(i-1)+(j-1))*32;
				if(m_pHZK == NULL || n < 0 || n >= m_nHZKSize)
				{
					pstr +=2;
					x1 += 16*delta;
					continue;
				}
					
				for( i = 0; i < 16; i++)
				{					
					p = pY + ((int)(yy + i*delta + 0.5))*nStride + (int)(x1+0.5);
					
					dx = 0;
					
					if(m_pHZK[n] & 0x080)
					{
						*p = 255;
						*(p+1) = 255;
						*(p+2) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x040)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(m_pHZK[n] & 0x020)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(m_pHZK[n] & 0x010)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x08)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x04)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x02)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x01)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;

					n++;

					if(m_pHZK[n] & 0x080)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x040)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(m_pHZK[n] & 0x020)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(m_pHZK[n] & 0x010)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x08)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x04)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x02)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(m_pHZK[n] & 0x01)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;

					n++;
				}
				x1+=16*delta;
				pstr+=2;
			}
			else if(*pstr == '\0')
				break;
			else
			{
				n = *pstr * 16;

				for(int i = 0; i < 16; i++)
				{
					p = pY + ((int)(yy + i*delta + 0.5))*nStride + (int)(x1+0.5);
					
					dx = 0;
					
					if(Ascii[n] & 0x080)
					{
						*p = 255;
					}
					dx+=delta;
				
					if(Ascii[n] & 0x040)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(Ascii[n] & 0x020)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
					
					if(Ascii[n] & 0x010)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(Ascii[n] & 0x08)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(Ascii[n] & 0x04)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(Ascii[n] & 0x02)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					dx+=delta;
				
					if(Ascii[n] & 0x01)
					{
						*(p + (int)(dx+0.4)) = 255;
					}
					n++;
				}
				x1+=8*delta;
				pstr++;
			}
		}
	}
}