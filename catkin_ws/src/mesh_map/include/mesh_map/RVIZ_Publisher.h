#ifndef RVIZ_PUBLISHER_H
#define RVIZ_PUBLISHER_H

#include <geometry_msgs/Point.h>
#include <ros/console.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>

#include <mesh_map/Triangle.h>
#include <mesh_map/Triangulation.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <vector>

bool display_static_line_list(false);
bool display_line_list(false);
bool display_triangle_list(false);
bool display_cube_list(false);
float line_width(.05);

int boundingBoxMax(15.0);

ros::Publisher marker_pub;
    

using namespace std;

void RVIZ_Publisher_Callback(mesh_map::Triangulation TriangulatedPoints);

void ConvertDelaunayFacesToLineVertices(vector<geometry_msgs::Point> * linePointsToDraw, vector<geometry_msgs::Point> *staticPointsToDraw, mesh_map::Triangulation * TriangulatedPoints);
void loadLaunchParameters();

#endif
