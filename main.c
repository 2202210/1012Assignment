
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
node head = NULL, temp = NULL;       // declaring process head of linked list, rear and temp
node readyQHead = NULL, rear = NULL; // queue head of linked list
node endHead = NULL;                 // last link list to store all the finished processes
float currentTime = 0;

// print the linked list value
void printLinkedlist(struct processNode *p)
{

    printf("lnikedlist");

    node temp = p;

    if (p == NULL)
    {
        printf("\nnothing to print as p is null \n");
    }
    else
    {
        printf("\n printing values ... \n");

        if (temp->next != NULL)
        {
            while (temp->next != p)
            {
                if (temp->next == temp)
                {
                    break;
                }

                printf("\t process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", temp->proccessNumber, temp->arrivalTime, temp->leftoverBurstTime, temp, temp->prev, temp->next);

                temp = temp->next;
            }

            // the following may cause seg fault due to next being null. Therefore printing null return fault
            printf("\t process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", temp->proccessNumber, temp->arrivalTime, temp->leftoverBurstTime, temp, temp->prev, temp->next);
        }
        else
        {
            if (temp != NULL)
            {
                printf("\t process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", temp->proccessNumber, temp->arrivalTime, temp->leftoverBurstTime, temp, temp->prev, temp->next);
            }
        }
    }
}

/*
node addToReadyQV2(float currentTime)
{

    printf("\n QV2\n");
    node Pheadprev = NULL;
    node Qheadprev = NULL;

    node Phead = NULL;
    node Qhead = NULL;

    if (head != NULL)
    {
        // printf("head not null\n");
        Phead = head;
    }

    if (readyQHead != NULL)
    {
        // printf("readyQheadhead not null\n");
        Qhead = readyQHead;
    }

    while (Phead->next != head)
    {
        printf("new process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

        // put to Qhead
        if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
        {
            // printf("current time: > || == \n");

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

                    printf("The process is the head now \n\n\n");

                    // printf("Qhead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Qhead->proccessNumber, Qhead->arrivalTime, Qhead->originalBurstTime, Qhead, Qhead->prev, Qhead->next);
                    // printf("Head process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", head->proccessNumber, head->arrivalTime, head->originalBurstTime, head, head->prev, head->next);
                    // printf("next \n\n;");
                    // printf("PHead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

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
                    printf("The pheadprev is num: %d, arrival: %f, Burst:%f \n", Pheadprev->proccessNumber, Pheadprev->arrivalTime, Pheadprev->leftoverBurstTime);

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
                // no previous node in the process linked list
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
                        printf("Phead->next != nulll \n");
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
                    printf("just some padding \n\n\n");
                }
                else
                {
                    // printf("??");
                    // printf("moving ahead first \n");
                    // Pheadprev = Phead;
                    Phead = Phead->next;
                }
            }
        }

        // move forward
        else if (currentTime < Phead->arrivalTime)
        {
            // printf(" current node> CT \n");
            Pheadprev = Phead;
            Phead = Phead->next;
        }
    }

    // // last item
    if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
    {
        if (Qhead != NULL)
        {
            Qhead->next = Phead;
            Phead->prev = Qhead;
            Phead->next = NULL;
            head = NULL;
        }
    }

    return readyQHead;
}

*/

