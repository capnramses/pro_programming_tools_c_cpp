/* Example of a C program that can use high-precision timers for 3 different operating systems
Author:     Dr Anton Gerdelan.
Licence:    see LICENSE.txt in repository root.
Repository: https://github.com/capnramses/pro_programming_tools_c_cpp
*/

#include <stdio.h>
#include <stdint.h>

// includes for precision timers on differnet platforms
#ifdef _WIN32
#include <windows.h>
#include <profileapi.h>
#elif __APPLE__
#include <mach/mach_time.h>
#else
#include <sys/time.h>
#include <time.h>
#endif

uint64_t frequency = 1000000, offset;

// initialise timer variables for build's platform
void init_timer() {
#ifdef _WIN32
  {
    uint64_t counter;
    frequency = 1000; // QueryPerformanceCounter default
    QueryPerformanceFrequency( (LARGE_INTEGER*)&frequency );
    QueryPerformanceCounter( (LARGE_INTEGER*)&offset );
  }
#elif __APPLE__
  {
    mach_timebase_info_data_t info;
    mach_timebase_info( &info );
    frequency = ( info.denom * 1e9 ) / info.numer;
    offset = mach_absolute_time();
  }
#else
  {
    frequency = 1000000000; // nanoseconds
    struct timespec ts;
    clock_gettime( CLOCK_MONOTONIC, &ts );
    offset = (uint64_t)ts.tv_sec * (uint64_t)frequency + (uint64_t)ts.tv_nsec;
  }
#endif
}

// get the current time in seconds with up to nanosecond precision
double get_seconds() {
#ifdef _WIN32
  {
    uint64_t counter = 0;
    QueryPerformanceCounter( (LARGE_INTEGER*)&counter );
    return (double)( counter - offset ) / frequency;
  }
#elif __APPLE__
  {
    uint64_t counter = mach_absolute_time();
    return (double)( counter - offset ) / frequency;
  }
#else
  {
    struct timespec ts;
    clock_gettime( CLOCK_MONOTONIC, &ts );
    uint64_t counter = (uint64_t)ts.tv_sec * (uint64_t)frequency + (uint64_t)ts.tv_nsec;
    return (double)( counter - offset ) / frequency;
  }
#endif
  return 0.0;
}

int main( void ) {
  init_timer();

  double start_s = get_seconds();

  int sum = 0;
  for ( int i = 0; i < 10000; i++ ) {
    sum++;
    printf( "sum = %i\n", i );
  }

  double end_s     = get_seconds();
  double elapsed_s = end_s - start_s;
  printf( "seconds start %lf, end %lf, elapsed= %lf\n", start_s, end_s, elapsed_s );

  return 0;
}
