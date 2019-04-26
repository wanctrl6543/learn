// Copyright (C) 2003 TightVNC Development Team. All Rights Reserved.
//
//  TightVNC is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
// TightVNC homepage on the Web: http://www.tightvnc.com/

// HotKeys.cpp: implementation of the HotKeys class.

#include "stdhdrs_client.h"
#include "vncviewer.h"
#include "HotKeys.h"

HotKeys::HotKeys()
{
	m_hwnd = 0;

	const int MAX_ACCELS = 16;
	ACCEL accel[MAX_ACCELS];
	int i = 0;

	accel[i].fVirt = FVIRTKEY | FALT | FCONTROL | FSHIFT | FNOINVERT;
	accel[i].key = 0x46;	// "F"
	accel[i++].cmd = ID_FULLSCREEN;


	int numKeys = i;
	assert(numKeys <= MAX_ACCELS);

	m_hAccel = CreateAcceleratorTable((LPACCEL)accel, numKeys);
}

bool HotKeys::TranslateAccel(MSG *pmsg)
{
	return (TranslateAccelerator(m_hwnd, m_hAccel, pmsg) != 0);
}

HotKeys::~HotKeys()
{
	DestroyAcceleratorTable(m_hAccel);
}
