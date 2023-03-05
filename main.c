
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A linked list (LL) node to store a queue entry
struct processNode
{
    int proccessNumber;    // 0 .. n
    int arrivalTime;       // time of arrival
    int originalBurstTime; // untouched value of original
    int leftoverBurstTime; // will be used to subtract whenever work is done
    int waitTime;          // total time spent waiting
    int responseTime;      // response time
    int turnAroundTime;    // turn around time
    int inReady;
    struct processNode *next;
    struct processNode *prev;
};

typedef struct processNode *node;

// // node copyList(node head)
// {
//     if (head == NULL)
//     {
//         return NULL;
//     }
//     else
//     {
//         // Allocate the memory for new Node
//         // in the heap and set its data
//         node newNode = (node)malloc(sizeof(struct processNode));

//         newNode->proccessNumber = head->proccessNumber;
//         newNode->arrivalTime = head->arrivalTime;
//         newNode->originalBurstTime = head->originalBurstTime;
//         newNode->leftoverBurstTime = head->originalBurstTime;
//         newNode->waitTime = head->waitTime;
//         newNode->responseTime = head->responseTime;
//         newNode->turnAroundTime = head->turnAroundTime;
//         newNode->inReady = head->inReady;

//         // Recursively set the next pointer of
//         // the new Node by recurring for the
//         // remaining nodes
//         newNode->next = copyList(head->next);

//         return newNode;
//     }
// }

node rearNode(node head)
{

    node temp, p;
    p = head;

    while (p->next != NULL)
    {
        p = p->next; // traverse the lsit until p is the last node.
    }
    temp = p;
    return temp;
}

node createNode(int num, int arrivalTime, int originalBurstTime)
{
    // printf("\ncreateNode\n");
    node temp;                                       // declare a node
    temp = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()

    temp->proccessNumber = num;
    temp->arrivalTime = arrivalTime;
    temp->originalBurstTime = originalBurstTime;
    temp->leftoverBurstTime = originalBurstTime;

    temp->waitTime = -1;
    temp->responseTime = -1;
    temp->turnAroundTime = -1;
    temp->inReady = -1; // may or may not need this

    temp->next = NULL; // make next point to NULL
    temp->prev = NULL; // make next point to NULL

    return temp;
}

