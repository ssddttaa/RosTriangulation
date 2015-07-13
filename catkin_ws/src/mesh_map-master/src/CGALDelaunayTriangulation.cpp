//
//  CGALDelaunayTriangulation.cpp
//  Tutorials
//
//  Created by Sadat Shaik on 6/23/15.
//
//
#include <iostream>
#include <typeinfo>
#include "mesh_map/CGALDelaunayTriangulation.h"

//   CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);

void CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices)
{
  //CHECK TO SEE IF THE POINT TO ADD NEEDS TO BE EITHER MODIFIED OR ADDED
  //ROS_INFO("SIZE OF DELAUNAY VERTICES:%i", DelaunayTriangulationVertices->size());
  //ROS_INFO("SIZE OF VERTICES to be added:%i", PointsToBeInserted->size());
  
  
  for(int i = 0;i<PointsToBeInserted->size();i++)
  {
      vector<float> currentPoint = PointsToBeInserted->at(i);
      T->insert(Point(currentPoint[0],currentPoint[1], currentPoint[2]));
  }
  
  
  //CONVERT DELAUNAY TRIANGULATION TO CONVEX HULL
  Polyhedron_3 chull;
  CGAL::convex_hull_3_to_polyhedron_3(*T, chull);
  
  int count = 0;
    
    int vec3Order[] = {0,1,2};
    
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
    *colorPointer = emptyVector;
    for( Polyhedron_3::Facet_iterator fit = chull.facets_begin(); fit != chull.facets_end(); ++fit){
        vector<Point> currentFacet;
	HF_circulator h = fit->facet_begin();
	size_t order = 0;
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
        BufferActions::addVec3ToBuffer(vec3Order, colorPointer, &TriangleVec, 3);
        
        count += 3;
    }
    *totalVertices= count;
}


//UNCOMMENT TO IMPLEMENT 3D DELAUANY TRIANGULATION INSTEAD OF JUST THE CONVEX HULL
/*

void CGALDelaunay::DelaunayTriangulateUsingCGAL(vector<vector<float> > *inputtedVertices, vector<vector<float> > *nodeArrayPointer, vector<float>* bufferPointer, vector<float> *colorPointer, int* numberOfVertices, std::list<Point> *VerticesToTriangulate, std::list<Point> * VerticesToAdd, int* verticesAlreadyAdded, Triangulation* T, int* totalVertices)
{
for(int i = 0;i<inputtedVertices->size();i++)
    {
      vector<float> currentInputVertex = inputtedVertices->at(i);
      bool foundSameID = false;
      for(int j = 0;j<nodeArrayPointer->size();j++)
      {
	vector<float> currentNodeVertex = nodeArrayPointer->at(j);
	//ROS_INFO("CURRENT NODE VERTEX 1:%f, CURRENT NODE VERTEX 2:%f", currentInputVertex[3], currentNodeVertex[3]);
	if(((int)(currentInputVertex[3])) == ((int)currentNodeVertex[3]))
	{
	  foundSameID = true;
	    //MODIFY THE POINT IN THE TRIANGULATION
	    nodeArrayPointer[j] = inputtedVertices[j];
	   break;
	}
      }
      if(!foundSameID)
      {
	//ADD THE VERTEX INTO THE TRIANGULATION
      }
    }
    bool isFirstTriangulation = false;
    // construction from a list of points :
    if(inputtedVertices->size()== 0)
    {
        isFirstTriangulation = true;
        for(int i = 0;i<*numberOfVertices;i++)
        {
            vector<float> tempVec;
            tempVec = nodeArrayPointer->at(i);
            VerticesToTriangulate->push_front(Point(tempVec[0],tempVec[1],tempVec[2]));
        }
        Triangulation TempTriangulation(VerticesToTriangulate->begin(), VerticesToTriangulate->end());
        *T = TempTriangulation;
    }
    else
    {
        for(int i = 0;i<*numberOfVertices;i++)
        {
            vector<float> tempVec;
            tempVec = nodeArrayPointer->at(i);
            T->insert(Point(tempVec[0], tempVec[1], tempVec[2]));
        }
    }

    
    
    int count = 0;
    
    int vec3Order[] = {0,1,2};
    
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
    *colorPointer = emptyVector;
    for( Triangulation::Finite_facets_iterator fit = T->finite_facets_begin(); fit != T->finite_facets_end(); ++fit){
        K::Triangle_3 triangle = T->triangle(*fit);
        
        Point vertex = triangle.vertex(0);
        
        vector<float> tempVec1;
        tempVec1.push_back(vertex.x());
        tempVec1.push_back(vertex.y());
        tempVec1.push_back(vertex.z());
        
        vertex = triangle.vertex(1);
        vector<float> tempVec2;
        tempVec2.push_back(vertex.x());
        tempVec2.push_back(vertex.y());
        tempVec2.push_back(vertex.z());
        
        vertex = triangle.vertex(2);
        vector<float> tempVec3;
        tempVec3.push_back(vertex.x());
        tempVec3.push_back(vertex.y());
        tempVec3.push_back(vertex.z());
        
        vector<vector<float> > TriangleVec;
        TriangleVec.push_back(tempVec1);
        TriangleVec.push_back(tempVec2);
        TriangleVec.push_back(tempVec3);
        
        
        BufferActions::addVec3ToBuffer(vec3Order, bufferPointer, &TriangleVec, 3);
        BufferActions::addVec3ToBuffer(vec3Order, colorPointer, &TriangleVec, 3);
        
        count += 3;
    }
    *totalVertices= count;
}
*/