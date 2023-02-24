
#include <stdio.h>

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

// sum of all the process
int sumProcesses(int *process)
{
    int total = 0;
    int n = sizeof(process) / sizeof(process[0]);
    for (int i = 0; i < n; i++)
    {
        total = total + process[i];
    }
    return total;
}

int main()
{

    int numProcesses = 0, timeSlice = 0, maxBurstTime = 0, temp = 0;

    int burstTime[10],       // The time left to run a particular process. will reach 0 eventually
        backupBurstTime[10], // copy of original burst time
        waitTime[10],
        turnAroundTime[10],
        responseTime[10],
        readyQueue[10]; // newly added to assigned process in here
    ;

    int TQ,                  // time quantum
        Sum_processes_burts, // total burst of all the process
        Average_Burst,       // average burst
        numItems;            // number of items left in the readyQ

    float avgWaitTime = 0.0,
          avgTurnAroundTime = 0.0,
          avgResponseTime = 0.0;

    printf("\n\t Enter the no of processes: "); // asking for number of processes
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) // asking for the burst time of each process
    {
        printf("\n\t Enter Burst Time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
        backupBurstTime[i] = burstTime[i];

        // //add to the queue
        readyQueue[i] = burstTime[i];
    }

    // ready queue is basically burstTime sort the queue
    numProcesses = sizeof(readyQueue) / sizeof(readyQueue[0]);
    selectionSort(readyQueue, numProcesses); // sorting the process

    //! important within the while loop
    while (readyQueue)

        // sumuptheprocess and return
        Sum_processes_burts = sumProcesses(readyQueue);

    // Calcualte average burst
    Average_Burst = Sum_processes_burts / numProcesses;

    // calculate the TQ
    TQ = 0.85 * Average_Burst;

    // execute first process in the ready queue

    // calcualte the remaining time of current process

    // if remaining time less than TQ
    // do stuff
    // else:
    // send process to the end of ready queue .

    return 0;
}
