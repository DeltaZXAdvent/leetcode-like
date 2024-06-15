# Implementing a graph in C++
## A graph can be seen as 2 * n sets
2 for each node, 1 for out, 1 for in.
You have only to synchronize these sets.
And the 2 * n sets can also be contained in a set.
(I mean probably hash tables because some sets may not even be allocated.)

## So any data structure can be seen as a possibly synchronized combination
of simple data structures. But you can optimize on them:
For example, hash tables are just optimized version of fixed-length arrays,
because some indexes may be ommited.

## But revise my model of set of sets representation of graph
The sets are basically hash tables. But hash tables also have drawbacks:
different nodes may have large differences between the numbers of their edges
In this case, a hash table that can shrink and expand may be very nice.
I suppose there is already some invented data structure for this.

## There is also a cross-linked list representation
This could be efficient in small amounts I guess?

## For current application -- solving problems
Just use std::unordered_set
