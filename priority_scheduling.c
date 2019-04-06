#include<unistd.h>
#include<stdio.h>

int Limit;
const int CONTEXT_SWITCH_TIME = 2;


struct process
{
	int processId, arrivalTime, burstTime, waitingTime, turnAroundTime, priority;

	//processStatus = 1 means completed.
	int processStatus, completionTime, num_of_switch;
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

        for (int i = 0 ; i < Limit ; i++)
        {
                if(processQueue[i].arrivalTime <= time && processQueue[currentProcess].priority > processQueue[i].priority && processQueue[i].processStatus != 1)
                {
                        currentProcess = i;
                }
        }

        //printf("%d", processQueue[currentProcess].processId);
        return processQueue[currentProcess].processId;
}

int main()
{

	int totalBurstTime=0, pid = 0, maxArrivalTime=0;

	printf("\nEnter the total number of processes: ");
	scanf("%d", &Limit);
	struct process processQueue[Limit+1];

	//variable for selecting among the process which will be executed next
	int currentProcess = Limit, previous = Limit;
	processQueue[Limit].priority = 1,000;

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

		totalBurstTime += processQueue[i].burstTime;
		processQueue[i].processStatus = 0;
		processQueue[i].num_of_switch = 0;

	}

	//sorting according to arrival time
	arrivalTimeSorting(processQueue);

	printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurn Around Time");

	for(int i =0; i< Limit; i++)
	{
	        if(processQueue[i].arrivalTime > maxArrivalTime)
	                {
	                        maxArrivalTime = processQueue[i].arrivalTime;
			}
	}

	

	for(int time = 0; time < totalBurstTime; )
	{

	        currentProcess = scheduler(processQueue, time, currentProcess);

		if(previous != currentProcess)
		{
			processQueue[previous].num_of_switch++;
		}

	        time += processQueue[currentProcess].burstTime;

	        processQueue[currentProcess].currentTime = time;

	        //Waiting time = Start of execution time - arrival time + Context Switch time
	        processQueue[currentProcess].waitingTime = processQueue[currentProcess].currentTime - processQueue[currentProcess].arrivalTime - processQueue[currentProcess].burstTime + (processQueue[currentProcess].num_of_switch*CONTEXT_SWITCH_TIME);

	        //Turn around time = Time of completion of execution - Arrival time
	        processQueue[currentProcess].turnAroundTime = processQueue[currentProcess].currentTime - processQueue[currentProcess].arrivalTime;

		if(processQueue[currentProcess].currentTime == processQueue[currentProcess].burstTime)
		{
			processQueue[currentProcess].processStatus = 1;
		}

	        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", processQueue[currentProcess].processId+1, processQueue[currentProcess].arrivalTime, processQueue[currentProcess].burstTime, processQueue[currentProcess].priority, processQueue[currentProcess].waitingTime, processQueue[currentProcess].turnAroundTime);

		previous = currentProcess;
	}


	printf("\n");

	return 0;
}
