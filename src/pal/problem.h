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

#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <list>
#include <pal/pal.h>
#include "rtree.hpp"

namespace pal
{

    class LabelPosition;
    class Label;

    class Sol
    {
        public:
            long int *s;
            long double cost;
    };

    typedef struct _subpart
    {
            /**
             * # of features in problem
             */
            long int probSize;

            /**
             * # of features bounding the problem
             */
            long int borderSize;

            /**
             *  total # features (prob + border)
             */
            long int subSize;

            /**
             * wrap bw sub feat and main feat
             */
            long int *sub;
            /**
             * sub solution
             */
            long int *sol;
            /**
             * first feat in sub part
             */
            long int seed;
    } SubPart;

    typedef struct _chain
    {
            long int degree;
            long double delta;
            long int *feat;
            long int *label;
    } Chain;

    /**
     * \brief Represent a problem
     */
    class Problem
    {

            friend class Pal;

        private:

            /**
             * How many layers are lebelled ?
             */
            long int nbLabelledLayers;

            /**
             * Names of the labelled layers
             */
            char **labelledLayersName;

            /**
             * # active candidates (remaining after reduce())
             */
            long int nblp;
            /**
             * # candidates (all, including)
             */
            long int all_nblp;

            /**
             * # feature to label
             */
            long int nbft;

            /**
             * if true, special value -1 is prohibited
             */
            bool displayAll;

            /**
             * Map extent (xmin, ymin, xmax, ymax)
             */
            long double bbox[4];

            /**
             * map scale is 1:scale
             */
            long double scale;

            long double *labelPositionCost;
            long int *nbOlap;

            LabelPosition **labelpositions;

            RTree< LabelPosition*, long  double, 2, long  double> *candidates;     // index all candidates
            RTree< LabelPosition*, long  double, 2, long  double> *candidates_sol;     // index active candidates
            RTree< LabelPosition*, long  double, 2, long  double> *candidates_subsol;     // idem for subparts

            //int *feat;        // [nblp]
            long int *featStartId;     // [nbft]
            long int *featNbLp;     // [nbft]
            long double *inactiveCost;     //

            Sol *sol;         // [nbft]
            long int nbActive;

            long int nbOverlap;

            long int *featWrap;

            Chain*
            chain ( SubPart *part,
                    long int seed);

            Chain*
            chain ( long int seed);

            Pal *pal;

            void
            solution_cost ();
            void
            check_solution ();

            Problem ();

            //Problem(char *lorena_file, bool displayAll);

            ~Problem ();

            void
            reduce ();

            void
            post_optimization ();

            /**
             * \brief popmusic framework
             */
            void
            popmusic ();

            /**
             * \brief Test with very-large scale neighborhood
             */
            void
            chain_search ();

            std::list< Label*>*
            getSolution ( bool returnInactive);

            PalStat*
            getStats ();

            /* usefull only for postscript post-conversion*/
            //void toFile(char *label_file);
            SubPart*
            subPart ( long int r,
                      long int featseed,
                      long int *isIn);

            void
            initialization ();

            long double
            compute_feature_cost ( SubPart *part,
                                   long int feat_id,
                                   long int label_id,
                                   long int *nbOverlap);
            long double
            compute_subsolution_cost ( SubPart *part,
                                       long int *s,
                                       long int *nbOverlap);

            long double
            popmusic_chain ( SubPart *part);

            long double
            popmusic_tabu ( SubPart *part);
            long double
            popmusic_tabu_chain ( SubPart *part);

            void
            init_sol_empty ();
            void
            init_sol_falp ();

#ifdef _EXPORT_MAP_
        void drawLabels (std::ofstream &svgmap);
#endif

    };

}     // namespace

#endif
