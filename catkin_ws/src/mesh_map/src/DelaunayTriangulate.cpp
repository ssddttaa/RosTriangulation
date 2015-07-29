/*created by
*Giuseppe Loianno and Sadat Shaik*/
#include "mesh_map/DelaunayTriangulate.h"
#include <ros/console.h>
#include "ros/ros.h"
DelaunayTriangulation::DelaunayTriangulation(vector<geometry_msgs::Point> *triangulatedVertices)
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
    CGALDelaunay::TriangulateUsingCGAL (pointsToAdd, &g_vertex_buffer_data, &numberOfPoints);
    int numTriangles = g_vertex_buffer_data.size()/3;
    vector<geometry_msgs::Point> Point_Array;
    for(int i = 0;i<numTriangles;i++)
    {
        geometry_msgs::Point Temp_Point;
        Temp_Point.x = g_vertex_buffer_data.at((i*3));
        Temp_Point.y = g_vertex_buffer_data.at((i*3)+1);
        Temp_Point.z = g_vertex_buffer_data.at((i*3)+2);
        Point_Array.push_back(Temp_Point);
    }
    
    *returnDelaunayVertices = Point_Array;
}
//This function triangulates the points using the library CGAL
/*void DelaunayTriangulation::triangulateUsingCGAL(vector<vector<float> > *nodeArrayPointer, bool pointsDynamicallyInserted, int nodeArraySize)
{
    int VerticesAlreadyAdded(0);
    CGALDelaunay::TriangulateUsingCGAL (nodeArrayPointer, &g_vertex_buffer_data, &VerticesAlreadyAdded);
    *returnDelaunayVertices = g_vertex_buffer_data;
}*/