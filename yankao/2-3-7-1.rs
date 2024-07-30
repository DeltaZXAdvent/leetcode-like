/*
 * RUST BEGINNER
 */
// Rust pointers
// Requirements:
// 1. Lifetime of Box? What if in multithreaded programs it's deleted?
//    We don't consider the lifetime of Box?
// 2. Access elements of a tuple?
//    tuple.0
// 3. Access fields in a struct?
//    How do I which enumeration it is?
//    enum.discriminant ()
// 4. Box type to normal type?
//    *b

// The first element cannot be deleted
#[derive (Debug)]
enum ListNode<'a> {
    Cons (i32, &'a mut Box<ListNode<'a>>),
    Nil
}
// type List<'a> = &'a ListNode;
// struct List<'a> { first: &'a ListNode }
use ListNode::{Cons, Nil};
use std::ops::Deref;
use std::ops::DerefMut;
fn del_vals<'a> (list: &'a mut &'a mut Box<ListNode<'a>>, x: i32) {
    match &mut ***list {
	Cons (v, b) => {
	    if *v == x {
		*list = *b;
		del_vals (list, x);
		println!("yes");
	    } else {
		del_vals (b, x);
		println!("no");
	    }
	},
	Nil => {},
    }
}
fn main () {
    let mut l0 = Box::new (ListNode::Nil);
    let mut l1 = Box::new (ListNode::Cons (1, &mut l0));
    let mut l2 = Box::new (ListNode::Cons (2, &mut l1));
    let mut l3 = Box::new (ListNode::Cons (3, &mut l2));
    let mut l4 = Box::new (ListNode::Cons (1, &mut l3));
    let mut l5 = Box::new (ListNode::Cons (1, &mut l4));

    let mut L = &mut l5;
    let mut LL = &mut L;
    del_vals (LL, 1);
    // println!("{L:?}");
    println!("hel");
}
