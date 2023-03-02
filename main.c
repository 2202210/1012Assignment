
#include <stdio.h>
#include <string.h>

struct process
{
    int proccessNumber;    // 0 .. n
    int arrivalTime;       // time of arrival
    int originalBurstTime; // untouched value of original
    int leftoverBurstTime; // will be used to subtract whenever work is done
    int waitTime;          // total time spent waiting
    int responseTime;      // response time
    int turnAroundTime;    // turn around time
};

void swap2(struct process *xp, struct process *yp)
{
    struct process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void arrivalTimeSorter(struct process process[], int n)
{
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (process[j].arrivalTime < process[min_idx].arrivalTime)
                min_idx = j;
        // Swap the found minimum element
        // with the first element
        swap2(&process[min_idx], &process[i]);
    }
}

void burstTimeSorter(struct process process[], int n)
{
    int i, j, min_idx;
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (process[j].leftoverBurstTime < process[min_idx].leftoverBurstTime)
                min_idx = j;
        // Swap the found minimum element
        // with the first element
        swap2(&process[min_idx], &process[i]);
    }
}

// select those processes that should go into ready queue
int readyQueueSelector(
    struct process readyQueue[], struct process allProcess[],
    int numProcesses, float currentTime)
{
    // printf("\n\n ready Queue Selector");
    int num = 0;
    for (int i = 0; i < numProcesses; i++)
    {

        if (currentTime > allProcess[i].arrivalTime || allProcess[i].arrivalTime == currentTime)
        {
            readyQueue[num] = allProcess[i];
            num++;
        }
        else
        {
        }
    }
    return num;
}

// sum of all the process
int sumReadyQueueProcesses(struct process process[], int numProcesses)
{
    int total = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        total = total + process[i].leftoverBurstTime;
    }
    return total;
}

int main()
{
    int numProcesses = 0;

    float TQ,          // time quantum
        Average_Burst; // average burst
    int numItems;      // number of items left in the readyQ

    float Sum_processes_burts, currentTime = 0;
    float avgWaitTime = 0.0,
          avgTurnAroundTime = 0.0,
          avgResponseTime = 0.0;

    printf("\n\t Enter the no of processes: ");
    scanf("%d", &numProcesses);

    struct process allProcess[numProcesses];
    struct process allProcessBackup[numProcesses];
    struct process readyQueue[numProcesses];

    // asking for the burst time & arrival time of each process
    for (int i = 0; i < numProcesses; i++)
    {
        allProcess[i].proccessNumber = i;
        printf("\n\t Enter Arrival Time for process %d :", i + 1);
        scanf("%d", &allProcess[i].arrivalTime);

        printf("\n\t Enter Burst Time for process %d :", i + 1);
        scanf("%d", &allProcess[i].originalBurstTime);
        allProcess[i].leftoverBurstTime = allProcess[i].originalBurstTime;

        allProcess[i].waitTime = -1;
        allProcess[i].responseTime = -1;
        allProcess[i].turnAroundTime = -1;
    }

    // sort process by arrival  time
    arrivalTimeSorter(allProcess, numProcesses);
    // making a copy to backup
    memcpy(allProcessBackup, allProcess, sizeof(allProcess));

    /*// check arrival time is in sequence
    printf("after sorting by arrival Time \n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("proccess id %d arrival %d burst time %d \n", allProcess[i].proccessNumber, allProcess[i].arrivalTime, allProcess[i].leftoverBurstTime);
    }*/
    // check backup working fine
    /*for (int i = 0; i < sizeof(allProcessBackup); i++)
    {
        printf("proccess id %d arrival %d burst time %d \n", allProcessBackup[i].proccessNumber, allProcessBackup[i].arrivalTime, allProcessBackup[i].leftoverBurstTime);
    }*/

    // ready Queue selector
    numItems = readyQueueSelector(readyQueue, allProcess, numProcesses, currentTime);
    /* checking ready queue to make sure only things appears as it is
    for (int i = 0; i < numItems; i++)
        printf("\n arrival timing %d \n", readyQueue[i].arrivalTime);
    */

    printf("items inside ready queue %d \n", numItems);
    // sort ready queue by burst time
    burstTimeSorter(readyQueue, numItems);
    /*    for (int i = 0; i < numItems; i++)
            printf("arrival timing %d \n", readyQueue[i].arrivalTime);
    */

    // temporary variable to hold onto the number of items
    int originalNumItems = numItems;

    while (originalNumItems == numItems)
    {

        for (int i = 0; i < numItems; i++)
        {
            Sum_processes_burts = sumReadyQueueProcesses(readyQueue, numItems);
            printf("sum of all process in ready queue %f \n", Sum_processes_burts);
            Average_Burst = Sum_processes_burts / numItems;
            printf("average burst of all process in ready queue %f \n", Average_Burst);
            TQ = 0.85 * Average_Burst;
            printf("TQ is %f \n", TQ);

            //! Execute first process
            readyQueue[i].leftoverBurstTime = readyQueue[i].leftoverBurstTime - TQ;
            currentTime = currentTime + TQ;

            if (readyQueue[i].responseTime == -1)
            {
                // response time = time at which process get cpu for the first time - arrival time
                readyQueue[i].responseTime = (currentTime - TQ) - readyQueue[i].arrivalTime;
            }

            //! re-allocate the cpu to the current process for the remaining time
            if (TQ >= readyQueue[i].leftoverBurstTime)
            {
                readyQueue[i].leftoverBurstTime = readyQueue[i].leftoverBurstTime - readyQueue[i].leftoverBurstTime;
                currentTime = currentTime + readyQueue[i].leftoverBurstTime;
                numItems = numItems - 1; // remove it
                printf("to break out from process");

                // !!NOTE: may have issues here !! potential problem
                memcpy(&readyQueue[numItems], &readyQueue[i], sizeof(readyQueue[i]));
                break; // break out
            }
            else
            {
                // send process to end of ready queue and recount
            }
        }
    }
    printf("end for now \n");

    printf("check ready queue");
    printf("process id %d", readyQueue[0].proccessNumber);
    printf("burst left over %d", readyQueue[0].leftoverBurstTime);

    printf("process id %d", readyQueue[1].proccessNumber);
    printf("burst left over %d", readyQueue[1].leftoverBurstTime);

    printf("process id %d", readyQueue[2].proccessNumber);
    printf("burst left over %d", readyQueue[2].leftoverBurstTime);

    printf("process id %d", readyQueue[3].proccessNumber);
    printf("burst left over %d", readyQueue[3].leftoverBurstTime);

    // Sum_processes_burts = sumProcesses(readyQueue, numProcesses);
    // printf("\nSum_Process_Bursts : %d \n", Sum_processes_burts);
    // Calcualte average burst
    // Average_Burst = Sum_processes_burts / numProcesses;
    // printf("Average_Burst: %d \n", Average_Burst);

    // calculate the TQ
    // TQ = 0.85 * Average_Burst;
    // printf("TQ: %d \n", TQ);

    // execute first process in the ready queue

    // calcualte the remaining time of current process

    // if remaining time less than TQ
    // do stuff
    // else:
    // send process to the end of ready queue .

    return 0;
}

// references
// structs
// https://stackoverflow.com/questions/1693853/copying-arrays-of-structs-in-c
// https://stackoverflow.com/questions/8206014/passing-an-array-of-structs-in-c
// https://stackoverflow.com/questions/18914960/how-to-iterate-over-of-an-array-of-structures

// to be used
//  https://stackoverflow.com/questions/67727355/delete-item-in-array-of-struct-that-has-char-array-member-in-c