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
#include <CGAL/array.h>
// Types

//  CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);
void CGALDelaunay::TriangulateUsingCGAL(vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, int*totalVertices)

{
    
    Reconstruction reconstruct( 10, 100 );
    // Add the points.
    vector<Point> PointsToAdd;
    for(int i = 0;i<PointsToBeInserted->size();i++)
    {
        vector<float> tempVec = PointsToBeInserted->at(i);
        PointsToAdd.push_back(Point(tempVec.at(0),tempVec.at(1),tempVec.at(2)));
    }
    reconstruct.insert( PointsToAdd.begin(), PointsToAdd.end() );
    // Advance the scale-space several steps.
    // This automatically estimates the scale-space.
    reconstruct.increase_scale( 2 );
    // Reconstruct the surface from the current scale-space.
    reconstruct.reconstruct_surface();
    // Write the reconstruction.
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
    int count = 0;
    
    for( std::size_t shell = 0; shell < reconstruct.number_of_shells(); ++shell ) {
        std::cerr << "Shell " << shell << std::endl;
        for( Triple_iterator it = reconstruct.shell_begin( shell ); it != reconstruct.shell_end( shell ); ++it )
        {
            std::array<unsigned int, 3> current_triangle = *it;
            for(int i = 0;i< 3;i++)
            {
                Point tempPoint = PointsToAdd.at(current_triangle[i]);
                bufferPointer->push_back(tempPoint.x());
                bufferPointer->push_back(tempPoint.y());
                bufferPointer->push_back(tempPoint.z());
                count+=3;
            }
        }
    }

}
