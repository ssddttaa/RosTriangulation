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
//#include <CGAL/Point_with_normal_3.h>
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
    FT sm_angle = 10.0; // Min triangle angle in degrees.
    FT sm_radius = 1; // Max triangle size w.r.t. point set average spacing.
    FT sm_distance = 0.1; // Surface Approximation error w.r.t. point set average spacing.
    // Reads the point set file in points[].
    // Note: read_xyz_points_and_normals() requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    PointList points;
    vector<Point_Vector_Pair> InsertPWN; //PWN = point with normal
    for(int i = 0 ;i<PointsToBeInserted->size();i++)
    {
        vector<float> tempVec = PointsToBeInserted->at(i);
        InsertPWN.push_back(make_pair(Point(tempVec.at(0),tempVec.at(1),tempVec.at(2)),Vector(0.0,0.0,0.0)));
    }
    
        const unsigned int nb_neighbors = 18; // K-nearest neighbors = 3 rings
    CGAL::pca_estimate_normals(InsertPWN.begin(), InsertPWN.end(),
                               CGAL::First_of_pair_property_map<Point_Vector_Pair>(),
                               CGAL::Second_of_pair_property_map<Point_Vector_Pair>(),
                               nb_neighbors);
    // Orients normals.
    // Note: mst_orient_normals() requires an iterator over points
    // as well as property maps to access each point's position and normal.
    std::vector<Point_Vector_Pair>::const_iterator unoriented_points_begin =
        CGAL::mst_orient_normals(InsertPWN.begin(), InsertPWN.end(),
                                 CGAL::First_of_pair_property_map<Point_Vector_Pair>(),
                                 CGAL::Second_of_pair_property_map<Point_Vector_Pair>(),
                                 nb_neighbors);
    
    for(unoriented_points_begin = InsertPWN.begin(); unoriented_points_begin != InsertPWN.end();++unoriented_points_begin)
    {
        Point tempPoint = unoriented_points_begin->first;
        Vector tempVec = unoriented_points_begin->second;
        //typedef std::vector<Point_with_normal> PointList;
        points.push_back(Point_with_normal(tempPoint,tempVec));
        
    }
    // Creates implicit function from the read points using the default solver.
    // Note: this method requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    ROS_INFO("BEFORE computing the posison reocntsruction function");
    Poisson_reconstruction_function function(points.begin(), points.end(),CGAL::make_normal_of_point_with_normal_pmap(PointList::value_type()) );
    // Computes the Poisson indicator function f()
    // at each vertex of the triangulation.
    ROS_INFO("BEFORE computing the implicity function");
    if ( ! function.compute_implicit_function() ) 
        ROS_INFO("could not ocmpute implicity function");
    // Computes average spacing
    ROS_INFO("before computing average spacing");
    FT average_spacing = CGAL::compute_average_spacing(points.begin(), points.end(),nb_neighbors);
    // Gets one point inside the implicit surface
    // and computes implicit function bounding sphere radius.
    ROS_INFO("before getting inner point");
    Point inner_point = function.get_inner_point();
    ROS_INFO("before creating the sphere");
    Sphere bsphere = function.bounding_sphere();
    FT radius = std::sqrt(bsphere.squared_radius());
    // Defines the implicit surface: requires defining a
    // conservative bounding sphere centered at inner point.
    FT sm_sphere_radius = 5.0 * radius;
    FT sm_dichotomy_error = sm_distance*average_spacing/1000.0; // Dichotomy error must be << sm_distance
    ROS_INFO("BEFORE creating the surface");
    Surface_3 surface(function,
                      Sphere(inner_point,sm_sphere_radius*sm_sphere_radius),
                      sm_dichotomy_error/sm_sphere_radius);
    // Defines surface mesh generation criteria
    ROS_INFO("BEFORE mesh critera");
    CGAL::Surface_mesh_default_criteria_3<STr> criteria(sm_angle,  // Min triangle angle (degrees)
                                                        sm_radius*average_spacing,  // Max triangle size
                                                        sm_distance*average_spacing); // Approximation error
    // Generates surface mesh with manifold option
    STr tr; // 3D Delaunay triangulation for surface mesh generation
    C2t3 c2t3(tr); // 2D complex in 3D Delaunay triangulation
    ROS_INFO("Before making the surface mesh");
    CGAL::make_surface_mesh(c2t3,                                 // reconstructed mesh
                            surface,                              // implicit surface
                            criteria,                             // meshing criteria
                            CGAL::Manifold_with_boundary_tag());  // require manifold mesh
    ROS_INFO("after making the surface mesh");
    if(tr.number_of_vertices() == 0)
        ROS_INFO("FAILURE, NOT ENOUGH VERTICES");
    // saves reconstructed surface mesh
    std::ofstream out("./kitten_poisson-20-30-0.375.off");
    Polyhedron output_mesh;
    CGAL::output_surface_facets_to_polyhedron(c2t3, output_mesh);
    out<<output_mesh;

    //CONVERT DELAUNAY TRIANGULATION TO CONVEX HULL
    int count = 0;
    int vec3Order[] = {0,1,2};
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
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
            TriangleVec.push_back(tempVec);
        }
        while(++h != fit->facet_begin());
        BufferActions::addVec3ToBuffer(vec3Order, bufferPointer, &TriangleVec, 3);
        count += 3;
    }
    *totalVertices= count;
}