node addToReadyQV2(float currentTime)
{
    printf("\n\n\n\t\t\t\tcalling addtoreadyq V2\n");

    printf("head\n");
    printLinkedlist(head);
    printf("just some padding \n\n\n");

    printf("ready head\n");
    printLinkedlist(readyQHead);

    node Phead = NULL;
    node Qhead = NULL;

    if (head != NULL)
    {
        // printf("head not null\n");
        Phead = head;
    }

    if (readyQHead != NULL)
    {
        // printf("readyQheadhead not null\n");
        Qhead = readyQHead;
    }

    do
    {
        printf("\t\tnew process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);
        if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
        {
            // printf("current time: > || == \n");

            // add to queue
            if (Qhead == NULL)
            {
                printf("Qhead == NUL \n");
                // assign the link list to node.
                // Qhead = Phead;

                Qhead = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()

                memcpy(Qhead, Phead, sizeof(struct processNode));

                // shift phead
                node toRemoveNode = Phead;
                while (Phead->next != toRemoveNode)
                {
                    Phead = Phead->next; // go to next node
                }
                Phead->next = toRemoveNode->next;
                free(toRemoveNode);
                head = Phead->next; // assigning the second node as the head now

                // Qhead->next = Qhead;
                // Qhead->prev = Qhead;

                Qhead->next = NULL; // removing the previous head's next so it is single node
                Qhead->prev = NULL;
                readyQHead = Qhead;

                printf("The process is the head now \n");
                printf("process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", readyQHead->proccessNumber, readyQHead->arrivalTime, readyQHead->originalBurstTime, readyQHead, readyQHead->prev, readyQHead->next);
                printf("just some padding \n\n\n");

                printf("head\n");
                printLinkedlist(head);

                printf("Qhead\n");
                printLinkedlist(Qhead);
                printf("just some padding \n\n\n");
            }
            else if (Qhead != NULL)
            {
                printf("Qhead not null \n");
                while (Qhead->next != NULL) // move to the end
                {
                    if (Qhead->next == Qhead)
                    {
                        break;
                    }
                    Qhead = Qhead->next;
                }

                node tempNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
                memcpy(tempNode, Phead, sizeof(struct processNode));
                printf("process num: %d, current: %p, next: %p, prev %p \n", tempNode->proccessNumber, tempNode, tempNode->next, tempNode->prev);
                tempNode->next = NULL;
                tempNode->prev = NULL;

                Qhead->next = tempNode; // to do
                Qhead = Qhead->next;
                tempNode->prev = Qhead;

                // Qhead->prev = NULL;
                // to do all the linking heree.

                // remove node
                node toRemoveNode = Phead;
                while (Phead->next != toRemoveNode)
                {
                    Phead = Phead->next; // go to next node
                }
                Phead->next = toRemoveNode->next;
                free(toRemoveNode);
                // head = Phead;

                // // may have error here
                // Qhead->next = tempNode;
                // Phead = Phead->next;
                // Phead->prev = NULL;
                // head = Phead;
            }
        }
        else
        {
            printf("else for now");
        }
    } while (Phead != head);

    if (Phead == head)
    {
        int linkedlistNum = 0;
        do
        {
            linkedlistNum = linkedlistNum + 1;
            Phead = Phead->next;
        } while (Phead != head);

        if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
        {

            node tempNode = (node)malloc(sizeof(struct processNode)); // allocate memory using malloc()
            memcpy(tempNode, Phead, sizeof(struct processNode));
            printf("process num: %d, current: %p, next: %p, prev %p \n", tempNode->proccessNumber, tempNode, tempNode->next, tempNode->prev);
            tempNode->next = NULL;
            tempNode->prev = NULL;

            Qhead->next = tempNode; // to do
            Qhead = Qhead->next;
            tempNode->prev = Qhead;

            printf("linkedlistnum: %d", linkedlistNum);
            if (linkedlistNum == 1)
            {
                head = NULL;
            }

            printf("may have caused some issues here \n");
        }
    }
}

node addToReadyQ2(float currentTime)
{
    printf("\tadd to ready q2 \n");
    node Pheadprev = NULL;
    node Qheadprev = NULL;

    node Phead = NULL;
    node Qhead = NULL;

    if (head != NULL)
    {
        printf("head not null\n");
        Phead = head;
    }

    if (readyQHead != NULL)
    {
        printf("readyQheadhead not null\n");
        Qhead = readyQHead;
    }

    while (Phead != NULL)
    {
        printf("process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

        // put to Qhead
        if (currentTime > Phead->arrivalTime || currentTime == Phead->arrivalTime)
        {
            // printf("current time: > || == \n");

            // add to queue
            if (Qhead == NULL)
            {
                // printf("Qhead == NULL \n"); // no previous node
                if (Pheadprev == NULL)
                {
                    // printf("pheadprev == NUL \n");
                    // assign the link list to node.
                    Qhead = Phead;

                    // shift phead
                    Phead = Phead->next; // go to next node
                    Phead->prev = NULL;  // removing the 2node previous
                    head = Phead;        // assigning the second node as the head now

                    Qhead->next = NULL; // removing the previous head's next so it is single node
                    readyQHead = Qhead;

                    // printf("Qhead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Qhead->proccessNumber, Qhead->arrivalTime, Qhead->originalBurstTime, Qhead, Qhead->prev, Qhead->next);
                    // printf("Head process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", head->proccessNumber, head->arrivalTime, head->originalBurstTime, head, head->prev, head->next);
                    // printf("next \n\n;");
                    // printf("PHead process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", Phead->proccessNumber, Phead->arrivalTime, Phead->originalBurstTime, Phead, Phead->prev, Phead->next);

                    // break;
                }
                // got previous node
                else if (Pheadprev != NULL)
                {
                    // printf("Pheadprev != Null \n");
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
                // printf("Qhead != Nulll\n");

                if (Pheadprev != NULL)
                {
                    // printf("Pheadprev != NULL \n");
                    // printf("num: %d, arrival: %f, Burst:%f \n", Pheadprev->proccessNumber, Pheadprev->arrivalTime, Pheadprev->leftoverBurstTime);

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
                    // printf("Pheadprev == NULL\n");
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
                    // printf("??");
                    // printf("moving ahead first \n");
                    // Pheadprev = Phead;
                    Phead = Phead->next;
                }
            }
        }

        // move forward
        else if (currentTime < Phead->arrivalTime)
        {
            // printf(" current node> CT \n");
            Pheadprev = Phead;
            Phead = Phead->next;
        }
    }

    // printf("end of first while loop\n");

    node tempP = NULL;

    tempP = Pheadprev;

    if (tempP != NULL)
    {
        // printf("tempP not null");
        while (tempP->prev != NULL)
        {
            tempP = tempP->prev;
        }
        // printf("tempP process number: %d   arrival time %f  burst time: %f, current:%p prev: %p next: %p ; \n", tempP->proccessNumber, tempP->arrivalTime, tempP->originalBurstTime, tempP, tempP->prev, tempP->next);
        head = tempP;
    }
    else if (tempP == NULL)
    {
        // printf("is NULL");
        return readyQHead;
    }
    else
    {
        // printf("need to return");
        return readyQHead;
    }

    // printf("return v2");
    return readyQHead;
}

node rearNodeL(node head)
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

node rearNode(node head)
{
    printf("rearnode\n");
    node temp, p;
    p = head;

    while (p->next != head)
    {
        if (p->next == NULL)
        {
            break;
        }
        else
        {
            p = p->next; // traverse the lsit until p is the last node.
        }
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

int numOfNodes()
{
    printf("num of nodes");
    node Qhead = readyQHead;
    int totalNodes = 0;
    while (Qhead != NULL)
    {

        totalNodes = totalNodes + 1;
        Qhead = Qhead->next;
        if (Qhead->next == Qhead->prev)
        {
            return totalNodes;
        }
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
        if (Qhead->next == Qhead->prev)
        {
            return TotalBurstTime;
        }
    }
    return TotalBurstTime;
}

void sortList()
{
    printf("sortList");
    // Current will point to head
    node current = readyQHead;
    node index = NULL;
    int temp;
    if (head == NULL)
    {
        printf("List is empty");
    }
    else
    {
        printf("else");

        do
        {
            // Index will point to node next to current
            index = current->next;
            while (index != head)
            {
                // If current node is greater than index data, swaps the data
                if (current->leftoverBurstTime > index->leftoverBurstTime)
                {
                    temp = current->leftoverBurstTime;
                    current->leftoverBurstTime = index->leftoverBurstTime;
                    index->leftoverBurstTime = temp;
                }
                index = index->next;
            }
            current = current->next;
        } while (current->next != head);
    }
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
        // printLinkedlist(head);
    }

    // somnething wrong below

    // printf("\n to be processed by the ready queue. Time Now: %f \n", currentTime);
    if (currentTime == 0)
    {
        addToReadyQ2(currentTime); // adding process

        node headRear = rearNodeL(head);

        if (headRear->next == NULL)
        {
            headRear->next = head;
            head->prev = headRear;
        }

        rear = rearNodeL(readyQHead);
        printf("rear %p, %p \n\n", rear->next, rear->prev);
        if (rear->next == NULL)
        {
            rear->next = readyQHead;
            readyQHead->prev = rear;
        }
    }

    printf("\n\n\n\n\n\n TIME CURRENT 0  \n");

    printf("head \n");
    printLinkedlist(head);
    printf("ready q head \n");
    printLinkedlist(readyQHead);

    while (currentTime < 10)
    // while (readyQHead != NULL)
    {
        if (currentTime != 0)
        {
            addToReadyQV2(currentTime); // adding process
            printf("end of adding to ready Q2 \n\n\n\n\n\n");
        }

        if (head != NULL)
        {
            printf("before rear, check not null\n");
            node headRear = rearNode(head);
            if (headRear->prev != NULL)
            {
                headRear->next = head;
                head->prev = headRear;
            }
        }

        if (readyQHead != NULL)
        {
            printf("before rear, check not null2\n");
            // printLinkedlist(readyQHead); // error appear here as queue is invalid
            rear = rearNode(readyQHead);
            if (rear->prev != NULL)
            {
                rear->next = readyQHead;
                readyQHead->prev = rear;
            }
        }

        printf("head\n");
        printLinkedlist(head);

        printf("ready head\n");
        printLinkedlist(readyQHead);
        printf("just some padding \n\n\n");

        printf("\n\n\n\n\n\ncurrent time %f \n", currentTime);

        float Sum_processes_burts = 0;
        int totalNodes = 0;

        printf("\n\n\n\nhead \n");
        printLinkedlist(head);

        printf("\n\n\n\nreadyQ\n");
        printLinkedlist(readyQHead);

        if (readyQHead->next != readyQHead)
        {
            printf("more than 1 item\n");
            sortList();
            printf("end sort");

            Sum_processes_burts = sumReadyQueueProcesses(readyQHead);
            totalNodes = numOfNodes();
            Average_Burst = Sum_processes_burts / (float)totalNodes;
            TQ = Average_Burst * 0.85;
        }
        else if (readyQHead->next == readyQHead)
        {
            printf("\n\n\n only 1 item\n");
            Sum_processes_burts = readyQHead->leftoverBurstTime;
            totalNodes = 1;
            Average_Burst = Sum_processes_burts / (float)totalNodes;
            TQ = Average_Burst * 0.85;
        }
        else
        {
            printf("weird");
        }

        printf("sum of process bursts: %f, num of nodes: %d, average Burst: %f, TQ: %f\n", Sum_processes_burts, totalNodes, Average_Burst, TQ);

        // doing the time loop
        node qhead = readyQHead;
        while (qhead != NULL)
        {

            // setting the time
            if (qhead->firstTime == -1)
            {
                printf("putting first time\n");
                qhead->firstTime = currentTime;
            }

            // The first subtraction
            if (qhead->leftoverBurstTime > TQ)
            {
                printf("qhead->leftoverBurstTime > TQ \n");
                qhead->leftoverBurstTime = qhead->leftoverBurstTime - TQ;
                currentTime = currentTime + TQ;

                // The potential second subtraction: Checking to subtract or not
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

                        if (qhead->next != qhead)
                        {

                            qhead = qhead->next;
                        }
                        else
                        {
                            qhead = NULL;
                        }

                        endHeadDup->next = NULL;
                        endHeadDup->prev = NULL;
                        readyQHead = qhead;
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
                        readyQHead = qhead;
                        endHeadDup = endHeadDup->next;
                        endHeadDup->next = NULL;
                    }
                    break;
                }
                // The potential subtraction: False
                else
                {
                    // go to next process;
                    qhead = qhead->next;
                }
            }

            // The first subtraction
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
                    qhead = qhead->next; // move to next;
                    qhead->prev = NULL;  // second node set prev to null
                    readyQHead = qhead;

                    endHeadDup->next = NULL;
                    endHeadDup->prev = NULL;
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
                    readyQHead = qhead;

                    node endHeadDuptemp = endHeadDup;

                    endHeadDup = endHeadDup->next;
                    endHeadDup->prev = endHeadDuptemp;
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