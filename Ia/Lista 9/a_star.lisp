(defstruct node
  name
  parent
  g
  h)

(defun make-node (name &optional (parent nil) (g 0) (h 0))
  (make-node :name name :parent parent :g g :h h))

(defun f (node)
  (+ (node-g node) (node-h node)))

(defun reconstruct-path (node)
  (if (null node)
      '()
      (cons (node-name node) (reconstruct-path (node-parent node)))))

(defun get-node (name open)
  (find name open :key #'node-name :test #'equal))

(defun remove-node (node open)
  (remove node open))

(defun a-star (start goal graph heuristics)
  (labels ((neighbors (node)
             (cdr (assoc (node-name node) graph :test #'equal)))
           (heuristic (name)
             (gethash name heuristics)))

    (let ((open (list (make-node start nil 0 (heuristic start))))
          (closed '()))
      (loop
         (when (null open)
           (return nil))

         (setf open (sort open #'< :key #'f))
         (let* ((current (first open)))
           (when (equal (node-name current) goal)
             (return (reverse (reconstruct-path current))))

           (setf open (rest open))
           (push current closed)

           (dolist (neighbor (neighbors current))
             (destructuring-bind (name cost) neighbor
               (let ((g (+ (node-g current) cost)))
                 (let ((existing (or (get-node name open)
                                     (get-node name closed))))
                   (if (and existing (<= (node-g existing) g))
                       nil
                       (progn
                         (let ((h (heuristic name)))
                           (setf existing (make-node name current g h)))
                         (unless (get-node name open)
                           (push existing open))))))))))))
