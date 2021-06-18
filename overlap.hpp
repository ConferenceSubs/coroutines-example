#ifndef OVERLAP_H
#define OVERLAP_H

// coroutine co2
#include <co2/coroutine.hpp>
#include <bits/stdc++.h> 


//Simple round-robin scheduler
void overlap(int window_size,auto work_set)
{
    // the ending parenthesis ensure initialization to 0
    co2::coroutine<>* work_buffer = new co2::coroutine<>[window_size]();
    int index = 0;

    // schedule work
    auto sched = [&work_buffer, &index, &window_size](auto work_unit){
        while(work_buffer[index]) {
            work_buffer[index]();
            if (!work_buffer[index]) {
                 break;
            }
            index = (index + 1) % window_size;
        }

        // add new work_unit to the current free slot buffer[index]
        std::cout << "Assigning coroutine scheduler slot \033[1;31m" << index << "\033[0m (window size = " << window_size << ")" << std::endl;
        work_buffer[index] = std::move(work_unit);
        index = (index + 1) % window_size;
    };

    work_set(sched);

    // tail
    int count;
    do {
        count = 0;
        for(int i=0; i<window_size; i++)
        {
            if(work_buffer[i])
            {   
                work_buffer[i]();
                if(work_buffer[i])
                    count++;
            }
        }
    } while(count);

    delete[] work_buffer;
}



#define BEGIN_BENCH(size)                                     \
   overlap(size,[&](auto _sched) {
/****/

#define END_BENCH                                             \
   });
/****/

#endif