// A utility function to create a new linked list node.
node addNode(int num, int arrivalTime, int originalBurstTime, node head)
{
    // printf("\naddNode\n");
    node temp, p, prev = NULL;
    temp = createNode(num, arrivalTime, originalBurstTime); // use function to create new node
    printf("\n\t check newly created node.  id: %d  arrival: %d  burst: %d \n\n", temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime);

    // check if head is empty/
    if (head == NULL)
    {
        head = temp; // assign temp as head.
    }
    else
    {
        printf("2 nodes only\n");
        p = head; // asign head to p

        // if currently there is only 2 seperate nodes:
        if (p->next == NULL)
        {
            if (p->arrivalTime > temp->arrivalTime)
            {
                temp->next = p;
                p->prev = temp;
                head = temp;
            }
            else if (temp->arrivalTime > p->arrivalTime)
            {

                p->next = temp;
                temp->prev = p;
                head = p;
            }
            else if (temp->arrivalTime == p->arrivalTime)
            {
                if (temp->leftoverBurstTime > p->leftoverBurstTime)
                {
                    p->next = temp; // if temp is bigger, place it behind
                    temp->prev = p;
                    head = p;
                }
                else
                {
                    temp->next = p;
                    temp->prev = p;
                    head = temp;
                }
            }
        }
        else
        { // already have more than 2 nodes
            printf("adding to linked list \n");
            printf("num: %d, arrival: %d, Burst:%d \n", num, arrivalTime, originalBurstTime);
            int boo = 0;

            while (p->next != NULL)
            {
                printf(" \n\n inside while loop\n");
                // printf("current p. process id:%d arrival time: %d burstime: %d\n", p->proccessNumber, p->arrivalTime, p->originalBurstTime);

                // new node is bigger than current node
                if (temp->arrivalTime > p->arrivalTime)
                {
                    printf("next");
                    prev = p;    // assign p to previous node
                    p = p->next; // traverse the list
                    // check to see if it is the end. if so, we just append
                }
                else if (temp->arrivalTime == p->arrivalTime)
                {
                    printf("arrival time are equal\n");
                    printf("new node %d ", temp->leftoverBurstTime);
                    printf("linked list node: %d \n", p->leftoverBurstTime);

                    if (temp->leftoverBurstTime > p->leftoverBurstTime)
                    {
                        printf("go next\n");
                        prev = p;
                        p = p->next;
                    }
                    else
                    {
                        printf("appending \n");
                        if (prev != NULL)
                        {                      // slightly more complicated.
                            prev->next = temp; // previous node point to newly created node.
                            temp->prev = prev;

                            temp->next = p; // newly created node points to p
                            p->prev = temp;
                            boo = 1;
                            break;
                        }
                        else if (prev == NULL) // means that p is the first item
                        {                      // simple & done.
                            temp->next = p;    // assign new node to point to p.
                            p->prev = temp;

                            head = temp; // head is now temp.
                            boo = 1;
                            break;
                        }
                    }
                }
                else // current node is bigger than p of link list
                {
                    printf("else \n");

                    if (prev != NULL)
                    { // slightly more complicated.
                        printf("prev is not null");
                        prev->next = temp; // previous node point to newly created node.
                        temp->prev = prev;

                        temp->next = p; // newly created node points to p
                        p->prev = temp;
                        boo = 1;
                        break;
                    }

                    else if (prev == NULL) // means that p is the first item
                    {                      // simple & done.
                        printf("prev is null \n");
                        printf("num: %d, arrival: %d, Burst:%d \n", p->proccessNumber, p->arrivalTime, p->leftoverBurstTime);

                        temp->next = p; // assign new node to point to p.
                        p->prev = temp;

                        head = temp; // head is now temp.
                        boo = 1;
                        break;
                    }
                }
            }

            // p is at the last node of the linked list.

            // append at the end if it is not appended in any of the cases while looping
            if (boo == 0)
            {
                printf("boo");
                if (p->arrivalTime > temp->arrivalTime)
                {
                    prev->next = temp; // 2nd last element should point to new node
                    temp->prev = prev;

                    temp->next = p; // new node should point to p.
                    p->prev = temp;

                    p->next = NULL;
                }
                else if (temp->arrivalTime > p->arrivalTime)
                {
                    p->next = temp; // normal assigning to the last
                    temp->prev = p;
                }
                // same arrival time.
                else if (temp->arrivalTime == p->arrivalTime)
                { // there should be a prev node
                    printf("temp->arrivalTime == p->arrivalTime \n");
                    if (temp->leftoverBurstTime > p->leftoverBurstTime)
                    {
                        printf("temp->leftoverBurstTime > p->leftoverBurstTime \n");
                        p->next = temp;
                        temp->prev = p;
                    }
                    else // the issue
                    {
                        printf("elsee issuess.. \n");
                        if (prev->arrivalTime == temp->arrivalTime)
                        {
                            printf("if \n");
                            if (temp->leftoverBurstTime > prev->leftoverBurstTime)
                            {

                                prev->next = temp;
                                temp->prev = prev;
                                temp->next = p;
                                p->prev = temp;
                            }
                        }
                        else if (prev->arrivalTime > temp->arrivalTime)
                        {
                            printf("else if \n");

                            prev->next = temp;
                            temp->prev = prev;
                            temp->next = p;
                            p->prev = temp;
                        }
                    }
                }
                else // both are equal
                {
                    p->next = temp; // normal assigning to the last
                    temp->prev = p;
                }
            }
        }
    }
    return head;
}

// print the linked list value
void printLinkedlist(struct processNode *p)
{
    printf("\nprintLinkedList \n");

    while (p != NULL)
    {
        printf("process number: %d   arrival time %d  burst time %d ; \n\n", p->proccessNumber, p->arrivalTime, p->originalBurstTime);
        // printf("test next %p", p->next);
        p = p->next;
    }
}

