#include <mesh_map/RVIZ_Publisher.h>

void RVIZ_Publisher_Callback(mesh_map::Triangulation TriangulatedPoints)
{
    Current_Triangulation = TriangulatedPoints;
}

void RVIZ_Publisher()
{
    vector<geometry_msgs::Point> linePointsToDraw;
    vector<geometry_msgs::Point> staticPointsToDraw;
    ConvertDelaunayFacesToLineVertices(&linePointsToDraw, &staticPointsToDraw, &Current_Triangulation);
    visualization_msgs::MarkerArray marker_array;
    int marker_array_size = 0;
    //BEGINNING OF REGULAR LINE LIST
    if(display_line_list)
    {
        marker_array_size++;
        marker_array.markers.resize(marker_array_size);
        visualization_msgs::Marker line_list;
        line_list.header.stamp = ros::Time::now();
        line_list.ns = "mesh_map";
        line_list.header.frame_id = "/world";
        line_list.action = visualization_msgs::Marker::ADD;
        line_list.id = marker_array_size-1;
        line_list.type = visualization_msgs::Marker::LINE_LIST;
        line_list.lifetime = ros::Duration(1);
        line_list.color.a = line_list.color.b = line_list.pose.orientation.w = 1.0;
        line_list.color.r = line_list.color.g = 0.0;
        line_list.scale.x = line_list.scale.y = line_list.scale.z = line_width;
        for(unsigned int i = 0; i<linePointsToDraw.size();i++)
        {
            geometry_msgs::Point currentPoint = linePointsToDraw.at(i);
            std_msgs::ColorRGBA c;
            c.a = 1.0;
            c.r = currentPoint.x;
            c.g = currentPoint.y;
            c.b = currentPoint.z;
            if(!(abs(currentPoint.x) >boundingBoxMax|| abs(currentPoint.y) >boundingBoxMax|| abs(currentPoint.z)>boundingBoxMax))
            {
                line_list.colors.push_back(c);
                line_list.points.push_back(currentPoint);
            }
        }
        marker_array_size++;
        marker_array.markers.resize(marker_array_size);
        marker_array.markers[marker_array_size-1] = line_list;
    }
    //END OF REGULAR LINE LIST
    //BEGINNING OF COLOR LINE LIST
    if(display_static_line_list)
    {
        marker_array_size++;
        marker_array.markers.resize(marker_array_size);
        visualization_msgs::Marker static_line_list;
        static_line_list.header.stamp = ros::Time::now();
        static_line_list.ns = "mesh_map";
        static_line_list.header.frame_id = "/world";
        static_line_list.action = visualization_msgs::Marker::ADD;
        static_line_list.id = marker_array_size-1;
        static_line_list.type = visualization_msgs::Marker::LINE_LIST;
        static_line_list.lifetime = ros::Duration(1);
        static_line_list.color.a = static_line_list.color.g = 1.0;
        static_line_list.color.r = static_line_list.color.b = 0.0;
        static_line_list.scale.x = static_line_list.scale.y = static_line_list.scale.z = line_width;
        static_line_list.pose.orientation.w = static_line_list.pose.orientation.x = static_line_list.pose.orientation.y = static_line_list.pose.orientation.z = 0.0;
        for(unsigned int i = 0; i<staticPointsToDraw.size();i++)
        {
            geometry_msgs::Point currentPoint = staticPointsToDraw.at(i);
            if(!(abs(currentPoint.x) >boundingBoxMax|| abs(currentPoint.y) >boundingBoxMax|| abs(currentPoint.z)>boundingBoxMax))
            {
                static_line_list.points.push_back(currentPoint);
            }
        }
        marker_array.markers[marker_array_size-1] = static_line_list;
    }
    //END OF COLOR LINE LIST
    //BEGINNING OF TRIANGLE LIST
    if(display_triangle_list)
    {
        marker_array_size++;
        marker_array.markers.resize(marker_array_size);
        visualization_msgs::Marker triangle_list;
        triangle_list.header.stamp = ros::Time::now();
        triangle_list.ns = "mesh_map";
        triangle_list.header.frame_id = "/world";
        triangle_list.action = visualization_msgs::Marker::ADD;
        triangle_list.id = marker_array_size-1;
        triangle_list.type = visualization_msgs::Marker::TRIANGLE_LIST;
        triangle_list.lifetime = ros::Duration(1);
        triangle_list.color.a = 1.0;
        triangle_list.color.r = 1.0;
        triangle_list.color.g = 0.0;
        triangle_list.color.b = 0.0;
        triangle_list.scale.x = 1.0;
        triangle_list.scale.y = 1.0;
        triangle_list.scale.z = 1.0;
        triangle_list.pose.orientation.w = triangle_list.pose.orientation.x = triangle_list.pose.orientation.y = triangle_list.pose.orientation.z = 0.0;
        for(unsigned int i = 0; i<Current_Triangulation.Triangulation_Triangles_Size;i++)
        {
            mesh_map::Triangle Temp_Triangle= Current_Triangulation.Triangulation_Triangles[i];
            for(int j = 0;j<3;j++)
            {
                geometry_msgs::Point currentPoint(Temp_Triangle.Triangle_Vertices[j]);
                std_msgs::ColorRGBA tempColor;
                tempColor.a = 1.0;
                tempColor.r = currentPoint.x;
                tempColor.g = currentPoint.y;
                tempColor.b = currentPoint.z;
                if(!(abs(currentPoint.x) >boundingBoxMax|| abs(currentPoint.y) >boundingBoxMax|| abs(currentPoint.z)>boundingBoxMax))
                {
                    triangle_list.points.push_back(currentPoint);
                    triangle_list.colors.push_back(tempColor);
                }
            }   
        }
        marker_array.markers[marker_array_size-1] = triangle_list;
    }
    marker_pub.publish(marker_array);
}

