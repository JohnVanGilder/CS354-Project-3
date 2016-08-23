/*
John Van Gilder
Section 1
jvangilder@wisc.edu

This program takes in two user-input integer values
and divides them together.*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*Keeps track of the number of divisions the
  program has completed*/
static int count;

void zeroHandle(int signum);
void finale(int signum);

/*Main takes in two variables from the user
  and divides them, giving the user the 
  result of the integer division and its 
  remainder. Divide-by-zero and program
  termination conditions are handled by
  other functions in this program.*/
int main(int argc, char *argv[])
{

  char in1[100];
  char in2[100];
  int num1;
  int num2;
  int ans;
  int rem;
  count = 0;

  struct sigaction divzero;
  /*Sets up the handler for the divide-by-zero 
    exception.*/
  divzero.sa_handler = zeroHandle;
  if(sigaction(SIGFPE, &divzero, NULL) != 0){
    fprintf(stderr, "sigaction failure");
    exit(0);
  }

  struct sigaction ender;
  /*Sets up the handler for the user-prompted
    program termination condition.*/
  ender.sa_handler = finale;
  if(sigaction(SIGINT, &ender, NULL) != 0){
    fprintf(stderr, "sigaction failure");
    exit(0);
  }

  /*This loop runs infinitely until the user inputs
    ctrl-C or attempts to divide by zero. It prompts the user
    for two integers, divides them, and gives the output and its
    remainder*/
  while(1){
    printf("Enter first integer: ");
    if(fgets(in1, 100, stdin) == NULL){
      fprintf(stderr, "Input read failure");
      exit(0);
    }
    printf("Enter second integer: ");
    if(fgets(in2, 100, stdin) == NULL){
      fprintf(stderr, "Input read failure");
      exit(0);
    }
    /*atoi converts a cstring to an int. If
      the cstring input isn't an integer, 
      atoi returns zero, a case not handled
      specially by this program.*/
    num1 = atoi(in1);
    num2 = atoi(in2);
    
    ans = num1/num2;
    rem = num1 % num2;
    printf("%d / %d is %d with a remainder of %d \n", num1, num2, ans, rem);
    count++;
  }


}
/*This function handles the divide-by-zero condition where the 
  second user-input integer is zero.*/
void zeroHandle(int signum){

  fprintf(stderr, "Divide By Zero Error\n");
  exit(0);
}
/*This function handles the program's termination when the user
  uses the ctrl-c interrupt to end the program.*/
void finale(int signum){
  if(count == 1){
    printf("\nThis program successfully completed 1 division operation. Have a nice day! \n");
  }else{
    printf("\nThis program successfully completed %d division operations. Have a great day! \n", count);
  }

  exit(0);
}
