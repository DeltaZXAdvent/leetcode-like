// This is wrong implementation of linked list
// A linked list should support owned nodes,
// because the referenced nodes have determined lifetime, I guess.
//
// So there must be a mechanic in Rust that adds multiple owernship to an object,
// and drop them (not by constructing the object passed with values).
// So try Option, if we could modify Option, then we could possibly drop and takes multiple ownership.
#[derive (Debug)]
struct List {
    data: i32,
    next: Option<Box<List>>,
}
impl List {
    fn del_vals (&mut self, x: i32) {
	match &mut self.next {
	    None => {},
	    Some (b) => {
		if b.data == x {
		    self.pop ();
		    self.del_vals (x);
		} else {
		    b.del_vals (x);
		}
	    },
	};
    }
    fn pop (&mut self) -> Option<Box<List>> {
	match self.next.take () {
	    None => None,
	    Some (mut m) => {
		match m.next.take () {
		    None => (),
		    Some (b) => {
			self.next = Some (b);
		    }
		};
		Some (m)
	    }
	}
    }
    // TODO if using an argument of value type, will it not be optimized?
    fn push (&mut self, mut node: Box<List>) {
	match self.next.take () {
	    None => {},
	    Some (b) => {
		node.next = Some (b);
	    },
	}
	self.next = Some (node);
    }
    // insert at the beginning
    fn new (l: &[i32]) -> Self {
	let mut ll = List { data: 0, next: None };
	for i in l {
	    ll.push (Box::new (List { data: *i, next: None }));
	}
	ll
    }

    fn len (&mut self) -> usize {
	let mut p = self;
	let mut ct = 0;
	loop {
	    match &mut p.next {
		None => break,
		Some (b) => { p = b.as_mut (); ct += 1; }
	    }
	}
	ct
    }

    // problem 20
    // Naming: one kind of rearrangement
    fn rearrange_1 (&mut self) {
	let mut right = self.right_half ();
	reverse (&mut right);
	self.merge_1 (&mut right);
    }

    fn right_half (&mut self) -> List {
	// Rust cannot support multiple mutable pointers? Except by unsafe?
	let len = self.len ();
	let remain = len - len / 2;
	let mid = self;
	return List { data: 0, next: increment (mid, remain).next.take () };
	// return List { data: 0, next: increment (&mut mid, remain) };
    }

    // Naming: one kind of merging
    fn merge_1 (&mut self, r: &mut List) {
	let mut l = self;
	loop {
	    match &mut l.next {
		None => break,
		Some (b) => { l = b.as_mut (); }
	    };
	    match r.pop () {
		None => break,
		Some (b) => { l.push (b); }
	    };
	    match &mut l.next {
		None => break,
		Some (b) => { l = b.as_mut (); }
	    };
	}
    }
}

fn increment (p: &mut List, mut num: usize) -> &mut List {
    let mut q = p;
    while num > 0 {
	match q.next {
	    None => break,
	    Some (ref mut b) => {
		q = b.as_mut ();
		num -= 1;
	    }
	}
    }
    return q;
}

fn reverse (l: &mut List) {
    let mut original = List { data: 0, next: l.next.take () };
    loop {
	match original.pop () {
	    None => break,
	    Some (b) => {
		l.push (b);
	    }
	}
    }
}

fn main () {
    let mut l = List::new (&[1,2,3,4,5,6,7]);
    reverse (&mut l);
    println!("{l:?}");
    l.rearrange_1 ();
    println!("{l:?}");
    l.del_vals (1);
    println!("{l:?}");
}
