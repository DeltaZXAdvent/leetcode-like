/**
 * Test for dining philosophers solutions
 * with user-defined semaphores
 *
 * n philosophers with n chopsticks and m bowls (n >= 3 and m >= 1)
 *
 * TODO
 * - possibly use condition variables to implement semaphores
 */
static_assert (__cplusplus <= 201703L);
#include <mutex>
#include <condition_variable>
#include <cstdio>
#include <cassert>
#include <memory>
#include <thread>
#include <random>
#include <chrono>
#include <stdexcept>
#include <vector>
#include <type_traits>
extern "C" {
#include <semaphore.h>
}
using namespace std;

struct semaphore
{
  sem_t sem;
  semaphore (unsigned value)
  { assert (!sem_init (&sem, 0, value)); }
  semaphore (): semaphore (1) { }
  ~semaphore ()
  { assert (!sem_destroy (&sem)); }
  void wait ()
  { assert (!sem_wait (&sem)); }
  void signal ()
  { assert (!sem_post (&sem)); }
  semaphore (const semaphore&) = delete;
  semaphore (semaphore&&) = delete;
};

/**
 * C++ holy crap, ok, still reasonable
 */
static_assert (!is_copy_constructible_v<semaphore>
	       && !is_move_constructible_v<semaphore>);

// Not needed, printf is inherently thread-safe, see the C standard
// template<class... Args>
// void locked_printf (const char *format, Args... args)
// {
//   static mutex lock;
//   lock_guard<mutex> guard (lock);
//   printf (format, args...);
// }

size_t my_rand (size_t min, size_t max)
{
  static mt19937 rnd(std::time(nullptr));
  return uniform_int_distribution<>(min, max)(rnd);
}

void
dining_philosophers_pairwise_lock (size_t n,
				   size_t m)
{
  assert (n >= 3 && m >= 1);
  vector<semaphore> chopsticks (n);
  semaphore bowls (m);
  vector<thread> philosophers (n);
  size_t total = 0;
  for (size_t i = 0; i < n; ++i)
    {
      philosophers[i] = thread ([&] (size_t i) {
	while (true)
	  {
	    printf ("%d thinks\n", i);
	    this_thread::sleep_for (chrono::milliseconds (my_rand (400, 800)));
	    size_t first = i % 2 ? (i + 1) % n : i,
	      second = i % 2 ? i : (i + 1) % n;
	    chopsticks[first].wait ();
	    chopsticks[second].wait ();
	    bowls.wait ();
	    printf ("%d eats, eat count: %d\n", i, ++total);
	    this_thread::sleep_for (chrono::milliseconds (my_rand (400, 800)));
	    bowls.signal ();
	    chopsticks[second].signal ();
	    chopsticks[first].signal ();
	  }
      }, i);
    }
  for (size_t i = 0; i < n; ++i)
    philosophers[i].join ();
}
void
dining_philosophers_restrict_number (size_t n,
				     size_t m)
{
  assert (n >= 3 && m >= 1);
  vector<semaphore> chopsticks (n);
  semaphore bowls (min (m, n - 1));
  vector<thread> philosophers (n);
  size_t total = 0;
  for (size_t i = 0; i < n; ++i)
    {
      philosophers[i] = thread ([&] (size_t i) {
	while (true)
	  {
	    printf ("%d thinks\n", i);
	    this_thread::sleep_for (chrono::milliseconds (my_rand (400, 800)));
	    chopsticks[i].wait ();
	    printf ("%d picked fork %d\n", i, i);
	    chopsticks[(i + 1) % n].wait ();
	    printf ("%d picked fork %d\n", i, (i + 1) % n);
	    bowls.wait ();
	    printf ("%d eats, eat count: %d\n", i, ++total);
	    this_thread::sleep_for (chrono::milliseconds (my_rand (400, 800)));
	    bowls.signal ();
	    chopsticks[(i + 1) % n].signal ();
	    chopsticks[i].signal ();
	    printf ("%d released fork %d, %d\n", i, i, (i + 1) % n);
	  }
      }, i);
    }
  for (size_t i = 0; i < n; ++i)
    philosophers[i].join ();
}

/**
 * Simple test result:
 * pairwise lock seems faster
 */
int main (int argc, char *argv[])
{
  size_t n = 100, m = 50;
  assert (argc == 2);
  string type (argv[1]);
  if (type == "0")
    dining_philosophers_pairwise_lock (n, m);
  else if (type == "1")
    dining_philosophers_restrict_number (n, m);
  else
    {
      fprintf (stderr, "invalid type\n");
      return 1;
    }
  return 0;
}
