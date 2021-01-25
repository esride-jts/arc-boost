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

#include "arcboost.h"

#include "pygeometry.h"

#include <vector>

using namespace boost::geometry;
using namespace std;

/*!
* \brief Creates a new two dimensional point using x and y.
* \details This point instance can be used from Python.
*/
point2d point_from_xy(double x, double y)
{
	return point2d::from_xy(x, y);
}

/*!
* \brief Creates an array of two dimensional points using x and y.
* \details These point instances can be used from Python.
*/
vector<point2d> points_from_xy(const vector<double> &x, const vector<double> &y)
{
	if (x.size() != y.size())
	{
		vector<point2d> empty;
		empty.reserve(0);
		return empty;
	}

	vector<point2d> points;
	points.reserve(x.size());
	for (size_t index = 0, count = x.size(); index < count; index++)
	{
		points.push_back(point_from_xy(x.at(index), y.at(index)));
	}
	return points;
}

/*!
\brief Creates a new two dimensional point using the WKT representation.
\details This point instance can be used from Python.
*/
point2d point_from_wkt(const string &wkt)
{
	return point2d::from_wkt(wkt);
}

/*!
\brief Constructs the convex hull of two dimensional points represented as x and y coordinates.
The convex hull is returned as vector or tuples/pairs of x and y coordinates.
\details These tuple instances can be used from Python.
*/
vector<pybind11::tuple> convex_hull(const vector<double>& x, const vector<double>& y)
{
	polygon2d hull_polygon = geometry_engine::convex_hull(x, y);
	vector<pybind11::tuple> hull_tuple;
	hull_tuple.reserve(hull_polygon.point_count());
	for (const point2d &point : hull_polygon.points())
	{
		pybind11::tuple coordinate_tuple = pybind11::make_tuple(point.x(), point.y());
		hull_tuple.push_back(coordinate_tuple);
	}
	return hull_tuple;
}



PYBIND11_MODULE(arcboost, pymodule)
{
	pymodule.doc() = "arcboost is a C++/Python module offering various geospatial workflows.";

	pybind11::class_<point2d>(pymodule, "Two dimensional point")
		.def("x", &point2d::x)
		.def("y", &point2d::y);
	pybind11::class_<polygon2d>(pymodule, "Two dimensional polygon")
		.def("points", &polygon2d::points)
		.def("point_count", &polygon2d::point_count);
	pymodule.def("point_from_xy", &point_from_xy, "Creates a point using x and y.");
	pymodule.def("points_from_xy", &points_from_xy, "Creates an array of points using x and y.");
	pymodule.def("point_from_wkt", &point_from_wkt, "Creates a point from a WKT represenation.");
	pymodule.def("convex_hull", &convex_hull, "Constructs the convex hull of two dimensional points represented as x and y coordinates.");
}

int main()
{
	cout << "Hello arcboost." << endl;
	return 0;
}
