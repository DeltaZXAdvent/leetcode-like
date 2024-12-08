#include <iostream>
#include <chrono>
#define timer(exp) ({				\
      tt.start (string (#exp));			\
      (exp);					\
      tt.stop ();				\
    })
struct task_timer
{
  std::chrono::system_clock clock;
  std::chrono::time_point<std::chrono::system_clock> begin;
  void start (std::string task)
  {
    std::cout << "Start timer for task \"" << task << "\"? ";
    std::cin.ignore (std::numeric_limits<int>::max (), '\n');
    begin = clock.now ();
  }
  void stop ()
  {
    std::cout << "Cost time: "
	      << std::chrono::duration_cast<std::chrono::duration<double>> (clock.now () - begin).count ()
	      << std::endl;
  }
};
extern task_timer tt;
