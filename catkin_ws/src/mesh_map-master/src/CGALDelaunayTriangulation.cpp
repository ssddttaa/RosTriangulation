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

void CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation_2 * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices)
{
  //CHECK TO SEE IF THE POINT TO ADD NEEDS TO BE EITHER MODIFIED OR ADDED
  //ROS_INFO("SIZE OF DELAUNAY VERTICES:%i", DelaunayTriangulationVertices->size());
  //ROS_INFO("SIZE OF VERTICES to be added:%i", PointsToBeInserted->size());
  vector<Point_2> PointVector;
  for(int i = 0;i<PointsToBeInserted->size();i++)
  {
      vector<float> currentPoint = PointsToBeInserted->at(i);
      Point_2 tempPoint = Point_2(currentPoint[1],currentPoint[2]);
      PointVector.push_back(tempPoint);
  }
  
  vector<Point_2>::iterator PointIteratorBegin = PointVector.begin();
  vector<Point_2>::iterator PointIteratorEnd = PointVector.end();
  T->insert(PointIteratorBegin, PointIteratorEnd);
  int count = 0;
  for(Edge_iterator ei = T->finite_edges_begin(); ei != T->finite_edges_end(); ++ei){
    ROS_INFO("starting to iterate through the edges");
	Triangulation_2::Face& f = *(ei->first);
	int i = ei->second;
	Vertex_handle vs = f.vertex(f.cw(i));
	Vertex_handle vt = f.vertex(f.ccw(i));
	Point_2 v1 = vs->point();
	Point_2 v2 = vt->point();
	
	
	bufferPointer->push_back(v1.x());
	bufferPointer->push_back(v1.y());
	
	bufferPointer->push_back(v2.x());
	bufferPointer->push_back(v2.y());
	
	ROS_INFO("POINTS PUSHING BACK:(%f, %f), (%f, %f)" , v1.x(), v1.y(), v2.x(), v2.y());
	
        count += 2;
    }
  
  *totalVertices = count;
}