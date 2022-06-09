/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Parameters to print_function.  */

struct char_print_parms
{
  /* The character to print.  */
  char character;
  /* The number of times to print it.  */
  int count;
};

/* Prints a number of characters to stderr, as given by PARAMETERS,
   which is a pointer to a struct char_print_parms.  */

void* char_print (void* parameters)
{
  /* Cast the cookie pointer to the right type.  */
  struct char_print_parms* p = (struct char_print_parms*) parameters;
  int i;
  
  char msg[]="thread is done";
  char *ptr_msg = malloc(strlen(msg));
  
  strcpy(ptr_msg, msg);
  
  for (i = 0; i < p->count; ++i)
    fputc (p->character, stderr);
    
  printf("\nthread (%c) - %lu\n", p->character, (unsigned long) pthread_self());

  pthread_exit((void *)ptr_msg);
}

/* The main program.  */

int main ()
{
  pthread_t thread1_id;
  pthread_t thread2_id;
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;
  char * return_thread;
  


  /* Create a new thread to print 5 x's.  */
  thread1_args.character = 'x';
  thread1_args.count = 5000;
  pthread_create (&thread1_id, NULL, &char_print, &thread1_args);

  /* Create a new thread to print 5 o's.  */
  thread2_args.character = 'o';
  thread2_args.count = 5000;
  pthread_create (&thread2_id, NULL, &char_print, &thread2_args);
  
  /* Make sure the first thread has finished.  */
  //pthread_join (thread1_id, (void *)&return_thread);
    
  //printf("\nthread1_id (%c) - %lu - %s\n", thread1_args.character, (unsigned long) thread1_id, return_thread);

  /* Make sure the second thread has finished.  */
  //pthread_join (thread2_id, (void *)&return_thread);


  //printf("\nthread2_id (%c) - %lu - %s\n", thread2_args.character, (unsigned long) thread2_id, return_thread);

  //printf("\nmain thread - %lu\n", (unsigned long) pthread_self());

  if(pthread_equal(thread1_id, thread1_id)){
    printf("\nThis is the same thread");
  }

  if(!pthread_equal(thread1_id, thread2_id)){
    printf("\nThis is the not same thread\n");
  }
  
  /* Now we can safely return.  */
  pthread_exit(NULL);
}
