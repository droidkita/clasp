(in-package #:cmp)

;;;; Checking the type header of objects.
;;; This code is used by both bclasp and cclasp.

(defparameter *debug-typeq* nil)

(defun compile-tag-check (object-raw mask ctag then-br else-br)
  ;; object at this point is a smart ptr { {}* }
  (if *debug-typeq* (irc-intrinsic "debugPrintI32" (jit-constant-i32 10002)))
  (let* ((tag (irc-and (irc-ptr-to-int object-raw %uintptr_t%) (jit-constant-uintptr_t mask) "tag-only"))
         (cmp (irc-icmp-eq tag (jit-constant-uintptr_t ctag) "test")))
    (irc-cond-br cmp then-br else-br)))


(defun compile-header-check (header-value-min-max object-raw then-br else-br)
  (let ((header-check-br  (irc-basic-block-create "header-check-br")))
    (compile-tag-check object-raw +immediate-mask+ +general-tag+ header-check-br else-br)
    (irc-begin-block header-check-br)
    (if *debug-typeq* (irc-intrinsic "debugPrintI32" (jit-constant-i32 10001)))
    (let* ((byte-ptr           (irc-bit-cast object-raw %i8*%))
           (header-addr        (irc-gep %i8% byte-ptr (list (+ +header-stamp-offset+ (- (+ +header-size+ +general-tag+))))))
           (_ (if *debug-typeq* (irc-intrinsic "debugPointer" header-addr)))
           (header-stamp-ptr-type (cond
                                    ((= 4 +header-stamp-size+) %i32*%)
                                    ((= 8 +header-stamp-size+) %i64*%)
                                    (t (error "illegal +header-stamp-size+ ~a expected 4 or 8" +header-stamp-size+))))
           (header-stamp-type (cond
                                ((= 4 +header-stamp-size+) %i32%)
                                ((= 8 +header-stamp-size+) %i64%)
                                (t (error "illegal +header-stamp-size+ ~a expected 4 or 8" +header-stamp-size+))))
           (header-addr         (irc-bit-cast header-addr header-stamp-ptr-type))
           (value32             (irc-typed-load header-stamp-type header-addr))
           (_ (if *debug-typeq* (irc-intrinsic "debugPrintI32" value32)))
           (header-value        (irc-zext value32 %uintptr_t%)))
      (if (fixnump header-value-min-max)
          (let* ((shifted-header-value (core:shift-stamp-for-compiled-code header-value-min-max))
                 (match (irc-icmp-eq header-value (jit-constant-uintptr_t shifted-header-value))))
            (irc-cond-br match then-br else-br))
          (let ((maybe-in-range-br (irc-basic-block-create "maybe-in-range")))
            (check-type header-value-min-max cons)
            (let* ((shifted-header-range-min (core:shift-stamp-for-compiled-code (car header-value-min-max)))
                   (shifted-header-range-max (core:shift-stamp-for-compiled-code (cdr header-value-min-max)))
                   (min-match        (irc-icmp-uge header-value (jit-constant-uintptr_t shifted-header-range-min))))
              (irc-cond-br min-match maybe-in-range-br else-br)
              (irc-begin-block maybe-in-range-br)
              (let* ((maybe-more-tests-br (irc-basic-block-create "maybe-more-tests"))
                     (max-match (irc-icmp-ule header-value (jit-constant-uintptr_t shifted-header-range-max))))
                (irc-cond-br max-match maybe-more-tests-br else-br)
                (irc-begin-block maybe-more-tests-br)
                #+(or)(if (typeq-function header-value-min-max)
                          (compile-generic-function-check header-value then-br else-br)
                          (irc-br then-br))
                (irc-br then-br))))))))
