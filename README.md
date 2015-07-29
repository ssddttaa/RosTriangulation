# Dynamic Mesh Construction with ROS
This repository obtains a point cloud (pcl2) message from ROS, and generates a mesh surrounding those points for use in collision detection.

####This repository contains the following methods for mesh generation (located in different branches):
- Scale Space Mesh Reconstruction ([CGAL Algorithm Documentation Link](http://doc.cgal.org/latest/Scale_space_reconstruction_3/index.html))
  
  - Most accurate for generating real-time meshes
  
  - Generates holes
  
  - Best suited for lidar 
  
- 3D Delaunay Triangulation ([CGAL Algorithm Documentation Link](http://doc.cgal.org/latest/Triangulation_3/))

  - Generates 3-D Tetrahedralization of given points.
  
  - Triangulates over holes

- Poisson Surface Reconstruction([CGAL Algorithm Documentation Link](http://doc.cgal.org/latest/Surface_reconstruction_points_3/index.html))

- 2D Delaunay Triangulation ([CGAL Algorithm Documentation Link](http://doc.cgal.org/latest/Triangulation_2/))

#Installation

First, you must have the following dependencies installed: [link](http://doc.cgal.org/latest/Manual/installation.html#secessential3rdpartysoftware) 

Then, you must install the CGAL tarball, [link](https://gforge.inria.fr/frs/?group_id=52&release_id=9274).

Extract the tarball, and run 
```
cmake .
```

Then run
```
make install
```

Move the CGAL folder from inside the include folder into your /usr/local/include folder.
Move the CGAL folder from inside the src folder into your /usr/local/lib folder.

To use the Scale Space Reconstruction:

```
cd /usr/local/include/CGAL
```

If you do not have the following file "Scale_space_surface_reconstruction_3_impl.h":
```
cd Scale_space_reconstruction_3
cp Scale_space_surface_reconstruction_3_impl.h ..
```

Now you must install ROS, instructions can be found [here](http://wiki.ros.org/indigo/Installation/Ubuntu).

#Usage

cd into the catkin_ws directory

```
catkin_make
```

If all compiles successfully, cd into the launch folder, and run the following command:

```
roslaunch mesh_map.launch
```

#Contact

For any questions / debugging hints, please e-mail me at sadatalishaik@gmail.com

-Sadat Shaik


