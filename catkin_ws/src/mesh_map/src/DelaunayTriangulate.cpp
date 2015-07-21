/*created by
*Giuseppe Loianno and Sadat Shaik*/
#include "mesh_map/DelaunayTriangulate.h"
#include <ros/console.h>
#include "ros/ros.h"
DelaunayTriangulation::DelaunayTriangulation(vector<float> * triangulatedVertices)
{
    returnDelaunayVertices = triangulatedVertices;
}
//Add points to the triangulation dynamically. The code re-tetrahedralizes with the given points
void DelaunayTriangulation::addPointsToTriangulation(vector<vector<float> > * pointsToAdd, int numberOfPoints)
{
    //Calls the class that triangulates using the library CGAL
    for(unsigned int i = 0 ;i<pointsToAdd->size();i++)
    {
        vector<float> currentPoint = pointsToAdd->at(i);
        currentPoint.push_back(i);
        pointsToAdd->at(i) = currentPoint;
    }
    CGALDelaunay::TriangulateUsingCGAL (pointsToAdd, &TriangulationOfPoints, &g_vertex_buffer_data, &numberOfPoints);
    *returnDelaunayVertices = g_vertex_buffer_data;
}
//This function triangulates the points using the library CGAL
void DelaunayTriangulation::triangulateUsingCGAL(vector<vector<float> > *nodeArrayPointer, bool pointsDynamicallyInserted, int nodeArraySize)
{
    int VerticesAlreadyAdded(0);
    CGALDelaunay::TriangulateUsingCGAL (nodeArrayPointer, &TriangulationOfPoints, &g_vertex_buffer_data, &VerticesAlreadyAdded);
    *returnDelaunayVertices = g_vertex_buffer_data;
}