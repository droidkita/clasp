;;;
;;;    File: cmputil.lisp
;;;

;; Copyright (c) 2014, Christian E. Schafmeister
;;
;; CLASP is free software; you can redistribute it and/or
;; modify it under the terms of the GNU Library General Public
;; License as published by the Free Software Foundation; either
;; version 2 of the License, or (at your option) any later version.
;;
;; See directory 'clasp/licenses' for full details.
;;
;; The above copyright notice and this permission notice shall be included in
;; all copies or substantial portions of the Software.
;;
;; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
;; THE SOFTWARE.

;; -^-

;;;; This is the compiler signaling system as used by bclasp, i.e. before
;;;; the CLOS condition system exists. Most of this file will be redefined
;;;; in compiler-conditions.lisp.


(in-package :cmp)

(defvar *global-function-defs*)
(defvar *global-function-refs*)
(defvar *compilation-messages*)

(defvar *warnings-p*)
(defvar *failure-p*)

(core:defconstant-equal +note-format+        "Note:          {}")
(core:defconstant-equal +style-warn-format+  "Style warning: {}")
(core:defconstant-equal +warn-format+        "Warning:       {}")
(core:defconstant-equal +error-format+       "Error:         {}")
(core:defconstant-equal +fatal-format+       "Fatal-error:   {}")

(defstruct (compiler-message (:type vector))
  (format +note-format+)
  message
  source-pos-info)

(defstruct (compiler-note (:include compiler-message)
                          (:type vector)))

(defstruct (compiler-warning
             (:type vector)
             (:include compiler-message
              (format +warn-format+))))

(defstruct (compiler-error
             (:type vector)
             (:include compiler-message
              (format +error-format+))))

(defstruct (compiler-fatal-error
             (:type vector)
             (:include compiler-error
              (format +fatal-format+))))

(defstruct (compiler-style-warning
             (:type vector)
             (:include compiler-warning
              (format +style-warn-format+))))

