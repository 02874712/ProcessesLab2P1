#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include <time.h>       /* time */

#define   MAX_COUNT  3
#define   TIME_MAX_COUNT 10

void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);                /* parent process prototype - initial ParentProcess(void) */


void  main(void)
{
  pid_t  pid;
  int status;

  int i;
  for (i = 0; i< 2; i++){
    /**parent process creates child1 : 2 processes running**/
    pid = fork(); 
    if (pid < 0){
      printf("Error: Fork Op\n");
      exit(-1);
    }
    else if (pid == 0) { /**child enters**/ 
      ChildProcess();
    }
  } 
  /**blocking call returns an address from child  - puts parent in waitng state and waits for a signal from child**/
    
  
  ParentProcess();
          
     
}

void  ChildProcess(void)
{
  /** ppid - PARENT PID, cpid - CHILD PID **/
  pid_t  ppid, cpid;  
  int i;
  cpid = getpid(); 
  ppid = getppid();

  /** INITIALIZE RANDOM GENERATOR WITH SEED = TIME(NULL)**/
  srand(time(NULL));
  int loop_count = rand()%MAX_COUNT;

  for (i = 1; i <= loop_count; i++){
    printf("Child Pid: %d is going to sleep!\n", cpid);
    sleep(rand()%TIME_MAX_COUNT);
    printf("Child Pid: %d is awake! Where is my Parent: %d\n", cpid, ppid);
  }
  
  exit(0);
}

void  ParentProcess()
{
  int i, status, child_pid;
     
  for (i = 0; i< 2; i++){
    child_pid = wait(&status);
    printf("Child Pid: %d has completed !\n", child_pid);
  }
     
  printf("*** Parent is done, Child exited with exit status | %d | ***\n", status);

}