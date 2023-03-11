
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
node head = NULL, rear = NULL, temp = NULL; // declaring head, rear and temp
node readyQHead = NULL;
float currentTime = 0;

void addToReadyQ2(float currentTime)
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

        printf("process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

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

                    printf("Qhead process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n", Qhead->proccessNumber, Qhead->arrivalTime, Qhead->originalBurstTime, Qhead, Qhead->prev, Qhead->next);

                    printf("Head process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n", head->proccessNumber, head->arrivalTime, head->originalBurstTime, head, head->prev, head->next);

                    printf("next \n\n;");
                    printf("PHead process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

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
                    printf("num: %d, arrival: %d, Burst:%d \n", Pheadprev->proccessNumber, Pheadprev->arrivalTime, Pheadprev->leftoverBurstTime);

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
        else if (Phead == NULL)
        {
            break;
        }
    }

    printf("end of first while loop\n");

    node tempP;

    tempP = Pheadprev;

    if (tempP != NULL)
    {
        while (tempP->prev != NULL)
        {
            tempP = tempP->prev;
        }
        printf("tempP process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n", tempP->proccessNumber, tempP->arrivalTime, tempP->originalBurstTime, tempP, tempP->prev, tempP->next);
    }
    head = tempP;
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
            printf("more than 2 nodes");
            printf("adding to linked list \n");
            printf("num: %d, arrival: %d, Burst:%d \n", num, arrivalTime, originalBurstTime);
            int boo = 0;

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
                    printf("new node %d ", temp->leftoverBurstTime);         // compare the leftover burst time
                    printf("linked list node: %d \n", p->leftoverBurstTime); // compare the leftover burst time

                    // if bigger, go to next node.
                    if (temp->leftoverBurstTime > p->leftoverBurstTime)
                    {
                        prev = p;
                        p = p->next;
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
                            boo = 1; // set boolean to show it is done
                            break;
                        }
                        // if there is no previous node [could be the first node of linked list]
                        else if (prev == NULL)
                        {
                            temp->next = p; // assign new node to point to p.
                            p->prev = temp;

                            head = temp; //  Set the head to temp.
                            boo = 1;
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
                        printf("prev is not null");
                        prev->next = temp; // previous node point to newly created node.
                        temp->prev = prev;

                        temp->next = p; // newly created node points to p
                        p->prev = temp;
                        boo = 1;
                        break;
                    }

                    else if (prev == NULL) // means that p is the first item
                    {
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

            // last node
            // p is at the last node of the linked list.
            // append at the end if it is not appended in any of the cases while looping
            // if (boo == 0)
            // {
            //     printf("boo: at the last item of linked list");
            //     // new node arrival time is smaller than linked list.
            //     if (p->arrivalTime > temp->arrivalTime)
            //     {
            //         if (prev != NULL)
            //         {
            //             prev->next = temp; // 2nd last element should point to new node
            //             temp->prev = prev;

            //             temp->next = p; // new node should point to p.
            //             p->prev = temp;

            //             p->next = NULL;
            //         }
            //         else
            //         {
            //             // there is no prev, which should not happen
            //             printf("error 1: No previous node");
            //         }
            //     }

            //     // new node's arrival time is bigger than linked list
            //     else if (temp->arrivalTime > p->arrivalTime)
            //     {
            //         p->next = temp; // normal assigning to the last
            //         temp->prev = p;
            //     }

            //     // same arrival time.
            //     else if (temp->arrivalTime == p->arrivalTime)
            //     {
            //         printf("temp->arrivalTime == p->arrivalTime \n");

            //         // check left over burst time
            //         // new node's burst time is greater, append to back
            //         if (temp->leftoverBurstTime > p->leftoverBurstTime)
            //         {
            //             printf(" new node's burst time is greater, append to end of linked list \n");
            //             p->next = temp;
            //             temp->prev = p;
            //         }

            //         // burst time is equal to
            //         else if (temp->leftoverBurstTime == p->leftoverBurstTime)
            //         {
            //             p->next = temp;
            //             temp->prev = p;
            //         }
            //         // burst time is smaller
            //         else
            //         {
            //             printf("elsee.....? \n");
            //             prev->next = temp;
            //             temp->prev = prev;

            //             temp->next = p;
            //             p->prev = temp;
            //             p->next = NULL;
            //         }
            //     }
            //     else // both are equal, append to back
            //     {
            //         printf("last else .");
            //         p->next = temp; // normal assigning to the last
            //         temp->prev = p;
            //     }
            // }
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
        printf("\t process number: %d   arrival time %d  burst time: %d, current:%p prev: %p next: %p ; \n\n", p->proccessNumber, p->arrivalTime, p->originalBurstTime, p, p->prev, p->next);
        // printf("test next %p", p->next);
        p = p->next;
    }
    printf("end of printLinkedList\n");
}

