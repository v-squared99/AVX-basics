#include"cprofiler.h"
/*
 *     Sakshama Ghoslya,
 *     Hyderabad, India
 */
/***************** HOW TO USE THIS FILE TO PROFILE YOUR CODE *****************
*
*   Make sure you run your code to multiple iterations (usually 1000+) to get
*   better results. Iter = number of iterations. (Keep default = 1)
*   Call wnNrExeTimeX86Intel(0, Iter) just before your code
*   Call wnNrExeTimeX86Intel(1, Iter) just after your code
*
******************************************************************************/

/*
RDTSC is a current time-stamp counter variable ,which is a 64-bit variable, into registers (edx:eax).
TSC(time stamp counter) is incremented every cpu tick (1/CPU_HZ)
*/
unsigned long long int getCycles()
{
 unsigned int low;
 unsigned int high;
 __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));

 return ((unsigned long long int)high << 32) | low;
}

static unsigned long long int startClock, endClock;
unsigned long long int executedCycles;
static struct timespec startTime, endTime;

void wnNrExeTimeX86Intel(char flag, int Iter)
{
 if (flag == 0)
 {
  /* To get the current time */
  clock_gettime(CLOCK_REALTIME, &startTime);

  /* to get the current cycles */
  startClock = getCycles();
 }

 else if (flag == 1)
 {
  /* To get the current time */
  clock_gettime(CLOCK_REALTIME, &endTime);

  /* to get the current cycles */
  endClock = getCycles();

  /* Number of iterations can't be negative */
  if (Iter <= 0)
  {
   Iter = 1;
   printf("\nWarning: Number of iterations should be positive. Results may not be correct");
  }

  /* Total executed cycles */
  executedCycles = endClock - startClock;

  /* Execution time in milli seconds
  * Time in milli seconds = (time in seconds: tv_sec)*1000 + (time in nano seconds: tv_nsec)/1000000
  */
  double exeTime = ((endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_nsec - startTime.tv_nsec) / (1.0 * 1000000));

  /* Execution time in nano seconds */
  double exeTimeNano = exeTime * 1000000;

  executedCycles = executedCycles/Iter;
  exeTimeNano = exeTimeNano/Iter;

  double exeTimeMicro = exeTimeNano/1000;

  /* Print total executed cycles */
  printf("\nProgram executed cycles = %llu cycles", executedCycles);

  /* print total execution time */
  printf("\nProgram execution time  = %0.0f nano secs | %0.3f micro secs\n", exeTimeNano,exeTimeMicro);

  /* Print CPU clock frequency */
  printf("\nSystem clock frequency = %f GHz", executedCycles / exeTimeNano);

  /* Print CPU clock duration */
  printf("\nSystem clock duration = %f Nano secs\n", exeTimeNano / executedCycles);
 }
}
