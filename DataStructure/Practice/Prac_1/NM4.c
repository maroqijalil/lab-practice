#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
  
typedef struct Node 
{ 
  int data; 
  struct Node *next; 
  struct Node *prev;
} cNode;

typedef struct List
{
  int size;
  cNode *head;
} cDList;
  
cNode *addToEmpty(cNode *node, int data) 
{ 
  if (node != NULL) 
    return node; 

  cNode *temp = (cNode*)malloc(sizeof(cNode)); 

  temp->data = data;
  temp->next = temp->prev = temp;
  node = temp;

  return node; 
} 
  
cNode *addBegin(cNode *node, int data) 
{ 
  if (node == NULL) 
    return addToEmpty(node, data); 

  cNode *temp = (cNode *)malloc(sizeof(cNode)); 

  temp->data = data; 
  temp->next = node->next; 
  node->next = temp; 

  return node; 
} 
  
cNode *addEnd(cNode *node, int data) 
{ 
  if (node == NULL) 
    return addToEmpty(node, data); 
    
  cNode *temp = (cNode *)malloc(sizeof(cNode)); 

  temp->prev = node;
  temp->data = data; 
  temp->next = node->next; 
  node->next = temp; 
  node = temp; 

  return node; 
}

cNode *del(cNode *node) 
{ 
  if (node->next == NULL)
  {
    return node;
  }
    
  cNode *temp = node->next;

  temp->next = node->next; 
  node->next = temp; 
  node = temp; 

  return node; 
} 
  
void traverse(cNode *node) 
{ 
  cNode *p; 

  if (node == NULL) 
  { 
    printf("List is empty.\n"); 
    return; 
  } 

  p = node->next; 

  do
  { 
    printf("%d ", p->data); 
    p = p->next; 
  } 
  while(p != node->next); 
} 
  
int main() 
{ 
  cNode *node = NULL; 

  int input;
  int target;
  int i = 1;
  int j = 1;

  scanf("%d %d", &input, &target);

  int num = input;

  target++;

  node = addToEmpty(node, i++);

  while (true)
  {
    j += target;
    if (j > input)
    {
      input--;

      j %= input;

      if (j == 0)
        j = input;
    }
    printf("%d \n", j);
    
    if (i <= num)
      node = addEnd(node, i++);
    else
      break;
  }

  traverse(node); 

  return 0; 
} 