#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct dynamicarr_t {
  int *_arr;
  int pen;
  unsigned _size, _capacity;
} DynamicArray;

void dArray_init(DynamicArray *darray)
{
  darray->_capacity = 2u;
  darray->_size = 0u;
  darray->pen = 0;
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
  if (value == 0)
    darray->pen++;
  else
    darray->pen--;
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

void dArr_removeAt(DynamicArray *arr, unsigned index)
{
  int i, k = 0;
  arr->_size--;

  for (i = index - 1; i <= arr->_size - 1; i++)
  {
    arr->_arr[i] = arr->_arr[i + 1];
  }

  arr->_arr[arr->_size] = 0;
}

int main(int argc, char const *argv[])
{
  DynamicArray myArray;
  DynamicArray hasil;
  int query;
  int input;
  int target;
  int i = 0;

  dArray_init(&myArray);
  dArray_init(&hasil);

  scanf("%d %d", &input, &target);

  query = input;
  while (query--)
  {
    i++;
    dArray_pushBack(&myArray, i);
  }

  i = 0;
  while (myArray.pen != 1)
  {
    i+=(target+1);
    if (i > input)
    {
      i -= input;
    }
    printf("%d\n", i);
    // printf("%d ", dArray_getAt(&myArray, i-1));
    dArray_pushBack(&myArray, 0);
  }

  printf("~ %d\n", dArray_getAt(&myArray, i+1));
  return 0;
}
