/*created by
*Giuseppe Loianno and Sadat Shaik*/


/*#include <iostream>
#include <fstream>
#include <typeinfo>
#include <CGAL/trace.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
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
#include <vector>
#include <fstream>

using Eigen::MatrixXd;*/
#include "mesh_map/CGALDelaunayTriangulation.h"
#define CGAL_EIGEN3_ENABLED

#include <CGAL/Eigen_solver_traits.h>
#include <CGAL/trace.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
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
#include <CGAL/Triangulation_3.h>
#include <vector>
#include <fstream>
#include <map>
#include <boost/property_map/property_map.hpp>
#include <ros/console.h>
#include "ros/ros.h"
// Types

//   CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);
void CGALDelaunay::TriangulateUsingCGAL(vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, int*totalVertices)
{    
  FT sm_angle = 20.0; // Min triangle angle in degrees.
    FT sm_radius = 30; // Max triangle size w.r.t. point set average spacing.
    FT sm_distance = 0.375; // Surface Approximation error w.r.t. point set average spacing.
    // Reads the point set file in points[].
    // Note: read_xyz_points_and_normals() requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    PointList points;
    std::ifstream stream("/home/mrsl_student/git/catkin_ws/src/mesh_map/src/data/kitten.xyz");
    if (!stream ||
        !CGAL::read_xyz_points_and_normals(
                              stream,
                              std::back_inserter(points),
                              CGAL::make_normal_of_point_with_normal_pmap(points.begin())))
    {
      ROS_INFO("kitten not loading");
    }
    ROS_INFO("yooo kitten loaded");
    // Creates implicit function from the read points using the default solver.
    // Note: this method requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    ROS_INFO("aight, aight poisson reconstructed");
    vector<Point_Vector_Pair> Point_With_Normal_List;
    map<Point, Vector> Point_Vector_Map;
    
    for(int i = 0;i<points.size();i++)
    {
      Point tempPoint(points.at(i).position());
      Vector tempVec(points.at(i).normal());
      Point_With_Normal_List.push_back(make_pair(tempPoint,tempVec));
    }
    
    Poisson_reconstruction_function function(Point_With_Normal_List.begin(), Point_With_Normal_List.end(),CGAL::First_of_pair_property_map<Point_Vector_Pair>(),CGAL::Second_of_pair_property_map<Point_Vector_Pair>());
    ROS_INFO("aight, aight poisson reconstructed");
    for(int i = 0;i<points.size();i++)
    {
      Point_with_normal tempPWN;
      Point tempPoint;
      tempPWN = points.at(i);
      tempPoint = tempPWN.position();
      Vector tempVec(tempPWN.normal());
      if(i<=10)
      {
     ROS_INFO("POINT: (%f, %f, %f), with normal (%f, %f, %f)", tempPoint.x(), tempPoint.y(), tempPoint.z(), tempVec.x(), tempVec.y(), tempVec.z());
    
      }	
    }
    
    
    // Computes the Poisson indicator function f()
    // at each vertex of the triangulation.
    //if ( ! function.compute_implicit_function() ) 
      //ROS_INFO("yo not computing implicit function");
    // Computes average spacing
    FT average_spacing = CGAL::compute_average_spacing(points.begin(), points.end(),
                                                       6 /* knn = 1 ring */);
    ROS_INFO("calculating average spascing");
    // Gets one point inside the implicit surface
    // and computes implicit function bounding sphere radius.
    Point inner_point = function.get_inner_point();
    ROS_INFO("inner point: (%f, %f, %f)", inner_point.x(), inner_point.y(),inner_point.z());
    Sphere bsphere = function.bounding_sphere();
    FT radius = std::sqrt(bsphere.squared_radius());
    // Defines the implicit surface: requires defining a
    // conservative bounding sphere centered at inner point.
    FT sm_sphere_radius = 5.0 * radius;
    FT sm_dichotomy_error = sm_distance*average_spacing/1000.0; // Dichotomy error must be << sm_distance
    Surface_3 surface(function,
                      Sphere(inner_point,sm_sphere_radius*sm_sphere_radius),
                      sm_dichotomy_error/sm_sphere_radius);
    ROS_INFO("created the surface man");
    // Defines surface mesh generation criteria
    CGAL::Surface_mesh_default_criteria_3<STr> criteria(sm_angle,  // Min triangle angle (degrees)
                                                        sm_radius*average_spacing,  // Max triangle size
                                                        sm_distance*average_spacing); // Approximation error
    ROS_INFO("surface mesh default criteria");
    // Generates surface mesh with manifold option
    STr tr; // 3D Delaunay triangulation for surface mesh generation
    C2t3 c2t3(tr); // 2D complex in 3D Delaunay triangulation
    ROS_INFO("created the 2d compex in 3d delaunay triangulatoin");
    
    
    CGAL::make_surface_mesh(c2t3,                                 // reconstructed mesh
                            surface,                              // implicit surface
                            criteria,                             // meshing criteria
                            CGAL::Manifold_with_boundary_tag());  // require manifold mesh
    
    
    ROS_INFO("created the surface mesh");
    if(tr.number_of_vertices() == 0)
      ROS_INFO("not enough vertices yo");
    // saves reconstructed surface mesh
    Polyhedron output_mesh;
    CGAL::output_surface_facets_to_polyhedron(c2t3, output_mesh);
    int count = 0;
    int vec3Order[] = {0,1,2};
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
    ROS_INFO("DONE TRIANGULATION AND NOW STARTING TO OUPUT IT");
    for( Polyhedron_3::Facet_iterator fit = output_mesh.facets_begin(); fit != output_mesh.facets_end(); ++fit)
    {
        vector<Point> currentFacet;
        HF_circulator h = fit->facet_begin();
        vector<vector<float> > TriangleVec;
        do
        {
            Point currentPoint = h->vertex()->point();
            vector<float> tempVec;
            tempVec.push_back(currentPoint.x());
            tempVec.push_back(currentPoint.y());
            tempVec.push_back(currentPoint.z());
	    ROS_INFO("pushing back point:(%f, %f, %f)", tempVec[0], tempVec[1], tempVec[2]);
            TriangleVec.push_back(tempVec);
        }
        while(++h != fit->facet_begin());
        BufferActions::addVec3ToBuffer(vec3Order, bufferPointer, &TriangleVec, 3);
        count += 3;
    }
}