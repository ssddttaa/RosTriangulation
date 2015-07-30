/*created by
*Giuseppe Loianno and Sadat Shaik*/

#ifndef __Tutorials__CGALDelaunayTriangulation__
#define __Tutorials__CGALDelaunayTriangulation__

#include "ros/ros.h"
#include <ros/console.h>
#include <stdio.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3_to_polyhedron_3.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/output_surface_facets_to_polyhedron.h>
#include <CGAL/property_map.h>
#include <utility>
#include <CGAL/Cartesian.h>
#include <CGAL/Scale_space_surface_reconstruction_3.h>
#include <CGAL/Scale_space_surface_reconstruction_3_impl.h>
#include <string>
#include <map>
#include <CGAL/array.h>

#include <algorithm>

#include <CGAL/Origin.h>
#include <CGAL/value_type_traits.h>

#include <boost/version.hpp>
#if BOOST_VERSION >= 104000
  #include <boost/property_map/property_map.hpp>
#else
    #include <boost/property_map.hpp>
#endif
#define CGAL_EIGEN3_ENABLED 1

using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;


typedef vector<Point_3> Point_collection;

typedef CGAL::Scale_space_surface_reconstruction_3< Kernel > Reconstruction;
typedef Reconstruction::Triple_const_iterator                   Triple_iterator;

class CGALDelaunay
{
    public:
        static void TriangulateUsingCGAL(vector<vector<float>> * PointsToBeInserted, vector<float> *bufferPointer, int*totalVertices);
	static Point_3 Transform_Vector_To_Point(vector<float> tempVec);
};

#endif