//
//  CGALDelaunayTriangulation.h
//  Tutorials
//
//  Created by Sadat Shaik on 6/23/15.

#ifndef __Tutorials__CGALDelaunayTriangulation__
#define __Tutorials__CGALDelaunayTriangulation__
#include <stdio.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3_to_polyhedron_3.h>
#include <CGAL/Point_2.h>
#include <iostream>
#include <fstream>
#include <cassert>
#include <list>
#include <vector>
#include "BufferActions.h"
#include <ros/console.h>
#include "ros/ros.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_3<K>      Triangulation;
typedef CGAL::Delaunay_triangulation_2<K>      Delaunay_2;
typedef CGAL::Triangulation_2<K>               Triangulation_2;
typedef CGAL::Point_2<K>		       Point_2;
typedef Triangulation::Cell_handle    	       Cell_handle;
typedef Triangulation::Vertex_handle 	       Vertex_handle;
typedef Triangulation::Locate_type   	       Locate_type;
typedef Triangulation::Point          	       Point;
typedef CGAL::Polyhedron_3<K>	     	       Polyhedron_3;
typedef Triangulation_2::Vertex_circulator     Vertex_Circulator;
typedef Polyhedron_3::Halfedge_around_facet_circulator HF_circulator;

typedef CGAL::Triangulation_3<CGAL::Epick, CGAL::Default> Triangulation_3;

using namespace std;

class CGALDelaunay
{
    public:
        static void TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation_2 * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);
	static void DelaunayTriangulateUsingCGAL(vector<vector<float> > *inputtedVertices, vector<vector<float> > *nodeArrayPointer, vector<float>* bufferPointer, vector<float> *colorPointer, int* numberOfVertices, std::list<Point> *VerticesToTriangulate, std::list<Point> * VerticesToAdd, int* verticesAlreadyAdded, Triangulation_2* T, int* totalVertices);
  
};

#endif