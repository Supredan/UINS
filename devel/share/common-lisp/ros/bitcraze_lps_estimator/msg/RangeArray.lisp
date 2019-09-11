; Auto-generated. Do not edit!


(cl:in-package bitcraze_lps_estimator-msg)


;//! \htmlinclude RangeArray.msg.html

(cl:defclass <RangeArray> (roslisp-msg-protocol:ros-message)
  ((ranges
    :reader ranges
    :initarg :ranges
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (valid
    :reader valid
    :initarg :valid
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil))
   (los
    :reader los
    :initarg :los
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 0 :element-type 'cl:boolean :initial-element cl:nil)))
)

(cl:defclass RangeArray (<RangeArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RangeArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RangeArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name bitcraze_lps_estimator-msg:<RangeArray> is deprecated: use bitcraze_lps_estimator-msg:RangeArray instead.")))

(cl:ensure-generic-function 'ranges-val :lambda-list '(m))
(cl:defmethod ranges-val ((m <RangeArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bitcraze_lps_estimator-msg:ranges-val is deprecated.  Use bitcraze_lps_estimator-msg:ranges instead.")
  (ranges m))

(cl:ensure-generic-function 'valid-val :lambda-list '(m))
(cl:defmethod valid-val ((m <RangeArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bitcraze_lps_estimator-msg:valid-val is deprecated.  Use bitcraze_lps_estimator-msg:valid instead.")
  (valid m))

(cl:ensure-generic-function 'los-val :lambda-list '(m))
(cl:defmethod los-val ((m <RangeArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader bitcraze_lps_estimator-msg:los-val is deprecated.  Use bitcraze_lps_estimator-msg:los instead.")
  (los m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RangeArray>) ostream)
  "Serializes a message object of type '<RangeArray>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ranges))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'ranges))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'valid))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'valid))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'los))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'los))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RangeArray>) istream)
  "Deserializes a message object of type '<RangeArray>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ranges) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ranges)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'valid) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'valid)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'los) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'los)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RangeArray>)))
  "Returns string type for a message object of type '<RangeArray>"
  "bitcraze_lps_estimator/RangeArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RangeArray)))
  "Returns string type for a message object of type 'RangeArray"
  "bitcraze_lps_estimator/RangeArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RangeArray>)))
  "Returns md5sum for a message object of type '<RangeArray>"
  "6eea5c2b2055cd08369bcbebe9f0032b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RangeArray)))
  "Returns md5sum for a message object of type 'RangeArray"
  "6eea5c2b2055cd08369bcbebe9f0032b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RangeArray>)))
  "Returns full string definition for message of type '<RangeArray>"
  (cl:format cl:nil "float32[] ranges~%bool[] valid~%bool[] los~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RangeArray)))
  "Returns full string definition for message of type 'RangeArray"
  (cl:format cl:nil "float32[] ranges~%bool[] valid~%bool[] los~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RangeArray>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ranges) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'valid) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'los) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RangeArray>))
  "Converts a ROS message object to a list"
  (cl:list 'RangeArray
    (cl:cons ':ranges (ranges msg))
    (cl:cons ':valid (valid msg))
    (cl:cons ':los (los msg))
))
