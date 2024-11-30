;; does not work, if will fork
(defn fibfib-2 [a]
  (lazy-seq
   (if (<= a 1) [(list a)]
       (let [lchild (fibfib-2 (- a 1))
             rchild (fibfib-2 (- a 2))]
         [(concat (nth lchild 0) (nth rchild 0) (list a))]))))

;; works
(defn fibfib-5 [a]
  (lazy-seq
   (if (<= a 1) (list a)
       (concat (fibfib-5 (- a 1)) (fibfib-5 (- a 2)) (list a)))))

;; let is not lazy
(defn fibfib-6 [a]
   (if (<= a 1) (list a)
       (let [lchild (fibfib-6 (- a 1))
             rchild (fibfib-6 (- a 2))]
       (concat lchild rchild (list a)))))

(defn fibfib-3 [a]
  (lazy-seq
   (if (<= a 1) (list a)
       (let [lchild (fibfib-3 (- a 1))
             rchild (fibfib-3 (- a 2))]
         (concat lchild rchild (list a))))))

;; works at least the two fibfib-7 is lazy
(defn fibfib-7 [a]
  (if (<= a 1) (list a)
      (lazy-seq
       (let [lchild (fibfib-7 (- a 1))
             rchild (fibfib-7 (- a 2))]
         (concat lchild rchild (list a))))))

;; does not work, the if statement will fork
(defn fibfib-8 [a]
  (if (<= a 1) (list a)
      (concat (fibfib-8 (- a 1)) (fibfib-8 (- a 2)) (list a))))

(defn fibfib-4 [a]
   (if (<= a 1) (list a)
       (let [lchild (fibfib-4 (- a 1))
             rchild (fibfib-4 (- a 2))]
         (concat lchild rchild (list a)))))

(defn fibfib [a]
  (if (<= a 1) [(list [a a a]) a a]
      (let [lchild (fibfib (- a 1))
            rchild (fibfib (- a 2))
            n1 (+ (nth lchild 1) (nth rchild 1))
            n2 (+ (nth lchild 2) (nth rchild 2))]
        [(concat (nth lchild 0) (nth rchild 0) (list [a n1 n2]))
         n1 n2])))

;; (pr (take 25 (nth (fibfib-2 40) 0)))
;; (prn (take 10 (fibfib-3 50)))
;; (prn (take 10 (fibfib-5 50)))
;; (prn (take 10 (fibfib-7 50)))
;; (prn (take 10 (fibfib-8 50)))
;; (prn (take 10 (fibfib-6 50)))
;; (prn (take 10 (fibfib-2 50)))
;; (prn (take 10 (fibfib-4 50)))
;; (prn (type (fibfib-3 20)))
;; (pr (nth (fibfib 1000) 0))
;; (pr (nth (fibfib 10000) 0))
;; (pr (nth (fibfib 100000) 0))
;; (pr (nth (fibfib 1000000) 0))
;; (pr (nth (fibfib 10000000) 0))
