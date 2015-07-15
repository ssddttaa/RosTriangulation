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
  
  Vertex_Circulator vc = T->incident_vertices(T->infinite_vertex()), done(vc);
  int count = 0;
  do{
    //ROS_INFO("CURRENT POINT(%f, %f)", vc->point().x(), vc->point().y());
    vector<float> tempPointVec;
    tempPointVec.push_back(vc->point().x());
    tempPointVec.push_back(vc->point().y());
    
    bufferPointer->push_back(tempPointVec[0]);
    bufferPointer->push_back(tempPointVec[1]);
    
    count++;
  }
  while(++vc!=done);
  
  *totalVertices = count;
}