node addToReadyQ(node head, node readyQHead, int currentTime)
{
    printf("add to ready q \n\n");
    node phead = readyQHead;

    node prevNode = NULL;
    node nextNode = NULL;
    node currNode = NULL;
    currNode = head;

    while (currNode->next != NULL)
    {

        printf("id: %d, arrival time: %d", currNode->proccessNumber, currNode->arrivalTime);

        // if current time is not big enough, continue on.
        if (currNode->arrivalTime > currentTime)
        {
            printf("c1\n");
            prevNode = currNode;
            currNode = currNode->next; // go to next one
        }
        else if (currentTime > currNode->arrivalTime || currentTime == currNode->arrivalTime)
        { // smaller than or equal to currentTime

            if (phead == NULL) // if there is nothing in the readyqueue
            {
                printf("c2.1\n");
                phead = currNode;   // assign the currentnode as head.
                readyQHead = phead; // assisofgn the currentnode as head.

                if (prevNode != NULL)
                {
                    // remove the current node's existence as we moved to ready queue
                    prevNode->next = currNode->next;
                }
            }
            else
            {
                // if there is already item in the readqueue
                printf("c2.2\n");
                phead->next = currNode; // set the next to the current node
                if (prevNode != NULL)
                {
                    prevNode->next = currNode->next;
                }
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
    }

    // printf("current node? last item? %d %d ", currNode->proccessNumber, currNode->arrivalTime);
    // // check the last item in the linked list before leaving
    // if (currNode->arrivalTime == currentTime || currentTime > currNode->arrivalTime)
    // {
    //     phead->next = currNode;
    // }

    return readyQHead;
}

int main()
{

    node head = NULL, rear = NULL, temp = NULL; // declaring head, rear and temp
    int numProcesses = 0;

    float TQ,          // time quantum
        Average_Burst; // average burst
    int numItems;      // number of items left in the readyQ

    float Sum_processes_burts, currentTime = 0;
    float avgWaitTime = 0.0,
          avgTurnAroundTime = 0.0,
          avgResponseTime = 0.0;

    printf("\t Enter the no of processes: ");
    scanf("%d", &numProcesses);

    // asking for the burst time & arrival time of each process
    for (int i = 0; i < numProcesses; i++)
    {
        int arrivalTime;
        int originalBurstTime;
        printf("\n\t Enter Arrival Time for process %d :", i + 1);
        scanf("%d", &arrivalTime);

        printf("\n\t Enter Burst Time for process %d :", i + 1);
        scanf("%d", &originalBurstTime);

        // pass in data into node creator
        head = addNode(i, arrivalTime, originalBurstTime, head);
    }
    printLinkedlist(head);
    // rear = rearNode(head);
    // printf("rear node check: processnum: %d, arrivalTime %d, bursttime %d \n", rear->proccessNumber, rear->arrivalTime, rear->leftoverBurstTime);

    // node dupHead = copyList(head); // create another new linkedlist
    // node dupRear = rearNode(dupHead);
    // printLinkedlist(dupHead);

    printf("the ready queue. Time 0");
    node readyQHead = NULL; // using currentTime to put in nodes into this linkedlist
    // readyQHead = addToReadyQ(dupHead, readyQHead, currentTime);
    printLinkedlist(readyQHead);

    return 0;
}

// within main
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
// numItems = readyQueueSelector(readyQueue, allProcess, numProcesses, currentTime);
/* checking ready queue to make sure only things appears as it is
for (int i = 0; i < numItems; i++)
    printf("\n arrival timing %d \n", readyQueue[i].arrivalTime);
*/

// printf("items inside ready queue %d \n", numItems);
//  sort ready queue by burst time
// burstTimeSorter(readyQueue, numItems);
/*    for (int i = 0; i < numItems; i++)
        printf("arrival timing %d \n", readyQueue[i].arrivalTime);
*/

// temporary variable to hold onto the number of items
/*int originalNumItems = numItems;

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
} */

/*    printf("end for now \n");

    printf("check ready queue");
    printf("process id %d", readyQueue[0].proccessNumber);
    printf("burst left over %d", readyQueue[0].leftoverBurstTime);

    printf("process id %d", readyQueue[1].proccessNumber);
    printf("burst left over %d", readyQueue[1].leftoverBurstTime);

    printf("process id %d", readyQueue[2].proccessNumber);
    printf("burst left over %d", readyQueue[2].leftoverBurstTime);

    printf("process id %d", readyQueue[3].proccessNumber);
    printf("burst left over %d", readyQueue[3].leftoverBurstTime); */

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
// end of main

// not used for now

/* if to implement a queue

// The queue, front stores the front node of LL and rear stores the last node of LL
struct Queue
{
    struct processNode *front, *rear;
};
// A utility function to create an empty queue
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a key k to q
void enQueue(struct Queue *q, int k)
{
    // Create a new LL node
    struct processNode *temp = newNode(k);

    // If queue is empty, then new node is front and rear
    // both
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove a key from given queue q
void deQueue(struct Queue *q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;

    // Store previous front and move front one node ahead
    struct processNode *temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}*/

/* to fix the swapping*/
// void swap2(struct process *xp, struct process *yp)
// {
//     struct process temp = *xp;
//     *xp = *yp;
//     *yp = temp;
// }

/*
// change the following 2 to linked list
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
*/

// references
// structs
// https://stackoverflow.com/questions/1693853/copying-arrays-of-structs-in-c
// https://stackoverflow.com/questions/8206014/passing-an-array-of-structs-in-c
// https://stackoverflow.com/questions/18914960/how-to-iterate-over-of-an-array-of-structures

// to be used
//  https://stackoverflow.com/questions/67727355/delete-item-in-array-of-struct-that-has-char-array-member-in-c