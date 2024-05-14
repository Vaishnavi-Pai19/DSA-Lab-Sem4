//Vaishnavi B220070CS: Cycle 1 Part 1 - Question 2

#include <stdio.h>
#include <stdlib.h>

struct linkedlist {
    int key;
    struct linkedlist* next;
};

typedef struct linkedlist* node;

node create_new (int data)       //CREATE-NODE(k)
{
    node new = (node)malloc(sizeof(struct linkedlist));
    
    new->next = NULL;
    new->key = data;
    return new;
}

node insert_last (node head, int val)       //LIST-INSERT(L,x)
{
    node temp = create_new (val);

    if (head==NULL)
    {  return temp;  }
    else
    {
        node current = head;
        while (current->next != NULL)
        {  current = current->next;  }
        current->next = temp;
        return head;
    }
}

node delete (node head, int index)    //LIST-DELETE(L,i)
{
    if (head == NULL)
    {  
        printf ("-1\n");  
        return NULL; 
    }
    if (index == 1)
    {
        node temp = head;
        head = head->next;
        printf ("%d\n", temp->key);
        free (temp);
    }
    else 
    {
        int x;
        node current = head;
        for (x=1; x<(index-1) && current->next != NULL;x++)
        {
            current = current->next;
        }
        
        if (current->next == NULL)
        {
            printf ("-1\n");
            return head;
        }
        
        node temp = current->next;
        current->next = current->next->next;
        printf ("%d\n", temp->key);
        free(temp);
    }
    return head;
}

void print_list (node head)     //LIST-DISPLAY(L)
{
    if (head == NULL)
    {  printf ("-1\n");  }
    else 
    {
        while (head->next != NULL)
        {
            printf ("%d ", head->key);
            head = head->next;
        }
        printf ("%d\n", head->key);
    }
}

node remove_duplicate (node head)     //LIST-RDUPLICATE(L)
{
    if (head == NULL)
    {
        printf ("-1\n");
        return NULL;
    }

    node ptr1, ptr2, dupli;
    ptr1 = head;

    while (ptr1 != NULL && ptr1->next != NULL)
    {
        ptr2 = ptr1;
        while (ptr2->next != NULL)
        {  
          if (ptr1->key == ptr2->next->key)
            {
                dupli = ptr2->next;
                ptr2->next = ptr2->next->next;
                free (dupli);
            }
            else 
                ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    return head;
}

node reverse (node head)
{
   node prevtemp = NULL;
   node current = head;
   node nexttemp = NULL;
   
   while (current != NULL)
   {
      nexttemp = current->next;
      current->next = prevtemp;
      
      prevtemp = current;
      current = nexttemp;
   }
   return prevtemp;
}

char check_palindrome (node head)     //LIST-PAL(L)
{  
   if (head == NULL || head->next == NULL)
     return 'Y';
     
   node ptr1 = head;
   node ptr2 = head;
   
   while (ptr2->next != NULL && ptr2->next->next != NULL)
   {
       ptr1 = ptr1->next;
       ptr2 = ptr2->next->next;
   }
   
   node reversed_half = reverse (ptr1->next);
   ptr1->next = reverse (reversed_half);

   node temp = head;
   while (reversed_half != NULL)
   {
       if (temp->key != reversed_half->key)
           return 'N';
       temp = temp->next;
       reversed_half = reversed_half->next;
   }
   return 'Y';
}

int main ()
{
    int val;
    char choice;
    node head = NULL;
    
    while (1)
    {
       scanf (" %c", &choice);
       
       switch (choice)
       {
           case 'a': scanf ("%d", &val);
                     head = insert_last (head, val);
                     break;
                     
           case 'r': scanf ("%d", &val);
                     head = delete (head, val);
                     break;
                     
           case 'd': head = remove_duplicate (head);
                     print_list (head);
                     break;
                     
           case 'p': if (head == NULL)
                     printf ("-1\n");
                     else {
                     printf ("%c\n", check_palindrome (head)); }
                     break;
            
           case 's': print_list (head);
                     break;

           case 'e': exit (0);
                     break;
         }
     }  
     return 1;
} 