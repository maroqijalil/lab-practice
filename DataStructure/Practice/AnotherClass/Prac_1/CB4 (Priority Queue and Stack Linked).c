#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct pqueueNode_t {
  int _data;
  struct pqueueNode_t *next;
  struct pqueueNode_t *prev;
} PQueueNode;

typedef struct pqueue_t {
  PQueueNode *_top;
  PQueueNode *_down;
  unsigned _size;
} PriorityQueue;

typedef struct stackNode_t {
  int data;
  struct stackNode_t *next;
  PQueueNode *pqnode;
} StackNode;

typedef struct stack_t {
  StackNode *_top;
  unsigned _size;
} Stack;

void pqueue_init(PriorityQueue *pqueue)
{
  pqueue->_top = pqueue->_down = NULL;
  pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
  return (pqueue->_top == NULL && pqueue->_down == NULL);
}

PQueueNode* pqueue_push(PriorityQueue *pqueue, int data)
{
  PQueueNode *temp = pqueue->_top;
  PQueueNode *newNode = (PQueueNode*)malloc(sizeof(PQueueNode));

  pqueue->_size++;

  newNode->_data = data;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (pqueue_isEmpty(pqueue))
  {
    pqueue->_top = pqueue->_down = newNode;
    return newNode;
  }

  if (pqueue->_top == pqueue->_down)
  {
    if (data > pqueue->_top->_data) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else
    {
      pqueue->_top->next = newNode;
      newNode->prev = pqueue->_top;
      pqueue->_down = newNode;
    }

    return newNode;
  }
  else
  {
    if (data > pqueue->_top->_data) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else {
      while ( temp->next != NULL && temp->next->_data > data)
        temp = temp->next;
      if (temp == pqueue->_down)
      {
        if (pqueue->_down->_data > newNode->_data)
        {
          // printf("flag 1\n");
          newNode->prev = pqueue->_down;
          pqueue->_down->next = newNode;
          pqueue->_down = newNode;
        }
        else
        {
          // printf("flag 2\n");
          newNode->prev = pqueue->_down->prev;
          pqueue->_down->prev->next = newNode;
          pqueue->_down->prev = newNode;
          newNode->next = pqueue->_down;
        }
      }
      else
      {
          // printf("flag 3\n");
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode; 
      }
    }
    return newNode;
  }
}

void pqueue_pop(PriorityQueue *pqueue, PQueueNode *node)
{
  PQueueNode *temp;
  pqueue->_size--;
  if (pqueue->_top == pqueue->_down)
  {
    // printf("1\n");
    temp = node;
    pqueue->_top = pqueue->_down = NULL;
    free(node);
  }
  else if (node == pqueue->_top)
  {
    // printf("2\n");
    temp = pqueue->_top;
    pqueue->_top->next->prev = NULL;
    pqueue->_top = pqueue->_top->next;
    free(temp);
  }
  else if (node == pqueue->_down)
  {
    // printf("3\n");
    temp = pqueue->_down;
    pqueue->_down->prev->next = NULL;
    pqueue->_down = pqueue->_down->prev;
    free(temp);
  }
  else
  {
    // printf("4\n");
    temp = node;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
  }
  // printf("falgg\n");
}

int pqueue_top(PriorityQueue *pqueue) {
  if (!pqueue_isEmpty(pqueue))
    return pqueue->_top->_data;
  else return 0;
}

int pqueue_down(PriorityQueue *pqueue) {
  if (!pqueue_isEmpty(pqueue))
    return pqueue->_down->_data;
  else return 0;
}

void stack_init(Stack *stack) 
{
  stack->_size = 0;
  stack->_top = NULL;
}

bool stack_isEmpty(Stack *stack) {
  return (stack->_top == NULL);
}

void stack_push(Stack *stack, PriorityQueue *pqueue, int value) 
{
  StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
  if (newNode) {
    stack->_size++;
    if (stack_isEmpty(stack)) newNode->next = NULL;
    else newNode->next = stack->_top;

    newNode->data = value;
    newNode->pqnode = pqueue_push(pqueue, value);
    stack->_top = newNode;
  }
}

void stack_pop(Stack *stack, PriorityQueue *pqueue)
{
  if (!stack_isEmpty(stack)) {
    // printf("falg\n");
    StackNode *temp = stack->_top;
    // printf("gg\n");
    // printf("ff %d %d",stack->_top->data, stack->_top->pqnode->_data);
    // printf("ss\n");
    pqueue_pop(pqueue, stack->_top->pqnode);
    // printf("ssk\n");
    if (stack->_top->next != NULL)
      stack->_top = stack->_top->next;
    else
      stack->_top = NULL;
    // printf(" kk\n");
    free(temp);
    stack->_size--;
  }
}

