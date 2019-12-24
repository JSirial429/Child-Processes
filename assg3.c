/*
 *Author:Jorge Sirias
 *Professor Caryl Rahn
 *COP 4338
 *
 *Purpose: To create a program that creates two child processes while calling the ls and grip command respectively.
 *The parent process will print the PID of both children.
 *
 *I affirm that I wrote this program myself without help from people or the internet
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

  int fd[2];

  pid_t pid;

  pipe(fd);

  //This is the first child process
  if( (pid = fork()) == 0)
  {

    dup2(fd[1], 1);  //This end of the pipe becomes stdout
    close(fd[0]);    //Close this end of the pipe to receive 
    execlp("/bin/ls", "ls", "-al", NULL);
    
    //If there is an error in calling the above function print error message
    printf("Failed to call ls -al.\n");
    exit(1); 

  }
  else
  {
    //Calls second child
    if( (pid = fork()) == 0  )
    {
      
      dup2(fd[0], 0);   //This end of the pipe becomes stdin
      close(fd[1]);     //Close this end of the pipe to send
      execlp("grep", "grep", "minishell.c", NULL);
      printf("Failed to call grep.\n");
      exit(1);
  
    }
    else
    {

      close(fd[0]);
      close(fd[1]);     
      //Parent waits for child to finish
      wait( (int *)0 );
      printf("Child 1 PID: %d done.\n", pid);
      //printf("Parent done\n");
      wait( (int *)0  );
      printf("Child 2 PID: %d done.\n", pid);
    
    }

  }

  return 0;

}
