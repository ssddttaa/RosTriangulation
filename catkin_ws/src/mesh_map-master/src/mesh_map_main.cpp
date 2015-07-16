/*created by
 *Giuseppe Loianno and Sadat Shaik*/

#include <mesh_map/mesh_map.h>
#include <cmath>
#include <stdlib.h>
void cloud_callback(const sensor_msgs::PointCloud::ConstPtr& msg) {
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
      
//       //Get the id of the current point cloud point
      int currentID = PointCloudMessage.channels[0].values[i];
      
      //Searches through the ID map for the id.
      int getIndexOfID = find(IDMap.begin(), IDMap.end(), currentID) - IDMap.begin();
      //If the id is greater than or equal to the size of hte IDMpa
      if(getIndexOfID>=IDMap.size())
      {
	IDMap.push_back(currentID);
	Current_Points.push_back(tempVec);
	All_Points.push_back(tempVec);
	isStaticMap.push_back(0);
      }
      else
      {
	vector<float> tempVecDebug = Current_Points.at(getIndexOfID);
	Current_Points.at(getIndexOfID) = tempVec;
	tempVecDebug = All_Points.at(getIndexOfID+deletedPoints);
 	All_Points.at(getIndexOfID+deletedPoints) = tempVec;
	isStaticMap.at(getIndexOfID) = 0;
      }
    }
    vector<vector<float> > staticPointsToAdd;
    vector<vector<float> > tempCurrentPoints;
    tempCurrentPoints = Current_Points;
    for(int i = 0 ;i<isStaticMap.size();i++)
    {
      if(isStaticMap.at(i)>=staticFramesThreshold)
      {
	staticPointsToAdd.push_back(tempCurrentPoints.at(i));
	if(firstPointSet&&staticPointsToAdd.size()>=4)
	{
	  firstPointSet = false;
	}
	
	if(!firstPointSet)
	{
	    Current_Points.erase(Current_Points.begin()+i);
	    IDMap.erase(IDMap.begin()+i);
	    isStaticMap.erase(isStaticMap.begin()+i);
	    deletedPoints++;
	}
      }
    }
    if(!firstPointSet&&staticPointsToAdd.size()>0)
    {
      numberOfPointsInTriangulation += staticPointsToAdd.size();
      recalculateMean(&staticPointsToAdd);
      for(int i = 0;i<staticPointsToAdd.size();i++)
      {
	staticPointsToAdd.at(i).at(0) = currentXMean;
      }
      triangulation.addPointsToTriangulation(&staticPointsToAdd, staticPointsToAdd.size());
      RVIZPublisher(marker_pub, &tempCurrentPoints);
    }
    for(int i = 0;i<isStaticMap.size();i++)
    {
      isStaticMap.at(i) +=1;
    }
  }
