#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
  
typedef struct Node 
{ 
  int data; 
  struct Node *next; 
  struct Node *prev;
} cNode;

cNode *first = NULL;
  
cNode *addToEmpty(cNode *node, int data) 
{ 
  if (node != NULL) 
    return node; 

  cNode *temp = (cNode*)malloc(sizeof(cNode)); 

  temp->data = data;
  temp->next = temp->prev = temp;
  first = node = temp;

  return node; 
}
  
cNode *addEnd(cNode *node, int data) 
{ 
  if (node == NULL) 
    return addToEmpty(node, data); 
    
  cNode *temp = (cNode *)malloc(sizeof(cNode)); 

  temp->data = data;
  temp->prev = node;
  temp->next = first;
  first->prev = temp;
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
    
  cNode *temp = node;
  cNode *prev = node->prev;

  prev->next = node->next; 
  node->next->prev = prev;
  free(temp);

  return prev; 
}
  
int main() 
{
  cNode *cnode =  NULL;

  int input;
  int target;
  int i, j;
  int p = 1;
  int size = 0;

  scanf("%d %d", &input, &target);

  int num = input;

  if (target > 0)
  {
    i = 1;
    j = 1;
    target++;
  }
  else
  {
    i = 0;
    j = -2;
    target--;
  }
  

  cnode = addToEmpty(cnode, i++);

  while (p < input)
  {
    if (target > 0)
    {
      if (j%target == 0)
      {
        printf("%d ", cnode->data);
        cnode = del(cnode);
        p++;
      }
      j++;

      if (i <= num)
        cnode = addEnd(cnode, i++);
      else
        cnode = cnode->next;
    }
    else
    {
      if (j%target == 0)
      {
        if (cnode->data == 0)
          printf("%d ", input);
        else
          printf("%d ", cnode->data);
        cnode = del(cnode);
        p++;
      }
      j--;

      if (i < num)
        cnode = addEnd(cnode, num - (i++));
      else
        cnode = cnode->next;
    }
    
  }

  printf("~ %d\n", cnode->next->data);

  return 0; 
} 