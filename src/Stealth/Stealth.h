/* Stealth - Stealth.h
 * Copyright (C) 2009 Stealth Authors
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef __STEALTH_H__
#   define __STEALTH_H__

#ifdef __INTEL_COMPILER
#   pragma warning( disable : 869  )
#   pragma warning( disable : 1418 )
#elif _MSC_VER
#   pragma warning( disable : 4100 )
#   pragma warning( disable : 4706 )
#   pragma warning( disable : 4995 )
#endif

/**
 * Specify that the minimum platform be Windows Server 2003, Windows XP.
 * This is because the size of the PROCESS_ALL_ACCESS flag is increased in modern
 * Windows operating systems. In order words, stone age operating systems (Windows XP, Server 2003)
 * returned an ERROR_ACCESS_DENIED when we attempted to change the process rights.
 *
 * See http://msdn.microsoft.com/en-us/library/ms684880(VS.85).aspx for more info "PROCESS_ALL_ACCESS"
 */
#define _WIN32_WINNT _WIN32_WINNT_WINXP 

/* Exclude all the extra crap from Windows.h that is rarely used. */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

/**
 * VersionTable. Structure that contains mIRC versions, so we know what we have to do.
 */
typedef struct {
    DWORD dwVersion;
    DWORD dwAddress;
} VersionTable;

/**
 * Defined in Memory.cc
 */
extern DWORD FindAddress(DWORD dwVersion);
extern BOOL WriteAddress(DWORD dwPid, LPVOID dwAddress, LPVOID lpBuffer);
extern VersionTable TableList[];

#endif /* __STEALTH_H__ */

/* EOF */

