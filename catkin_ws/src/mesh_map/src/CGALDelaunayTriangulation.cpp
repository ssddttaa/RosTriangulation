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
    
    /*for(int i = 0;i<bufferPointer->size()/3;i++)
    {
      ROS_INFO("DELAUNAY VERTEX: (%f, %f, %f)", bufferPointer->at(i*3),bufferPointer->at((i*3)+1), bufferPointer->at((i*3)+2));
    }*/
    *totalVertices= count;
}