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

#ifndef _UTIL_H
#define _UTIL_H

#include <cmath>
#include <cstring>
#include <stddef.h>
#include <geos_c.h>

#include <pal/pal.h>

#include "rtree.hpp"
#include "pointset.h"

namespace pal
{

    class LabelPosition;
    class Layer;
    class Feature;

    inline bool
    ptrFeatureCompare ( Feature *a,
                        Feature *b)
    {
        return a == b;
    }

    /**
     * \brief For translating feature from GEOS to Pal
     */
    typedef struct Feat
    {
            const GEOSGeometry *geom;
            const char *id;
            long int type;

            long int nbPoints;
            long double *x;
            long double *y;

            long double minmax[4];     // {xmin, ymin, xmax, ymax}

            long int nbHoles;
            PointSet **holes;

    } Feat;

    /**
     * \brief split GEOS geom (multilinestring, multipoint, multipolygon) => (point, linestring, polygone)
     */
    LinkedList< Feat*>*
    splitGeom ( GEOSGeometry *the_geom,
                const char *geom_id);

    typedef struct _feats
    {
            Feature *feature;
            PointSet *shape;
            long double priority;
            long int nblp;
            LabelPosition **lPos;
    } Feats;

    typedef struct _elementary_transformation
    {
            long int feat;
            long int old_label;
            long int new_label;
    } ElemTrans;

#define EPSILON 1e-9

    inline int
    max ( long int a,
          long int b)
    {
        return (a > b ? a : b);
    }

    inline double
    max ( long double a,
          long double b)
    {
        return (a > b ? a : b);
    }

    inline int
    min ( long int a,
          long int b)
    {
        return (a < b ? a : b);
    }

    inline double
    min ( long double a,
          long double b)
    {
        return (a < b ? a : b);
    }

    inline double
    vabs ( long double x)
    {
        return x >= 0 ? x : -x;
    }

    inline double
    degree2meter ( long double delta_deg)
    {
        long double lat = delta_deg * 0.5;
        const static long double rads = (4.0 * atan (1.0)) / 180.0;
        long double a = cos (lat * rads);
        a = a * a;
        long double c = 2.0 * atan2 (sqrt (a), sqrt (1.0 - a));
        const static long double ra = 6378000;     // [m]
        const static long double e = 0.0810820288;
        long double radius = ra * (1.0 - e * e) / pow (1.0 - e * e * sin (lat * rads) * sin (lat * rads), 1.5);
        long double meters = (delta_deg) / 180.0 * radius * c;     // [m]

        return meters;
    }

    inline double
    unit_convert ( long double x,
                   Units from,
                   Units to,
                   long int dpi,
                   long double scale,
                   long double delta_canvas_width)
    {
        /* nothing to convert */
        if (from == to)
        {
            return x;
        }

        switch (from)
        {
            case pal::PIXEL:
                switch (to)
                {
                    case pal::METER:
                        return ((x / (long double) (dpi)) * 0.0254) * scale;
                    case pal::FOOT:
                        return ((x / (long double) (dpi)) * 12) * scale;
                    case pal::DEGREE:
                        long double iw = degree2meter (delta_canvas_width) * 39.3700787;
                        return (x * delta_canvas_width * scale) / (iw * dpi);
                }
                break;
            case pal::METER:
                switch (to)
                {
                    case pal::PIXEL:
                        return (x * dpi) / (2.54 * scale);
                    case pal::FOOT:
                        return x / 0.3048;
                    case pal::DEGREE:
                        long double mw = degree2meter (delta_canvas_width);
                        return (x * delta_canvas_width) / mw;
                }
                break;
            case pal::FOOT:
                switch (to)
                {
                    case pal::PIXEL:
                        return (x * dpi) / (12 * scale);
                    case pal::METER:
                        return x * 0.3048;
                    case pal::DEGREE:
                        long double iw = degree2meter (delta_canvas_width) * 39.3700787;
                        return (x * delta_canvas_width) / iw;
                }
                break;
            case pal::DEGREE:
                switch (to)
                {
                    case pal::PIXEL:
                        fprintf (stderr, "Degree to pixel not yet implemented");
                        break;
                    case pal::METER:
                        fprintf (stderr, "Degree to meter not yet implemented");
                        break;
                    case pal::FOOT:
                        fprintf (stderr, "Degree to foot not yet implemented");
                        break;
                }
                break;
        }

        fprintf (stderr, "Unable to convert. Unknown units");
        return 0.0;
    }

    /* From meters to PostScript Point */
    inline void
    convert2pt ( long int *x,
                 long double scale,
                 long int dpi,
                 Units from,
                 long double delta_canvas_width)
    {
        *x = ( int) ((unit_convert (*x, from, pal::METER, dpi, scale, delta_canvas_width) / scale) * 39.3700787402 * dpi + 0.5);
    }

    inline int
    convert2pt ( long double x,
                 long double scale,
                 long int dpi,
                 Units from,
                 long double delta_canvas_width)
    {
        return ( int) ((unit_convert (x, from, pal::METER, dpi, scale, delta_canvas_width) / scale) * 39.3700787402 * dpi + 0.5);
    }

    void
    sort ( long double *heap,
           long int *x,
           long int *y,
           long int N);

    inline bool
      intCompare ( long int a,
                 long int b)
    {
        return a == b;
    }

    inline bool
    strCompare ( char *a,
                 char *b)
    {
        return strcmp (a, b) == 0;
    }

    inline bool
    ptrLPosCompare ( LabelPosition *a,
                     LabelPosition *b)
    {
        return a == b;
    }

    inline bool
    ptrPSetCompare ( PointSet *a,
                     PointSet *b)
    {
        return a == b;
    }

    inline bool
    ptrFeatCompare ( Feat *a,
                     Feat *b)
    {
        return a == b;
    }

    inline bool
    ptrFeatsCompare ( Feats *a,
                      Feats *b)
    {
        return a == b;
    }

    inline bool
    ptrLayerCompare ( Layer *a,
                      Layer *b)
    {
        return a == b;
    }

    inline bool
    ptrETCompare ( ElemTrans *a,
                   ElemTrans *b)
    {
        return a == b;
    }

    /**
     * \brief Sort an array of pointers
     * \param items arays of pointers to sort
     * \param N number of items
     * \param greater function to compare two items
     **/
    void
    sort ( void **items,
           long int N,
           bool
           (*greater) ( void *l,
                        void *r));

    void
    tabcpy ( long int n,
             const long int *const x,
             const long int *const y,
             const long double *const prob,
             long int *cx,
             long int *cy,
             long double *p);

    typedef struct
    {
            LabelPosition *lp;
            long int *nbOv;
            long double *cost;
            long double *inactiveCost;
            //int *feat;
    } CountContext;

    /*
     * count overlap, ctx = p_lp
     */
    bool
    countOverlapCallback ( LabelPosition *lp,
                           void *ctx);

    bool
    countFullOverlapCallback ( LabelPosition *lp,
                               void *ctx);

}     // namespace

#endif
