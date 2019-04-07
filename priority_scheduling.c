
#include<stdio.h>
#include<conio.h>

int num;
int numOfSwitch=0;

struct process
{
  int pid, arrivalTime, burstTime, priority, bt;
  int waitingTime, turnAroundTime, completionTime, processStatus;
  int num_of_switch;
};

void arrivalTimeSorting(struct process *processQueue)

{
	int i,j;
	struct process temp;
	for (i = 0; i < num ; i++)
	{
		for(j = i+1; j < num ; j++)
		{
			if(processQueue[j].arrivalTime < processQueue[i].arrivalTime )
			{
				temp = processQueue[j];
				processQueue[j] = processQueue[i];
				processQueue[i] = temp;
			}
		}
	}
}

void priorityScheduling(struct process *processQueue)
{
  struct process temp;
  int i,j;
  for (i = 0; i < num ; i++)
	{
		for(j = i+1; j < num ; j++)
		{
			if(processQueue[j].priority < processQueue[i].priority )
			{
				temp = processQueue[j];
				processQueue[j] = processQueue[i];
				processQueue[i] = temp;
			}
		}
	}
}

int main()
{

  printf("Enter the number of processes : ");
  scanf("%d", &num);

  struct process processQueue[num];

  int current = num, pid=0, totalBurstTime=0;
  int previous = num, time=0;
  
  int i;
  
  //taking input
  for(i =0; i< num; i++)
  {
    processQueue[i].pid = pid;
		printf("\nEnter the details for P[%d]", pid);

		//arrival time
		printf("\nEnter the arrival time : ");
		scanf("%d", &processQueue[i].arrivalTime);

		//burst time
		printf("\nEnter the burst time: ");
		scanf("%d", &processQueue[i].burstTime);
		processQueue[i].bt = processQueue[i].burstTime;

		//priority
		printf("\nEnter the priority: ");
		scanf("%d", &processQueue[i].priority);

		totalBurstTime = totalBurstTime + processQueue[i].burstTime;
		processQueue[i].processStatus = 0;
		processQueue[i].num_of_switch = 0;
		processQueue[i].completionTime = 0;
		
    pid++;
  }
  
  //sorting according to arrival time
  arrivalTimeSorting(processQueue);
  processQueue[current].priority = 1000;

  int maxArrivalTime=0;

  //for calculating max arrival time
  for(i =0; i< num ;i++)
  {
    if(processQueue[i].arrivalTime > maxArrivalTime)
    {
      maxArrivalTime = processQueue[i].arrivalTime;
    }
  }

  for(time = processQueue[0].arrivalTime; time < totalBurstTime ; )
  {

    //this part will run untill all processes arrive.
    if( time <= maxArrivalTime)
    {
      for(i = 0 ; i < num ; i++)
      {
        if(processQueue[i].arrivalTime <= time && processQueue[i].priority < processQueue[current].priority && processQueue[i].processStatus !=1)
        {
          current = i;
        }

      }

      //current and previous variables are for keeping the track of context switches.
      if(previous != current && time > processQueue[0].arrivalTime)
      {
        numOfSwitch ++;
      }

      int bt = processQueue[current].bt - 1;
      
      //this part is for the situation if some process finishes before all the processes arrive
      if(bt == 0)
      {
        processQueue[current].processStatus =1;
        time = time + processQueue[current].burstTime;
        processQueue[current].completionTime = time ;
        processQueue[current].waitingTime = processQueue[current].completionTime - processQueue[current].arrivalTime - processQueue[current].burstTime + numOfSwitch*2;
        processQueue[current].turnAroundTime = processQueue[current].completionTime - processQueue[current].arrivalTime;
      }
      
      //this part is for simple execution 
      else
      {
      	processQueue[current].completionTime  += 1;
      	processQueue[current].bt--;
	  }

      previous = current;
      time++;

    }
    
    //this section is for when all the processes has arrive and then pre-emptive priority scheduling acts like non pre-emptive priority scheduling.
    else
    {
    	
      //function to arrange processes according to the priority.
      priorityScheduling(processQueue);
      
      //section for the execution of the remaining part of the processes.
      for(i =0 ; i< num ; i++)
      {
      	current = processQueue[i].pid;
        if(processQueue[i].processStatus != 1)
        {
        	if(previous != current)
        	{	
				numOfSwitch++;	
			}
          
          time = time + processQueue[i].bt;
          processQueue[i].completionTime = time;
          processQueue[i].waitingTime = processQueue[i].completionTime - processQueue[i].arrivalTime - processQueue[i].burstTime + numOfSwitch*2;
          processQueue[i].turnAroundTime = processQueue[i].completionTime - processQueue[i].arrivalTime;
          processQueue[i].processStatus = 1;
          previous = current;
        }
      }
    }


  }

  //printing data of the processes
  printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurn Around Time\n");

  for(i =0; i< num ;i++)
  {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processQueue[i].pid, processQueue[i].arrivalTime, processQueue[i].burstTime, processQueue[i].priority, processQueue[i].waitingTime,processQueue[i].turnAroundTime);
  }


  printf("\n");
}
