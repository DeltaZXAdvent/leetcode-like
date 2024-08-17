use std::collections::VecDeque;
use std::ptr;
fn reverse (deque: &mut VecDeque<i32>) {
    let mut stack = VecDeque::new ();
    loop {
	match deque.pop_front () {
	    None => break,
	    Some (e) => stack.push_back (e)
	}
    }
    loop {
	match stack.pop_back () {
	    None => break,
	    Some (e) => deque.push_back (e)
	}
    }
}

#[derive (Debug)]
struct Queue {
    head: Option<Box<Node>>,
    tail: *mut Node
}

#[derive (Debug)]
struct Node {
    data: i32,
    next: Option<Box<Node>>
}

impl Queue {
    fn new () -> Self {
	return Queue { head: None, tail: ptr::null_mut () };
    }
    fn enqueue (&mut self, value: i32) {
	let mut new_node = Box::new (Node { data: value, next: None });
	let node_ptr = &mut *new_node as *mut Node;
	if self.head.is_none () {
	    self.head = Some (new_node);
	} else {
	    unsafe {
		(*self.tail).next = Some (new_node);
	    }
	}
	self.tail = node_ptr;
    }
    fn dequeue (&mut self) -> i32 {
	if let Some (mut head) = self.head.take () {
	    let pop = head.data;
	    self.head = head.next.take ();
	    if self.head.is_none () { self.tail = ptr::null_mut (); }
	    return pop;
	} else {
	    panic!();
	}
    }
}

fn main () {
    let mut q = Queue::new ();

    for i in 1..8 {
	q.enqueue (i);
	unsafe {
	    let tail_data = (*q.tail).data;
	    println!("{i:?} {tail_data:?}");
	}
    }
    println!("{q:?}");
    for i in 1..8 {
	q.dequeue ();
	let tail = q.tail;
	if !tail.is_null () {
	    let tail_data;
	    unsafe { tail_data = (*tail).data; }
	    println!("{i:?} {tail_data:?}");
	}
    }
    for i in 1..8 {
	q.enqueue (i);
	unsafe {
	    let tail_data = (*q.tail).data;
	    println!("{i:?} {tail_data:?}");
	}
    }

    println!("{q:?}");
}
