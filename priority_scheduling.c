#include<unistd.h>
#include<stdio.h>

int Limit;
const int CONTEXT_SWITCH_TIME = 2;

//processStatus = 1 means completed.

struct process
{
	int processId, arrivalTime, burstTime, waitingTime, turnAroundTime, priority;
	int processStatus, remainingTime;
};

void arrivalTimeSorting(struct process *processQueue)

{

	struct process temp;
	for (int i = 0; i < Limit ; i++)
	{
		for(int j = i+1; j < Limit ; j++)
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

int scheduler(struct process *processQueue, int time, int currentProcess)
{

        for (int i = 0 ; i < Limit+1 ; i++)
        {
                if(processQueue[i].arrivalTime <= time && processQueue[currentProcess].priority > processQueue[i].priority && processQueue[i].processStatus != 1)
                {
                        currentProcess = i;
                }
        }
        return processQueue[currentProcess].processId;	
}

int main()
{

	int totalBurstTime=0, pid = 1, maxArrivalTime=0;
	
	printf("\nEnter the total number of processes: ");
	scanf("%d", &Limit);
	struct process processQueue[Limit+1];

	//variable for selecting among the process which will be executed next
	int currentProcess = Limit+1;
	processQueue[Limit+1].priority = 1,000;

	for (int i = 0 ; i<Limit ; i++, pid++)
	{

		processQueue[i].processId = pid;
		printf("\nEnter the details for P[%d]", pid);

		//arrival time
		printf("\nEnter the arrival time : ");
		scanf("%d", &processQueue[i].arrivalTime);

		//burst time
		printf("\nEnter the burst time: ");
		scanf("%d", &processQueue[i].burstTime);

		//priority
		printf("\nEnter the priority: ");
		scanf("%d", &processQueue[i].priority);
		
		totalBurstTime += processQueue[i].priority;	

	}

	//sorting according to arrival time
	arrivalTimeSorting(processQueue);
	
	for(int i =0; i< Limit; i++)
	{
	        if(processQueue[i].arrivalTime > maxArrivalTime)
	                {
	                        maxArrivalTime = processQueue[i].arrivalTime;
			}
	}
	
	printf("%d", maxArrivalTime);
	 

	/*for(int time = 0; time < totalBurstTime; )
	{
	        currentProcess = scheduler(processQueue, time, currentProcess);
	        
	        processQueue[currentProcess].burstTime--;	
	}*/

	return 0;
}