// node addToReadyQ(node head, node readyQHead, int currentTime)
// {
//     printf("add to ready q \n\n");
//     node Qhead = readyQHead;

//     node prevNode = NULL;
//     node nextNode = NULL;
//     node currNode = NULL;
//     currNode = head;

//     while (currNode->next != NULL)
//     {

//         printf("id: %d, arrival time: %d burst time: %d\n ", currNode->proccessNumber, currNode->arrivalTime, currNode->leftoverBurstTime);

//         // if current time is not big enough, continue on.
//         if (currNode->arrivalTime > currentTime)
//         {
//             printf("c1\n");
//             prevNode = currNode;
//             currNode = currNode->next; // go to next one
//         }
//         else if (currentTime > currNode->arrivalTime || currentTime == currNode->arrivalTime)
//         { // smaller than or equal to currentTime

//             if (Qhead == NULL) // if there is nothing in the readyqueue
//             {
//                 printf("c2.1\n");
//                 Qhead = currNode;   // assign the currentnode as head.
//                 readyQHead = Qhead; // assign the currentnode as head.

//                 if (prevNode != NULL)
//                 {
//                     // remove the current node's existence as we moved to ready queue
//                     prevNode->next = currNode->next;
//                 }
//             }
//             else
//             {
//                 // if there is already item in the readqueue
//                 printf("c2.2\n");
//                 Qhead->next = currNode; // set the next to the current node
//                 Qhead = Qhead->next;
//                 if (prevNode != NULL)
//                 {
//                     prevNode->next = currNode->next;
//                 }
//             }
//             prevNode = currNode;
//             currNode = currNode->next;

//         } // end of else if
//     }     // end of while loop

//     // // check the last item in the linked list before leaving
//     if (currNode->arrivalTime == currentTime || currentTime > currNode->arrivalTime)
//     {
//         if (Qhead == NULL)
//         {
//             Qhead = currNode;
//             readyQHead = Qhead;
//             if (prevNode != NULL)
//             {
//                 prevNode->next = currNode->next;
//             }
//         }
//         else if (Qhead != NULL)
//         {
//             printf("Qhead rocessNumber %d", Qhead->proccessNumber);
//             printf("Qhead rocessNumber %d", currNode->proccessNumber);
//             printf("qhead not null att he end");
//             Qhead->next = currNode; // set the next to the current node
//             if (prevNode != NULL)
//             {
//                 prevNode->next = currNode->next;
//             }
//         }
//     }

//     return readyQHead;
// }

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

    // printf("\n to be processed by the ready queue. Time Now: %f \n", currentTime);

    while (currentTime < 6)
    {

        printf("\n\n\n\n\n\ncurrent time %f \n", currentTime);
        addToReadyQ2(currentTime);
        // printLinkedlist(readyQHead);
        currentTime = currentTime + 1;
        printf("head \n");
        printLinkedlist(head);

        printf("\n\n\n\n readyQ\n");
        printLinkedlist(readyQHead);
    }
    printf("\n end");

    return 0;
}

// macos
//  clang main.c -o main
//  open main