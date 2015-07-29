# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "mesh_map: 2 messages, 0 services")

set(MSG_I_FLAGS "-Imesh_map:/home/mrsl_student/git/catkin_ws/src/mesh_map/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(mesh_map_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg" NAME_WE)
add_custom_target(_mesh_map_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mesh_map" "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg" "mesh_map/Triangle:geometry_msgs/Point"
)

get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg" NAME_WE)
add_custom_target(_mesh_map_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "mesh_map" "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg" "geometry_msgs/Point"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg"
  "${MSG_I_FLAGS}"
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mesh_map
)
_generate_msg_cpp(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mesh_map
)

### Generating Services

### Generating Module File
_generate_module_cpp(mesh_map
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mesh_map
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(mesh_map_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(mesh_map_generate_messages mesh_map_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_cpp _mesh_map_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_cpp _mesh_map_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mesh_map_gencpp)
add_dependencies(mesh_map_gencpp mesh_map_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mesh_map_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg"
  "${MSG_I_FLAGS}"
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mesh_map
)
_generate_msg_lisp(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mesh_map
)

### Generating Services

### Generating Module File
_generate_module_lisp(mesh_map
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mesh_map
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(mesh_map_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(mesh_map_generate_messages mesh_map_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_lisp _mesh_map_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_lisp _mesh_map_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mesh_map_genlisp)
add_dependencies(mesh_map_genlisp mesh_map_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mesh_map_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg"
  "${MSG_I_FLAGS}"
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg;/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map
)
_generate_msg_py(mesh_map
  "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/geometry_msgs/cmake/../msg/Point.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map
)

### Generating Services

### Generating Module File
_generate_module_py(mesh_map
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(mesh_map_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(mesh_map_generate_messages mesh_map_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangulation.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_py _mesh_map_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/mrsl_student/git/catkin_ws/src/mesh_map/msg/Triangle.msg" NAME_WE)
add_dependencies(mesh_map_generate_messages_py _mesh_map_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(mesh_map_genpy)
add_dependencies(mesh_map_genpy mesh_map_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS mesh_map_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mesh_map)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/mesh_map
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(mesh_map_generate_messages_cpp std_msgs_generate_messages_cpp)
add_dependencies(mesh_map_generate_messages_cpp geometry_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mesh_map)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/mesh_map
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(mesh_map_generate_messages_lisp std_msgs_generate_messages_lisp)
add_dependencies(mesh_map_generate_messages_lisp geometry_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/mesh_map
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(mesh_map_generate_messages_py std_msgs_generate_messages_py)
add_dependencies(mesh_map_generate_messages_py geometry_msgs_generate_messages_py)
