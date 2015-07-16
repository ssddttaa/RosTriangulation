#include "mesh_map/DelaunayTriangulate.h"
#include <ros/console.h>
#include "ros/ros.h"


DelaunayTriangulation::DelaunayTriangulation(vector<float> * triangulatedVertices)
{
    //temporary set of coordinates used to copy the default cube coordiantes into the cube_vertex_data and cube_color_data buffers

    numberOfTetrahedra = 0; //Used for the tetgen tetrahedralization

    currentViewScale = -5.0;
    
    totalVertices = 0;//Variable used for the tetegen library
    
    returnDelaunayVertices = triangulatedVertices;
}

//Add points to the triangulation dynamically. The code re-tetrahedralizes with the given points
void DelaunayTriangulation::addPointsToTriangulation(vector<vector<float> > * pointsToAdd, int numberOfPoints)
{
    //Calls the class that triangulates using the library CGAL
    //(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices)
  for(int i = 0 ;i<pointsToAdd->size();i++)
  {
   vector<float> currentPoint = pointsToAdd->at(i);
   currentPoint.push_back(i);
   pointsToAdd->at(i) = currentPoint;
  }
  CGALDelaunay::TriangulateUsingCGAL (&DelaunayVertices, pointsToAdd, &TriangulationOfPoints, &g_vertex_buffer_data, &g_color_buffer_data, &numberOfPoints);
  
  //CGALDelaunay::DelaunayTriangulateUsingCGAL(&inputtedVertices,pointsToAdd, &g_vertex_buffer_data, &g_color_buffer_data,&numberOfPoints,&VerticesToTriangulate, &VerticesToAdd,&numberOfPoints, &TriangulationOfPoints, &numVertices);
  //void CGALDelaunay::DelaunayTriangulateUsingCGAL(vector<vector<float> > *inputtedVertices, vector<vector<float> > *nodeArrayPointer, vector<float>* bufferPointer, vector<float> *colorPointer, int* numberOfVertices, std::list<Point> *VerticesToTriangulate, std::list<Point> * VerticesToAdd, int* verticesAlreadyAdded, Triangulation* T, int* totalVertices)
  *returnDelaunayVertices = g_vertex_buffer_data;
}

//Calls the different triangulation libraries. One calls the tetgen library, the other uses the CGAL library
/*void DelaunayTriangulation::triangulate(bool usingTetgen, vector<vector<float> >*nodeArray, bool pointsDynamicallyInserted, int nodeArraySize)
{
    if(usingTetgen)
    {
        //triangulateUsingTetgen(nodeArray);
    }
    else
    {
      
        for(int i = 0 ;i<nodeArray->size();i++)
	{
	   inputtedVertices.push_back(nodeArray->at(i));
	}
        triangulateUsingCGAL(nodeArray, pointsDynamicallyInserted, nodeArraySize, vector<bool> *isStaticPoint);
	*returnDelaunayVertices = g_vertex_buffer_data;
	
    }
}*/

//This function triangulates the points using the library CGAL
void DelaunayTriangulation::triangulateUsingCGAL(vector<vector<float> > *nodeArrayPointer, bool pointsDynamicallyInserted, int nodeArraySize)
{
    int VerticesAlreadyAdded(0);
    
    
    //(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices)
    CGALDelaunay::TriangulateUsingCGAL (&DelaunayVertices, nodeArrayPointer, &TriangulationOfPoints, &g_vertex_buffer_data, &g_color_buffer_data, &VerticesAlreadyAdded);
    *returnDelaunayVertices = g_vertex_buffer_data;
  
}