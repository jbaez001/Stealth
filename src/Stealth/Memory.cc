/* Stealth - Memory.cc
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

/**
 * mIRC Version Table list. This took approximately 5 secs to find, 
 *  and another 5 seconds to calculate the offset for different mIRC versions.
 */
VersionTable TableList[] =
{
    { 0x00020006, 0x005A77DC }, // 6.2
    { 0x00150006, 0x0059C888 }, // 6.21
    { 0x001F0006, 0x005EDEE4 }, // 6.31
    { 0x00200006, 0x005F4FA8 }, // 6.32
    { 0x00210006, 0x005F7FA4 }, // 6.33
    { 0x00220006, 0x005F7FA4 }, // 6.34
    { 0x00230006, 0x005F7FA4 }, // 6.35 
    { 0 }
};

/**
 * FindAddress. Used to search the table above and return what we need from it.
 *
 * @param dwVersion     mIRC's version.
 *
 * @return NULL         If the mIRC version is not supported.
 * @return dwAddress    The address in memory that we should null out.
 */
DWORD FindAddress(DWORD dwVersion)
{
    for (int i = 0; TableList[i].dwVersion; i++) 
        if (TableList[i].dwVersion == dwVersion) 
            return TableList[i].dwAddress;

    return NULL;
}

/**
 * WriteAddress. Attempt to write to a process's memory.
 *  If for some reason it fails, we don't bother about what the error was. So instead,
 *  we attempt to change the process security and access rights so we can try again.
 *  If we fail after all that, then there is nothing we can do, or rather, there is 
 *  nothing that we want to do (because anything further than and that it's called rape ;0).
 *
 * @param dwPid         PID of the process that we are writing to.
 * @param dwAddress     Address that we are going to be writing to.
 * @param lpBuffer      Pointer to the buffer that contains the data that we are writing.
 *
 * @return false        If we have failed.
 * @return true         All green.
 */
BOOL WriteAddress(DWORD dwPid, LPVOID dwAddress, LPVOID lpBuffer)
{
    HANDLE m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPid);

    if (!m_hProcess)
        return false;

    BOOL  bReturn = true;

    if (!::WriteProcessMemory(m_hProcess, dwAddress, lpBuffer, sizeof(lpBuffer), NULL)) {
        DWORD dwOldProtect = 0;
        if (VirtualProtect(dwAddress, sizeof(lpBuffer), PAGE_WRITECOPY, &dwOldProtect)) {
            bReturn = ::WriteProcessMemory(m_hProcess, dwAddress, lpBuffer, sizeof(lpBuffer), NULL);
            VirtualProtect(dwAddress, sizeof(lpBuffer), dwOldProtect, &dwOldProtect);
        }
    }

    CloseHandle(m_hProcess);

    return bReturn;
}

/* EOF */

