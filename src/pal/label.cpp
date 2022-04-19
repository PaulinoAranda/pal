/*
 *   libpal - Automated Placement of Labels Library     http://pal.heig-vd.ch
 *
 *
 *   Copyright (C) 2007, 2008 MIS-TIC, HEIG-VD (University of Applied Sciences Western Switzerland)
 *   Copyright (C) 2008, 2009 IICT-SYSIN, HEIG-VD (University of Applied Sciences Western Switzerland)
 *
 *
 * This file is part of libpal.
 *
 * libpal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libpal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libpal. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define _CRT_SECURE_NO_DEPRECATE

#include <cstring>

#include <pal/label.h>
#include <pal/palgeometry.h>

namespace pal
{

    Label::Label ( long double x[4],
                   long double y[4],
                   long double alpha,
                   const char *ftid,
                   const char *lyrName,
                   PalGeometry *userGeom,
                   long double alphaPAu) :
            alphaPAu (alphaPAu), a (alpha), userGeom (userGeom)
    {

        for ( long int i = 0; i < 4; i++)
        {
            this->x[i] = x[i];
            this->y[i] = y[i];
        }

        featureId = new char[strlen (ftid) + 1];
        strcpy (featureId, ftid);

        this->lyrName = new char[strlen (lyrName) + 1];
        strcpy (this->lyrName, lyrName);
    }

    Label::~Label ()
    {
        delete[] featureId;
        delete[] lyrName;
    }

     long double
    Label::getOrigX ()
    {
        return x[0];
    }

     long double
    Label::getOrigY ()
    {
        return y[0];
    }

     long double
    Label::getX ( size_t i)
    {
        return (i < 4 ? x[i] : -1);
    }

     long double
    Label::getY ( size_t i)
    {
        return (i < 4 ? y[i] : -1);
    }

    PalGeometry*
    Label::getGeometry ()
    {
        return userGeom;
    }

     long double
    Label::getRotation ()
    {
        return a;
    }

     long double
    Label::getAlphaPAu ()
    {
        return alphaPAu;
    }

    const char*
    Label::getLayerName ()
    {
        return lyrName;
    }

    const char*
    Label::getFeatureId ()
    {
        return featureId;
    }

}     // end namespace

