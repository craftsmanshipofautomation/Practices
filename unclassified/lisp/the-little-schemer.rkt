#lang racket

;defined in page 10
(define atom?
  (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

(displayln "hello world")

(displayln "page 9:")
(define l `(`(b) c d))
(define s `a)
(cons s (cdr l))

(displayln "test atom?:")
(define atom-test-1 `(1 (2 3)))
(define atom-test-2 1)
(display atom-test-1)(atom? atom-test-1)
(display atom-test-2)(atom? atom-test-2)

;lat?:
(define lat?
  (lambda (l)
    (cond
      ((null? l) #t)
      ((atom? (car l)) (lat? (cdr l)))
      (else #f))))

;member?
(define member?
  (lambda (a lat)
    (cond
      ((null? lat) #f)
      (else (or (eq? a (car lat))
                (member? a (cdr lat)))))))

(displayln "test member?:")
(member? 1 `(2 3 4 5 1 6))
(member? 1 `(2 3 4 5 6))

;rember
(define rember
  (lambda (a lat)
    (cond
      ((null? lat) lat)
      ((eq? a (car lat)) (rember a (cdr lat)))
      (else (cons (car lat) (rember a (cdr lat)))))))

(displayln "test rember:")
(rember 1 `(2 3 4 1 3 3 1 5))
(rember 1 `(1 2 3 4 1 3 4 5))
(rember 1 `(1 2 3 4 3 3 4 1))

(define firsts
  (lambda (l)
    (cond
      ((null? l) l)
      (else (cons (car (car l))
                  (firsts (cdr l)))))))

(displayln "test firsts:")
(define test-firsts
  (list
   `(1 2)
   `(2 3 4)
   `(3 4 5 6)
   `(4 5 6 7 8)
   `(5 6 7 8 9 0)
   ))
(displayln test-firsts)
(firsts test-firsts)
(define test-firsts-2
  (list
   (list `(1 2) 3)
   (list 4 5 6)
   (list (list 7) 8)))
(define test-firsts-3
  `(
   ((1 2) 3)
   (4 5 6)
   ((7) 8)))
(displayln test-firsts-2)
(firsts test-firsts-2)
(displayln test-firsts-3)
(firsts test-firsts-3)

;insertR : insert right
(define insertR
  (lambda (new old lat)
    (cond
      ((member? old lat)
       (cond
         ((eq? old (car lat)) (cons (car lat)
                                    (cons new (cdr lat))))
         (else (cons (car lat) (insertR new old (cdr lat))))))
      (else lat))))

(define insert-lat
  `(1 2 3 4 5 6))
(displayln "test insertR:")
(displayln (insertR 0 1 insert-lat))
(displayln (insertR 0 6 insert-lat))
(displayln (insertR 0 3 insert-lat))
(displayln (insertR 0 1 (quote ()))   )    

;insertL : insert left
(define insertL
  (lambda (new old lat)
    (cond
      ((null? lat) (quote ()))
      (else (cond
              ((eq? old (car lat)) (cons new lat))
              (else (cons (car lat) (insertL new old (cdr lat)))))))))

(displayln "test insertL:")
(displayln (insertL 0 1 insert-lat))
(displayln (insertL 0 6 insert-lat))
(displayln (insertL 0 3 insert-lat))
(displayln (insertL 0 1 (quote ())))

;subst
(define subst
  (lambda (new old lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((eq? old (car lat)) (cons new (cdr lat)))
              (else (cons (car lat) (subst new old (cdr lat)))))))))
;lat
(define lat0
  `(1 2 3 4 5 6))
(displayln "test subst:")
(subst 0 1 lat0)
(subst 0 2 lat0)
(subst 0 3 lat0)
(subst 0 4 lat0)
(subst 0 5 lat0)
(subst 0 6 lat0)

;subst2
(define subst2
  (lambda (new o1 o2 lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((eq? o1 (car lat)) (subst new o1 lat))
              ((eq? o2 (car lat)) (subst new o2 lat))
              (else (cons (car lat) (subst2 new o1 o2 (cdr lat)))))))))
(displayln "test subst2:")
(subst2 0 2 3 lat0)
(subst2 0 3 2 lat0)
(subst2 0 3 3 lat0)
(subst2 0 3 4 lat0)
(subst2 0 6 7 lat0)

;multiinsertR
(define multiinsertR
  (lambda (new old lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((eq? old (car lat)) (cons old
                                         (cons new
                                               (multiinsertR new
                                                            old (cdr lat)))))
              (else (cons (car lat)
                          (multiinsertR new old (cdr lat)))))))))
(displayln "test multiinsertR:")
(define lat1 `(1 1 1 1))
(displayln (multiinsertR 0 1 lat1))

;multiinsertL
(define multiinsertL
  (lambda (new old lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((eq? old (car lat)) (cons new (cons old
                                       (multiinsertL new old
                                                     (cdr lat)))))
              (else (cons (car lat)
                        (multiinsertL new old
                                      (cdr lat)))))))))

(displayln "test multiinsertL:")
(displayln (multiinsertL 0 1 lat1))

;multisubst
(define multisubst
  (lambda (new old lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((eq? old (car lat)) (cons new
                                         (multisubst new old
                                                     (cdr lat))))
              (else (cons (car lat)
                          (multisubst new old
                                      (cdr lat)))))))))
(displayln "test multisubst :")
(displayln (multisubst 0 1 `(1 2 2 1 2 2 1)))

(define add1
  (lambda (n)
    (+ n 1)))

(define sub1
  (lambda (n)
    (- n 1)))

(define zero?
  (lambda (n)
    (eq? n 0)))
;page 60
(define plus
  (lambda (lhs rhs)
    (cond
      ((zero? rhs) lhs)
      (else (plus (add1 lhs)
                 (sub1 rhs))))))
(displayln "test plus :")
(displayln (plus 100 0))
(displayln (plus 100 200))
(displayln (plus 0 100))
;page 60
(define subtract
  (lambda (lhs rhs)
    (cond
      ((zero? rhs) lhs)
      (else (subtract (sub1 lhs) (sub1 rhs))))))
(displayln "test subtract :")
(displayln (subtract 100 0))
(displayln (subtract 100 200))
(displayln (subtract 0 100))

;addtup
(define addtup
  (lambda (tup)
    (cond
      ((null? tup) 0)
      (else (plus (car tup)
                  (addtup (cdr tup)))))))

(displayln "test addtup :")
(addtup `(1 2 3 4))
(addtup `(1 1 1))
(addtup `(1))
(addtup `())
    
;multiply
(define multiply
  (lambda (lhs rhs)
    (cond
      ((zero? rhs) rhs)
      (else (plus lhs (multiply lhs (sub1 rhs)))))))
(displayln "test multiply :")
(multiply 233 10)
(multiply 0 233)
(multiply 233 0)

;exponent
(define exponent
  (lambda (base power)
    (cond
      ((eq? 1 power) base)
      (else (multiply base (exponent base (sub1 power)))))))
(displayln "test exponent :")
(exponent 2 3)
(exponent 3 2)
(exponent 1 10)


;size
(define size
  (lambda (lat)
    (cond
      ((null? lat) 0)
      (else (add1 (size (cdr lat)))))))
(displayln "test size :")
(size `())
(size `(1))
(size `(1 2 3 4 5))

;tup+
(define tup+
  (lambda (lhs rhs)
    (cond
      ((not (eq? (size lhs) (size rhs))) `())
      (else (cond
            ((null? lhs) `())
            (else (cons (plus (car lhs) (car rhs))
                        (tup+ (cdr lhs) (cdr rhs)))))))))
(displayln "test tup+ :")
(tup+ `(1 2 3) `(1 2 3))
(tup+ `(1 2) `(1 2 3))
(tup+ `(1 1 1 1 1) `(2 2 2 2 2))
(tup+ `() `())

;divide
(define divide
  (lambda (lhs rhs)
    (cond
      ((< lhs rhs) 0)
      (else
       (add1 (divide (subtract lhs rhs) rhs))))))
(displayln "test divide :")
(divide 10 2)
(divide 3 1)
(divide 20 3)

;length
(define length
  (lambda (n)
    (size n)))
(displayln "test length :")
(length `())
(length `(1))
(length `(1 2 3 4 5))

;pick
(define pick
  (lambda (n lat)
    (cond
      ((> n (length lat)) `null)
      (else (cond
              ((eq? 1 n) (car lat))
              (else (pick (sub1 n) (cdr lat))))))))

(displayln "test pick :")
(pick 2 `(1 2 3 4 5))

;rempick
(define rempick
  (lambda (n lat)
    (cond
      ((> n (length lat)) `null)
      (else (cond
              ((eq? 1 n) (cdr lat))
              (else (cons (car lat)
                          (rempick (sub1 n) (cdr lat)))))))))
(displayln "test rempick :")
(rempick 2 `(1 2 3 2 2 4 2 5))
(rempick 1 `(1 2 3 4 5))
(rempick 5 `(1 2 3 4 5))

;no-nums
(define no-nums
  (lambda (lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((number? (car lat)) (no-nums (cdr lat)))
              (else (cons (car lat)
                          (no-nums (cdr lat)))))))))
(displayln "test no-nums :")
(no-nums `(1 `a 2 `b 3 `c))              
                                         
;all-nums
(define all-nums
  (lambda (lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((number? (car lat)) (cons (car lat)
                                         (all-nums (cdr lat))))
              (else (all-nums (cdr lat))))))))
(displayln "test all-nums :")
(all-nums `(1 `a 2 `b 3 `c))      

;occur
(define occur
  (lambda (a lat)
    (cond
      ((null? lat) 0)
      (else (cond
              ((eq? a (car lat)) (add1 (occur a (cdr lat))))
              (else (occur a (cdr lat))))))))
(displayln "test occur :")
(occur 0 `(0 1 1 1 0 0 1 0 1 0))
(occur 0 `())
(occur 0 `(0 0 0))

;one?
(define one?
  (lambda (n)
    (eq? 1 n)))
(displayln "test one? :")
(one? 1)
(one? 0)

;rember*
;deal with lists of lists
(define rember*
  (lambda (a l)
    (cond
      ((null? l) `())
      (else (cond
              ((atom? (car l)) (cond
                                 ((eq? a (car l))
                                  (rember* a (cdr l)))
                                 (else (cons (car l)
                                             (rember* a (cdr l))))))
              (else (cons (rember* a (car l))
                          (rember* a (cdr l)))))))))
(displayln "test rember* :")
(define lat-396
  `(1 (1 2 3 1) (5) (((1 2 1) 1) 2 3 (3 1))))
(define lat-398
  `(1 (1 2 3 1)))
(rember* 1 lat-396)
(rember* 1 lat-398)
(rember* 1 `((1 2)))

;insertR*
(define insertR*
  (lambda (new old l)
    (cond
      ((null? l) l)
      (else (cond
              ((atom? (car l)) (cond
                                 ((eq? old (car l))
                                  (cons old
                                        (cons new
                                              (insertR* new old (cdr l)))))
                                 (else (cons (car l)
                                             (insertR* new old (cdr l))))))
              (else (cons (insertR* new old (car l))
                          (insertR* new old (cdr l)))))))))
(displayln "test insertR* :")
(insertR* 0 1 lat-396)
(insertR* 0 1 lat-398)

;occursomething
(define occursomething
  (lambda (a l)
    (cond
      ((null? l) 0)
      (else (cond
              ((atom? (car l)) (cond
                                 ((eq? a (car l))
                                  (add1 (occursomething a (cdr l))))
                                 (else (occursomething a (cdr l)))))
              (else (plus (occursomething a (car l))
                          (occursomething a (cdr l)))))))))
(displayln "test occursomething :")
(occursomething 1 lat-396)
(occursomething 1 lat-398)

;occur*
(define occur*
  (lambda (a l)
    (occursomething a l)))

;subst*
(define subst*
  (lambda (new old l)
    (cond
      ((null? l) l)
      (else (cond
              ((atom? (car l))
               (cond
                 ((eq? old (car l))
                  (cons new (subst* new old (cdr l))))
                 (else (cons (car l)
                             (subst* new old (cdr l))))))
              (else (cons (subst* new old (car l))
                          (subst* new old (cdr l)))))))))
(displayln "test subst* :")
(subst* 0 1 lat-396)
(subst* 0 1 lat-398)

;insertL*
(define insertL*
  (lambda (new old l)
    (cond
      ((null? l) l)
      (else (cond
              ((atom? (car l)) (cond
                                 ((eq? old (car l))
                                  (cons new
                                       (cons old
                                             (insertL* new old
                                                       (cdr l)))))
                                 (else (cons (car l)
                                             (insertL* new old
                                                       (cdr l))))))
              (else (cons (insertL* new old (car l))
                          (insertL* new old (cdr l)))))))))
(displayln "test insertL* :")
(insertL* 0 1 lat-396)
(insertL* 0 1 lat-398)

;member*
(define member*
  (lambda (a l)
    (cond
      ((null? l) #f)
      (else (cond
              ((atom? (car l))
               (cond
                 ((eq? a (car l)) #t)
                 (else (member* a (cdr l)))))
              (else
               (or (member* a (car l))
                    (member* a (cdr l)))))))))
(displayln "test member* :")
(member* 1 lat-396)
(member* 2 lat-396)
(member* 5 lat-396)

;leftmost
(define leftmost
  (lambda (l)
    (cond
      ((null? l) `null)
      (else (cond
              ((atom? (car l)) (car l))
              (else (leftmost (car l))))))))