;;; defined analogously to WARN, etc.
(defun coerce-compiler-message (datum args)
  (cond ((stringp datum) ; it's a fmt string
         (apply #'core:fmt nil datum args))
        ((null args) ; it's some kind of object, e.g. a condition
         (princ-to-string datum))
        (t (error "BUG: Bad arguments to compiler-warn/error/something: ~a ~a"
                  datum args))))

(defun compiler-error (spi datum &rest args)
  (setf *failure-p* (setf *warnings-p* t))
  (let* ((cspi (or spi (ext:current-source-location)))
         (err (make-compiler-error :message (coerce-compiler-message datum args)
                                   :source-pos-info cspi)))
      (push err *compilation-messages*)))

(defun compiler-warn (spi datum &rest args)
  (setf *failure-p* (setf *warnings-p* t))
  (let* ((cspi (or spi (ext:current-source-location)))
         (err (make-compiler-warning :message (coerce-compiler-message datum args)
                                     :source-pos-info cspi)))
    (push err *compilation-messages*)))

;;; We redefine all these warn-specific-thing functions later to signal actual
;;; conditions using actual format strings.

(defun warn-undefined-global-variable (spi var)
  (compiler-warn spi "Undefined variable {}" var))

(defun warn-undefined-type (spi type)
  (compiler-style-warn spi "Undefined type {}" type))

(defun warn-cannot-coerce (spi type)
  (compiler-style-warn spi "Cannot coerce to type {}: unknown or not defined for coerce" type))

(defun warn-invalid-number-type (spi type)
  (compiler-warn spi "Invalid number type: {}" type))

(defun warn-icsp-iesp-both-specified (spi)
  (compiler-warn
   spi ":initial-contents and :initial-element both specified"))

(defun compiler-style-warn (spi datum &rest args)
  (setf *warnings-p* t)
  (let* ((cspi (or spi (ext:current-source-location)))
         (err (make-compiler-style-warning :message (coerce-compiler-message datum args)
                                           :source-pos-info cspi)))
    (push err *compilation-messages*)))

(defun describe-source-location (spi)
  (let* ((lineno (source-pos-info-lineno spi))
         (filepos (source-pos-info-filepos spi))
         (file-scope (file-scope spi))
         (pathname (file-scope-pathname file-scope)))
  (core:fmt nil "{} filepos: {}  lineno: {}" (namestring pathname) filepos lineno)))

(defun print-compiler-message (c stream)
  (let ((msg (core:fmt nil (compiler-message-format c) (compiler-message-message c))))
    (fresh-line stream)
    (core:fmt stream ";;; {}%N" msg)
    (core:fmt stream ";;;     at {} %N" (describe-source-location (compiler-message-source-pos-info c)))))

;;; (setq core::*echo-repl-read* t)

(defmacro with-compiler-env ((&rest options) &rest body)
  "Initialize the environment to protect nested compilations from each other"
  (declare (ignore options)) ; FIXME: Find a use or remove
  `(let ((*the-module* nil)
	 (*irbuilder-function-alloca* nil)
	 (*irbuilder-function-body* nil)
	 (*generate-compile-file-load-time-values* nil)
	 (*load-time-value-holder-global-var-type* nil)
	 (*load-time-value-holder-global-var* nil)
	 (*the-module-dibuilder* nil)
	 (*readtable* *readtable*)
	 (*package* *package*))
     (with-compilation-unit () ,@body)))

(defmacro with-compilation-unit ((&rest options) &body body)
  `(do-compilation-unit #'(lambda () ,@body) ,@options))

(defun make-global-function-defs-table ()
  (make-hash-table :test #'equal))

(defun make-global-function-refs-table ()
  (make-hash-table :test #'equal :thread-safe t))

(defvar *active-protection* nil)

;;; Will be redefined in compiler-conditions.lisp
(defun do-compilation-unit (closure &key override)
  (if (or (not *active-protection*) ; we're not in a do-compilation-unit
          override) ; we are, but we're overriding it
      (let* ((*active-protection* t)
             (*compilation-messages* nil)
             (*global-function-defs* (make-global-function-defs-table))
             (*global-function-refs* (make-global-function-refs-table)))
        (unwind-protect
             (funcall closure) ; --> result*
          (compilation-unit-finished *compilation-messages*)))
      (funcall closure)))

;;; Redefined in compiler-conditions.lisp
(defun compilation-unit-finished (messages)
  ;; Add messages for global function references that were never satisfied
  (maphash (lambda (name references)
             (unless (or (fboundp name)
                         (gethash name *global-function-defs*))
               (dolist (ref references)
                 (pushnew (make-compiler-style-warning
                           :message (core:fmt nil "Undefined function {}" name)
                           :source-pos-info (global-function-ref-source-pos-info ref))
                          messages :test #'equalp))))
           *global-function-refs*)
  (dolist (m (reverse messages))
    (print-compiler-message m *error-output*)))

(defstruct (global-function-def (:type vector) :named)
  type
  name
  source-pos-info)


(defstruct (global-function-ref (:type vector) :named)
  name
  source-pos-info)

(defun known-function-p (name)
  (and (boundp '*global-function-defs*)
       (gethash name *global-function-defs*)))

(export '(known-function-p)) ; FIXME MOVE

;;; Redefined in compiler-conditions.lisp
(defun warn-redefined-function (name new-type new-origin old-type old-origin)
  (compiler-warn new-origin "The {} {} was previously defined as a {} at {}%N"
                 new-type name
                 old-type (describe-source-location old-origin)))

(defun register-global-function-def (type name)
  (when (boundp '*global-function-defs*)
    (let ((existing (gethash name *global-function-defs*))
          (cspi (ext:current-source-location)))
      (if (and existing
               ;; defmethod can define a gf, so we still want to note it-
               ;; but multiple defmethods, or a defmethod after a defgeneric,
               ;; shouldn't cause a warning.
               (not (and (eq type 'defmethod)
                         (or (eq (global-function-def-type existing) 'defgeneric)
                             (eq (global-function-def-type existing) 'defmethod)))))
          (warn-redefined-function
           name type cspi
           (global-function-def-type existing)
           (global-function-def-source-pos-info existing))
          (setf (gethash name *global-function-defs*)
                (make-global-function-def :type type
                                          :name name
                                          :source-pos-info cspi))))))

(defun register-global-function-ref (name &optional (origin (ext:current-source-location)))
  ;; Can't do (push ... (gethash ...)) because we're too early.
  (let ((existing-refs (gethash name *global-function-refs*))
        (new-ref
          (make-global-function-ref :name name :source-pos-info origin)))
    (setf (gethash name *global-function-refs*) (cons new-ref existing-refs))))

(defun function-info (env func)
  (let ((info (classify-function-lookup env func)))
    (when (eq (car info) 'core::global-function)
      (when (not *code-walking*)
        (register-global-function-ref func)))
    info))

(defun variable-info (env var)
  "Lookup the variable in the lexical environment - if not found then check if it is a special"
  (let (#+(or)(core:*environment-debug* (null (symbol-package var))))
    (let ((info (classify-variable env var)))
      (cond (info)
            (t
             ;; We treat constants pretty much identically to specials in bclasp.
             ;; It's not the best way to compile constants.
             (unless (or (ext:specialp var) (core:symbol-constantp var))
               (when (not *code-walking*)
                 (warn-undefined-global-variable nil var)))
             (cons 'ext:special-var var))))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;
;;; Stuff for taking care of the second & third return values
;;; of COMPILE, COMPILE-FILE, etc.

(defmacro with-compilation-results ((&rest options) &body body)
  `(call-with-compilation-results (lambda () ,@body) ,@options))

;;; Redefined in compiler-conditions.lisp
(defun call-with-compilation-results (thunk &rest options)
  (declare (ignore options)) ; maybe later
  (let ((*warnings-p* nil)
        (*failure-p* nil))
    (values (funcall thunk) *warnings-p* *failure-p*)))

(defmacro with-atomic-file-rename ((temp-pathname final-pathname) &body body)
  `(let ((,temp-pathname (core:mkstemp (namestring ,final-pathname))))
     #+(or)(format t "Writing to ~s~%" ,temp-pathname)
     (unwind-protect
          (progn
            ,@body)
       (progn
         #+(or)(format t "Renaming ~s to ~s~%" ,temp-pathname ,final-pathname)
         (rename-file ,temp-pathname ,final-pathname :if-exists t)))))


(defun write-bitcode (module output-path &key output-type)
  ;; Write bitcode as either .bc files or .ll files
  (cond
    ((eq output-type :object)
     (if *use-human-readable-bitcode*
         (let* ((filename (make-pathname :type "ll" :defaults (pathname output-path))))
           (with-atomic-file-rename (temp-pathname filename)
             (with-open-file (fout temp-pathname :direction :output)
               (llvm-sys:dump-module module fout))))
         (with-atomic-file-rename (temp-pathname output-path)
           (llvm-sys:write-bitcode-to-file module (namestring temp-pathname)))))
    ((eq output-type :faspll)
     (with-atomic-file-rename (temp-pathname output-path)
       (with-open-file (fout temp-pathname :direction :output)
         (llvm-sys:dump-module module fout))))
    ((eq output-type :faspbc)
     (with-atomic-file-rename (temp-pathname output-path)
       (llvm-sys:write-bitcode-to-file module (namestring temp-pathname)))))
  (let ((file-length 0))
    (with-open-file (fin output-path :direction :input)
      (setf file-length (file-length fin)))
    (if (= file-length 0)
        (error "A zero length ~a file was written" output-type))))

;;;(setq core::*echo-repl-read* t)
