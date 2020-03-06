#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct queueNode_t {
  int data;
  struct queueNode_t *next;
} QueueNode;

void init(QueueNode *node, int data)
{ 
  if (node != NULL) 
    return; 

  QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode)); 

  temp->data = data;
  temp->next = node; 
  node = temp;
} 
  
void add(QueueNode *node, int data) 
{ 
  if (node == NULL) 
    return init(node, data); 

  QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 

  temp->data = data; 
  temp->next = node->next; 
  node->next = temp;
} 
  
void app(QueueNode *node, int data) 
{ 
  if (node == NULL) 
    return init(node, data); 
    
  QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); 

  temp->data = data; 
  temp->next = node->next;
  node->next = temp;
  node = temp;
}
  
void print(QueueNode *last) 
{ 
  QueueNode *p; 

  if (last == NULL) 
  { 
    printf("List is empty.\n"); 
    return; 
  } 

  p = last -> next; 

  // Traversing the list. 
  do
  { 
    printf("%d ", p->data); 
    p = p -> next; 

  } 
  while(p != last->next);
}
  

// void queue_init(QueueNode *queue)
// {
//   queue->_size = 0;
//   queue->_front = NULL;
//   queue->_rear = NULL;
// }

// bool queue_isEmpty(QueueNode *queue) {
//   return (queue->_front == NULL && queue->_rear == NULL);
// }

// void queue_push(QueueNode *queue, int value)
// {
//   QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
//   if (newNode) {
//     queue->_size++;
//     newNode->data = value;
//     newNode->next = NULL;
    
//     if (queue_isEmpty(queue))                 
//       queue->_front = queue->_rear = newNode;
//     else {
//       queue->_rear->next = newNode;
//       queue->_rear = newNode;
//     }
//   }
// }

// void queue_pop(QueueNode *queue)
// {
//   if (!queue_isEmpty(queue)) {
//     QueueNode *temp = queue->_front;
//     queue->_front = queue->_front->next;
//     free(temp);
    
//     if (queue->_front == NULL)
//       queue->_rear = NULL;
//     queue->_size--;
//   }
// }

// int queue_front(QueueNode *queue)
// {
//   if (!queue_isEmpty(queue)) {
//     return (queue->_front->data);
//   }
//   return (int)0;
// }

// int queue_size(QueueNode *queue) {
//   return queue->_size;
// }

int main(int argc, char const *argv[])
{
  QueueNode *myQueue;

  int input;
  int target;
  int i = 1;
  int j = 0;

  scanf("%d %d", &input, &target);

  target++;

  init(myQueue, i++);
  
  QueueNode **temp = (QueueNode **)malloc(sizeof(QueueNode*)*input);

  QueueNode *next = myQueue;

  while (input--)
  {
    // if (i == input)
    // {
    //   app(myQueue, i);
    //   break;
    // }
    // else
    // {
      temp[j] = (QueueNode*)malloc(sizeof(QueueNode)); 
      
      temp[j]->data = i++; 
      temp[j]->next = next->next;
      next->next = temp[j++];
    // }
    next = next->next;
    printf("%d", next->data);
  }
  myQueue = next;

  printf("%d %d %d", myQueue->data, myQueue->next->data, myQueue->next->next->data);

  // while (myQueue->next != myQueue)
  // {
  //   printf("%d ", myQueue->data);
  //   myQueue = myQueue->next;
  // }

  return 0;
}
