
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A linked list (LL) node to store a queue entry
struct processNode
{
    int proccessNumber;      // 0 .. n
    float arrivalTime;       // time of arrival
    float originalBurstTime; // untouched value of original
    float leftoverBurstTime; // will be used to subtract whenever work is done
    float waitTime;          // total time spent waiting
    float responseTime;      // response time
    float turnAroundTime;    // turn around time
    float firstTime;
    float exitTime;
    int inReady;
    struct processNode *next;
    struct processNode *prev;
};

typedef struct processNode *node;
node head = NULL, rear = NULL, temp = NULL; // declaring head, rear and temp
node readyQHead = NULL;
node endHead = NULL;
float currentTime = 0;

node addToReadyQ2(float currentTime)
{
    printf("\tadd to ready q \n");
    node Pheadprev = NULL;
    node Qheadprev = NULL;

    node Phead = NULL;
    node Qhead = NULL;

    if (head != NULL)
    {
        Phead = head;
    }

    if (readyQHead != NULL)
    {
        Qhead = readyQHead;
    }

    // printf("current Time: %f", currentTime);
    while (Phead != NULL)
    {

        printf("process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

        // put to Qhead
        if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
        {
            printf("current time: > || == \n");

            // add to queue
            if (Qhead == NULL)
            {
                printf("Qhead == NULL \n"); // no previous node
                if (Pheadprev == NULL)
                {
                    printf("pheadprev == NUL \n");
                    // assign the link list to node.
                    Qhead = Phead;

                    // shift phead
                    Phead = Phead->next; // go to next node
                    Phead->prev = NULL;  // removing the 2node previous
                    head = Phead;        // assigning the second node as the head now

                    Qhead->next = NULL; // removing the previous head's next so it is single node
                    readyQHead = Qhead;

                    printf("Qhead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Qhead->proccessNumber, Qhead->arrivalTime, Qhead->originalBurstTime, Qhead, Qhead->prev, Qhead->next);

                    printf("Head process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", head->proccessNumber, head->arrivalTime, head->originalBurstTime, head, head->prev, head->next);

                    printf("next \n\n;");
                    printf("PHead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

                    // break;
                }
                // got previous node
                else if (Pheadprev != NULL)
                {
                    printf("Pheadprev != Null \n");
                    Pheadprev->next = Phead->next; // assign previous's node next to next next node

                    while (Qhead->next != NULL) // move to the end
                    {
                        Qhead = Qhead->next;
                    }
                    Qheadprev = Qhead;
                    Qhead->next = Phead; // assign the last node of Qhead to the node

                    Qhead = Qhead->next; // shift to node that have been placed.
                    Phead = Phead->next; // move the phead's next

                    Phead->prev = NULL;
                    Qhead->next = NULL; // clear the node's next
                    Qhead->prev = Qheadprev;
                    // break;
                }
            }
            // temporary not working on it
            else if (Qhead != NULL)
            {
                printf("Qhead != Nulll\n");

                if (Pheadprev != NULL)
                {
                    printf("Pheadprev != NULL \n");
                    printf("num: %d, arrival: %f, Burst:%f \n", Pheadprev->proccessNumber, Pheadprev->arrivalTime, Pheadprev->leftoverBurstTime);

                    Pheadprev->next = Phead->next;

                    while (Qhead->next != NULL) // move to the end
                    {
                        Qhead = Qhead->next;
                    }
                    Qheadprev = Qhead;
                    Qhead->next = Phead;

                    Qhead = Qhead->next;
                    if (Phead->next != NULL)
                    {
                        // Pheadprev = Phead;
                        Phead = Phead->next;
                        Phead->prev = NULL;
                    }
                    else
                    {
                        // Pheadprev = Phead;
                        Phead = Phead->next;
                    }
                    Qhead->next = NULL;
                    Qhead->prev = Qheadprev;
                }
                // no previous node in the linked list
                else if (Pheadprev == NULL)
                {
                    printf("Pheadprev == NULL\n");
                    while (Qhead->next != NULL) // move to the end
                    {
                        Qhead = Qhead->next;
                    }
                    Qheadprev = Qhead;
                    Qhead->next = Phead;

                    Qhead = Qhead->next;
                    if (Phead->next != NULL)
                    {
                        // Pheadprev = Phead;
                        Phead = Phead->next;
                        Phead->prev = NULL;
                    }
                    else
                    {
                        // Pheadprev = Phead;
                        Phead = Phead->next;
                    }

                    Qhead->next = NULL;
                    Qhead->prev = Qheadprev;
                }
                else
                {
                    printf("??");
                    printf("moving ahead first \n");
                    // Pheadprev = Phead;
                    Phead = Phead->next;
                }
            }
        }

        // move forward
        else if (currentTime < Phead->arrivalTime)
        {
            printf(" current node> CT \n");
            Pheadprev = Phead;
            Phead = Phead->next;
        }
    }

    printf("end of first while loop\n");

    node tempP = NULL;

    tempP = Pheadprev;

    if (tempP != NULL)
    {
        printf("tempP not null");
        while (tempP->prev != NULL)
        {
            tempP = tempP->prev;
        }
        printf("tempP process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", tempP->proccessNumber, tempP->arrivalTime, tempP->originalBurstTime, tempP, tempP->prev, tempP->next);
        head = tempP;
    }
    else if (tempP == NULL)
    {
        printf("is NULL");
        return readyQHead;
    }
    else
    {
        printf("need to return");
        return readyQHead;
    }

    printf("return v2");
    return readyQHead;
}

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

    temp->firstTime = -1;
    temp->waitTime = -1;
    temp->responseTime = -1;
    temp->turnAroundTime = -1;
    temp->inReady = -1; // may or may not need this
    temp->exitTime = -1;

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
    printf("\n\t check newly created node.  id: %d  arrival: %f  burst: %f \n\n", temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime);

    // check if head is empty/
    if (head == NULL)
    {
        head = temp; // assign temp as head.
    }
    // at least 2 nodes
    else
    {
        printf("At least 2 node exist\n");
        p = head; // asign head to p

        // if currently there is only 2 seperate nodes:
        if (p->next == NULL)
        {
            printf("2 Nodes only");
            // check the arrival time and assign accordingly
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

        // already have more than 2 nodes
        else
        {
            printf("more than 2 nodes \n");
            printf("adding to linked list \n");
            printf("num: %d, arrival: %d, Burst:%d \n", num, arrivalTime, originalBurstTime);

            while (p != NULL)
            {
                printf(" \n\n inside while loop\n");
                // printf("current p. process id:%d arrival time: %d burstime: %d\n", p->proccessNumber, p->arrivalTime, p->originalBurstTime);

                // new node is bigger than current node, go to next node in linked list
                if (temp->arrivalTime > p->arrivalTime)
                {
                    printf("next");
                    prev = p;    // assign p to previous node
                    p = p->next; // traverse the list
                    // check to see if it is the end. if so, we just append
                }

                // new node is same as current node
                else if (temp->arrivalTime == p->arrivalTime)
                {
                    printf("arrival time are equal\n");
                    printf("new node's leftover burst time %f ", temp->leftoverBurstTime);          // compare the leftover burst time
                    printf("linked list node's left over burst time: %f \n", p->leftoverBurstTime); // compare the leftover burst time

                    // if bigger, go to next node.
                    if (temp->leftoverBurstTime > p->leftoverBurstTime)
                    {
                        printf("check if can go next\n");

                        if (p->next == NULL)
                        {
                            printf("next is null, appending now");
                            p->next = temp;
                            temp->prev = p;
                            p = p->next;
                            break;
                        }
                        else
                        {
                            printf("next not null, append later");
                            prev = p;
                            p = p->next; // become null
                        }
                    }
                    // if smaller or the same, append
                    else
                    {
                        printf("appending\n");
                        // if there is a prevous node
                        if (prev != NULL)
                        {
                            prev->next = temp; // previous node point to newly created node.
                            temp->prev = prev;

                            temp->next = p; // newly created node points to p
                            p->prev = temp;
                            break;
                        }
                        // if there is no previous node [could be the first node of linked list]
                        else if (prev == NULL)
                        {
                            temp->next = p; // assign new node to point to p.
                            p->prev = temp;

                            head = temp; //  Set the head to temp.
                            break;
                        }
                    }
                }

                // new node is smaller than curret node
                else
                {
                    printf("else: new node is smaller than current node \n");

                    if (prev != NULL)
                    {
                        printf("prev is not null.. \n");
                        prev->next = temp; // previous node point to newly created node.
                        temp->prev = prev;

                        temp->next = p; // newly created node points to p
                        p->prev = temp;

                        // printf("\t process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n\n", prev->proccessNumber, prev->arrivalTime, prev->originalBurstTime, prev, prev->prev, prev->next);

                        // printf("\t process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n\n", temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime, temp, temp->prev, temp->next);

                        // printf("\t process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n\n", p->proccessNumber, p->arrivalTime, p->originalBurstTime, p, p->prev, p->next);

                        break;
                    }

                    else if (prev == NULL) // means that p is the first item
                    {
                        printf("prev is null.. \n");
                        printf("num: %d, arrival: %f, Burst:%f \n", p->proccessNumber, p->arrivalTime, p->leftoverBurstTime);

                        temp->next = p; // assign new node to point to p.
                        p->prev = temp;

                        head = temp; // head is now temp.
                        break;
                    }
                }
            }
        }
    }
    return head;
}

// print the linked list value
void printLinkedlist(struct processNode *p)
{
    printf("printLinkedList \n");

    while (p != NULL)
    {
        printf("\t process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", p->proccessNumber, p->arrivalTime, p->leftoverBurstTime, p, p->prev, p->next);
        // printf("test next %p", p->next);
        p = p->next;
    }
    printf("end of printLinkedList\n");
    return;
}

int numOfNodes()
{
    printf("num of nodes");
    node Qhead = readyQHead;
    int totalNodes = 0;
    while (Qhead != NULL)
    {
        totalNodes = totalNodes + 1;
        Qhead = Qhead->next;
    }

    return totalNodes;
}

int sumReadyQueueProcesses(node readyQHead)
{
    printf("sumReadyQueue Processes");
    node Qhead = readyQHead;
    int TotalBurstTime = 0;
    while (Qhead != NULL)
    {
        TotalBurstTime = TotalBurstTime + Qhead->leftoverBurstTime;
        Qhead = Qhead->next;
    }
    return TotalBurstTime;
}

int main()
{

    int numProcesses = 0;

    float TQ,          // time quantum
        Average_Burst; // average burst
    int numItems;      // number of items left in the readyQ

    float currentTime = 0;
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
        printLinkedlist(head);
    }
    printLinkedlist(head);

    // printf("\n to be processed by the ready queue. Time Now: %f \n", currentTime);

    addToReadyQ2(currentTime); // adding process

    while (head != NULL)
    // while (readyQHead != NULL)
    {

        printf("\n\n\n\n\n\ncurrent time %f \n", currentTime);
        addToReadyQ2(currentTime); // adding process

        printf("head \n");
        printLinkedlist(head);

        printf("\n\n\n\nreadyQ\n");
        printLinkedlist(readyQHead);

        rear = rearNode(readyQHead);
        rear->next = readyQHead;
        readyQHead->prev = rear;

        printf("now:");
        float Sum_processes_burts = 0;
        Sum_processes_burts = sumReadyQueueProcesses(readyQHead);
        printf("sum processes_burst %f", Sum_processes_burts);
        int totalNodes = 0;
        totalNodes = numOfNodes();

        Average_Burst = Sum_processes_burts / (float)totalNodes;
        TQ = Average_Burst * 0.85;

        printf("sum of process bursts: %f, num of nodes: %d, average Burst: %f, TQ: %f", Sum_processes_burts, totalNodes, Average_Burst, TQ);

        node qhead = readyQHead;

        while (qhead != NULL)
        {

            if (qhead->firstTime == -1)
            {
                printf("putting first time");
                qhead->firstTime = currentTime;
            }

            // first subtract
            if (qhead->leftoverBurstTime > TQ)
            {
                printf("qhead->leftoverBurstTime > TQ");
                qhead->leftoverBurstTime = qhead->leftoverBurstTime - TQ;
                currentTime = currentTime + TQ;
                // Checking to subtract or not
                if (TQ > qhead->leftoverBurstTime || TQ == qhead->leftoverBurstTime)
                {
                    currentTime = currentTime + qhead->leftoverBurstTime;

                    qhead->leftoverBurstTime = qhead->leftoverBurstTime - qhead->leftoverBurstTime;

                    qhead->exitTime = currentTime;
                    // !! To check for new processes
                    node endHeadDup = endHead;
                    if (endHeadDup == NULL)
                    {
                        endHeadDup = qhead;
                        qhead = qhead->next;
                        qhead->prev = NULL;
                        endHeadDup->next = NULL;
                    }
                    else if (endHeadDup != NULL)
                    {
                        while (endHeadDup->next != NULL)
                        {
                            endHeadDup = endHeadDup->next;
                        }
                        endHeadDup->next = qhead;
                        qhead = qhead->next;
                        qhead->prev = NULL;
                        endHeadDup = endHeadDup->next;
                        endHeadDup->next = NULL;
                    }
                    break;
                }
                else
                {
                    // go to next process;
                    qhead = qhead->next;
                }
            }
            else if (TQ > qhead->leftoverBurstTime || TQ == qhead->leftoverBurstTime)
            {
                printf("if TQ > = leftover");
                currentTime = currentTime + qhead->leftoverBurstTime;
                qhead->leftoverBurstTime = qhead->leftoverBurstTime - qhead->leftoverBurstTime;

                qhead->exitTime = currentTime;

                // !! To check for new processes
                node endHeadDup = endHead;
                if (endHeadDup == NULL)
                {
                    endHeadDup = qhead;
                    qhead = qhead->next;
                    qhead->prev = NULL;
                    endHeadDup->next = NULL;
                }
                else if (endHeadDup != NULL)
                {
                    while (endHeadDup->next != NULL)
                    {
                        endHeadDup = endHeadDup->next;
                    }
                    endHeadDup->next = qhead;
                    qhead = qhead->next;
                    qhead->prev = NULL;
                    endHeadDup = endHeadDup->next;
                    endHeadDup->next = NULL;
                }
                break;
            }
        }

        // currentTime = currentTime + 1;
    }

    // readyQHead = addToReadyQ2(currentTime); // adding process

    printf("\n end");

    return 0;
}

// macos
//  clang main.c -o main
//  open main