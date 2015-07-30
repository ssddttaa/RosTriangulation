; Auto-generated. Do not edit!


(cl:in-package mesh_map-msg)


;//! \htmlinclude Triangle.msg.html

(cl:defclass <Triangle> (roslisp-msg-protocol:ros-message)
  ((Triangle_Vertices
    :reader Triangle_Vertices
    :initarg :Triangle_Vertices
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 3 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass Triangle (<Triangle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Triangle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Triangle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mesh_map-msg:<Triangle> is deprecated: use mesh_map-msg:Triangle instead.")))

(cl:ensure-generic-function 'Triangle_Vertices-val :lambda-list '(m))
(cl:defmethod Triangle_Vertices-val ((m <Triangle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mesh_map-msg:Triangle_Vertices-val is deprecated.  Use mesh_map-msg:Triangle_Vertices instead.")
  (Triangle_Vertices m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Triangle>) ostream)
  "Serializes a message object of type '<Triangle>"
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'Triangle_Vertices))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Triangle>) istream)
  "Deserializes a message object of type '<Triangle>"
  (cl:setf (cl:slot-value msg 'Triangle_Vertices) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'Triangle_Vertices)))
    (cl:dotimes (i 3)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Triangle>)))
  "Returns string type for a message object of type '<Triangle>"
  "mesh_map/Triangle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Triangle)))
  "Returns string type for a message object of type 'Triangle"
  "mesh_map/Triangle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Triangle>)))
  "Returns md5sum for a message object of type '<Triangle>"
  "25cdd87d1562bec196e1f54f80b6b393")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Triangle)))
  "Returns md5sum for a message object of type 'Triangle"
  "25cdd87d1562bec196e1f54f80b6b393")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Triangle>)))
  "Returns full string definition for message of type '<Triangle>"
  (cl:format cl:nil "geometry_msgs/Point[3] Triangle_Vertices~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Triangle)))
  "Returns full string definition for message of type 'Triangle"
  (cl:format cl:nil "geometry_msgs/Point[3] Triangle_Vertices~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Triangle>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Triangle_Vertices) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Triangle>))
  "Converts a ROS message object to a list"
  (cl:list 'Triangle
    (cl:cons ':Triangle_Vertices (Triangle_Vertices msg))
))
