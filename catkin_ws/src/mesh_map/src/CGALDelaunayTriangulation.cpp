/*created by
*Giuseppe Loianno and Sadat Shaik*/
#include <iostream>
#include <typeinfo>
#include "mesh_map/CGALDelaunayTriangulation.h"
//   CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);
void CGALDelaunay::TriangulateUsingCGAL(vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, int*totalVertices)
{
    //CHECK TO SEE IF THE POINT TO ADD NEEDS TO BE EITHER MODIFIED OR ADDED
    //ROS_INFO("SIZE OF DELAUNAY VERTICES:%i", DelaunayTriangulationVertices->size());
    //ROS_INFO("SIZE OF VERTICES to be added:%i", PointsToBeInserted->size());
    for(unsigned int i = 0;i<PointsToBeInserted->size();i++)
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
    for( Polyhedron_3::Facet_iterator fit = chull.facets_begin(); fit != chull.facets_end(); ++fit)
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