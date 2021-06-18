# sample_coroutine

Requirements: gcc, C++14


sample_cor.cpp demonstrates the conversion of a very simple program to make use of coroutines.
The original program is a loop that iterates over a small array and increments each element twice.
Its coroutized version spawns a command-line defined number of concurrent coroutines (i.e., window_size), which distribute loop iterations among themselves. Max coroutine concurrency is min(window_size, array_num_elements). In our example, array_num_elements is hardcoded to 10.

To build and run, execute the run.sh script.
