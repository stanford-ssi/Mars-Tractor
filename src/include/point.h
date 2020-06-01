/*
 * File: point.h
 * -------------
 * This file exports a class representing an integer-valued x-y pair.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _point_h
#define _point_h

#include <string>

/*
 * Class: Point
 * ------------
 * This class represents an x-y coordinate point on a two-dimensional
 * integer grid.  If you need to work with real-valued points, you should
 * use the gtypes.h interface instead.
 */

class Point {

public:

/*
 * Constructor: Point
 * Usage: Point origin;
 *        Point pt(x, y);
 * ----------------------
 * Creates a Point object with the specified x and y coordinates.  If the
 * coordinates are not supplied, the default constructor sets these fields
 * to 0.
 */

   Point();
   Point(int x, int y);

/*
 * Method: getX
 * Usage: int x = pt.getX();
 * -------------------------
 * Returns the x-coordinate of the point.
 */

   int getX() const;

/*
 * Method: getY
 * Usage: int y = pt.getY();
 * -------------------------
 * Returns the y-coordinate of the point.
 */

   int getY() const;

/*
 * Method: toString
 * Usage: string str = pt.toString();
 * ----------------------------------
 * Returns a string representation of the Point in the form "(x, y)".
 */

   std::string toString() const;

/*
 * Friend operator: ==
 * Usage: if (p1 == p2) ...
 * ------------------------
 * Returns true if p1 and p2 are the same point.
 */

   bool operator==(const Point & p2) const;

/*
 * Friend operator: !=
 * Usage: if (p1 != p2) ...
 * ------------------------
 * Returns true if p1 and p2 are different.
 */

   bool operator!=(const Point & p2) const;

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

/* Instance variables */

   int x;                         /* The x-coordinate of the point */
   int y;                         /* The y-coordinate of the point */

};

/*
 * Operator: <<
 * Usage: cout << pt;
 * ------------------
 * Overloads the << operator so that it is able to display Point values.
 */

std::ostream & operator<<(std::ostream & os, const Point & pt);

#endif