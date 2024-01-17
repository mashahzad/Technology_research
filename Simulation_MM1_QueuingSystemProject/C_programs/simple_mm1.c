//========================================================== file = mm1.c =====
//=  A simple "straight C" M/M/1 queue simulation                             =
//=============================================================================
//=  Notes: 1) This program is adapted from Figure 1.6 in Simulating          =
//=            Computer Systems, Techniqyes and Tools by M. H. MacDougall     =
//=            (1987).                                                        =
//=         2) The values of SIM_TIME, ARR_TIME, and SERV_TIME need to be     =
//=            set.                                                           =
//=---------------------------------------------------------------------------=
//=  Build: gcc mm1.c -lm, bcc32 mm1.c, cl mm1.c                              =
//=---------------------------------------------------------------------------=
//=  Execute: mm1                                                             =
//=---------------------------------------------------------------------------=
//=  Perfected by: github.com/mashahzad                                       =
//=---------------------------------------------------------------------------=
//=  History: KJC (03/09/99) - Genesis                                        =
//=============================================================================

//----- Include files ---------------------------------------------------------
#include <stdio.h>             // Needed for printf()
#include <stdlib.h>            // Needed for exit() and rand()
#include <math.h>              // Needed for log()

//----- Constants -------------------------------------------------------------
#define SIM_TIME   1.0e7       // Simulation time
//----- Function prototypes ---------------------------------------------------
double expntl(double x);       // Generate exponential RV with mean x

//===== Main program ==========================================================
void main(void)
{
  // tAKING USER INPUTS
  double ARR_TIME_USER;
  double SERV_TIME_USER;
  printf("Please enter Mean Arrival time: ");
  scanf("%lf", &ARR_TIME_USER);
  printf("Mean Arrival time is  %f\n",ARR_TIME_USER);
  printf("Please enter Mean Service time: ");
  scanf("%lf", &SERV_TIME_USER);
  printf("Mean Service time is %f\n",SERV_TIME_USER);
  double   end_time = SIM_TIME; // Total time to simulate
  double   Ta = ARR_TIME_USER;       // Mean time between arrivals // = 1/lambda
  double   Ts = SERV_TIME_USER;      // Mean service time // = 1/ mue

  double   time = 0.0;         // Simulation time
  double   t1 = 0.0;           // Time for next event #1 (arrival)
  double   t2 = SIM_TIME;      // Time for next event #2 (departure)
  unsigned long int n = 0;     // Number of customers in the system

  unsigned long int c = 0;     // Number of service completions
  double   b = 0.0;            // Total busy time
  double   s = 0.0;            // Area of number of customers in system
  double   tn = time;          // Variable for "last event time"
  double   tb;                 // Variable for "last start of busy time"
  double   x;                  // Throughput
  double   u;                  // Utilization
  double   l;                  // Mean number in the system
  double   w;                  // Mean residence time

  double   qs = 0.0;            // Area of number of customers in the queue
  double tq=0.0;				//total time in queue

  // Main simulation loop
  while (time < end_time)
  {
    if (t1 < t2)                 // *** Event #1 (arrival)
    {
      time = t1;
      s = s + n * (time - tn);   // Update area under "s" curve

	  if(n>1)
	  {
		 qs = qs + ((n-1) * (time - tn));  // Update area under "qs" curve
		 //tq=tq+((n-1) * (time - tn));  //if we want the result as W=Nq/Lamda we include this step.(with is add calculation of the queueing delay for all customers even if they didn't leave the queue).
	  }

      n++;

      tn = time;                 // tn = "last event time" for next event
      t1 = time + expntl(Ta);


      if (n == 1)
      {
        tb = time;               // Set "last start of busy time"
        t2 = time + expntl(Ts);
      }
    }
    else                         // *** Event #2 (departure)
    {
      time = t2;
      s = s + n * (time - tn);   // Update area under "s" curve

	 if(n>1)
	  {
		 qs = qs + ((n-1) * (time - tn));
		 tq=tq+((n-1) * (time - tn)); //compute the time only for the customers that complete the times in queue (i.e who leave the queue as in slide 53).
	  }

      n--;

      tn = time;                 // tn = "last event time" for next event
      c++; // Increment number of completions


      if (n > 0)
        t2 = time + expntl(Ts);
      else
      {
        t2 = SIM_TIME;
        b = b + time - tb;      // Update busy time sum if empty
      }
    }
  }

  x = c / time;   // Compute throughput rate
  u = b / time;   // Compute server utilization
  l = s / time;   // Compute mean number in system
  w = l / x;      // Compute mean residence or system time

  // Output results
  printf("=============================================================== \n");
  printf("=            *** Results from M/M/1 Simulation ***            = \n");
  printf("=============================================================== \n");
  printf("=  Total simulated time         = %3.4f sec  \n", end_time);
  printf("=============================================================== \n");
  printf("=  INPUTS: \n");
  printf("=    Mean time between arrivals = %f sec      \n", Ta);
  printf("=    Mean service time          = %f sec      \n", Ts);
  printf("=============================================================== \n");
  printf("=  OUTPUTS: \n");
  printf("=    Number of completions      = %ld cust    \n", c);
  printf("=    Throughput rate            = %f cust/sec \n", x);
  printf("=    Server utilization         = %f %%       \n", 100.0 * u);
  printf("=    Mean number in system      = %f cust     \n", l);
  printf("=    Mean residence time        = %f sec      \n", w);
  printf("=    Mean number in the queue   = %f cust      \n", qs/time);
  printf("=    Mean time in the queue     = %f sec/cust      \n", tq/(c-1));
  printf("=============================================================== \n");
}
//=============================================================================
//=  Function to generate exponentially distributed RVs using inverse method  =
//=    - Input:  x (mean value of distribution)                               =
//=    - Output: Returns with exponential RV                                  =
//=============================================================================
double expntl(double x)
{
  double z;                 // Uniform random number from 0 to 1

  // Pull a uniform RV (0 < z < 1)
  do
  {
    z = ((double) rand() / RAND_MAX);
  }
  while ((z == 0) || (z == 1));

  return(-x * log(z));
}