(displayln "test leftmost :")
(leftmost `((potato) (chips ((with) fish) (chips))))
(leftmost `((((((((1))))))) 2))
(leftmost `(((((((())))))) 2))

;eqlist?
(define eqlist?
  (lambda (lat1 lat2)
    (cond
      ((and (lat? lat1) (lat? lat2))
       (cond
         ((and (null? lat1) (null? lat2)) #t)
         (else (cond
                 ((or (null? lat1) (null? lat2)) #f)
                 (else (and (eq? (car lat1) (car lat2))
                            (eqlist? (cdr lat1) (cdr lat2))))))))
      (else #f))))
(displayln "test eqlist? :")
(eqlist? `(1 2 3) `(1 2 3))
(eqlist? `(1 2) `(1 2 3))
(eqlist? `() `())


;debug
(define log
  (lambda (string)
    (displayln string)))


;eqlist*?
(define eqlist*?
  (lambda (l1 l2)
    (cond
      ((and (null? l1) (null? l2)) #t)
      ((or (null? l1) (null? l2)) #f)
      ((and (atom? l1) (atom? l2)) (eq? l1 l2))
      ((or (atom? l1) (atom? l2)) #f)
      ;both are non-empty lists
      (else (and (eqlist*? (car l1) (car l2))
                 (eqlist*? (cdr l1) (cdr l2)))))))
       
(displayln "test eqlist*? :")
(eqlist*? `(1 2 3) `(1 2 3))
(eqlist*? `(1 2 3) `(1 2))
(eqlist*? `(1 2) `(1 2 3))
(eqlist*? `((1) 2 3) `(1 2 3))
(eqlist*? `((1 2) 2 3) `((1 2) 2 3))
(eqlist*? `() `())
(eqlist*? `(1 2 3) `(1 (2) 3))
(eqlist*? `(1 2 3) `(1 (2 3)))
(eqlist*? `(1 2 3) `(1 ((((2)))) 3))
(eqlist*? `(1 2 (3)) `(1 2 (3 4)))
(eqlist*? 1 1)
(eqlist*? `(3) `())

;three?
(define three?
  (lambda (l)
    (cond
      ((atom? l) #f)
      ((null? (car l)) #f)
      (else (cond
              ((null? (cdr l)) #f)
              ((or (atom? (car (cdr l))) (not (null? (car (cdr l)))))
                   (not (null? (cdr (cdr l)))))
              (else #f))))))

;numbered-operator?
(define numbered-operator?
  (lambda (operator)
    (cond
      ((eq? operator (quote +)) #t)
      ((eq? operator (quote *)) #t)
      ((eq? operator (quote ^)) #t)
      (else #f))))

;numbered?
(define numbered?
  (lambda (aexp)
    ;(displayln aexp)
    (cond
      ;if there are 3
      ((three? aexp)
       (cond
         ;see if the second element belongs to expected operators
         ((numbered-operator? (car (cdr aexp)))
          (cond
            ;if the first element is a number
            ((number? (car aexp)) (numbered? (car (cdr (cdr aexp)))))
            ;else if it is list
            (else
              (and (numbered? (car aexp))
                (numbered? (car (cdr (cdr aexp))))))))
         ;else it must fail
         (else #f)))
      (else (cond
              ((number? aexp) #t)
              (else (number? (car aexp))))))))

(displayln "test three? :")
(three? `(1 2 3))
(three? `(1 (2 3) 3))
(three? `((1 2) 2 (3 4 5)))
(three? `(2 (3 4 5)))

(displayln "test numbered? :")
(numbered? 1)
(numbered? `(1))
(numbered? `(1 + 2))
(numbered? `(1 - 2))
(numbered? `(1 + (2 ^ 3)))
(numbered? `((1 * 2) + (2 ^ 3)))
(numbered? `(((1 ^ (4 * 5)) * (2 + 5)) + ((2 ^ 7) ^ 3)))

;power
(define ^
  (lambda (base power)
    (exponent base power)))

(displayln "test ^ :")
(^ 2 4)

;what-operator
(define what-operator
  (lambda (operator)
    (cond
      ((eq? operator (quote +)) +)
      ((eq? operator (quote *)) *)
      ((eq? operator (quote ^)) ^))))

;value
(define value
  (lambda (aexp)
    (cond
      ((three? aexp)
       ((what-operator (car (cdr aexp)))
        (value (car aexp))
        (value (car (cdr (cdr aexp))))))
      (else (cond
              ((number? aexp) aexp)
              ((number? (car aexp)) (car aexp))
              (else `NAN))))))
