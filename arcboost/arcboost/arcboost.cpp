﻿// arcboost is a C++/Python module for geospatial workflows.
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
#include "arcboost.h"

using namespace boost::geometry;
using namespace std;

point2d point_from_wkt(const string &wkt)
{
	return point2d::from_wkt(wkt);
}


PYBIND11_MODULE(arcboost, pymodule)
{
	pymodule.doc() = "arcboost is a C++/Python module offering various geospatial workflows.";

	pybind11::class_<point2d>(pymodule, "Two dimensional point")
		.def("x", &point2d::x)
		.def("y", &point2d::y);
	pymodule.def("point_from_wkt", &point_from_wkt, "Creates a point from a WKT represenation.");
}

int main()
{
	cout << "Hello arcboost." << endl;
	return 0;
}
