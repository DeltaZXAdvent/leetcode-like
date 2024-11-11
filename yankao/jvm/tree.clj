;; unnamed package import??
;; or you can't use the name for it is seen as unqualified
(import Tree)
;; Let's ignore the following statements:
;; There are supposedly two methods of generating the lazy seq.
;; One is to only pop when the node's children is generated
;; The other is to pop every nodes and keep the nodes whose children is not yet generated in the closure
;; The second is chosen.
(defn list-only [x]
  (if (nil? x) () (list x)))
(defn tree-level-order [tree]
  (assert (instance? Tree tree))
  ((fn f [daughters mothers]
     (concat daughters
             (if (empty? mothers)
               ()
               (lazy-seq
                (let [moms (concat (list-only (.lchild (first mothers)))
                                   (list-only (.rchild (first mothers))))]
                  (f moms (concat (rest mothers) moms)))))))
   (list-only tree) (list-only tree)))

;; (pr (tree-level-order Tree/exampleTree))
(defn tree-reverse-level-order [tree]
  (reverse (tree-level-order tree)))

(defrecord tree-stats [tree pct qct])
;; possibly nil
(defn tree-common-ancestor [tree p q]
  (assert (and (instance? Tree tree)
               (not (nil? tree))
               (instance? String p)
               (instance? String q)))
  (first
   (filter
    (fn [stats] (cond
                  (and (= (.name (.-tree stats)) p)
                       (= (.name (.-tree stats)) q))
                  (and (> (.-pct stats) 1) (> (.-qct stats) 1))
                  (= (.name (.-tree stats)) p)
                  (and (> (.-pct stats) 1) (> (.-qct stats) 0))
                  (= (.name (.-tree stats)) q)
                  (and (> (.-pct stats) 0) (> (.-qct stats) 1))
                  true (and (> (.-pct stats) 0) (> (.-qct stats) 0))))
    ((fn f [tree p q]
       (if (nil? tree) ()
           (let [left (lazy-seq (f (.lchild tree) p q))
                 right (lazy-seq (f (.rchild tree) p q))]
             (concat left right
                     (lazy-seq
                      (list (->tree-stats
                             tree
                             (+ (if (empty? left) 0
                                    (.-pct (last left))) ;I guess the left and right lazy-seq will continue to be kept in memory after it is traversed because in this form it is not yet evaluated, there is solution to this, but too troublesome
                                (if (empty? right) 0
                                    (.-pct (last right)))
                                (if (= (.name tree) p)
                                  1 0))
                             (+ (if (empty? left) 0
                                    (.-qct (last left)))
                                (if (empty? right) 0
                                    (.-qct (last right)))
                                (if (= (.name tree) q)
                                  1 0)))))))))
     tree p q))))
(defn test-tree-common-ancestor []
  (let [r1 (tree-common-ancestor
            Tree/exampleTree "d" "c")
        r2 (tree-common-ancestor
            Tree/exampleTree "b" "d")]
    ;; (prn r1 r2 (.name (.-tree r1)) (.name (.-tree r2)))
    (assert
     (and (= (.name (.-tree r1)) "a")
          (= (.name (.-tree r2)) "e")))))
(test-tree-common-ancestor)

(defn tree-full-nlr-to-level [nlr]
  (let [h (Math/round (/ (Math/log (+ 1 (count nlr)))
                         (Math/log 2)))
        n (Math/round (Math/pow 2 h))]
    (pr h n)
    (assert (and (= n (+ 1 (count nlr)))
                 (> h 0)))
    (loop [v (vec (repeat n 0))
           i 1
           nlr nlr]
      (prn v i nlr)
      (if (= i (- n 1))
        (assoc v i (first nlr))
        (recur (assoc v i (first nlr))
               (cond (< (* 2 i) n)
                     (* 2 i)
                     (< (+ 1 (* 2 i)) n) ;actually not needed
                     (+ 1 (* 2 i))
                     true
                     (+ 1
                        (loop [i i]
                          (if (= 0 (mod i 2)) i
                              (recur (quot i 2))))))
               (rest nlr))))))


(defn tree-full-level-to-lrn [level]
  (let [h (Math/round (/ (Math/log (count level))
                         (Math/log 2)))
        n (Math/round (Math/pow 2 h))]
    (assert (and (= n (count level))
                 (> h 0)))
    ;; reverse lrn that is nrl
    ;; (prn h n (count level))
    (loop [lrn ()
           i 1]
      (prn lrn i)
      (if (= i (/ n 2))
        (cons (nth level i) lrn)
        (recur (cons (nth level i) lrn)
               (cond (< (+ 1 (* 2 i)) n)
                     (+ 1 (* 2 i))
                     (< (* 2 i) n)      ;actually not needed
                     (* 2 i)
                     true
                     (- (loop [i i]
                          (if (= 1 (mod i 2)) i
                              (recur (quot i 2))))
                        1)))))))

(tree-full-level-to-lrn
 (tree-full-nlr-to-level (list "a" "b" "d" "e" "c" "f" "g")))

(defn tree-similar [tl tr]
  (if (or (nil? tl) (nil? tr))
    (and (nil? tl) (nil? tr))
    (do
      (prn tl tr)
      (assert (and (instance? Tree tl)
                  (instance? Tree tr)))
      (and (tree-similar (.lchild tl) (.lchild tr))
          (tree-similar (.rchild tl) (.rchild tr))))))

(assert (tree-similar
         Tree/exampleTree
         (new Tree
              ""
              (new Tree
                   ""
                   (new Tree
                        ""
                        nil
                        (new Tree
                             ""
                             nil
                             nil))
                   (new Tree
                        ""
                        nil
                        nil))
              (new Tree
                   ""
                   nil
                   nil))))

(assert (not (tree-similar
              Tree/exampleTree
              (new Tree
                   ""
                   (new Tree
                        ""
                        (new Tree
                             ""
                             nil
                             (new Tree
                                  ""
                                  nil
                                  nil))
                        (new Tree
                             ""
                             nil
                             nil))
                   (new Tree
                        ""
                        nil
                        (new Tree
                             ""
                             nil
                             nil))))))


;; (pr (map (fn [record] (.name (nth record 0)))
;;          (tree-common-ancestors Tree/exampleTree "c" "f")))
(pr (map (fn [tree] (.name tree))
         (tree-reverse-level-order Tree/exampleTree)))
