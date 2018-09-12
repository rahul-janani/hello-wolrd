#include <stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define SIZE 6

void insert();
void delete();
void *enQueue(void *arg);
void *deQueue(void *arg);

pthread_t tid1,tid2;
pthread_mutex_t elock,dlock;

int items[SIZE];
int front = -1, rear =-1,en,de,count;
char buffer[100];
int isFull()
{
  if( (front == rear + 1) || (front == 0 && rear == SIZE-1)) return 1;
  return 0;
}

int isEmpty()
{
  if(front == -1) return 1;
  return 0;
}

void *enQueue(void *arg)
{
  int n,i;
  pthread_mutex_lock(&elock);
  puts("enter how many no of elements you want to enqueue");
  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    insert();

  }
  pthread_mutex_unlock(&elock);
}
void insert()
{
  int element;

  puts("enter element");
  scanf("%d",&element);
  if(isFull()) printf("\n Queue is full!! \n");

  else
  {
    if(front == -1) front = 0;
    rear = (rear + 1) % SIZE;
    items[rear] = element;
    printf("\n Inserted -> %d\n", element);
    en++;
  }

}
void delete()
{
  int element;
 

  if(isEmpty()) 
  {
    printf("\n Queue is empty !! \n");
    return;
  } 
  else 
  {
	    element = items[front];
	    if (front == rear)
	    {
	      front = -1;
	      rear = -1;
	    } 
	    else 
	    {
	      front = (front + 1) % SIZE;

	    }
	    printf("\n Deleted element -> %d \n", element);
	    de++;
	    sprintf(&buffer[count++], "%d", element);
	 
    
  }
}


void *deQueue(void *arg)
{

  int n,i;
   FILE *fp;
  pthread_mutex_lock(&elock);
  puts("enter how many no of elements you want to dequeue");

  scanf("%d",&n);
  for(i=0;i<n;i++)
  {
    puts("enter element");
    delete();
   
    fp = fopen( "dequeue.txt" , "wb" );
    if (fp != NULL) 
    {
      printf("File created successfully!\n");
    }
    else 
    {
      printf("Failed to create the file.\n");
    }
       fputs(buffer, fp);

    fclose(fp);

  }
  pthread_mutex_unlock(&elock);

}




void display()
{
  int i;
  if(isEmpty()) printf(" \n Empty Queue\n");
  else
  {
    printf("\n Front -> %d ",front);
    printf("\n Items -> ");
    for( i = front; i!=rear; i=(i+1)%SIZE) {
      printf("%d ",items[i]);
    }
    printf("%d ",items[i]);
    printf("\n Rear -> %d \n",rear);
    printf("\n Enqueued %d messages \n",en);
    printf("\n Dequeued %d messages \n",de);
  }
}

int main()
{
  int id1,id2,ret;

  pthread_mutex_init(&elock,NULL);
  id1=pthread_create(&tid1,NULL,enQueue,NULL);
  if(id1)
  {
    fprintf(stderr,"Error - pthread_create() return code: %d\n",id1);
    exit(EXIT_FAILURE);
  }


  id2=pthread_create(&tid2,NULL,deQueue,NULL);
  if(id2)
  {
    fprintf(stderr,"Error - pthread_create() return code: %d\n",id2);
    exit(EXIT_FAILURE);
  }

  if ( pthread_join(tid1,NULL) != 0) {
    perror("pthread_join() error");
    exit(0);
  }

  if (  pthread_join(tid2,NULL) != 0) {
    perror("pthread_join() error");
    exit(0);
  }


  display();

  pthread_mutex_destroy(&elock);
  return 0;
}
