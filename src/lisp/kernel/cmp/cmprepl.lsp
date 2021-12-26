;;;
;;;    File: cmprepl.lsp
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
;;
;; Insert the compiler into the repl
;;
;; Don't use FORMAT here use BFORMAT 
;; otherwise you will have problems when format.lsp is bootstrapped

#+(or)
(eval-when (:compile-toplevel :execute)
  (setq core:*debug-eval* t))

(defun trace-compiler ()
  (format t "Turning on safe-trace of compiler functions~%")
  (core:safe-trace
   cmp::irc-gep
   literal::do-literal-table
   cmp::maybe-spill-to-register-save-area
   cmp::codegen-startup-shutdown
   literal::constants-table-reference
   cmp::compile-to-module-with-run-time-table
   cmp::bclasp-compile*
   cmp::compile-with-hook
   cmp::compile-in-env
   compile
   load
   cmp::bclasp-implicit-compile-repl-form
   cmp::irc-const-gep2-64
   literal::constants-table-value
   cmp::gen-defcallback
   cmp::irc-rack-slot-address
   cmp::irc-value-frame-reference
   cmp::irc-array-dimension
   cmp::irc-header-stamp
   cmp::irc-calculate-entry
   cmp::irc-calculate-real-args
   cmp::compile-lambda-list-code
   cmp::c++-field-ptr
   cmp::layout-xep-function*
   cmp::layout-xep-function
   cmp::bclasp-compile-lambda-list-code
   cmp::layout-xep-group
   cmp::do-new-function
   literal::do-rtv
   llvm-sys:make-global-variable
   ))

(in-package :cmp)

(defparameter *print-implicit-compile-form* nil)

(defun bclasp-implicit-compile-repl-form (form &optional environment)
  (declare (core:lambda-name cmp-repl-implicit-compile))
  (when *print-implicit-compile-form* 
    (bformat t "Compiling form: %s%N" form)
    (bformat t "*active-protection* --> %s%N" cmp::*active-protection*))
  (let ((repl-name (intern (core:bformat nil "repl-form-%d" (core:next-number)) :core)))
    (funcall
     (core:with-memory-ramp (:pattern 'gctools:ramp)
       (compile-in-env `(lambda ()
                          (declare (core:lambda-name ,repl-name))
                          ,form)
                       environment
                       nil
                       *default-compile-linkage*)))))

;;;
;;; Don't install the bootstrapping compiler as the implicit compiler when compiling cleavir
;;;
;;; When debugging the aclasp/bclasp compiler
;;; you might not want implicit compilation of repl forms
;;;   the no-implicit-compilation *feature* controls this.
;;;   Don't add this feature if you want implicit compilation
;;;
;;; 
#-(or cleavir no-implicit-compilation)
(setq *implicit-compile-hook* #'bclasp-implicit-compile-repl-form)

;;#+(and clasp-min (not no-implicit-compilation))
#+(or)
(eval-when (:execute)
  ;; Load the compiler and the file compiler in aclasp
  ;; lets see if that speeds up the compilation
  (load "sys:kernel;cmp;compiler.lsp" :print t)
  (load "sys:kernel;cmp;compilefile.lsp" :print t))

#+(or)
(eval-when (:execute)
  (bformat t "!%N!%N!\n! cmprepl.lsp has (setq cmp:*debug-dump-module* t)\n!\n!\n!  TURN IT OFF AGAIN\n!\n")
  (setq cmp:*debug-dump-module* t)
  )

(defmacro with-interpreter (&body body)
  "Run the body using the interpreter"
  `(let ((core:*eval-with-env-hook* #'core:interpret-eval-with-env))
    ,@body))
