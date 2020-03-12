#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct stackNode_t {
  int data;
  struct stackNode_t *next;
} StackNode;

typedef struct stack_t {
  StackNode *_top;
  int result;
  unsigned _size;
} Stack;

void stack_init(Stack *stack) 
{
  stack->_size = 0;
  stack->_top = NULL;
  stack->result = 0;
}

bool stack_isEmpty(Stack *stack) {
  return (stack->_top == NULL);
}

void stack_push(Stack *stack, int value) 
{
  StackNode *newNode = (StackNode*) malloc(sizeof(StackNode));
  if (newNode) {
    newNode->data = value;
    if (stack_isEmpty(stack))
    {
      newNode->next = NULL;
      stack->_top = newNode;
      stack->_size++;
    }
    else
    {
      if (stack->_top->data > 0)
      {
        if (newNode->data < 0)
        {
          int num_temp = newNode->data*-1;
          
          if (num_temp == stack->_top->data)
          {
            StackNode *temp = stack->_top;
            stack->_top = stack->_top->next;

            free(temp);
            
            stack->_size--;
            stack->result++;

            return;
          }
        }
      }
      newNode->next = stack->_top;
      stack->_top = newNode;
      stack->_size++;
    }
  }
}

void stack_pop(Stack *stack) 
{
  if (!stack_isEmpty(stack)) {
    StackNode *temp = stack->_top;
    stack->_top = stack->_top->next;
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
  int i = 0;
  int arr[100] = {0};
  int num;
  Stack myStack;
  int input;

  stack_init(&myStack);

  scanf("%d", &num);

  while (num--)
  {
    scanf("%d", &input);
    stack_push(&myStack, input);
  }

  printf("%d\n", myStack.result*2);
  
  return 0;
}