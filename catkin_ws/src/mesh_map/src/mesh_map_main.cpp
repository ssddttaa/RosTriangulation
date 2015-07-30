/*created by
*Giuseppe Loianno and Sadat Shaik*/
#include <mesh_map/mesh_map.h>
#include <cmath>
#include <stdlib.h>
void cloud_callback(const sensor_msgs::PointCloud::ConstPtr& msg)
{
    sensor_msgs::PointCloud PointCloudMessage = *msg;
    int arrayLength = PointCloudMessage.points.size();
    //Creating ID Map. Each point has a unique ID which the ID Map stores. From there, to retrieve the ID, we just get it by index.
    for(int i = 0;i<arrayLength;i++)
    {
        //Gets the current point from the point cloud
        vector<float> tempVec;
        tempVec.push_back((float)(PointCloudMessage.points[i].x));
        tempVec.push_back((float)(PointCloudMessage.points[i].y));
        tempVec.push_back((float)(PointCloudMessage.points[i].z));
        //Get the id of the current point cloud point
        int currentID = PointCloudMessage.channels[0].values[i];
        //Searches through the ID map for the id.
        unsigned int getIndexOfID = find(IDMap.begin(), IDMap.end(), currentID) - IDMap.begin();
        //If the id is greater than or equal to the size of the map, this means that we were not able to find the ID in the map, and thus this is a new point.
        if(getIndexOfID>=IDMap.size())
        {
            IDMap.push_back(currentID);
            Current_Points.push_back(tempVec);
            All_Points.push_back(tempVec);
            isStaticMap.push_back(0);
        }
        else //if the id is not greater than the size of the map, then the point at the ID should be modified instead, in both instances, the static map for their ID should be set to 0
        {    //because the point is either new or being modified
            vector<float> tempVecDebug = Current_Points.at(getIndexOfID);
            Current_Points.at(getIndexOfID) = tempVec;
            tempVecDebug = All_Points.at(getIndexOfID+deletedPoints);
            All_Points.at(getIndexOfID+deletedPoints) = tempVec;
            isStaticMap.at(getIndexOfID) = 0;
        }
    }
    vector<vector<float> > staticPointsToAdd;
    vector<vector<float> > tempCurrentPoints;
    tempCurrentPoints = All_Points;
    triangulation.addPointsToTriangulation(&All_Points, All_Points.size());
    
    mesh_map::Triangulation triangulation;
    createTriangulationFromTriangulatedPoints(&triangulation);
    marker_pub.publish(triangulation);
//    RVIZPublisher(&tempCurrentPoints);
    ofstream Graph_Data;
    Graph_Data.open("graph_data.txt", ios::out| ios::app);
    Graph_Data<<All_Points.size()<<",";
    firstPointSet = false;
}

void createTriangulationFromTriangulatedPoints(mesh_map::Triangulation *triangulation)
{
    for(int i = 0;i<TriangulatedPoints.size()/3;i++)
    {
        mesh_map::Triangle temp_triangle;
        temp_triangle.Triangle_Vertices[0] = TriangulatedPoints.at((i*3));
        temp_triangle.Triangle_Vertices[1] = TriangulatedPoints.at((i*3)+1);
        temp_triangle.Triangle_Vertices[2] = TriangulatedPoints.at((i*3)+2);
        triangulation->Triangulation_Triangles.push_back(temp_triangle);
    }
    triangulation->Triangulation_Triangles_Size = TriangulatedPoints.size()/3;
}

void loadLaunchParameters(ros::NodeHandle nh_)
{
    ROS_INFO("loading launch parameters");
    XmlRpc::XmlRpcValue v;
    ros::param::get("/mesh_map/static_frames_threshold", v);
    staticFramesThreshold = (int)(v);
}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "mesh_map");
    ros::NodeHandle nh_("");
    ros::Subscriber subpointcloud_ = nh_.subscribe("/phone1/SQuad_demo_visualizer_total/vslam/current_map_points", 100, &cloud_callback, ros::TransportHints().tcpNoDelay());
    //call all the callback
    //marker_pub = nh_.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 10);
    marker_pub = nh_.advertise<mesh_map::Triangulation>("rviz_publisher_data", 10);
    loadLaunchParameters(nh_);
    ros::spin();
    return 0;
};