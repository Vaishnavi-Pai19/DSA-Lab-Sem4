//Vaishnavi B220070CS: Cycle 1 Part - Question 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node 
{
    char* name;
    char* roll;
    int age;
    struct node* next;
};

typedef struct node person;

int hash_function (person* p)          //Calculates the hash function h(A)=(Sum of ASCII value of the characters in the name of ‘A’+ age of ‘A’) % 4
{
    int length = strlen(p->name);
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        index += p->name[i];
    }
    index += p->age;
    return index % 4;
}

void initialize_hash (person* arr[], int size)
{
    for (int i = 0; i<size; i++)
       arr[i] = NULL;
}

void insert_person (person* hash_table[], person* p)      //Inserts a person's details into the hash table
{
    int index = hash_function(p);
    if (hash_table[index] == NULL)
    {
        hash_table[index] = p;
        p->next = NULL;
    }
    else
    {
        person* current = hash_table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = p;
        p->next = NULL;
    }
}

void check_count (person* hash_table[], int index)       //Function to check the number of people in either of the groups
{
    int count = 0;
    if (hash_table[index] == NULL)
    {
        printf ("0\n");
        return;
    }
    else
    {
        person* current = hash_table[index];
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
        printf ("%d ", count);

        current = hash_table[index];
        while (current != NULL)
        {
            printf ("%s ", current->name);
            current = current->next;
        }
    }
    printf ("\n");
}

void branch_count (person* hash[], int group, char* branch)      //Function to check the number of people of a certain branch in the given group
{
    int count = 0;
    int index = group;
    if (hash[index] == NULL)
    {
        printf ("-1\n");       //0 or -1 based on the requirement
        return;
    }
    else
    {
        person* current = hash[index];
        while (current != NULL)
        {
            char student_branch[3];
            strncpy(student_branch, current->roll + 7, 2);
            student_branch[2] = '\0';

            if (strcmp(student_branch, branch) == 0)
            {
                printf ("%s ", current->name);
                count++;
            }
            current = current->next;
        }
        if (count == 0)
           printf ("-1");
    }
    printf ("\n");
}

int main ()
{
    int num;
    scanf ("%d", &num);
    person* students = (person*)malloc(num * sizeof(person));
    person* hash_table[4];
    initialize_hash (hash_table, 4);

    for (int i = 0; i < num; i++)
    {
        students[i].name = (char*)malloc(50 * sizeof(char));
        scanf ("%s", students[i].name);

        students[i].roll = (char*)malloc(9 * sizeof(char));
        scanf ("%s", students[i].roll);

        scanf ("%d", &students[i].age);
        insert_person (hash_table, &students[i]);
    }

    char choice;
    int k;
    char branch[3];
    while (1)
    {
        scanf (" %c", &choice);

        if (choice == 'c')
        {
            scanf ("%d", &k);
            check_count (hash_table, k);
        }
        else if (choice >= '0' && choice <= '3')
        {
            scanf ("%s", branch);
            if (branch[0] >= 'a' && branch[0] <= 'z')
                branch[0] -= 32;
            if (branch[1] >= 'a' && branch[1] <= 'z')
                branch[1] -= 32;
            
            branch_count (hash_table, choice - '0', branch);
        }
        else if (choice == 'e')
           break;
    }
    return 0;
}