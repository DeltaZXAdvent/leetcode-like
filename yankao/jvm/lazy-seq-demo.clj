(defn fib [a b] (cons a (fib b (+ a b))))
(defn integers [n] (cons n (integers (+ n 1))))
;; (assert (fib 1 2))
;; lazy-seq is macro
(assert (lazy-seq (fib 1 2)))
;; concat is function
;; (assert (concat (fib 1 2) (list 0)))

;; of course this is still to be evaluated, so stackoverflow
;; (apply concat (lazy-seq (integers 0)))
