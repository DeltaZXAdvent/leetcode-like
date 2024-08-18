use std::collections::VecDeque;
use std::ptr;
type Ele = i32;
type Vdq = VecDeque<Ele>;
fn reverse (deque: &mut Vdq) {
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
    data: Ele,
    next: Option<Box<Node>>
}

impl Queue {
    fn new () -> Self {
	return Queue { head: None, tail: ptr::null_mut () };
    }
    fn enqueue (&mut self, value: Ele) {
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
    fn dequeue (&mut self) -> Ele {
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

struct StackBounded {
    s: Vdq,
    maxlen: usize
}
impl StackBounded {
    fn new (l: usize) -> Self { Self { s: Vdq::new (), maxlen: l } }
    fn push (&mut self, value: Ele) { if !self.full () { self.s.push_back (value); } else { panic!(); } }
    fn pop (&mut self) -> Ele { if !self.empty () { return self.s.pop_back ().unwrap (); } else { panic!(); } }
    fn empty (&self) -> bool { self.s.is_empty () }
    fn full (&self) -> bool { self.s.len () == self.maxlen }
}

struct Queue2stacks {
    s1: StackBounded,
    s2: StackBounded
}
impl Queue2stacks {
    fn new (l: usize) -> Self {
	let ret = Self { s1: StackBounded::new (l), s2: StackBounded::new (l) };
	assert!(ret.s1.maxlen <= ret.s2.maxlen); // to make s2 able to hold all of s1
	assert!(ret.s1.maxlen >= ret.s2.maxlen); // to make all of s2 useful
	ret
    }
    fn enqueue (&mut self, value: Ele) {
	if self.s1.full () {
	    if !self.s2.empty () { panic!(); }
	    else {
		while !self.s1.empty () {
		    self.s2.push (self.s1.pop ());
		}
	    }
	}
	self.s1.push (value);
    }
    fn dequeue (&mut self) -> Ele {
	if self.s2.empty () {
	    if self.s1.empty () { panic!(); }
	    else {
		while !self.s1.empty () {
		    self.s2.push (self.s1.pop ());
		}
	    }
	}
	self.s2.pop ()
    }
    fn empty (&self) -> bool {
	self.s1.empty () && self.s2.empty ()
    }
}

#[derive (Debug)]
struct LinkedCircularQueue {
    head: *mut Nodep,
    tail: *mut Nodep
}
struct Nodep {
    data: Ele,
    next: *mut Nodep
}
impl Nodep {
    fn new (value: Ele) -> Self {
	Self { data: value, next: ptr::null_mut () }
    }
}
impl LinkedCircularQueue {
    fn new () -> Self {
	let p = Box::into_raw (Box::new (Nodep::new (0)));
	unsafe { (*p).next = p; }
	Self { head: p, tail: p }
    }
    fn enqueue (&mut self, value: Ele) {
	unsafe {
	    if (*self.tail).next == self.head {
		let p = Box::into_raw (Box::new (Nodep::new (value)));
		(*p).next = (*self.tail).next;
		(*self.tail).next = p; 
		self.tail = p;
	    } else {
		self.tail = (*self.tail).next;
		(*self.tail).data = value;
	    }
	}
    }
    fn dequeue (&mut self) -> Ele {
	if self.head == self.tail { panic!(); }
	else {
	    unsafe {
		self.head = (*self.head).next;
		return (*self.head).data;
	    }
	}
    }
    fn drop (self) {
	let p = self.head;
	let mut q = p;
	loop {
	    unsafe {
		let r = q;
		q = (*q).next;
		drop (Box::from_raw (r));
	    }
	    if q == p { break; }
	}
    }
}

fn main () {
    let mut r = LinkedCircularQueue::new ();
    for i in 0..8 {
	r.enqueue (i);
	println!("{i:?}");
	println!("{r:?}");
    }
    println!("{r:?}");
    for i in 0..8 {
	let out = r.dequeue ();
	println!("{out:?}");
	println!("{r:?}");
    }
    r.drop ();
    return;

    let mut qq = Queue2stacks::new (4);
    for i in 1..9 {
	qq.enqueue (i);
	println!("{i:?}");
    }
    for i in 1..9 {
	let out = qq.dequeue ();
	println!("{out:?}");
    }
    return;
    
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
