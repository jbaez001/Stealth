/* Genscripts Library - Map.hpp
 * Copyright (C) 2009  Genscripts
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
#ifndef __MAP_HPP__
#   define __MAP_HPP__

#pragma message("Genscripts Library: Compiling Map.hpp")

#include <stdarg.h>

namespace Gen {
   /**
    * LOADINFO. Structure used by mIRC when loading a DLL.
    */
    typedef struct {
        DWORD   mVersion;
        HWND    mHwnd;
        BOOL    mKeep;
    } LoadInfo;

    /**
     * CGenMap. Classed used for Mapping mIRC.
     */
    class CGenMap
    {
    private:
        HANDLE m_Map;           /* Handle to mIRC's Map. */
        LPSTR m_Data;           /* Handle to a file shared with mIRC's Map. */
        HWND m_MoohWnd;         /* Handle to mIRC's Window Handle */

        /**
         * SendMooData. Sends mIRC a command or evaulation.
         *
         * @param bEvaluate.    Should the command be valuated?
         */
        inline int SendMooData(BOOL bEvaluate)
        {
            return SendMessage(m_MoohWnd, WM_USER + (bEvaluate ? 201 : 200), 1, 3);
        }

    public:

        /**
         * Class Constructor.
         */
        CGenMap()
        {
            m_Data = NULL;
        }

        /**
         * Class Destructor. Closes all maps.
         */
        virtual ~CGenMap()
        {
            CloseMapView();
            CloseMap();
        }

        /**
         * SetMooHandle. Sets the mIRC Window handle.
         */
        void SetMooHandle(HWND m_hWnd)
        {
            m_MoohWnd = m_hWnd;
        }

        /**
         * OpenMap. Opens a map with mIRC using the specified map name.
         *
         * @param lpName        Name of file mapping object.
         *
         * @return true         If the map was created.
         * @return false        If we could not map.
         */
        BOOL OpenMap(LPCWSTR lpName)
        {
            if ((m_Map = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096, lpName)))
                return true;

            return false;
        }

        /**
         * CloseMap. Closes a map with mIRC.
         *
         * @return true         If the map was closed.
         * @return false        If we could not close it.
         */
        BOOL CloseMap()
        {
            if (m_Map && CloseHandle(m_Map))
                return true;

            return false;
        }

        /**
         * OpenMapView. Maps a view of the current file map with mIRC.
         *
         * @return m_Data       Starting address of the mapped view.
         */
        LPSTR OpenMapView()
        {
            m_Data = (LPSTR) MapViewOfFile(m_Map, 
                FILE_MAP_ALL_ACCESS, 0, 0, 0);

            return m_Data;
        }

        /**
         * CloseMapView. Closes a view of the current file map with mIRC.
         *
         * @return true     If the view was unmapped.
         * @return false    If it was not.
         */
        BOOL CloseMapView()
        {
            return UnmapViewOfFile(m_Data);
        }

        /**
         * Cmd. Sends mIRC a command.
         */
        int Cmd(const char *fmt, ...)
        {
            char sBuffer[1024];

            memset(sBuffer, 0, sizeof(sBuffer));
            OpenMapView();

            va_list vl;

            va_start(vl, fmt);
            vsnprintf(sBuffer, sizeof(sBuffer) - 1, fmt, vl);
            sprintf(m_Data, "%s", sBuffer);
            int iReturn = SendMooData(false);
            CloseMapView();

            va_end(vl);

            return iReturn;
            
        }
        /**
         * Eval. Sends mIRC an "evaluation" command.
         */
        int Eval(char *ReturnBuff, int BuffSize, const char *fmt, ...)
        {
            char sBuffer[1024];

            memset(sBuffer, 0, sizeof(sBuffer));
            OpenMapView();

            va_list vl;

            va_start(vl, fmt);
            vsnprintf(sBuffer, sizeof(sBuffer) - 1, fmt, vl);
            sprintf(m_Data, "%s", sBuffer);

            ZeroMemory(ReturnBuff, BuffSize);

            int iReturn = 0;

            if ((iReturn = SendMooData(true)) == 1)
                sprintf(ReturnBuff, "%s", m_Data);
            else
                *ReturnBuff = '\0';

            CloseMapView();

            va_end(vl);

            return iReturn;
        }
    };
}
#endif /* __GENMAP_HPP__*/

/* EOF */

