// a element occurs more than half the times
fn majority (a: &[i32]) -> Option<i32> {
    let mut b = a[0];
    let mut ct = 0;
    for i in 0..a.len () {
	if a[i] == b {
	    ct += 1;
	} else {
	    ct -= 1;
	    if ct < 0 {
		b = a[i];
		ct = 1;
	    }
	}
    }

    let mut total = 0;
    for i in 0..a.len () {
	if a[i] == b { total += 1; }
    }
    if 2 * total > a.len () { Some (b) } else { None }
}

fn main () {
    println!("{:?}", majority (&[0,5,5,3,5,7,5,5]));
    println!("{:?}", majority (&[0,5,5,3,5,1,5,7]));
}
