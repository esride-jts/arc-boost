// arcboost is a C++/Python module for geospatial workflows.
// Copyright (C) 2021 Esri Deutschland GmbH
// Jan Tschada (j.tschada@esri.de)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Additional permission under GNU LGPL version 3 section 4 and 5
// If you modify this Program, or any covered work, by linking or combining
// it with ArcGIS (or a modified version of these libraries),
// containing parts covered by the terms of ArcGIS libraries,
// the licensors of this Program grant you additional permission to convey the resulting work.
// See <https://developers.arcgis.com/> for further information.
//

#ifndef PYGEOMETRY_H
#define PYGEOMETRY_H

#include <boost/geometry.hpp>
#include <vector>

typedef boost::geometry::model::d2::point_xy<double> point_2d;
typedef boost::geometry::model::polygon<point_2d> polygon_2d;
typedef boost::geometry::model::multi_point<point_2d> multipoint_2d;


struct point2d {

	/*!
	\brief Creates a new two dimensional point using x and y.
	*/
	point2d static from_xy(double x, double y);

	/*!
	* \brief Creats a new two dimensional point using the WKT representation.
	*/
	point2d static from_wkt(const std::string& wkt);
	
	double x() const;
	double y() const;

private:
	point2d(point_2d point);

	point_2d _point;
};



struct polygon2d {

	/*!
	\brief Creates a new two dimensional polygon using x and y coordinates.
	*/
	polygon2d static from_xy(const std::vector<double>& x, const std::vector<double>& y);

	/*!
	\brief Creates an empty two dimensional polygon.
	*/
	polygon2d static empty();

	const std::vector<point2d>& points() const;
	size_t point_count() const;

private:
	polygon2d(std::vector<point2d> &&points);

	std::vector<point2d> _points;

	friend class geometry_engine;
};



class geometry_engine {

public:
	/*!
	\brief Constructs the convex hull of two dimensional points represented as x and y coordinates.
	*/
	static polygon2d convex_hull(const std::vector<double>& x, const std::vector<double>& y);
};

#endif