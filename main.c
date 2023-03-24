
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
    float firstTime;         // first time that the process get cpu
    float exitTime;          // time at which the node is finished
    struct processNode *next;
    struct processNode *prev;
};

typedef struct processNode *node;    // defining as node
node head = NULL, temp = NULL;       // declaring process head of linked list, rear and temp
node readyQHead = NULL, rear = NULL; // queue head of linked list and rear
node endHead = NULL;                 // last link list to store all the finished processes
float currentTime = 0;               // the time passed since process started
int numProcesses = 0;                // number of process inserted by user
int loop = 0;                        // to be used as boolean to control looping
int contextSwitch = 0;

// print the link list at the end of the process. Will return aveverage time of response, wait and turnaround time
void printEndLinkedlist(struct processNode *p)
{
    float avgWaitTime = 0;
    float avgTurnAroundTime = 0;
    float avgResponseTime = 0;

    node temp = p;

    if (p == NULL)
    {
    }
    else
    {

        if (temp->next != NULL)
        {
            while (temp->next != p)
            {
                if (temp->next == temp)
                {
                    break;
                }
                if (temp->next == NULL)
                {
                    break;
                }
                temp->responseTime = temp->firstTime - temp->arrivalTime;

                temp->turnAroundTime = temp->exitTime - temp->arrivalTime;
                temp->waitTime = temp->turnAroundTime - temp->originalBurstTime;

                avgWaitTime = temp->waitTime + avgWaitTime;
                avgResponseTime = temp->responseTime + avgResponseTime;
                avgTurnAroundTime = avgTurnAroundTime + temp->turnAroundTime;

                printf("\t process number: %d   arrival time %f , original burst: %f, waitTime:%f, responsetime:%f,turnAroundTime %f, exittime:%f\n ",
                       temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime, temp->waitTime, temp->responseTime, temp->turnAroundTime, temp->exitTime);

                temp = temp->next;
            }

            if (temp != NULL)
            {
                temp->responseTime = temp->firstTime - temp->arrivalTime;

                temp->turnAroundTime = temp->exitTime - temp->arrivalTime;
                temp->waitTime = temp->turnAroundTime - temp->originalBurstTime;

                avgWaitTime = temp->waitTime + avgWaitTime;
                avgResponseTime = temp->responseTime + avgResponseTime;
                avgTurnAroundTime = avgTurnAroundTime + temp->turnAroundTime;

                printf("\t process number: %d   arrival time %f , original burst: %f, waitTime:%f, responsetime:%f,turnAroundTime %f,exittime:%f\n ",
                       temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime, temp->waitTime, temp->responseTime, temp->turnAroundTime, temp->exitTime);
            }

            printf("\n\tAverage Wait time:%f ", avgWaitTime / numProcesses);
            printf("Average Response time:%f ", avgResponseTime / numProcesses);
            printf("Average Turnaround time:%f ", avgTurnAroundTime / numProcesses);
            printf("Total Context Switch: %d \n", contextSwitch - 1);
        }
        else
        {
            if (temp != NULL)
            {
                printf(
                    "\t process number: %d   arrival time %f , original burst: %f, waitTime:%f, responsetime:%f,turnAroundTime %f,firstime:%f, exittime:%f\n ",
                    temp->proccessNumber, temp->arrivalTime, temp->originalBurstTime, temp->waitTime, temp->responseTime, temp->turnAroundTime, temp->firstTime, temp->exitTime);
            }
        }
    }
}

