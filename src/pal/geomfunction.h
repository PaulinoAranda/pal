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

#ifndef _GEOM_FUNCTION_
#define _GEOM_FUNCTION_

#include "util.h"

namespace pal
{

    /*
     *           o(x2,y2)
     *          /
     * cp > 0  /
     *        /    cp < 0
     *       /
     *      /
     *     o (x1, y1)
     */
    inline double
    cross_product ( long double x1,
                    long double y1,
                    long double x2,
                    long double y2,
                    long double x3,
                    long double y3)
    {
        return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    }

    inline double
    dist_euc2d ( long double x1,
                 long double y1,
                 long double x2,
                 long double y2)
    {
        return sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    inline double
    dist_euc2d_sq ( long double x1,
                    long double y1,
                    long double x2,
                    long double y2)
    {
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }

    bool
    isPointInPolygon ( long int npol,
                       long double *xp,
                       long double *yp,
                       long double x,
                       long double y);
    /*
     // code from Randolph Franklin (found at http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/)
     long int i, j;
     bool c = false;

     for (i = 0, j = npol-1; i < npol; j = i++){
     if ((( (yp[i] <= y) && (y < yp[j])) ||
     ((yp[j] <= y) && (y < yp[i])))
     && (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i])){
     c = !c;
     }
     }
     return c;
     }*/

    inline int
    nbLabelPointInPolygon ( long int npol,
                            long double *xp,
                            long double *yp,
                            long double x[4],
                            long double y[4])
    {
        long int a, k, count = 0;
        long double px, py;

        // cheack each corner
        for ( k = 0; k < 4; k++)
        {
            px = x[k];
            py = y[k];

            for ( a = 0; a < 2; a++)
            {     // and each middle of segment
                if (isPointInPolygon (npol, xp, yp, px, py))
                    count++;
                px = (x[k] + x[(k + 1) % 4]) / 2.0;
                py = (y[k] + y[(k + 1) % 4]) / 2.0;
            }
        }

        px = (x[0] + x[2]) / 2.0;
        py = (y[0] + y[2]) / 2.0;

        // and the label center
        if (isPointInPolygon (npol, xp, yp, px, py))
            count += 4;     // virtually 4 points

        return count;
    }

     long int
    convexHull ( long int *id,
                 const long double *const x,
                 const long double *const y,
                 long int n);

     long int
    convexHullId ( long int *id,
                   const long double *const x,
                   const long double *const y,
                   long int n,
                   long int *&cHull);

    bool
    isSegIntersects ( long double x1,
                      long double y1,
                      long double x2,
                      long double y2,     // 1st segment
                      long double x3,
                      long double y3,
                      long double x4,
                      long double y4);     // 2nd segment

    bool
    computeSegIntersectionExt ( long double x1,
                                long double y1,
                                long double x2,
                                long double y2,
                                long double xs1,
                                long double ys1,     // 1st (segment)
                                long double x3,
                                long double y3,
                                long double x4,
                                long double y4,
                                long double xs2,
                                long double ys2,     // 2nd segment
                                long double *x,
                                long double *y);

    /*
     * \brief Intersection bw a line and a segment
     * \return true if the point exist false otherwise
     */
    bool
    computeLineSegIntersection ( long double x1,
                                 long double y1,
                                 long double x2,
                                 long double y2,     // 1st line
                                 long double x3,
                                 long double y3,
                                 long double x4,
                                 long double y4,     // 2nd segment
                                 long double *x,
                                 long double *y);

    /*
     * \brief compute the point wherre two segmentss intersects
     * \return true if the point exists
     */
    bool
    computeSegIntersection ( long double x1,
                             long double y1,
                             long double x2,
                             long double y2,     // 1st line (segment)
                             long double x3,
                             long double y3,
                             long double x4,
                             long double y4,     // 2nd line segment
                             long double *x,
                             long double *y);

    /*
     * \brief compute the point wherre two lines intersects
     * \return true if the ok false if line are parallel
     */
    bool
    computeLineIntersection ( long double x1,
                              long double y1,
                              long double x2,
                              long double y2,     // 1st line (segment)
                              long double x3,
                              long double y3,
                              long double x4,
                              long double y4,     // 2nd line segment
                              long double *x,
                              long double *y);

#ifdef _EXPORT_MAP_
    /**
     * \brief generate SVG code for a geometry
     *
     * @param nbPoints # points in x and y vector
     * @param typeID from geos
     * @param x x coordinates
     * @param y y coordinates
     * @param dpi map resolution
     * @param scale map scale is 1:scale
     * @param xmin minimum x value in mapExtent
     * @param ymax maximum y value in mapExtent
     * @param layername SVG layer name
     * @param objectID SVG ID
     * @param out stream to write
     */
    void toSVGPath (int nbPoints, long int geomType,
                    long double *x, long double *y,
                    long int dpi, long double scale, Units unit,
                    long int xmin, long int xmax, long int ymax,
                    char *layername,
                    char *objectID,
                    std::ostream &out);
#endif

     long int
    reorderPolygon ( long int nbPoints,
                     long double *x,
                     long double *y);

}     // end namespace

#endif
