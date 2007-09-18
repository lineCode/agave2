/*******************************************************************************
 *
 *  Copyright (c) 2007 Jonathon Jongsma
 *
 *  This file is part of Agave
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>
 *
 *******************************************************************************/
#include "scheme-manager.h"

namespace agave
{
    SchemeManager* SchemeManager::s_instance = 0;

    // scheme functions
    // ANALOGOUS COLOR SCHEME
    static Color analogous_outer_left (const Color& c)
    {
        hsv_t shift = {-0.2, 0.0, 0.0, 0.0};
        return Color (c.as_hsv () + shift);
    }

    static Color analogous_inner_left (const Color& c)
    {
        hsv_t shift = {-0.1, 0.0, 0.0, 0.0};
        return Color (c.as_hsv () + shift);
    }

    static Color analogous_inner_right (const Color& c)
    {
        hsv_t shift = {0.1, 0.0, 0.0, 0.0};
        return Color (c.as_hsv () + shift);
    }

    static Color analogous_outer_right (const Color& c)
    {
        hsv_t shift = {0.2, 0.0, 0.0, 0.0};
        return Color (c.as_hsv () + shift);
    }

    // MONOCHROMATIC COLOR SCHEME
    static Color monochromatic_outer_left (const Color& c)
    {
        hsv_t shift = {0.0, 0.0, 0.0, 0.0};
        if (c.get_saturation () < 0.40)
        {
            shift.s = 0.30;
        }
        else
        {
            shift.s = -0.30;
        }
        return Color (c.as_hsv () + shift);
    }

    static Color monochromatic_inner_left (const Color& c)
    {
        hsv_t shift = {0.0, 0.0, 0.0, 0.0};
        if (c.get_value () > 0.70)
        {
            shift.v = -0.50;
        }
        else if (c.get_value () > 0.40)
        {
            shift.v = 0.30;
        }
        else
        {
            shift.v = 0.30;
        }
        return Color (c.as_hsv () + shift);
    }

    static Color monochromatic_inner_right (const Color& c)
    {
        hsv_t shift = {0.0, 0.0, 0.0, 0.0};
        if (c.get_saturation () < 0.40)
        {
            shift.s = 0.30;
        }
        else
        {
            shift.s = -0.30;
        }
        if (c.get_value () > 0.70)
        {
            shift.v = -0.50;
        }
        else if (c.get_value () > 0.40)
        {
            shift.v = 0.30;
        }
        else
        {
            shift.v = 0.30;
        }
        return Color (c.as_hsv () + shift);
    }

    static Color monochromatic_outer_right (const Color& c)
    {
        hsv_t shift = {0.0, 0.0, 0.0, 0.0};
        if (c.get_value () > 0.70)
        {
            shift.v = -0.20;
        }
        else if (c.get_value () > 0.40)
        {
            shift.v = -0.20;
        }
        else
        {
            shift.v = 0.60;
        }
        return Color (c.as_hsv () + shift);
    }


    // NOTE: this is not thread-safe, don't use in multi-threaded apps
    SchemeManager& SchemeManager::instance ()
    {
        if (!s_instance)
        {
            s_instance = new SchemeManager ();
        }
        return *s_instance;
    }

    SchemeManager::SchemeManager ()
    {
        // get and cache the list of available schemes
        Scheme analogous ("Analogous",
                analogous_outer_left,
                analogous_inner_left,
                analogous_inner_right,
                analogous_outer_right);
        m_schemes.push_back (analogous);

        Scheme monochromatic ("Monochromatic",
                monochromatic_outer_left,
                monochromatic_inner_left,
                monochromatic_inner_right,
                monochromatic_outer_right);
        m_schemes.push_back (monochromatic);

        // theoretically this could now load user-defined schemes somewhere
        // (either as defined to-be-defined text format or as compiled plugins),
        // but that hasn't been implemented
    }

    SchemeManager::~SchemeManager ()
    {
    }

    const std::vector<Scheme>& SchemeManager::get_schemes ()
    {
        return m_schemes;
    }
}
