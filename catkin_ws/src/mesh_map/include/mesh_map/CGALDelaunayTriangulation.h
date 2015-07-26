/*created by
*Giuseppe Loianno and Sadat Shaik*/

#ifndef __Tutorials__CGALDelaunayTriangulation__
#define __Tutorials__CGALDelaunayTriangulation__

#include <stdio.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3_to_polyhedron_3.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include <vector>
#include "BufferActions.h"
#include <ros/console.h>
#include "ros/ros.h"
#include <Eigen/Dense>

#include <CGAL/trace.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/output_surface_facets_to_polyhedron.h>
#include <CGAL/Poisson_reconstruction_function.h>
#include <CGAL/Point_with_normal_3.h>
#include <CGAL/property_map.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/compute_average_spacing.h>
#include <CGAL/pca_estimate_normals.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/property_map.h>
#include <utility>
#include <CGAL/Cartesian.h>

#include <algorithm>

#include <CGAL/Origin.h>
#include <CGAL/value_type_traits.h>

#include <boost/version.hpp>
#if BOOST_VERSION >= 104000
  #include <boost/property_map/property_map.hpp>
#else
    #include <boost/property_map.hpp>
#endif

/*
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
*/
//typedef CGAL::Delaunay_triangulation_3<Kernel>      Triangulation;
/*
typedef Triangulation::Cell_handle    Cell_handle;
typedef Triangulation::Vertex_handle  Vertex_handle;
typedef Triangulation::Locate_type    Locate_type;
typedef Polyhedron_3::Vertex_iterator Vertex_iterator;
//typedef Triangulation::Point Point;

typedef CGAL::Triangulation_3<CGAL::Epick, CGAL::Default> Triangulation_3;

typedef Kernel::FT FT;
typedef Kernel::Point_3 Point;
typedef CGAL::Point_with_normal_3<Kernel> Point_with_normal;
typedef Kernel::Sphere_3 Sphere;
typedef CGAL::Poisson_reconstruction_function<Kernel> Poisson_reconstruction_function;
typedef CGAL::Surface_mesh_default_triangulation_3 STr;
typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
typedef CGAL::Implicit_surface_3<Kernel, Poisson_reconstruction_function> Surface_3;


typedef std::vector<Point_with_normal> PointList;
*/

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef CGAL::Delaunay_triangulation_3<Kernel>      Triangulation;
typedef Triangulation::Vertex_handle  Vertex_handle;
typedef Kernel::Point_3 Point;
typedef Kernel::Vector_3 Vector;
typedef CGAL::Point_with_normal_3<Kernel> Point_with_normal;
typedef Kernel::Sphere_3 Sphere;
typedef std::vector<Point_with_normal> PointList;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef CGAL::Poisson_reconstruction_function<Kernel> Poisson_reconstruction_function;
typedef CGAL::Surface_mesh_default_triangulation_3 STr;
typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
typedef CGAL::Implicit_surface_3<Kernel, Poisson_reconstruction_function> Surface_3;
typedef CGAL::Delaunay_triangulation_3<Kernel>      Triangulation;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron_3;
typedef Polyhedron_3::Halfedge_around_facet_circulator HF_circulator;

typedef pair<Point, Vector> Point_Vector_Pair;














template <class Gt>
struct Point_Pmap: public boost::put_get_helper<typename Gt::Point_3&, Point_Pmap<Gt> >
{
  typedef Vector value_type;
  typedef value_type& reference;
  template <class Iter>
  reference operator[](Iter it) const { return (reference) it->point(); }
};

class CGALDelaunay
{
    public:
        static void TriangulateUsingCGAL(vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, int*totalVertices);
	static Point Transform_Vector_To_Point(vector<float> tempVec);
};

#endif