void recalculateMean(vector<vector<float> > *staticPoints)
{
  float previousSum = currentXMean*(numberOfPointsInTriangulation-staticPoints->size());
  for(int i = 0;i<staticPoints->size();i++)
  {
    previousSum+=staticPoints->at(i).at(0);
  }
  currentXMean = (previousSum/numberOfPointsInTriangulation);
  
}
void RVIZPublisher(ros::Publisher marker_pub, vector<vector<float> > * tempCurrentPoints)
{
     vector<geometry_msgs::Point> linePointsToDraw;
     vector<geometry_msgs::Point> staticPointsToDraw;
     
     ConvertDelaunayFacesToLineVertices(&linePointsToDraw, &staticPointsToDraw, tempCurrentPoints);
     
     visualization_msgs::MarkerArray marker_array;
     
     visualization_msgs::Marker line_list;
     
     //BEGINNING OF REGULAR LINE LIST
     line_list.header.stamp = ros::Time::now();
     
     line_list.ns = "mesh_map";
     
     line_list.header.frame_id = "/world";
     
     line_list.action = visualization_msgs::Marker::ADD;
     
     line_list.id = 0;
     
     line_list.type = visualization_msgs::Marker::LINE_LIST;
     
     line_list.lifetime = ros::Duration(1);
            line_list.color.a = 1.0;
       line_list.color.r = 0.0;
       line_list.color.g = 0.0;
       line_list.color.b = 1.0;
       line_list.scale.x = .005;
       line_list.scale.y = .005;
       line_list.scale.z = .005;
       
       line_list.pose.orientation.w = 1.0;
       //END OF REGULAR LINE LIST
     //BEGINNING OF COLOR LINE LIST
       visualization_msgs::Marker static_line_list;
     
     static_line_list.header.stamp = ros::Time::now();
     
     static_line_list.ns = "mesh_map";
     
     static_line_list.header.frame_id = "/world";
     
     static_line_list.action = visualization_msgs::Marker::ADD;
     
     static_line_list.id = 1;
     
     static_line_list.type = visualization_msgs::Marker::LINE_LIST;
     
     static_line_list.lifetime = ros::Duration(1);
            static_line_list.color.a = 1.0;
       static_line_list.color.r = 0.0;
        static_line_list.color.g = 1.0;
       static_line_list.color.b = 0.0;
       static_line_list.scale.x = .005;
       static_line_list.scale.y = .005;
       static_line_list.scale.z = .005;
       
       static_line_list.pose.orientation.w = static_line_list.pose.orientation.x = static_line_list.pose.orientation.y = static_line_list.pose.orientation.z = 0.0;
       //END OF COLOR LINE LIST
     //BEGINNING OF TRIANGLE LIST
       visualization_msgs::Marker triangle_list;
     
     triangle_list.header.stamp = ros::Time::now();
     
     triangle_list.ns = "mesh_map";
     
     triangle_list.header.frame_id = "/world";
     
     triangle_list.action = visualization_msgs::Marker::ADD;
     
     triangle_list.id = 2;
     
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
       //END OF TRIANGLE LIST
     for(int i = 0; i<linePointsToDraw.size();i++)
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
     
     for(int i = 0; i<staticPointsToDraw.size();i++)
     {
       geometry_msgs::Point currentPoint = staticPointsToDraw.at(i);
       if(!(abs(currentPoint.x) >boundingBoxMax|| abs(currentPoint.y) >boundingBoxMax|| abs(currentPoint.z)>boundingBoxMax))
       {
	 static_line_list.points.push_back(currentPoint);
       }
     }
     
     for(int i = 0; i<TriangulatedPoints.size()/3;i++)
     {
       vector<float> trianglePointsTemp;
       trianglePointsTemp.push_back(TriangulatedPoints.at(i*3));
       trianglePointsTemp.push_back(TriangulatedPoints.at((i*3)+1));
       trianglePointsTemp.push_back(TriangulatedPoints.at((i*3)+2));
       geometry_msgs::Point currentPoint;
       currentPoint.x = trianglePointsTemp.at(0);
       currentPoint.y = trianglePointsTemp.at(1);
       currentPoint.z = trianglePointsTemp.at(2);
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
     
     
     marker_array.markers.resize(2);
     marker_array.markers[0] = line_list;
     marker_array.markers[1] = static_line_list;
     //marker_array.markers[2] = triangle_list;
     marker_pub.publish(marker_array);     
}

void ConvertDelaunayFacesToLineVertices(vector<geometry_msgs::Point> * linePointsToDraw, vector<geometry_msgs::Point> *staticPointsToDraw, vector<vector<float> > * tempCurrentPoints)
{
  //ROS_INFO("before conversion yo");
  for(int i = 0 ;i<TriangulatedPoints.size()/2;i++)
  {
    geometry_msgs::Point p1, p2, p3;
    
    p1.x = currentXMean;
    p1.y = TriangulatedPoints.at(i*2);
    p1.z = TriangulatedPoints.at((i*2)+1);
    
    linePointsToDraw->push_back(p1);
    
    //ROS_INFO("CURRENT POINT CONVERSION(%f, %f)", p1.y, p1.z);
    
    
  }
}
void loadLaunchParameters(ros::NodeHandle nh_)
{
  ROS_INFO("lodaing launch parameters");
  XmlRpc::XmlRpcValue v;
  ros::param::get("/mesh_map/bounding_box", v);
  boundingBoxMax = (int)(v);
  ros::param::get("/mesh_map/static_frames_threshold", v);
  staticFramesThreshold = (int)(v);
}
int main(int argc, char** argv) {
  ros::init(argc, argv, "mesh_map");
  ros::NodeHandle nh_("");
  
  
  ros::Subscriber subpointcloud_ = nh_.subscribe("/phone1/SQuad_demo_visualizer_total/vslam/current_map_points", 100, &cloud_callback, ros::TransportHints().tcpNoDelay());
  //call all the callback
  marker_pub = nh_.advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 10);
  loadLaunchParameters(nh_);
  while(ros::ok())
  {
//     ROS_INFO("size of current points %i", Current_Points.size());
    if(Current_Points.size()>=4)
    {
      RVIZPublisher(marker_pub, &Current_Points);
    }
    ros::spinOnce();
  }
  
  return 0;
};