int stack_top(Stack *stack) 
{
  if (!stack_isEmpty(stack)) 
    return stack->_top->data;
  return 0;
}

unsigned stack_size(Stack *stack) {
  return stack->_size;
}

int main(int argc, char const *argv[])
{
  int jumlah;
  int query;
  int command;
  int index;
  int index_l;
  int index_r;
  int data;
  int i;
  int j;
  int marker = 0;
  int max_marker;
  int max_val = 0;
  int sec_val = 0;
  int null = 0;
  int queue = 0;

  scanf("%d %d", &jumlah, &query);

  Stack *stack = (Stack*)malloc(sizeof(Stack)*jumlah);
  PriorityQueue *pque = (PriorityQueue*)malloc(sizeof(PriorityQueue)*jumlah);
  int *init = (int*)calloc(sizeof(int), jumlah);

  while(query--)
  {
    scanf("%d", &command);

    if (command == 1)
    {
      scanf("%d %d", &index, &data);

      if (index <= jumlah && index > 0)
      {
        if (init[index-1] == 0)
        {
          // printf("push\n");
          stack_init((stack + (index-1)));
          pqueue_init((pque + (index-1)));
          init[index-1] = 1;
          queue++;
        }

        stack_push((stack + (index-1)), (pque + (index-1)), data);
      }
      // printf("%d\n", (pque + (index-1))->_top->_data);
      // printf("%d...\n", (stack + (index-1))->_top->pqnode->_data);
    }
    else if (command == 2)
    {
      scanf("%d", &index);
      
      if (index <= jumlah && index > 0)
      {
        if (!(stack_isEmpty((stack + (index-1)))))
          stack_pop((stack + index-1), (pque + (index-1)));

        if (stack_isEmpty(stack + (index-1)));
        {
          init[index-1] = 0;
          queue--;
        }
      }
    }
    // printf("%d\n", (pque + (index-1))->_top->_data);
    // printf("%d...\n", (stack + (index-1))->_top->data);
    else if (command == 3)
    {
      scanf("%d %d", &index_l, &index_r);
      // printf("%d..\n", queue);

      if (queue > 0)
      {
        PQueueNode *node = (PQueueNode*)malloc(sizeof(PQueueNode)*(index_r - index_l + 1));
        j = 0;
        sec_val = 0;
        max_val = 0;
        marker = 0;
        null = 0;
      
        while (true)
        {
          // printf("count %d\n", null);
          for (i = index_l-1; i < index_r; i++)
          {
            if (init[i] != 0)
            {
              // printf("flag\n");
              if (marker == 0)
                node[j] = *(pque + i)->_top;
              else if ((node + j)->next == NULL)
              {
                null++;
                continue;
              }
              else if ((node + j)->next != NULL)
                node[j] = *(node + j)->next;
              
              if ((node + j) != NULL)
              {
                // printf("%d ", (node + j)->_data);
                if (max_val < (node + j)->_data)
                {
                  sec_val = max_val;
                  max_val = (node + j)->_data;
                  max_marker = j;
                }
                else if (max_val > (node + j)->_data && (node + j)->_data > sec_val)
                  sec_val = (node + j)->_data;
              }
              j++;
            }
            else
            {
              null++;
              continue;
            }
          }
          // printf("%d... .\n", (node + max_marker)->next->_data);
          // printf("asad\n");
          if (sec_val != 0)
          {
            if ((node + max_marker)->next != NULL)
            {
              // printf("asd\n");
              if (sec_val < (node + max_marker)->next->_data && (node + max_marker)->next->_data < max_val)
              {
                printf("%d\n", (node + max_marker)->next->_data);
                free(node);
                break;
              }
            }

            if (sec_val != max_val)
            {
              printf("%d\n", sec_val);
              free(node);
              break;
            }
          }

          if (null >= (index_r - index_l + 1) && sec_val == 0)
          {
            printf("Tidak Ada!\n");
            free(node);
            break;
          }
          // printf("asad\n");
          marker = 1;
          j = 0;
          null = 0;
        }
      }
      else
        printf("Tidak Ada!\n");
    }
  }

  return 0;
}
