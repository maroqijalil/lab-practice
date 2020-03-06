#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct dynamicarr_t {
  int *_arr;
  unsigned _size, _capacity;
} DynamicArray;

void dArray_init(DynamicArray *darray)
{
  darray->_capacity = 2u;
  darray->_size = 0u;
  darray->_arr = (int*) malloc(sizeof(int) * 2);
}

bool dArray_isEmpty(DynamicArray *darray) {
  return (darray->_size == 0);
}

void dArray_pushBack(DynamicArray *darray, int value)
{
  if (darray->_size + 1 > darray->_capacity) {
    unsigned it;
    darray->_capacity *= 2;
    int *newArr = (int*) malloc(sizeof(int) * darray->_capacity);

    for (it=0; it < darray->_size; ++it)
      newArr[it] = darray->_arr[it];
    
    int *oldArray = darray->_arr;
    darray->_arr = newArr;
    free(oldArray);
  }
  darray->_arr[darray->_size++] = value;
}

void dArray_popBack(DynamicArray *darray) {
  if (!dArray_isEmpty(darray)) darray->_size--;
  else return;
}

int dArray_back(DynamicArray *darray) {
  if (!dArray_isEmpty(darray))
    return darray->_arr[darray->_size-1];
  else return 0;
}

int dArray_front(DynamicArray *darray) {
  if (!dArray_isEmpty(darray))
    return darray->_arr[0];
  else return 0;
}

void dArray_setAt(DynamicArray *darray, unsigned index, int value)
{
  if (!dArray_isEmpty(darray)) {
    if (index >= darray->_size)
      darray->_arr[darray->_size-1] = value;
    else
      darray->_arr[index] = value;
  }
}

int dArray_getAt(DynamicArray *darray, unsigned index)
{
  if (!dArray_isEmpty(darray)) {
    if (index >= darray->_size)
      return darray->_arr[darray->_size-1];
    else
      return darray->_arr[index];
  }
}

int main(int argc, char const *argv[])
{
  DynamicArray myArray;
  int query;
  int input;
  int minta;
  int i = 0;

  dArray_init(&myArray);

  scanf("%d", &query);

  while (query--)
  {
    scanf("%d", &input);
    dArray_pushBack(&myArray, input);
  }

  scanf("%d", &minta);

  for (i = 0; i < myArray._size; i++)
  {
    if (minta == dArray_getAt(&myArray, i))
    {
      printf("%d\n", myArray._size - (i+1));
      return 0;
    }
  }

  printf("Barangnya gak ada beb\n");
  return 0;
}
