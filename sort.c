
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

node head = NULL, rear = NULL;
node headFixed = NULL;

void printAll()
{

    node temp2 = headFixed;

    while (temp2->next != headFixed)
    {
        printf("process number: %d, bursttime %f, arrivaltime: %f  \n", temp2->proccessNumber, temp2->leftoverBurstTime, temp2->arrivalTime);
        temp2 = temp2->next;
    }
    printf("process number: %d, bursttime %f, arrivaltime: %f  \n", temp2->proccessNumber, temp2->leftoverBurstTime, temp2->arrivalTime);
}
void rearNode()
{
    node lastNode = head;

    while (lastNode->next != head)
    {
        lastNode = lastNode->next;
    }
    rear = lastNode;
    printf("rear node %d\n", rear->proccessNumber);
}

void sortLL()
{
    printf("sortLL\n");
    node prev = NULL;

    // sort by arrival time, then burst time
    node temp = headFixed;
    while (temp->next != headFixed)
    {
        // printf("process number: %d, bursttime %f, arrivaltime: %f  \n", temp->proccessNumber, temp->leftoverBurstTime, temp->arrivalTime);

        if (prev == NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        else
        {
            // sorting
            if (prev->leftoverBurstTime > temp->leftoverBurstTime)
            {
                node tempNext = NULL;
                tempNext = temp->next;

                temp->next = prev;
                temp->prev = prev->prev;

                prev->prev = temp;
                prev->next = tempNext;

                prev = temp;
                temp = temp->next;
            }
            else if (temp->leftoverBurstTime > prev->leftoverBurstTime)
            {
                prev = temp;
                temp = temp->next;
            }
        }
    }
    printf("end of sorting \n");
}

void sortList()
{
    // Current will point to head
    node current = head;
    node index = NULL;
    int temp;
    if (head == NULL)
    {
        printf("List is empty");
    }
    else
    {
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

    node node1 = (node)malloc(sizeof(struct processNode));

    node1->proccessNumber = 1;
    node1->arrivalTime = 0;
    node1->originalBurstTime = 4;
    node1->leftoverBurstTime = 4;
    node1->firstTime = -1;
    node1->waitTime = -1;
    node1->responseTime = -1;
    node1->turnAroundTime = -1;
    node1->inReady = -1; // may or may not need this
    node1->exitTime = -1;
    node1->next = NULL; // make next point to NULL
    node1->prev = NULL; // make next point to NULL

    node node2 = (node)malloc(sizeof(struct processNode));
    node2->proccessNumber = 2;
    node2->arrivalTime = 4;
    node2->originalBurstTime = 8;
    node2->leftoverBurstTime = 8;
    node2->firstTime = -1;
    node2->waitTime = -1;
    node2->responseTime = -1;
    node2->turnAroundTime = -1;
    node2->inReady = -1; // may or may not need this
    node2->exitTime = -1;
    node2->next = NULL; // make next point to NULL
    node2->prev = NULL; // make next point to NULL

    node node3 = (node)malloc(sizeof(struct processNode));
    node3->proccessNumber = 3;
    node3->arrivalTime = 4;
    node3->originalBurstTime = 2;
    node3->leftoverBurstTime = 2;
    node3->firstTime = -1;
    node3->waitTime = -1;
    node3->responseTime = -1;
    node3->turnAroundTime = -1;
    node3->inReady = -1; // may or may not need this
    node3->exitTime = -1;
    node3->next = NULL; // make next point to NULL
    node3->prev = NULL; // make next point to NULL

    node node4 = (node)malloc(sizeof(struct processNode));
    node4->proccessNumber = 4;
    node4->arrivalTime = 2;
    node4->originalBurstTime = 4;
    node4->leftoverBurstTime = 4;
    node4->firstTime = -1;
    node4->waitTime = -1;
    node4->responseTime = -1;
    node4->turnAroundTime = -1;
    node4->inReady = -1; // may or may not need this
    node4->exitTime = -1;
    node4->next = NULL; // make next point to NULL
    node4->prev = NULL; // make next point to NULL

    headFixed = node1;
    head = node1;

    node1->next = node2;
    node2->prev = node1;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node4;
    node4->prev = node3;
    node4->next = node1;
    node1->prev = node4;

    rearNode();

    printAll();
    printf("\n\n\n");
    // sortLL();
    sortList();
    printAll();

    return 0;
}

// clang sort.c -o sort
// open sort