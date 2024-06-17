// TODO does not work, this fucking C++ shit
// random C++ garbage
// OK, there is no need for a mapped iterator,
// because the argument for range-based for loop is normally a container not an iterator
// So what I should create is a mapped container
// So if a function takes an iterator argument,
// it will only in theory takes already defined containers if you do not define a new class for iterators.
// If we want to achieve universality, we could use function objects to represent iterators.
template<class iterator, class unary_op>
struct mapped_iterator
{
  iterator it;
  unary_op func;
  mapped_iterator (iterator it, unary_op func):
    it (it), func (func) { }
  auto operator* ()
  {
    return func (*it);
  }
  mapped_iterator& operator++ ()
  {
    ++it;
    return *this;
  }
  bool operator== (mapped_iterator<iterator, unary_op> another)
  {
    return it == another.it;
  }
  bool operator!= (mapped_iterator<iterator, unary_op> another)
  {
    return !(*this == another);
  }
};

template<class container, class unary_op>
struct mapped_container
{
  container& origin;		// maybe change to reference type?
  unary_op func;
  mapped_container (container origin, unary_op func):
    origin (origin), func (func) { }
  // using iterator = typename container::iterator;
  auto begin ()
  {
    return mapped_iterator (origin.begin (), func);
  }
  auto end ()
  {
    return mapped_iterator (origin.end (), func);
  }
  size_t size ()
  {
    return origin.size ();
  }
};