(displayln "test value :")
(value 1)
(value `(1 + 2))
(value `(1 + (2 ^ 3)))
(value `((1 * 2) + (2 ^ 3)))
(value `(((1 + (4 ^ 5)) * (2 + 5)) + ((2 ^ 7) * 3)))

;set?
(define set?
  (lambda (lat)
    (cond
      ((null? lat) #t)
      (else (cond
              ((member? (car lat) (cdr lat)) #f)
              (else (set? (cdr lat))))))))
(displayln "test set? :")
(set? `(1 2 3 4))
(set? `(1 2 3 4 1))
(set? `(1 2 3 4 4))

;makeset2
(define makeset2
  (lambda (lat)
    (cond
      ((null? lat) lat)
      (else (cond
              ((member? (car lat)
                        (cdr lat))
               (cons (car lat)
                     (rember (car lat) (makeset2 (cdr lat)))))
              (else
               (cons (car lat)
                     (makeset2 (cdr lat)))))))))
(displayln "test makeset2 :")
(makeset2 `(1 2 1 1 2 2 1 1))

;makeset
;set does not care about sequence
(define makeset
  (lambda (lat)
    (cond
      ((null? lat) lat)
      ((member? (car lat) (cdr lat))
       (makeset (cdr lat)))
      (else (cons (car lat)
                  (makeset (cdr lat)))))))
(displayln "test makeset :")
(makeset `(3 4 4 3 5 1 2 1 1 2 2 1 1))

;subset?
(define subset?
  (lambda (set1 set2)
    (cond
      ((null? set1) #t)
      (else (and (member? (car set1) set2)
                 (subset? (cdr set1) set2))))))
(displayln "test subset? :")
(subset? `(1 2) `(3 4 2 5 1))
(subset? `(1 6) `(3 4 2 5 1))

;eqset?
(define eqset?
  (lambda (set1 set2)
    (and (subset? set1 set2)
         (subset? set2 set1))))
(displayln "test eqset? :")
(eqset? `(2 1 3) `(3 2 1))

;intersect?
(define intersect
  (lambda (set1 set2)
    (cond
      ((null? set1) (quote ()))
      ((null? set2) (quote ()))
      (else (cond
              ((member? (car set1) set2)
               (cons (car set1)
                     (intersect (cdr set1) set2)))
              (else (intersect (cdr set1) set2)))))))
(displayln "test intersect :")
(intersect `(2 1 3) `(3 2 1))
(intersect `(10 23 25 2 1 3 4 6 7) `(100 3 2 1 6 7 8))
      
;union
(define union
  (lambda (set1 set2)
    (cond
      ((null? set1) set2)
      ((null? set2) set1)
      ((member? (car set1) set2)
       (union (cdr set1) set2))
      (else (cons (car set1)
                  (union (cdr set1) set2))))))
(define p
  (lambda (s)
    (displayln s)))

(p "test union :")
(union `(1 2 3) `(3 4 5))

;xxx
(define xxx
  (lambda (set1 set2)
    (p set1)
    (cond
      ((null? set1) set1)
      (else (cond
              ((member? (car set1) set2)
               (xxx (cdr set1) set2))
              (else (cons (car set1)
                          (xxx (cdr set1) set2))))))))
(p "test xxx")
(xxx `(1 2 3 4) `(2))
      
;intersectall
(define intersectall
  (lambda (l-set)
    (cond
      ((null? l-set) l-set)
      ((null? (cdr l-set)) (car l-set))
      (else (intersectall (cons (intersect (car l-set) (car (cdr l-set)))
                  (cdr (cdr l-set))))))))
(p "test intersectall :")
(intersectall `((1 2 3) (1 5 2 6) (1 7 8 3 2)))
(intersectall `((18 27 909) (1 5 2 6) (1 7 8 3 2)))

;a-pair?
(define a-pair?
  (lambda (x)
    (cond
    ((atom? x) #f)
    ((null? x) #f)
    ((null? (cdr x)) #f)
    ((null? (cdr (cdr x))) #t)
    (else #f))))
    
(p "test a-pair? :")
(a-pair? `((1 (((2)))) (3 4 5)))
(a-pair? `((1 2) 5))

;rel?
;rel stands for relation
(define rel?
  (lambda (l)
    (cond
      ((null? l) #t)
      (else (and
             (a-pair? (car l))
             (rel? (cdr l)))))))
(p "test rel? :")
(rel? `((1 2) (3 4) (5 6) (7 8)))
(rel? `((1 2 3) (3 4) (5 6) (7 8)))

(p "test firsts :")
(firsts `((1 2) (3 4) (5 6) (7 8)))

;rev
(define rev
  (lambda (p)
      (cons (car (cdr p))
            (cons (car p) (quote ())))))
(p "test rev :")
(rev `(1 2))
(rev `(1 (2 3)))

;revrel
(define revrel
  (lambda (rel)
    (cond
      ((null? rel) rel)
      (else (cons (rev (car rel))
                  (revrel (cdr rel)))))))
(p "test revrel :")
(revrel `((1 2) (3 4) (5 6) (7 8) (9 10)))

;even?
(define even?
  (lambda (n)
    (= (* (divide n 2) 2) n)))

(p "test even? :")
(even? 2)
(even? 100)
(even? 1)

;evens-only*
(define evens-only*
  (lambda (l)
    (cond
      ((null? l) l)
      ((atom? (car l))
       (cond
         ((even? (car l))
          (cons (car l) (evens-only* (cdr l))))
         (else
          (evens-only* (cdr l)))))
      (else (cons (evens-only* (car l))
                (evens-only* (cdr l)))))))

(p "test even-only* :")
(evens-only* `((1 2 4) 2 3 4))
(evens-only* `((1 2 (4 5 6 (32 45 65 76))) 2 3 4))














      


















