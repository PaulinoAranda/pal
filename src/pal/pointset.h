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

#ifndef _POINTSET_H
#define _POINTSET_H

#include <cfloat>

#include <cmath>
#include <stddef.h>
#include <geos_c.h>

#include "rtree.hpp"
#include "linkedlist.hpp"

namespace pal
{

    class Pal;
    class Feat;
    class Feature;
    class Projection;
    class LabelPosition;

    typedef struct _cross
    {
            long int pt;
            long double d;
            long double x;
            long double y;
            long int seg;        // seg{0,1,2,3}
            long int nextCorner;     // pt{0,1,2,3}
            long int way;

    } Crossing;

    class PointSet;

    typedef struct _cHullBox
    {
            long double x[4];
            long double y[4];

            long double alpha;

            long double width;
            long double length;
    } CHullBox;

    inline bool
    ptrCrossingCompare ( Crossing *a,
                         Crossing *b)
    {
        return a == b;
    }

    inline bool
    crossingDist ( void *a,
                   void *b)
    {
        return (( Crossing*) a)->d > (( Crossing*) b)->d;
    }

    class PointSet
    {
            friend class Feature;
            friend class Pal;
            friend class Layer;
            friend class LabelPosition;
            friend class PolygonCostCalculator;
            friend class Problem;
            friend bool
            pruneLabelPositionCallback ( LabelPosition *lp,
                                         void *ctx);
            //friend Feat *splitButterflyPolygon (Feat *f, long int pt_a, long int pt_b, long double cx, long double cy);
            friend bool
            obstacleCallback ( PointSet *feat,
                               void *ctx);
            friend bool
            extractFeatCallback ( Feature*,
                                  void*);
            friend void
            extractXYCoord ( Feat *f);
            friend LinkedList< Feat*>*
            splitGeom ( GEOSGeometry *the_geom,
                        const char *geom_id);
            friend void
            releaseAllInIndex ( RTree< PointSet*, long  double, 2, long  double> *obstacles);
            friend bool
            releaseCallback ( PointSet *pset,
                              void *ctx);
            friend bool
            filteringCallback ( PointSet*,
                                void*);
        protected:
            long int nbPoints;
            long double *x;
            long double *y;     // points order is counterclockwise

            long int *status;     // -1 means inside the bbox, +1 means outside and 0 is either in either out
            long int *cHull;
            long int cHullSize;

            long int type;

            //PointSet *parent;

            PointSet *holeOf;
            PointSet *parent;

//public:
            long double xmin;
            long double xmax;
            long double ymin;
            long double ymax;

            long int
            getPath ( long int start,
                      long int stop,
                      long int *path_val);

            PointSet*
            extractPath ( long int path,
                          long int nbPtPath,
                          long int nbBboxPt,
                          long double bbx[4],
                          long double bby[4],
                          Crossing *start,
                          Crossing *stop,
                          long int startPt);

            PointSet*
            extractShape ( long int nbPtSh,
                           long int imin,
                           long int imax,
                           long int fps,
                           long int fpe,
                           long double fptx,
                           long double fpty);

            PointSet*
            createProblemSpecificPointSet ( long double bbx[4],
                                            long double bby[4],
                                            bool *outside,
                                            bool *inside);

            CHullBox*
            compute_chull_bbox ();

            /*
             *  \brief Take each line in shape_toProcess and only keep inside bbox line parts
             */
            static void
            reduceLine ( PointSet *line,
                         LinkedList< PointSet*> *shapes_final,
                         long double bbx[4],
                         long double bby[4]);

            /**
             * \brief takes shapes from shapes_toProcess, compute intersection with bbox
             * and puts new shapes into shapes_final
             */
            static void
            reducePolygon ( PointSet *shape_toProcess,
                            LinkedList< PointSet*> *shapes_final,
                            long double bbx[4],
                            long double bby[4]);

            /*
             * split a concave shape into several convex shapes
             *
             */
            static void
            splitPolygons ( LinkedList< PointSet*> *shapes_toProcess,
                            LinkedList< PointSet*> *shapes_final,
                            long double xrm,
                            long double yrm,
                            char *uid);

            /*
             * Iterate on line by real step of dl on x,y points
             * @param nbPoint # point in line
             * @param x x coord
             * @param y y coord
             * @param d ??
             * @param ad distance from pt0 to each point (ad0 = pt0->pt0)
             * @param dl ??
             * @param px current x coord on line
             * @param py current y coord on line
             */
            inline void
            getPoint ( long double *d,
                       long double *ad,
                       long double dl,
                       long double *px,
                       long double *py)
            {
                long int i;
                long double dx, dy, di;
                long double distr;

                i = 0;
                if (dl >= 0)
                {
                    while (i < nbPoints && ad[i] <= dl)
                        i++;
                    i--;
                }

                if (i < nbPoints - 1)
                {
                    if (dl < 0)
                    {
                        dx = x[nbPoints - 1] - x[0];
                        dy = y[nbPoints - 1] - y[0];
                        di = sqrt (dx * dx + dy * dy);
                    }
                    else
                    {
                        dx = x[i + 1] - x[i];
                        dy = y[i + 1] - y[i];
                        di = d[i];
                    }

                    distr = dl - ad[i];
                    *px = x[i] + dx * distr / di;
                    *py = y[i] + dy * distr / di;
                }
                else
                {     // just select last point...
                    *px = x[i];
                    *py = y[i];
                }
            }

        public:
            long double
            getXmin ()
            {
                return xmin;
            }

            long double
            getXmax ()
            {
                return xmax;
            }

            long double
            getYmin ()
            {
                return ymin;
            }

            long double
            getYmax ()
            {
                return ymax;
            }

            inline long int
            getType ()
            {
                return type;
            }

            inline long double*
            getX ()
            {
                return x;
            }

            inline long double*
            getY ()
            {
                return y;
            }

            inline long int
            getNbPoints ()
            {
                return nbPoints;
            }

            /**
             * \brief return the minimum distance bw this and the point (px,py)
             *
             * compute the minimum distance bw the point (px,py) and this.
             * Optionnaly, store the nearest point in (rx,ry) 
             *
             * @param px x coordinate of the point
             * @param py y coordinate of the points
             * @param rx pointer to x coorinates of the nearest point (can be NULL)
             * @param ry pointer to y coorinates of the nearest point (can be NULL)
             */
            long double
            getDist ( long double px,
                      long double py,
                      long double *rx,
                      long double *ry);

            //double getDistInside(double px, long double py);

            void
            getCentroid ( long double &px,
                          long double &py);

            PointSet ( long double x,
                       long double y);

            PointSet ( PointSet &ps);

            PointSet ();
            PointSet ( long int nbPoints,
                       long double *x,
                       long double *y);
            ~PointSet ();
    };

}     // namespace pal

#endif

