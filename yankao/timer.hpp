#include <iostream>
#include <chrono>
#define timer(exp) ({				\
      tt.start (string (#exp));			\
      (exp);					\
      tt.stop ();				\
    })
using namespace std;
struct task_timer
{
  chrono::system_clock clock;
  chrono::time_point<chrono::system_clock> begin;
  void start (string task)
  {
    cout << "Start timer for task \"" << task << "\"?" << endl;
    cin.ignore (numeric_limits<int>::max (), '\n');
    begin = clock.now ();
  }
  void stop ()
  {
    cout << "Cost time: "
	 << chrono::duration_cast<chrono::duration<double>> (clock.now () - begin).count ()
	 << endl;
  }
};
task_timer tt;
