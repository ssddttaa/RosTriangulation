; Auto-generated. Do not edit!


(cl:in-package mesh_map-msg)


;//! \htmlinclude Triangulation.msg.html

(cl:defclass <Triangulation> (roslisp-msg-protocol:ros-message)
  ((Triangulation_Triangles
    :reader Triangulation_Triangles
    :initarg :Triangulation_Triangles
    :type (cl:vector mesh_map-msg:Triangle)
   :initform (cl:make-array 0 :element-type 'mesh_map-msg:Triangle :initial-element (cl:make-instance 'mesh_map-msg:Triangle)))
   (Triangulation_Triangles_Size
    :reader Triangulation_Triangles_Size
    :initarg :Triangulation_Triangles_Size
    :type cl:integer
    :initform 0))
)

(cl:defclass Triangulation (<Triangulation>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Triangulation>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Triangulation)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mesh_map-msg:<Triangulation> is deprecated: use mesh_map-msg:Triangulation instead.")))

(cl:ensure-generic-function 'Triangulation_Triangles-val :lambda-list '(m))
(cl:defmethod Triangulation_Triangles-val ((m <Triangulation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mesh_map-msg:Triangulation_Triangles-val is deprecated.  Use mesh_map-msg:Triangulation_Triangles instead.")
  (Triangulation_Triangles m))

(cl:ensure-generic-function 'Triangulation_Triangles_Size-val :lambda-list '(m))
(cl:defmethod Triangulation_Triangles_Size-val ((m <Triangulation>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mesh_map-msg:Triangulation_Triangles_Size-val is deprecated.  Use mesh_map-msg:Triangulation_Triangles_Size instead.")
  (Triangulation_Triangles_Size m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Triangulation>) ostream)
  "Serializes a message object of type '<Triangulation>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'Triangulation_Triangles))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Triangulation_Triangles))
  (cl:let* ((signed (cl:slot-value msg 'Triangulation_Triangles_Size)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Triangulation>) istream)
  "Deserializes a message object of type '<Triangulation>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'Triangulation_Triangles) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'Triangulation_Triangles)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'mesh_map-msg:Triangle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Triangulation_Triangles_Size) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Triangulation>)))
  "Returns string type for a message object of type '<Triangulation>"
  "mesh_map/Triangulation")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Triangulation)))
  "Returns string type for a message object of type 'Triangulation"
  "mesh_map/Triangulation")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Triangulation>)))
  "Returns md5sum for a message object of type '<Triangulation>"
  "b189e15305ff1c86d99e101f793d861a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Triangulation)))
  "Returns md5sum for a message object of type 'Triangulation"
  "b189e15305ff1c86d99e101f793d861a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Triangulation>)))
  "Returns full string definition for message of type '<Triangulation>"
  (cl:format cl:nil "Triangle[] Triangulation_Triangles~%int64 Triangulation_Triangles_Size~%================================================================================~%MSG: mesh_map/Triangle~%geometry_msgs/Point[3] Triangle_Vertices~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Triangulation)))
  "Returns full string definition for message of type 'Triangulation"
  (cl:format cl:nil "Triangle[] Triangulation_Triangles~%int64 Triangulation_Triangles_Size~%================================================================================~%MSG: mesh_map/Triangle~%geometry_msgs/Point[3] Triangle_Vertices~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Triangulation>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'Triangulation_Triangles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Triangulation>))
  "Converts a ROS message object to a list"
  (cl:list 'Triangulation
    (cl:cons ':Triangulation_Triangles (Triangulation_Triangles msg))
    (cl:cons ':Triangulation_Triangles_Size (Triangulation_Triangles_Size msg))
))
