/*
John Van Gilder
Section 1
jvangilder@wisc.edu

This program displays the current time every second, separated
by a line containing a random number of '.' characters.

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/*alarmTimer is the global variable defining
  how long all alarms in this program are going
  to be set for.*/
static int alarmTimer;

void timer(int signum);

/* Main sets up the response to the alarm
   that is called later; it also sets the alarm
   to go off in one second, and keeps the program
   running until then by counting to a large
   number inside an infinite loop.*/

int main(int argc, char *argv[])
{
  /*alarmTimer is set to 1, which will correspond to
    one second for all alarms in this program.*/

  alarmTimer = 1;

  printf("Enter ^C to end the program:\n");

  struct sigaction action;
  action.sa_handler = timer;
  if(sigaction(SIGALRM, &action, NULL) != 0){
    fprintf(stderr, "sigaction failure");
    exit(0);
  }


  alarm(alarmTimer);

  /*Sets up and seeds a random number
    generator; 5 is arbitrarily chosen
    as a seed value because
    it is my favorite number.*/

  srandom(5);
  int rand;
  int lastDigit;
  int bigNumber;
  int count;
  /*The program wastes time inside this infinite loop
    counting to a randomly large number (10000000-9000000)
    while it waits for the alarm to go off.*/
  while(1){
    rand = random();
    lastDigit = rand % 10;
    bigNumber = lastDigit * 10000000;
    while(count < bigNumber){
      count++;
    }
    count = 0;
    printf(".");
   
    }
  return 0;
}
/*This displays the current time, and
  resets the alarm to go off in one second
  every time it is called.*/
void timer(int signum){

  time_t rightnow;
  time(&rightnow);

  printf("\ncurrent time is %s", ctime(&rightnow));
  alarm(alarmTimer);
}
