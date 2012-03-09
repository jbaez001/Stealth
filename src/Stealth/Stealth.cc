/* Stealth - Stealth.cc
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
#include "Stealth.h"
#include "Gen/Error.hpp"
#include "Gen/mIRC/Moo.hpp"
#include <memory>

/* Namespaces for the Genscripts and STL. */
using namespace Gen;
using namespace std;

/**
 * LoadDll. EntryPoint for any mIRC DLL.
 *
 * @param pInfo     Pointer to the structure that contains mIRC's version and such.
 */
void __stdcall LoadDll(LoadInfo *pInfo)
{
    /* We don't want mIRC to keep us loaded. After all, we are pure evil. */
    pInfo->mKeep = false;

    /* Initialize an instance of CGenMoo (so we have a bridge between our DLL and mIRC). */
    auto_ptr<CGenMoo>mIRC(new CGenMoo(pInfo->mHwnd, L"mIRC3"));

    /* Attempt to find the address that we should nullify based on the user's mIRC version */
    DWORD dwAddress = FindAddress(pInfo->mVersion);

    /* mIRC is either outdated, or this DLL is. */
    if (dwAddress == NULL) {
        mIRC->Cmd("/echo -a [Stealth] Your mIRC is not supported.");
    } else {
        char lptrBuffer[8] = "       ";

        if (!WriteAddress(GetCurrentProcessId(), (LPVOID)dwAddress, lptrBuffer)) {
            DWORD dwError = GetLastError();
            LPSTR lptrMsg = GetLastErrorMessage(dwError);
            mIRC->Cmd("/echo -a [Stealth] Error Code: %d, Message: %s", dwError, lptrMsg);
            LocalFree(lptrMsg);
        } else {
            mIRC->Cmd("/echo -a [Stealth] Your CTCP Version Reply has been rendered useless.");
        }
    }
}

/**
 * Stealth. Blank call to allow the user to call us via /dll Stealth.dll Stealth.
 */
int __stdcall Stealth(HWND mWnd, HWND aWnd, char *data, char *params, BOOL show, BOOL nopause)
{
    return 1;
}

/* EOF */
