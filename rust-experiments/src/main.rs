use std::vec;
use kmp::*;
// returns shift
fn kmp_matcher (text: &[u8], pattern: &[u8]) -> Vec<usize> {
    let mut matches = Vec::<usize>::new ();
    let prefix = compute_prefix_function (pattern, true);
    println!("{:?}", prefix);
    let mut q = 0;
    for i in 0..text.len () {
	while q > 0 && pattern[q] != text[i] {
	    q = prefix[q - 1];
	}
	if pattern[q] == text[i] {
	    q += 1;
	}
	if q == pattern.len () {
	    matches.push (i + 1 - pattern.len ());
	    q = prefix[q - 1];
	}
    }
    matches
}
// prefix[i] is the prefix function value of i + 1
// Or another implementing method: prefix is defined on 0..pattern.len() (inclusive),
// but this makes the "proper" prefix condition intrincate?
fn compute_prefix_function (pattern: &[u8], improved: bool) -> Vec<usize> {
    let mut prefix = vec![0; pattern.len ()];
    prefix[0] = 0;
    let mut k = 0;
    for q in 1..pattern.len () {
	// q indexes which element of the prefix array
	// k is the last prefix value
	while k > 0 && pattern[k] != pattern[q] {
	    k = prefix[k - 1];
	}
	if pattern[k] == pattern[q] {
	    k += 1;
	}
	if improved && k > 0 && q + 1 < pattern.len () && pattern[k] == pattern[q + 1] {
	    prefix[q] = prefix[k - 1];
	} else {
	    prefix[q] = k;
	}
    }
    prefix
}

fn main() {
    let text = "bacbababaabcbabababaca".as_bytes ();
    let pattern = "ababaca".as_bytes ();
    println!("{:?}", kmp_find (pattern, text));
    println!("{:?}", kmp_matcher (text, pattern));
    println!("Hello, world!");
}
