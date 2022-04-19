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

#ifndef _PRIORITYQUEUE_H
#define _PRIORITYQUEUE_H

#include <iostream>

#define LEFT(x) (2*x+1)
#define RIGHT(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

namespace pal
{

    class PriorityQueue
    {
        private:
            long int size;
            long int maxsize;
            long int maxId;
            long int *heap;
            long double *p;
            long int *pos;

            bool
            (*greater) ( long double l,
                         long double r);

        public:
            /** \brief Create a priority queue of max size n
             * \@param n max size of the queuet
             * \@param p external vector representing the priority
             * \@param min best element has the smalest p when min is True ans has the biggest when min is false
             */
            PriorityQueue ( long int n,
                            long int maxId,
                            bool min);
            ~PriorityQueue ();

            void
            print ();

            long int
            getSize ();
            long int
            getSizeByPos ();

            bool
            isIn ( long int key);

            long int
            getBest ();     // O(log n)

            void
            remove ( long int key);
            void
            insert ( long int key,
                     long double p);

            void
            sort ();     // O(n log n)

            void
            downheap ( long int id);
            void
            upheap ( long int key);

            void
            decreaseKey ( long int key);
            void
            setPriority ( long int key,
                          long double new_p);

            long int
            getId ( long int key);
    };

}     // namespace

#endif