void loadLaunchParameters(ros::NodeHandle nh_)
{
    XmlRpc::XmlRpcValue v;
    ros::param::get("/mesh_map/bounding_box", v);
    boundingBoxMax = (int)(v);
    ros::param::get("/mesh_map/display_static_line_list", v);
    display_static_line_list = (bool)(v);
    ros::param::get("/mesh_map/display_line_list", v);
    display_line_list = (bool)(v);
    ros::param::get("/mesh_map/display_cube_list", v);
    display_cube_list = (bool)(v);
    ros::param::get("/mesh_map/display_triangle_list", v);
    display_triangle_list = (bool)(v);
    ros::param::get("/mesh_map/line_width", v);
    line_width = (double)(v);
}

void ConvertDelaunayFacesToLineVertices(vector<geometry_msgs::Point> * linePointsToDraw, vector<geometry_msgs::Point> *staticPointsToDraw, mesh_map::Triangulation *TriangulatedPoints)
{
    for(unsigned int i = 0 ;i<TriangulatedPoints->Triangulation_Triangles.size();i++)
    {
        mesh_map::Triangle Temp_Triangle = TriangulatedPoints->Triangulation_Triangles[i];
        staticPointsToDraw->push_back(Temp_Triangle.Triangle_Vertices[0]);
        staticPointsToDraw->push_back(Temp_Triangle.Triangle_Vertices[1]);
        staticPointsToDraw->push_back(Temp_Triangle.Triangle_Vertices[2]);
    }
}
int main(int argc, char ** argv)
{
    ROS_INFO("node created");
    ros::init(argc,argv,"RVIZ_Publisher");
    ros::NodeHandle nh_("");
    loadLaunchParameters(nh_);
    marker_pub = nh_.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 10);
    ros::Subscriber RVIZ_Publisher_Data = nh_.subscribe("rviz_publisher_data", 100, &RVIZ_Publisher_Callback, ros::TransportHints().tcpNoDelay());
    while(ros::ok())
    {
        RVIZ_Publisher();
        ros::spinOnce();
    }
}