/* Genscripts Library - Moo.hpp
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
#ifndef __MOO_HPP__
#   define __MOO_HPP__

#pragma message("Genscripts Library: Compiling Moo.hpp")

#include "Gen/mIRC/Map.hpp"

namespace Gen {
    class CGenMoo : public CGenMap
    {
    private:
        HWND m_MoohWnd;
        LPWSTR m_MapName;

    public:
        CGenMoo(HWND m_hWnd, LPWSTR m_Name)
            : m_MoohWnd(m_hWnd), m_MapName(m_Name)
        {
            SetMooHandle(m_hWnd);
            OpenMap(m_MapName);
        }
        ~CGenMoo()
        {
        }
    };
}

#endif /* __GENMOO_HPP__ */

/* EOF */

