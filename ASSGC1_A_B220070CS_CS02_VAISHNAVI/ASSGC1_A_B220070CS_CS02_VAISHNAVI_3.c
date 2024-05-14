//Vaishnavi B220070CS: Cycle 1 Part 1 - Question 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient {                //Structure for patient details
    char name[100];
    int priority;
    char admit_time[5];
};

struct manager {               //Structure for emergency room
    struct patient* heap;
    int capacity;
    int size;
};

typedef struct patient* node;
typedef struct manager* room;

room create_room (int capacity)
{
    room new = (room)malloc(sizeof(struct manager));
    new->heap = (node)malloc(sizeof(struct patient)*capacity);
    new->capacity = capacity;
    new->size = 0;
    return new;
}

node create_node (char name[], int pri, char time[])
{
    node new = (node)malloc(sizeof(struct patient));
    strcpy (new->name, name);
    new->priority = pri;
    strcpy (new->admit_time, time);
    return new;
}

void swap (node a, node b)
{
    struct patient temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify (room arr, int i)
{
    int left = (2*i)+1;
    int right = (2*i)+2;
    int largest = i;

    if (left < arr->size && ((arr->heap[left].priority > arr->heap[largest].priority) || ((arr->heap[left].priority == arr->heap[largest].priority) && (strcmp(arr->heap[left].admit_time, arr->heap[largest].admit_time) < 0))))
       largest = left;

    if (right < arr->size && ((arr->heap[right].priority > arr->heap[largest].priority) || ((arr->heap[right].priority == arr->heap[largest].priority) && (strcmp(arr->heap[right].admit_time, arr->heap[largest].admit_time) < 0))))
       largest = right;

    if (largest != i)
    {
        swap(&arr->heap[i], &arr->heap[largest]);
        max_heapify (arr, largest);
    }
}

void build_maxheap (room manage)
{
    int len = manage->size / 2;
    for (int i = (len-1); i>=0; i--)
       max_heapify (manage, i);
}

node find_maxpriority (room manage)
{
    if (manage->size > 0)
       return &manage->heap[0];
    else 
       return NULL;
}

void admit_patient (room wait, char name[], int priority, char admit_time[])       //admitPatient(priorityQ,name,priority,admitTime)
{
    node new = create_node (name, priority, admit_time);

    int i = wait->size - 1;

     while (i >= 0 && wait->heap[i].priority < new->priority)
    {
        wait->heap[i + 1] = wait->heap[i];
        i--;
    }

    wait->heap[i + 1] = *new;
    wait->size++;
}

void check_next (room check)       //checkNextPatient(priorityQ)
{
    node max = find_maxpriority (check);
    if (max != NULL)
       printf ("%s %d %s\n", max->name, max->priority, max->admit_time);
}

void discharge (room people, char name[], char admit[])     //n dischargePatient(priorityQ,name,admitTime)
{
    if (people->size == 0)
    {  return;  }
    
    int i = 0;
    for (i = 0; i<people->size; i++)
    {
        if (strcmp(people->heap[i].name, name) == 0 && strcmp(people->heap[i].admit_time, admit) == 0)
            break;
    }

    people->heap[i] = people->heap[people->size - 1];
    people->size--;

    max_heapify(people, i);
}

void treat_next (room manager)                      //treatNextPatient(priorityQ)
{
    if (manager->size == 0)
    {  return;  }
    node treated = &manager->heap[0];
    printf ("%s %d %s\n", treated->name, treated->priority, treated->admit_time);
    discharge(manager, treated->name, treated->admit_time);
}

void print_patients (room wait)        //printALLPatients(priorityQ)
{
    int num = wait->size;
    for (int i=0; i<num; i++)
    {
        printf ("%s %d %s\n", wait->heap[i].name, wait->heap[i].priority, wait->heap[i].admit_time);
    }

}

void update_priority (room manager, char name[], char admit[], int prior)          //updateConditionSeverity(priorityQ,name,admitTime,newPriority)
{
    int i;
    for (i=0; i<manager->size; i++)
    {
        if (strcmp(manager->heap[i].name, name) == 0 && strcmp(manager->heap[i].admit_time, admit) == 0)
            break;
    }

    manager->heap[i].priority = prior;

    max_heapify(manager, i);
}

int main ()
{
    char val;
    room emergency = create_room (100);
    while (1)
    {
        scanf (" %c", &val);

        if (val == 'a')
        {
            char name[100], admit_time[5];
            int priority;
            getchar();
            scanf ("%s %d %s", name, &priority, admit_time);
            admit_patient (emergency, name, priority, admit_time);
        }

        else if (val == 't')
        {
            treat_next (emergency);
        }

        else if (val == 'c')
        {
            check_next (emergency);
        }

        else if (val == 'd')
        {
            char name[100], admit[5];
            getchar();
            scanf ("%s %s", name, admit);
            discharge (emergency, name, admit);
        }

        else if (val == 'u')
        {
            char name[100], admit[5];
            int pri;
            getchar();
            scanf ("%s %s %d", name, admit, &pri);
            update_priority (emergency, name, admit, pri);
        }

        else if (val == 'p')
        {
            print_patients (emergency);
        }

        else if (val == 'e')
        {
            exit(0);
        }
    }
    return 0;
}