// This is wrong implementation of linked list
// A linked list should support owned nodes,
// because the referenced nodes have determined lifetime, I guess.
//
// So there must be a mechanic in Rust that adds multiple owernship to an object,
// and drop them (not by constructing the object passed with values).
// So try Option, if we could modify Option, then we could possibly drop and takes multiple ownership.
#[derive (Debug)]
enum ListNode<'a> {
    Cons (i32, &'a mut Box<ListNode<'a>>), // the reference is similar to a modifiable pointer
    Nil
}
// Using Option is also OK, to challenge I tried copying the example for the Rust Book,
// to use Nil; though this is a little bit illogical, Because a valid node should have some data
//
// To support empty lists, and avoid head nodes, let's use a reference to a ListNode for the list type;
// This reference is also mutable, otherwise the first node cannot be popped;
// Or don't use a function, use a method;
// 
use ListNode::{Cons, Nil};
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
    // Idk other ways to do this, a temporary value must be bound to a variable to make it last longer?
    let mut l0 = Box::new (Nil);
    let mut l1 = Box::new (Cons (1, &mut l0));
    let mut l2 = Box::new (Cons (2, &mut l1));
    let mut l3 = Box::new (Cons (3, &mut l2));
    let mut l4 = Box::new (Cons (1, &mut l3));
    let mut l5 = Box::new (Cons (1, &mut l4));
    let mut l = &mut l5;
    let mut ll = &mut l;
    del_vals (ll, 1);
    
    println!("{ll:?}");		// errors
}
