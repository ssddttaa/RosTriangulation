/*created by
 *Giuseppe Loianno and Sadat Shaik*/

#include <mesh_map/mesh_map.h>
#include <cmath>
#include <stdlib.h>
void cloud_callback(const sensor_msgs::PointCloud::ConstPtr& msg) {
    sensor_msgs::PointCloud PointCloudMessage = *msg;
    int arrayLength = PointCloudMessage.points.size();
    //ROS_INFO("getting cloud data points");
    for(int i = 0;i<arrayLength;i++)
    {
      vector<float> tempVec;
      tempVec.push_back((float)(PointCloudMessage.points[i].x));
      tempVec.push_back((float)(PointCloudMessage.points[i].y));
      tempVec.push_back((float)(PointCloudMessage.points[i].z));
      int currentID = PointCloudMessage.channels[0].values[i];
      
      int getIndexOfID = find(IDMap.begin(), IDMap.end(), currentID) - IDMap.begin();
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
      triangulation.addPointsToTriangulation(&staticPointsToAdd, staticPointsToAdd.size());
      RVIZPublisher(marker_pub, &tempCurrentPoints);
    }
    for(int i = 0;i<isStaticMap.size();i++)
    {
      isStaticMap.at(i) +=1;
    }
  }
  
void printEverything()
{
  for(int i = 0;i<Current_Points.size();i++)
  {
    vector<float> tempVec = Current_Points.at(i);
    ROS_INFO("ID:%i, Current Point:(%f, %f, %f))",i,tempVec.at(0),tempVec.at(1), tempVec.at(2));
  }
  for(int i= 0;i<IDMap.size(); i++)
  {
    ROS_INFO("Mapped point id: %i, to id: %i",IDMap.at(i), i); 
  }
  for(int i= 0;i<All_Points.size(); i++)
  {
    vector<float> tempVec = All_Points.at(i);
    ROS_INFO("ID:%i, All Point:(%f, %f, %f))",i,tempVec.at(0),tempVec.at(1), tempVec.at(2));
  }
}
void RVIZPublisher(ros::Publisher marker_pub, vector<vector<float> > * tempCurrentPoints)
{
     vector<geometry_msgs::Point> linePointsToDraw;
     vector<geometry_msgs::Point> staticPointsToDraw;
     
     ConvertDelaunayFacesToLineVertices(&linePointsToDraw, &staticPointsToDraw, tempCurrentPoints);
     
     visualization_msgs::MarkerArray marker_array;
     
     visualization_msgs::Marker line_list;
     
     
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
       line_list.scale.x = .05;
       line_list.scale.y = .05;
       line_list.scale.z = .05;
       
       line_list.pose.orientation.w = 1.0;
       
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
//        static_line_list.color.g = 1.0;
       static_line_list.color.b = 0.0;
       static_line_list.scale.x = .05;
       static_line_list.scale.y = .05;
       static_line_list.scale.z = .05;
       
       static_line_list.pose.orientation.w = 1.0;
     for(int i = 0; i<linePointsToDraw.size();i++)
     {
       geometry_msgs::Point currentPoint = linePointsToDraw.at(i);
       if(!(abs(currentPoint.x) >boundingBoxMax|| abs(currentPoint.y) >boundingBoxMax|| abs(currentPoint.z)>boundingBoxMax))
       {
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
     marker_array.markers.resize(2);
     marker_array.markers[0] = line_list;
     marker_array.markers[1] = static_line_list;
     marker_pub.publish(marker_array);     
}

void ConvertDelaunayFacesToLineVertices(vector<geometry_msgs::Point> * linePointsToDraw, vector<geometry_msgs::Point> *staticPointsToDraw, vector<vector<float> > * tempCurrentPoints)
{
  for(int i = 0 ;i<TriangulatedPoints.size()/9;i++)
  {
    geometry_msgs::Point p1, p2, p3;
    
    p1.x = TriangulatedPoints.at(i*9);
    p1.y = TriangulatedPoints.at((i*9)+1);
    p1.z = TriangulatedPoints.at((i*9)+2);
    
    p2.x = TriangulatedPoints.at((i*9)+3);
    p2.y = TriangulatedPoints.at((i*9)+4);
    p2.z = TriangulatedPoints.at((i*9)+5);
    
    p3.x = TriangulatedPoints.at((i*9)+6);
    p3.y = TriangulatedPoints.at((i*9)+7);
    p3.z = TriangulatedPoints.at((i*9)+8);
    
    bool staticPoint1, staticPoint2, staticPoint3;
    staticPoint1 = staticPoint2 = staticPoint3 = true;
    for(int j = 0 ;j<tempCurrentPoints->size();j++)
    {
      vector<float> Current_Point(tempCurrentPoints->at(j));
      geometry_msgs::Point current_point;
      current_point.x = Current_Point.at(0);
      current_point.y = Current_Point.at(1);
      current_point.z = Current_Point.at(2);

      if(p1.x == current_point.x && p1.y == current_point.y && p1.z == current_point.z)
      {
	staticPoint1 = false;
      }
      if(p2.x == current_point.x && p2.y == current_point.y && p2.z == current_point.z)
      {
	staticPoint2 = false;
      }
      if(p3.x == current_point.x && p3.y == current_point.y && p3.z == current_point.z)
      {
	staticPoint3 = false;
      }
      if(!staticPoint1 && !staticPoint2 && !staticPoint3)
      {
	break;
      }
    }
    if(staticPoint1 && staticPoint2)
    {
      linePointsToDraw->push_back(p1);
      linePointsToDraw->push_back(p2);
    }
    else
    {
      staticPointsToDraw->push_back(p1);
      staticPointsToDraw->push_back(p2);
    }
    if(staticPoint1 && staticPoint2)
    {
      linePointsToDraw->push_back(p1);
      linePointsToDraw->push_back(p3);
    }
    else
    {
      staticPointsToDraw->push_back(p1);
      staticPointsToDraw->push_back(p3);
    }
    if(staticPoint1 && staticPoint2)
    {
      linePointsToDraw->push_back(p2);
      linePointsToDraw->push_back(p3);    
    }
    else
    {
      staticPointsToDraw->push_back(p2);
      staticPointsToDraw->push_back(p3);
    }
    
  }
}
void loadLaunchParameters(ros::NodeHandle nh_)
{
  ROS_INFO("lodaing launch parameters");
  XmlRpc::XmlRpcValue v;
  ros::param::get("/mesh_map/bounding_box", v);
  boundingBoxMax = (int)(v);
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
    if(Current_Points.size()>=4)
    {
      RVIZPublisher(marker_pub, &Current_Points);
    }
    ros::spinOnce();
  }
  
  return 0;
};



