#include<unistd.h>
#include<stdio.h>

int LimitOfProcess;
const int CONTEXT_SWITCH_TIME = 2;

//processStatus = 1 means completed.

struct process
{
	int processId, arrivalTime, burstTime, waitingTime, turnAroundTime, priority, processStatus;
};

void prioritySorting(struct process *processQueue)

{

	struct process temp;
	for (int i = 0; i < LimitOfProcess ; i++)
	{
		for(int j = i; j < LimitOfProcess ; j++)
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

	int totalBurstTime=0, pid = 1;
	printf("\nEnter the total number of processes: ");
	scanf("%d", &LimitOfProcess);
	struct process processQueue[LimitOfProcess];

	for (int i = 0 ; i<LimitOfProcess ; i++, pid++)
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

	}

	//sorting according to priority
	prioritySorting(&processQueue);
	
	//printing of processes according to priority
	for (int i =0 ; i< LimitOfProcess ; i++)
	{
		printf("\nProcess id %d", processQueue[i].processId);
	}

	return 0;
}
