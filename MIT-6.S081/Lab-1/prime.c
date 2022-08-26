
// The sieve of Eratosthenes can be simulated by a pipeline of processes
// executing the following pseudocode :

//     p = get a number from left neighbor print p loop
//     : n = get a number from left neighbor if (p does not divide n)
//           send n to right neighbor

// A generating process can feed the numbers 2, 3, 4, ..., 1000
//     into the left end of the pipeline
// The first process in the line eliminates the multiples of 2,
//     the second eliminates the multiples of 3,
//     the third eliminates the multiples of 5,
//     and so on :

// Your goal is to use pipe and fork to set up the
//     pipeline.The first process feeds the numbers 2 through 35 into the
//     pipeline.

// For each prime number, you will arrange to create one process that reads from
//     its left neighbor over a pipe and writes to its right neighbor over
//     another pipe.

//     Since xv6 has limited number of file descriptors and processes,
//     the first process can stop at 35.

// Your solution is correct if it implements a pipe -
//     based sieve and produces the following output :

//     $ make qemu
//     ...
//     init: starting sh
//     $ primes
//     prime 2
//     prime 3
//     prime 5
//     prime 7
//     prime 11
//     prime 13
//     prime 17
//     prime 19
//     prime 23
//     prime 29
//     prime 31
//     $

#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  // array of all elements from 2...35
  int arr[34];
  // file descriptors for the pipeline
  int fd[2];
  // filling the array
  for (int i = 2; i <= 35; i++) {
    arr[i] = i + 2;
  }

  // starting value
  int n = 2;

  while (1) {
    if (n > 35) {
      break;
    }
    // creation of pipeline
    pipe(fd);

    // forking
    int pid = fork();

    if (pid == 0) {
      // Child Process

      // closing the write as child doesnt write to the parent
      close(fd[1]);
      // Reads the value provided by its parent
      // immediately closes its read for simplicity
      read(fd[0], n, sizeof(n));
      close(fd[0]);
    } else {
      // Parent Process

      // string that will be printed
      char* str = "prime ";

      // writes prime n to the output
      write(1, str, strlen(str));
      write(1, n, sizeof(n));

      // modifying the sieve with the n
      for (int i = n; i <= 35; i++) {
        if (i % n == 0) {
          arr[i - 2] = -1;
        }
      }

      // iterating until next prime is found
      while (arr[++n - 2] != -1) {
      }

      // Closing the read as parent doesnt read from its child
      // Writing it to the console immediately
      // Closing the write immediately
      write(fd[1], n, sizeof(n));
      close(fd[1]);

      // waiting for all the childs to finish before terminating the parent
      wait();
      exit(0);
    }
  }
  exit(0);
}