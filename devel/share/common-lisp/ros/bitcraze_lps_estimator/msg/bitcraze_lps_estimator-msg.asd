
(cl:in-package :asdf)

(defsystem "bitcraze_lps_estimator-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "RangeArray" :depends-on ("_package_RangeArray"))
    (:file "_package_RangeArray" :depends-on ("_package"))
  ))