// This function is to get process from the Process Queue and insert into ready queue accordingly
void addToReadyQV2(float currentTime)
{
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
    // if the process head is not null, we can loop and append accordingly
    if (Phead != NULL)
    {
        // loop all of the nodes in the process linked list to check whether it can be added to the ready queue
        do
        {
            // if it is bigger or smaller than
            if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
            {

                // add to Ready queue
                if (Qhead == NULL)
                {

                    // Make a copy of the node and put it into the ready queue

                    Qhead = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                    memcpy(Qhead, Phead, sizeof(struct processNode)); // copy the content of the node in the process linked list

                    // shift phead and remove node from process linked list
                    node toRemoveNode = Phead;
                    while (Phead->next != toRemoveNode)
                    {
                        Phead = Phead->next; // go to next node
                    }
                    Phead->next = toRemoveNode->next;
                    free(toRemoveNode);

                    head = Phead->next;  // assigning the second node as the head now
                    Phead = Phead->next; // move phead to the next item

                    Qhead->next = NULL; // removing the node's next which have been copied
                    Qhead->prev = NULL; // removing the node's previous which have been copied
                    readyQHead = Qhead; // set it as the head.
                }
                // if ready queue not empty. At least 1 node:
                else if (Qhead != NULL)
                {

                    // move to the end of the ready queue.
                    while (Qhead->next != NULL) // move to the end
                    {
                        if (Qhead->next == readyQHead)
                        {
                            break;
                        }
                        Qhead = Qhead->next;
                    }

                    // make a copy of the node in the process linked list
                    node tempNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                    memcpy(tempNode, Phead, sizeof(struct processNode));

                    tempNode->next = NULL; // set the copied node's next to null
                    tempNode->prev = NULL; // set the copied node's next to null

                    Qhead->next = tempNode; // point the last node of the linked list to the new node
                    Qhead = Qhead->next;    // move to the new last node
                    tempNode->prev = Qhead; // set the prev

                    // remove node fron process linked list
                    node toRemoveNode = Phead;
                    while (Phead->next != toRemoveNode)
                    {
                        Phead = Phead->next; // go to next node
                    }
                    Phead->next = toRemoveNode->next; // amend the next to skip the next away from the node to be removed
                    free(toRemoveNode);               // remove the node

                    head = Phead; // set the new head
                }
            }
            // Current time lesser than the node's arrival time, so moving on
            else
            {
                Phead = Phead->next;
            }
        } while (Phead->next != head);

        // Potential case of last node / head node, therefore not within the loop.
        if (Phead == head)
        {
            // check if it is the single node left for the head
            int linkedlistNum = 0;
            do
            {
                linkedlistNum = linkedlistNum + 1;
                Phead = Phead->next;
            } while (Phead != head);

            // usual checking of CT against process node's time
            if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
            {

                // allocate memory and copy
                node tempNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                memcpy(tempNode, Phead, sizeof(struct processNode));

                // removing the node
                node toRemoveNode = Phead;
                while (Phead->next != toRemoveNode)
                {
                    Phead = Phead->next; // go to next node
                }

                Phead->next = toRemoveNode->next;
                free(toRemoveNode);

                head = Phead;        // setting the new head
                Phead = Phead->next; // setting the next

                // setting the ready queue's node's next and prev to null
                tempNode->next = NULL;
                tempNode->prev = NULL;

                // append the new node to the end of ready queue
                while (Qhead->next != NULL)
                {
                    Qhead = Qhead->next;
                }
                Qhead->next = tempNode;
                Qhead = Qhead->next;
                tempNode->prev = Qhead;

                // if the number of node is 1, means there is no more nodes. Therefore set head to null
                if (linkedlistNum == 1)
                {
                    head = NULL;
                }
            }
        }
    }
    // if phead is null, nothing needed to do. Therefore nothing here
    else
    {
    }
}

// return last node
node rearNode(node head)
{
    node temp, p;
    p = head;

    if (p->next != NULL)
    {
        while (p->next != head)
        {
            // check not null
            if (p->next == NULL)
            {
                break;
            }
            // check that is is not pointing back to the same node
            else if (p->next == p)
            {
                break;
            }
            else
            {
                p = p->next; // traverse the lsit until p is the last node.
            }
        }
        temp = p;
    }
    else
    {
        p->next = p;
    }

    return temp;
}

// create a node and return the node. Used in the initial creation of nodes for the linked list
node createNode(int num, int arrivalTime, int originalBurstTime)
{
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
    temp->exitTime = -1;

    temp->next = NULL; // make next point to NULL
    temp->prev = NULL; // make next point to NULL

    return temp;
}

