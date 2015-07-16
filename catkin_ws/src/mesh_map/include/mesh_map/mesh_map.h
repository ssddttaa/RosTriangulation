/*created by 
 *Giuseppe Loianno and Sadat Shaik*/

#ifndef VIO_MESH_MAP_H
#define VIO_MESH_MAP_H

#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>
#include <sensor_msgs/PointCloud.h>
#include <memory>

#include "mesh_map/DelaunayTriangulate.h"

#include <geometry_msgs/Point32.h>
#include <ros/console.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <stdlib.h>

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

#include <cmath>

#include <sstream>
using namespace std;

vector<vector<float> > Current_Points;
vector<vector<float> > Static_Points;
vector<vector<float> > All_Points;

vector<int> isStaticMap;
vector<int> IDMap;
int lowestID = numeric_limits<int>::max();

int deletedPoints(0);

int clangs(0);
int finds(0);

int staticFramesThreshold(20);
bool firstPointSet = true;
int boundingBoxMax;

int numberOfPointsInTriangulation(0);

vector<float> TriangulatedPoints;

DelaunayTriangulation triangulation(&TriangulatedPoints);

ros::Publisher marker_pub;

float currentXMean(0.0);

void ConvertDelaunayFacesToLineVertices(vector<geometry_msgs::Point> * linePointsToDraw, vector<geometry_msgs::Point> * staticPointsToDraw, vector<vector<float> > * tempCurrentPoints);
void printEverything();
void RVIZPublisher(ros::Publisher marker_pub, vector<vector<float> > * tempCurrentPoints);
void loadLaunchParameters();
void recalculateMean(vector<vector<float> > *staticPoints);
#endif
