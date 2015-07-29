/*created by
*Giuseppe Loianno and Sadat Shaik*/

#include "mesh_map/CGALDelaunayTriangulation.h"
// Types

//  CGALDelaunay::TriangulateUsingCGAL(vector<Vertex_handle> * DelaunayTriangulationVertices, vector<vector<float> > * PointsToBeInserted, Triangulation * T, vector<float> *bufferPointer, vector<float> *colorPointer, int*totalVertices);
void CGALDelaunay::TriangulateUsingCGAL(vector<vector<float> > * PointsToBeInserted, vector<float> *bufferPointer, int*totalVertices)
{
    Reconstruction reconstruct(10,100);
    ros::Time current_time = ros::Time::now();
    // Add the points.
    vector<Point_3> PointsToAdd;
    for(int i = 0;i<PointsToBeInserted->size();i++)
    {
        vector<float> tempVec = PointsToBeInserted->at(i);
        PointsToAdd.push_back(Point_3(tempVec.at(0),tempVec.at(1),tempVec.at(2)));
    }
    reconstruct.insert( PointsToAdd.begin(), PointsToAdd.end() );
    // Advance the scale-space several steps.   
    // This automatically estimates the scale-space.
    //reconstruct.increase_scale( 10);
    // Reconstruct the surface from the current scale-space.
    reconstruct.reconstruct_surface();
    // Write the reconstruction.
    vector<float> emptyVector;
    *bufferPointer = emptyVector;
    int count = 0;
    for( std::size_t shell = 0; shell < reconstruct.number_of_shells(); ++shell ) {
        for( Triple_iterator it = reconstruct.shell_begin( shell ); it != reconstruct.shell_end( shell ); ++it )
        {
            std::array<unsigned int, 3> current_triangle = *it;
            for(int i = 0;i< 3;i++)
            {
                Point_3 tempPoint = PointsToAdd.at(current_triangle[i]);
                bufferPointer->push_back(tempPoint.x());
                bufferPointer->push_back(tempPoint.y());
                bufferPointer->push_back(tempPoint.z());
                count+=3;
            }
        }
    }
    
    ros::Time final_time = ros::Time::now();
    ros::Duration time_elapsed = final_time - current_time;
    ROS_INFO("time for triangulation:%f",time_elapsed.toSec()); 
    ofstream Graph_Data;
    Graph_Data.open("graph_data.txt", ios::out | ios::app);
    Graph_Data<<time_elapsed.toSec()<<endl;
}
