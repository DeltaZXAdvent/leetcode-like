use std::cmp::{max,min};
// This method minimizes the calculation of distances, but is not very elegant and concise
fn smallest_distance_of_three (x: &[i32], y: &[i32], z: &[i32]) -> i32 {
    let mut i = 0;
    let mut j = 0;
    let mut k = 0;
    let mut halfm = max (max ((y[0] - x[0]).abs (), (z[0] - y[0]).abs ()), (x[0] - z[0]).abs ());
    while i < x.len () {
	while y[j] < x[i] && j < y.len () { j += 1; }
	if j == 0 {		// xi <= yj
	    while z[k] < x[i] { k += 1; }
	    if k == 0 {		// xi <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
	    }
	    else if k == z.len () {
		k -= 1;		// xi > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	    else {		// xi <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
		k -= 1;		// xi > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	}
	else if j == y.len () {
	    j -= 1;		// xi > yj
	    while z[k] < y[j] { k += 1; }
	    if k == 0 {		// yj <= zk
		halfm = min (halfm, max (z[k] - y[j], x[i] - y[j]));
	    }
	    else if k == z.len () {
		k -= 1;		// yj > zk
		halfm = min (halfm, x[i] );
	    }
	    else {		// yj <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
		k -= 1;		// yj > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	}
	else
	{			// xi <= yj
	    while z[k] < x[i] { k += 1; }
	    if k == 0 {		// xi <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
	    }
	    else if k == z.len () {
		k -= 1;		// xi > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	    else {		// xi <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
		k -= 1;		// xi > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	    j -= 1;		// xi > yj
	    while z[k] < y[j] { k += 1; }
	    if k == 0 {		// yj <= zk
		halfm = min (halfm, max (z[k] - y[j], x[i] - y[j]));
	    }
	    else if k == z.len () {
		k -= 1;		// yj > zk
		halfm = min (halfm, x[i] );
	    }
	    else {		// yj <= zk
		halfm = min (halfm, max (z[k] - x[i], y[j] - x[i]));
		k -= 1;		// yj > zk
		halfm = min (halfm, y[j] - z[k]);
	    }
	}
	i += 1;
    }
    return halfm * 2;
}
fn main () {
    println!("{}", smallest_distance_of_three (
	&[-1,0,9], &[-25,-10,10,11], &[2,9,17,30,41]));
}

