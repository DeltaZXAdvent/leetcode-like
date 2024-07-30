fn kth_of_two_sorted (xx: &[i32], yy: &[i32], k: usize) -> i32
{
    let mut x = &xx[..k];
    let mut y = &yy[..k];
    assert!(x.len () + y.len () >= k);
    let lx = x.len ();
    let ly = y.len ();
    x = &x[k - ly..];
    y = &y[k - lx..];
    return if x.len () != y.len () {
	if x.len () < y.len () {
	    median_of_equal_sized_sorted (x, &y[..x.len ()])
	} else {
	    median_of_equal_sized_sorted (&x[..y.len ()], y)
	}
    } else {
	median_of_equal_sized_sorted (x, y)
    }
}

fn median_of_equal_sized_sorted (x: &[i32], y: &[i32]) -> i32
{
    println!("{:?} {:?}", x, y);
    assert!(x.len () == y.len ());
    let len = x.len ();
    assert!(len > 0);
    if len == 1 {
	return if x[0] < y[0] { x[0] } else { y[0] }
    }
    let x_mid = (len - 1) / 2;
    let y_mid = len - 1 - x_mid;
    return if x[x_mid] < y[y_mid] {
	println! ("1 {} {}", x_mid, y_mid);
	median_of_equal_sized_sorted (&x[(x_mid + 1)..], &y[..y_mid])
    } else {
	println! ("2 {} {}", x_mid, y_mid);
	median_of_equal_sized_sorted (&x[..(x_mid + 1)], &y[y_mid..])
    }
}
fn main () {
    let mut x = [1,4,7,2,8,0];
    let mut y = [6,9,3,6,1,4];
    x.sort ();
    y.sort ();
    println!("x = {:?}\ny = {:?}\nkth = {}", &x, &y, kth_of_two_sorted (&x, &y, 5));
    println!("hello, world!");
}