// A utility function to create a process linked list node. Used when the user is keying in the arrival time and burst time
node addNode(int num, int arrivalTime, int originalBurstTime, node head)
{

    node temp, p, prev = NULL;
    temp = createNode(num, arrivalTime, originalBurstTime); // use function to create new node

    // check if head is empty/
    if (head == NULL)
    {
        head = temp; // assign temp as head.
    }
    // at least 2 nodes
    else
    {
        p = head; // asign head to p

        // if currently there is only 2 seperate nodes:
        if (p->next == NULL)
        {

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
            // if both have the same arrival time, set according to their burst time
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

            while (p != NULL)
            {

                // new node is bigger than current node, go to next node in linked list
                if (temp->arrivalTime > p->arrivalTime)
                {
                    if (p->next == NULL)
                    {
                        p->next = temp;

                        break;
                    }
                    prev = p;    // assign p to previous node
                    p = p->next; // traverse the list
                                 // check to see if it is the end. if so, we just append
                }

                // new node is same as current node
                else if (temp->arrivalTime == p->arrivalTime)
                {

                    // if new node is bigger
                    if (temp->leftoverBurstTime > p->leftoverBurstTime)
                    {

                        // if null, set as last node
                        if (p->next == NULL)
                        {
                            p->next = temp;
                            temp->prev = p;
                            p = p->next;
                            break;
                        }
                        // else move to the next node in the linked list
                        else
                        {
                            prev = p;
                            p = p->next;
                        }
                    }
                    // if smaller or the same, append
                    else
                    {
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

                    // if prev is not null, means there are existing nodes already.
                    if (prev != NULL)
                    {
                        prev->next = temp; // previous node point to newly created node.
                        temp->prev = prev;

                        temp->next = p; // newly created node points to p
                        p->prev = temp;

                        break;
                    }
                    // means that is may be the first item in the linked list or there is no other nodes
                    else if (prev == NULL) // means that p is the first item
                    {

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

// calculate the number of nodes in the readyQ. For calculation purpose
int numOfNodes()
{
    node Qhead = readyQHead;
    int totalNodes = 1; // start off with one so that dont need to add the last item after looping
    if (Qhead == NULL)
    {
        totalNodes = 0; // if the qhead is null, then change accordingly
    }
    else
    {
        while (Qhead->next != readyQHead)
        {
            if (Qhead->next == Qhead)
            {
                break;
            }
            totalNodes = totalNodes + 1;
            Qhead = Qhead->next;
        }
        if (Qhead != NULL)
        {
        }
    }

    return totalNodes;
}

// calculate the total amount of burst time in the readyQ.
float sumReadyQueueProcesses()
{
    node Qhead = readyQHead;
    float TotalBurstTime = 0;

    if (Qhead == NULL)
    {
    }
    else
    {
        while (Qhead->next != readyQHead)
        {

            if (Qhead->next == Qhead)
            {
                break;
            }
            TotalBurstTime = TotalBurstTime + Qhead->leftoverBurstTime;
            Qhead = Qhead->next;
        }
        if (Qhead != NULL)
        {
            TotalBurstTime = TotalBurstTime + Qhead->leftoverBurstTime;
        }
    }
    return TotalBurstTime;
}

// sort the linked list according to the burst time.
// this is called after new nodes are added to the ready queue every time to sort (before work is done)
void sortList(node readyQHeadToSort)
{
    // Current will point to head
    node current = readyQHeadToSort;
    node index = NULL;
    node temp = NULL;

    if (current == NULL)
    {
    }
    else
    {

        do
        {
            // Index will point to node next to current
            index = current->next;
            while (index != readyQHeadToSort)
            {
                // If current node is greater than index data, swaps the data
                if (current->leftoverBurstTime > index->leftoverBurstTime)
                {
                    // make a copy of current as the node temp to store it temporary
                    temp = (node)malloc(sizeof(struct processNode));   // allocate memory using malloc()
                    memcpy(temp, current, sizeof(struct processNode)); // making a copy of current

                    // change accordingly
                    current->proccessNumber = index->proccessNumber;
                    current->arrivalTime = index->arrivalTime;
                    current->originalBurstTime = index->originalBurstTime;
                    current->leftoverBurstTime = index->leftoverBurstTime;
                    current->waitTime = index->waitTime;
                    current->responseTime = index->responseTime;
                    current->turnAroundTime = index->turnAroundTime;
                    current->firstTime = index->firstTime;
                    current->exitTime = index->exitTime;

                    // change accordingly based on the new node
                    index->proccessNumber = temp->proccessNumber;
                    index->arrivalTime = temp->arrivalTime;
                    index->originalBurstTime = temp->originalBurstTime;
                    index->leftoverBurstTime = temp->leftoverBurstTime;
                    index->waitTime = temp->waitTime;
                    index->responseTime = temp->responseTime;
                    index->turnAroundTime = temp->turnAroundTime;
                    index->firstTime = temp->firstTime;
                    index->exitTime = temp->exitTime;
                }
                index = index->next;
            }
            current = current->next;
        } while (current->next != readyQHeadToSort);
    }
}

int main()
{

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

        printf("\t Enter Burst Time for process %d :", i + 1);
        scanf("%d", &originalBurstTime);

        // pass in data into node creator
        head = addNode(i + 1, arrivalTime, originalBurstTime, head);
    }

    // the implementation of the algo.
    while (loop == 0)
    {
        if (currentTime == 0)
        {
            node headRear = rearNode(head);
            if (headRear->next == NULL) // ensure that it is at the end, then make the list ciruclar linked list
            {
                headRear->next = head;
                head->prev = headRear;
            }
        }

        addToReadyQV2(currentTime); // adding process

        // if head is not null, check the rear accordingly and set it to make it circular linked list
        if (head != NULL)
        {
            node headRear = rearNode(head);
            if (headRear->prev != NULL)
            {
                headRear->next = head;
                head->prev = headRear;
            }
        }
        // if ready queue not null, check the rear and set it  to make it circular linked list
        if (readyQHead != NULL)
        {

            rear = rearNode(readyQHead);
            if (rear->prev != NULL)
            {
                rear->next = readyQHead;
                readyQHead->prev = rear;
            }
        }

        float Sum_processes_burts = 0; // for calculation of TQ
        int totalNodes = 0;            // for calculation of TQ

        // Check if it points back to the head node || check if the first node points back to the head..
        if (readyQHead->next != readyQHead)
        {
            sortList(readyQHead); // sort accordingly

            Sum_processes_burts = sumReadyQueueProcesses();          // get the sum of all the process node in the ready queue
            totalNodes = numOfNodes();                               // get the number of nodes in the ready queue
            Average_Burst = Sum_processes_burts / (float)totalNodes; // calculate the average burst time
            TQ = Average_Burst * 0.85;                               // calculate TQ
        }
        // if there is only 1 node, which points back to the same thing
        else if (readyQHead->next == readyQHead)
        {
            Sum_processes_burts = readyQHead->leftoverBurstTime;
            totalNodes = 1;
            Average_Burst = Sum_processes_burts / (float)totalNodes;
            TQ = Average_Burst * 0.85;
        }
        else
        {
        }

        // to calculate the number of nodes in the ready queue
        node nodeCounter = readyQHead;
        int readyQlinkedlistNum = 0;
        do
        {
            readyQlinkedlistNum = readyQlinkedlistNum + 1;
            nodeCounter = nodeCounter->next;
        } while (nodeCounter != readyQHead);

        // doing the time loop
        node qhead = readyQHead;
        while (qhead != NULL)
        {

            // setting the time for the node accordingly if it is their first time
            if (qhead->firstTime == -1)
            {
                qhead->firstTime = currentTime;
            }

            contextSwitch = contextSwitch + 1;
            // The first subtraction
            if (qhead->leftoverBurstTime > TQ)
            {
                qhead->leftoverBurstTime = qhead->leftoverBurstTime - TQ;
                currentTime = currentTime + TQ;

                // The potential second subtraction: Checking to subtract or not
                if (TQ > qhead->leftoverBurstTime || TQ == qhead->leftoverBurstTime)
                {

                    currentTime = currentTime + qhead->leftoverBurstTime;
                    qhead->leftoverBurstTime = qhead->leftoverBurstTime - qhead->leftoverBurstTime;

                    qhead->exitTime = currentTime;

                    // do the same process of removing node from ready queue and adding node to the end queue
                    node endHeadDup = endHead;

                    if (endHeadDup == NULL) // if there are no nodes in this end link list..
                    {
                        node endHeadNewNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                        memcpy(endHeadNewNode, qhead, sizeof(struct processNode));

                        node toRemoveNode = qhead;
                        node currentNode = readyQHead;
                        if (toRemoveNode->next != NULL)
                        {
                            while (currentNode->next != toRemoveNode)
                            {
                                currentNode = currentNode->next;
                            }

                            currentNode->next = toRemoveNode->next;
                        }
                        free(toRemoveNode);
                        qhead = currentNode->next;
                        if (qhead == NULL)
                        {
                            readyQHead = qhead;
                        }

                        endHeadNewNode->next = NULL;
                        endHeadNewNode->prev = NULL;

                        endHeadDup = endHeadNewNode;
                        endHead = endHeadDup;
                    }
                    // there is already node in the linked list
                    else if (endHeadDup != NULL)
                    {

                        while (endHeadDup->next != NULL)
                        {
                            endHeadDup = endHeadDup->next;
                        }

                        node endHeadNewNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                        memcpy(endHeadNewNode, qhead, sizeof(struct processNode));

                        node toRemoveNode = qhead;
                        node currentNode = readyQHead;

                        while (currentNode->next != toRemoveNode)
                        {
                            currentNode = currentNode->next;
                        }
                        currentNode->next = toRemoveNode->next;

                        free(toRemoveNode);
                        readyQHead = currentNode;

                        // no more nodes in the ready queue, so set to null
                        if (readyQlinkedlistNum == 1)
                        {
                            readyQHead = NULL;
                        }

                        endHeadDup->next = endHeadNewNode;
                        endHeadDup = endHeadDup->next;
                        endHeadDup->next = NULL;
                    };
                    break;
                }
                // The second subtraction is false: go to next process;
                else
                {
                    qhead = qhead->next;
                }
            }

            // The first subtraction
            else if (TQ > qhead->leftoverBurstTime || TQ == qhead->leftoverBurstTime)
            {

                currentTime = currentTime + qhead->leftoverBurstTime;
                qhead->leftoverBurstTime = qhead->leftoverBurstTime - qhead->leftoverBurstTime;

                qhead->exitTime = currentTime;

                // same process of removing node from reeady queue and adding node to the end linked list
                node endHeadDup = endHead;
                if (endHeadDup == NULL)
                {

                    node endHeadNewNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                    memcpy(endHeadNewNode, qhead, sizeof(struct processNode));

                    node toRemoveNode = qhead;
                    node currentNode = readyQHead;
                    while (currentNode->next != toRemoveNode)
                    {
                        if (currentNode->next == NULL)
                        {
                            break;
                        }
                        currentNode = currentNode->next;
                    }
                    currentNode->next = toRemoveNode->next;
                    free(toRemoveNode);
                    readyQHead = currentNode->next;

                    // no more nodes in the ready queue, so set to null
                    if (readyQlinkedlistNum == 1)
                    {
                        readyQHead = NULL;
                    }
                    endHeadDup = endHeadNewNode;
                    endHeadDup->next = NULL;
                    endHeadDup->prev = NULL;
                    endHead = endHeadDup;
                }
                else if (endHeadDup != NULL)
                {
                    while (endHeadDup->next != NULL)
                    {
                        endHeadDup = endHeadDup->next;
                    }

                    node endHeadNewNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                    memcpy(endHeadNewNode, qhead, sizeof(struct processNode));

                    node toRemoveNode = qhead;
                    node currentNode = readyQHead;

                    while (currentNode->next != toRemoveNode)
                    {
                        currentNode = currentNode->next;
                    }
                    currentNode->next = toRemoveNode->next;

                    free(toRemoveNode);
                    readyQHead = currentNode;

                    if (readyQlinkedlistNum == 1)
                    {
                        readyQHead = NULL;
                    }

                    endHeadDup->next = endHeadNewNode;
                    endHeadDup = endHeadDup->next;
                    endHeadDup->next = NULL;
                }
                break;
            }
        }

        if (readyQHead == NULL && head == NULL)
        {
            loop = 1;
        }
    }

    printEndLinkedlist(endHead);
    return 0;
}

// macos
//  clang main.c -o main
//  open main