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

#include "pygeometry.h"

#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::geometry;
using namespace std;

point2d::point2d(point_2d point) : _point(point)
{}

point2d point2d::from_xy(double x, double y)
{
	return point2d(point_2d(x, y));
}

point2d point2d::from_wkt(const string& wkt)
{
	point_2d point;
	read_wkt(wkt, point);
	return point2d(point);
}

double point2d::x() const
{
	return _point.x();
}

double point2d::y() const
{
	return _point.y();
}




polygon2d::polygon2d(vector<point2d>&& points) : _points(std::move(points))
{}

polygon2d polygon2d::from_xy(const vector<double>& x, const vector<double>& y)
{
	if (x.size() != y.size())
	{
		vector<point2d> empty;
		empty.reserve(0);
		return polygon2d(move(empty));
	}

	vector<point2d> points;
	points.reserve(x.size());
	for (size_t index = 0, count = x.size(); index < count; index++)
	{
		points.push_back(point2d::from_xy(x.at(index), y.at(index)));
	}
	return polygon2d(move(points));
}

const vector<point2d>& polygon2d::points() const
{
	return _points;
}

size_t polygon2d::point_count() const
{
	return _points.size();
}