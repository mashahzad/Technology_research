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
#define SIM_TIME   1.0e6       // Simulation time
//#define TRANSMISSION_RATE 1.0e7  // R = 10mbps
#define TRANSMISSION_RATE 1.0e4  // R = 10kbps

//----- Function prototypes ---------------------------------------------------
double expntl(double x);       // Generate exponential RV with mean x

//===== Main program ==========================================================
void main(void)
{
  // tAKING USER INPUTS
  double ARR_TIME_USER;
  double SERV_TIME_USER;
  double QUEUE_MAX_USER;
  printf("Please enter Mean Arrival time: ");
  scanf("%lf", &ARR_TIME_USER);
  printf("Mean Arrival time is  %f sec\n",ARR_TIME_USER);
  printf("Please enter Mean Service time: ");
  scanf("%lf", &SERV_TIME_USER);
  printf("Mean Service time is %f sec\n",SERV_TIME_USER);
  printf("Please enter Max Queue size in Kbytes: ");
  scanf("%lf", &QUEUE_MAX_USER);
  printf("Max Queue size is %.2f KBytes\n",QUEUE_MAX_USER);

  double   end_time = SIM_TIME; // Total time to simulate
  double   Ta = ARR_TIME_USER;       // Mean time between arrivals
  double   Ts = SERV_TIME_USER;      // Mean service time

  double   time = 0.0;         // Simulation time
  double   t1 = 0.0;           // Time for next event #1 (arrival)
  double   t2 = SIM_TIME;      // Time for next event #2 (departure)
  double n = 0.0;              // Data of Packets in system in kbytes

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
  double queue = 0.0;
  double drop = 0; // in bytes
  double transmission_rate_Bps = TRANSMISSION_RATE/8; // = x bytes per second
  double packet_size_bytes = SERV_TIME_USER*transmission_rate_Bps; // = bytes per packet
  double packet_size_Kbytes = packet_size_bytes/1000; // = Kilo bytes per packet
  double queue_size = QUEUE_MAX_USER; // queue size limit for given transmission and packet size (how much data fills queue)
  double queue_data = 0.0;
  double total_data =0.0;

  // Main simulation loop
  while (time < end_time)
  {
    if (t1 < t2)                 // *** Event #1 (arrival)
    {
      time = t1;
      //s = s + (n * (time - tn)/packet_size_Kbytes);   // Update area under "s" curve
      s = s + ( n * (time - tn)); // Update area under "s" curve

	  if(n > 1)
	  {
	      if(n <= (queue_size/packet_size_Kbytes)+1 && queue_data<=queue_size) //total packets data in system = cusomers in queue + 1 in service
            {
                total_data = total_data + queue_data;
                //queue = ((n-packet_size_Kbytes)/packet_size_Kbytes); //number in queue = Number in system minus one in service
                qs = qs + (n-1) * (time - tn);  // Update area under "qs" curve
		 //tq=tq+((n-1) * (time - tn));  //if we want the result as W=Nq/Lamda we include this step.(with is add calculation of the queueing delay for all customers even if they didn't leave the queue).
            }
            else
            {
                drop = drop + (n - queue_size/packet_size_Kbytes); //data packets dropped
                n = ((queue_size/packet_size_Kbytes)+1); //drop excess packets
                queue_data = queue_size;
                total_data = total_data + queue_data;

            }
	  }

      //n++;
      n++;
      queue_data = queue_data + (packet_size_Kbytes + expntl(Ta/1000)); // Generating random sized random packets for processing
      total_data = total_data + queue_data;
      // ==========UNCOMMENT BELOW LINES AND SET SIM_TIME TO 1.0e2 FOR OBSERVING VALUES=========
      //printf("Queue data at # %f is %f:::",n,queue_data);
      //printf("Elements in queue = %f \n", n-1);

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
      //s = s + (n * (time - tn)/packet_size_Kbytes);   // Update area under "s" curve
      s = s + (n * (time - tn));

	 if(n > 1)
	  {
		 //qs = qs + ((n-packet_size_Kbytes) * (time - tn));
		 qs = qs + ((n-1) * (time - tn));  // Update area under "qs" curve
		 tq = tq +(n-1) * (time - tn); //compute the time only for the customers that complete the times in queue (i.e who leave the queue as in slide 53).
	  }

      n--;
      queue_data = queue_data - 1.25;

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
  printf("=    Transmission Rate R        = %.2f bits per sec     \n", TRANSMISSION_RATE);
  printf("=    Transmission Rate R        = %.2f Bytes per sec     \n", TRANSMISSION_RATE/8);
  printf("=    Maximum Queue Size Kbytes  = %.2f Kbytes     \n", QUEUE_MAX_USER);
  printf("=    Following output when packet size is variable \n");
  printf("=============================================================== \n");
  printf("=  OUTPUTS: \n");
  printf("=    Number of completions      = %d packets    \n", c);
  printf("=    Throughput rate            = %f packet/sec \n", x);
  printf("=    Server utilization         = %f %%       \n", 100*u);
  printf("=    Mean number in system      = %f packet     \n", l);
  printf("=    Mean residence time        = %f sec      \n", w);
  printf("=    Mean number in the queue   = %f packet      \n", qs/time);
  printf("=    Mean time in the queue     = %f sec/packet      \n", tq/(c-1));
  printf("=    Packets dropped            = %.0f packets     \n",drop);
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
