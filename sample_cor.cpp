/*
  Sample coroutine program

  Original (non-coroutine) code:

  int main (int argc, char* argv[]) {
    int *arr = (arr *)calloc(10,sizeof(int));
    for (int i = 0; i < 10; i++) {
        *(arr+i)+=1;
        *(arr+i)+=1;
    }
    return 0;
  }

*/

#include <iostream>

#include "./overlap.hpp"


int main (int argc, char* argv[]) {

  if (argc != 2) { 
	std::cerr << "Usage:" << argv[0] << " <window size>" << std::endl;
	exit(1);
  }


  int wsize = atoi(argv[1]);

  int *arr = (int *)calloc(10,sizeof(int));

  BEGIN_BENCH(wsize)	//macro defined in overlap.hpp

    for (int i = 0; i < 10; i++) {

      /*
        Create a coroutine
        The code it will run is the part enclosed in {}
        Variables are passed to the coroutine like in a normal function
        The coroutine is passed to _sched, our scheduling function, found in overlap.hpp
      */

      _sched(([&]() CO2_BEG(co2::coroutine<>, (arr,i)) 
      {
	//the used coroutine library will, by default, start executing this task as soon as it is spawned.
	//To facilitate comprehension, we suspend this task immediately, so it first registers
	//itself with the scheduling logic before it starts actually executing
        CO2_AWAIT(co2::suspend_always{}); //coroutine suspends itself
	std::cout << "Starting new task " << i << "...\n";
	std::cout << "\tIncrementing array's \033[1;31melement " << i << "\033[0m for the \033[1;31mfirst\033[0m time." << std::endl;
        *(arr+i)+=1;

        // YIELD - cycle to next waiting coroutine
	std::cout << "Pausing task " << i << "...\n";
        CO2_AWAIT(co2::suspend_always{});
	std::cout << "Back to task " << i << "...\n";

	std::cout << "\tIncrementing array's \033[1;31melement " << i << "\033[0m for the \033[1;31msecond\033[0m time." << std::endl;
        *(arr+i)+=1;

	 std::cout << "Task " << i << " finished.\n";
      } 
      CO2_END)());

    }

  END_BENCH     //macro defined in overlap.hpp

  std::cout << "\nFinal array contents:\n=====================" << std::endl;
  for (int i=0; i<10; i++)
    std::cout << arr[i] << std::endl;

  return 0;
}

