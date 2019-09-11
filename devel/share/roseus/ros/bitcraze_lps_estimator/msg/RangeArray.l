;; Auto-generated. Do not edit!


(when (boundp 'bitcraze_lps_estimator::RangeArray)
  (if (not (find-package "BITCRAZE_LPS_ESTIMATOR"))
    (make-package "BITCRAZE_LPS_ESTIMATOR"))
  (shadow 'RangeArray (find-package "BITCRAZE_LPS_ESTIMATOR")))
(unless (find-package "BITCRAZE_LPS_ESTIMATOR::RANGEARRAY")
  (make-package "BITCRAZE_LPS_ESTIMATOR::RANGEARRAY"))

(in-package "ROS")
;;//! \htmlinclude RangeArray.msg.html


(defclass bitcraze_lps_estimator::RangeArray
  :super ros::object
  :slots (_ranges _valid _los ))

(defmethod bitcraze_lps_estimator::RangeArray
  (:init
   (&key
    ((:ranges __ranges) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:valid __valid) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:los __los) (let (r) (dotimes (i 0) (push nil r)) r))
    )
   (send-super :init)
   (setq _ranges __ranges)
   (setq _valid __valid)
   (setq _los __los)
   self)
  (:ranges
   (&optional __ranges)
   (if __ranges (setq _ranges __ranges)) _ranges)
  (:valid
   (&optional __valid)
   (if __valid (setq _valid __valid)) _valid)
  (:los
   (&optional __los)
   (if __los (setq _los __los)) _los)
  (:serialization-length
   ()
   (+
    ;; float32[] _ranges
    (* 4    (length _ranges)) 4
    ;; bool[] _valid
    (* 1    (length _valid)) 4
    ;; bool[] _los
    (* 1    (length _los)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32[] _ranges
     (write-long (length _ranges) s)
     (dotimes (i (length _ranges))
       (sys::poke (elt _ranges i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; bool[] _valid
     (write-long (length _valid) s)
     (dotimes (i (length _valid))
       (if (elt _valid i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; bool[] _los
     (write-long (length _los) s)
     (dotimes (i (length _los))
       (if (elt _los i) (write-byte -1 s) (write-byte 0 s))
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32[] _ranges
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ranges (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _ranges i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; bool[] _valid
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _valid (make-list n))
     (dotimes (i n)
     (setf (elt _valid i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;; bool[] _los
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _los (make-list n))
     (dotimes (i n)
     (setf (elt _los i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;;
   self)
  )

(setf (get bitcraze_lps_estimator::RangeArray :md5sum-) "6eea5c2b2055cd08369bcbebe9f0032b")
(setf (get bitcraze_lps_estimator::RangeArray :datatype-) "bitcraze_lps_estimator/RangeArray")
(setf (get bitcraze_lps_estimator::RangeArray :definition-)
      "float32[] ranges
bool[] valid
bool[] los

")



(provide :bitcraze_lps_estimator/RangeArray "6eea5c2b2055cd08369bcbebe9f0032b")


