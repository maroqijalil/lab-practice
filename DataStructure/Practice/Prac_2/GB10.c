#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct bstnode_t {
  unsigned long long key;
  unsigned long long par;
  unsigned long long level;
  unsigned long long size;
  struct bstnode_t *left, *right;
} BSTNode;

typedef struct pqueueNode_t {
  unsigned long long _data;
  unsigned long long _par;
  struct pqueueNode_t *next;
  struct pqueueNode_t *prev;
} PQueueNode;

typedef struct pq_bst
{
  PQueueNode *_head;
  PQueueNode *_tail;
  unsigned long long _size;
} pQue_bst;

typedef struct bst_t {
  BSTNode *_root;
  unsigned long long _size;
  unsigned long long _pqueue_size;
} BST;

BSTNode* __bst__createNode(unsigned long long value, unsigned long long prevval, unsigned long long level) {
  // printf("flag4\n");
  BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
  newNode->key = value;
  newNode->par = prevval;
  newNode->level = level;
  newNode->size = 0u;
  newNode->left = newNode->right = NULL;
  // printf("flag5\n");
  return newNode;
}

BSTNode* insert_node(BSTNode* root, unsigned long long key) 
{
  unsigned long long prevval = 0;
  unsigned long long level = 1;

  BSTNode* node = root; 

  BSTNode* parent = NULL; 

  while (node != NULL) {
    prevval = node->key;
    // printf("%llu %llu\n", node->key, node->level);
    parent = node; 
    if (key < node->key) 
      node = node->left; 
    else
      node = node->right;
    level++;
  } 

  BSTNode* newnode = __bst__createNode(key, prevval, level);

  if (parent == NULL) 
    parent = newnode; 
  else if (key < parent->key) 
    parent->left = newnode; 
  else
    parent->right = newnode; 

  return newnode; 
} 
void pqueue_init(pQue_bst *pqueue)
{
  pqueue->_head = pqueue->_tail = NULL;
  pqueue->_size = 0;
}

bool pqueue_isEmpty(pQue_bst *pqueue) {
  return (pqueue->_head == NULL && pqueue->_tail == NULL);
}

PQueueNode* pqueue_push(pQue_bst *pqueue, unsigned long long data, unsigned long long prev)
{
  // printf("pq push\n");
  PQueueNode *temp = pqueue->_head;
  PQueueNode *newNode = (PQueueNode*)malloc(sizeof(PQueueNode));

  pqueue->_size++;

  newNode->_data = data;
  newNode->_par = prev;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (pqueue_isEmpty(pqueue))
  {
    pqueue->_head = pqueue->_tail = newNode;
    return newNode;
  }

  if (pqueue->_head == pqueue->_tail)
  {
    if (data < pqueue->_head->_data) {
      newNode->next = pqueue->_head;
      pqueue->_head->prev = newNode;
      pqueue->_head = newNode;
    }
    else
    {
      pqueue->_head->next = newNode;
      newNode->prev = pqueue->_head;
      pqueue->_tail = newNode;
    }

    return newNode;
  }
  else
  {
    if (data < pqueue->_head->_data) {
      newNode->next = pqueue->_head;
      pqueue->_head->prev = newNode;
      pqueue->_head = newNode;
    }
    else {
      while ( temp->next != NULL && temp->next->_data < data)
        temp = temp->next;
      if (temp == pqueue->_tail)
      {
        if (pqueue->_tail->_data < newNode->_data)
        {
          // printf("flag 1\n");
          newNode->prev = pqueue->_tail;
          pqueue->_tail->next = newNode;
          pqueue->_tail = newNode;
        }
        else
        {
          // printf("flag 2\n");
          newNode->prev = pqueue->_tail->prev;
          pqueue->_tail->prev->next = newNode;
          pqueue->_tail->prev = newNode;
          newNode->next = pqueue->_tail;
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

bool search_recur(BSTNode *root, unsigned long long value)
{  
  if (root != NULL)
  {
    if (root->par == value)
      return true;
    
    // if (root->left != NULL)
    // {
    //   if (root->left->key == value)
    //     return root->key;
    // }

    // if (root->right != NULL)
    // {
    //   if (root->right->key == value)
    //     return root->key;
    // }
    
    bool key = search_recur(root->left, value);
    
    if (key)
      return true;

    key = search_recur(root->right, value);
    
    if (key)
      return true;
  }

  return false;
}

BSTNode* __bst__search(BSTNode *root, unsigned long long value) {
  while (root != NULL) {
    if (value < root->key)
      root = root->left;
    else if (value > root->key)
      root = root->right;
    else
      return root;
  }
  return root;
}

BSTNode* __bst__findMinNode(BSTNode *node) {
  BSTNode *currNode = node;
  while (currNode && currNode->left != NULL)
    currNode = currNode->left;
  
  return currNode;
}

BSTNode* __bst__remove(BSTNode *root, unsigned long long value) {
  if (root == NULL) return NULL;

  if (value > root->key) 
    root->right = __bst__remove(root->right, value);
  else if (value < root->key) 
    root->left = __bst__remove(root->left, value);
  else {
      
    if (root->left == NULL) {
      BSTNode *rightChild = root->right;
      free(root);
      return rightChild;
    }
    else if (root->right == NULL) {
      BSTNode *leftChild = root->left;
      free(root);
      return leftChild;
    }

    BSTNode *temp = __bst__findMinNode(root->right);
    root->key     = temp->key;
    root->right   = __bst__remove(root->right, temp->key);
  }
  return root;
}

void __bst__inorder(BSTNode *root) {
  if (root) {
    __bst__inorder(root->left);
    printf("%llu ", root->key);
    __bst__inorder(root->right);
  }
}

void __bst__postorder(BSTNode *root) {
  // printf("flag1\n");
  if (root) {
    // printf("falg\n");
    __bst__postorder(root->left);
    __bst__postorder(root->right);
    printf("%llu ", root->key);
  }
}

void __bst__preorder(BSTNode *root) {
  if (root) {
    if (root->par != 0)
      printf("%llu..%llu >> ", root->key, root->par);
        
    __bst__preorder(root->left);
    __bst__preorder(root->right);
  }
}

void pque_init(pQue_bst *pqueue)
{
  pqueue->_head = pqueue->_tail = NULL;
  pqueue->_size = 0u;
}

void bst_init(BST *bst) {
  bst->_root = NULL;
  bst->_size = 0u;
  bst->_pqueue_size = 1u;
}

bool bst_isEmpty(BST *bst) {
  return bst->_root == NULL;
}

bool bst_find(BST *bst, unsigned long long value) {
  BSTNode *temp = __bst__search(bst->_root, value);
  if (temp == NULL)
    return false;
  
  if (temp->key == value)
    return true;
  else
    return false;
}

BSTNode* bst_insert(BST *bst, unsigned long long value) {
  if (!bst_find(bst, value)) {
    bst->_size++;
    if (bst->_root == NULL)
    {
      bst->_root = insert_node(bst->_root, value);
      // printf("%llu\n", pqueue->_head->key);
      
      return bst->_root;
    }

    BSTNode *newNode = insert_node(bst->_root, value);
    // printf("lev %llu siz %llu\n", newNode->level, (pqueue + (newNode->level - 1))->_size);

    return newNode;
  }
}

void bst_remove(BST *bst, unsigned long long value) {
  if (bst_find(bst, value)) {
    bst->_root = __bst__remove(bst->_root, value);
    bst->_size--;
  }
}

void bst_inorder(BST *bst) {
  __bst__inorder(bst->_root);
}

void bst_postorder(BST *bst) {
  __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
  __bst__preorder(bst->_root);
}

bool se_rec (BST *bst, unsigned long long value)
{
  return search_recur(bst->_root, value);
}

int main()
{
  BST set;
  pQue_bst *pqueue = (pQue_bst*)malloc(sizeof(pQue_bst));;
  bst_init(&set);
  // int j = 0;
  // while (j < 5)
    pque_init((pqueue));

  unsigned long long num;
  unsigned long long amu;
  unsigned long long input;
  unsigned long long mag;
  unsigned long long cap;
  unsigned long long count = 0;
  unsigned long long prevpar;
  unsigned long long size;

  scanf("%llu", &num);

  while (num--)
  {
    scanf("%llu", &input);

    BSTNode *bstnode = bst_insert(&set, input);

    if (set._pqueue_size < bstnode->level)
    {
      set._pqueue_size = bstnode->level;
      pqueue = realloc(pqueue, sizeof(pQue_bst*) * (bstnode->level+1));

      // while (set._pqueue_size < bstnode->level)
        pque_init((pqueue + (bstnode->level - 1)));
    }
    
    pqueue_push((pqueue + (bstnode->level - 1)), input, bstnode->par);
  }

  // printf("%llu\n", set._size);

  scanf("%llu %llu", &amu, &mag);
  // bst_inorder(&set);
  // printf("\n");

  cap = amu + (unsigned long long)(amu * mag);

  PQueueNode *node;

  int i = 0;

  while (i < set._pqueue_size)
  {
    node = (pqueue + i)->_head;
    printf("i:");
    while (node != NULL)
    {
      // printf("yok- ");
      printf(" %llu", node->_data);
      node = node->next;
    }
    i++;
    printf("\n");
  }
  // char *str = (char*)malloc(sizeof(char) * 5);
  
  // while (node != NULL)
  // {
  //   cap--;
  //   prevpar = node->_par;
  //   count += ((unsigned long long)log10(node->_data) + 1);
  //   count++;
  //   size = strlen(str);

  //   if (size <= count)
  //     str = realloc(str, sizeof(char*) * (count + 3 ));

  //   sprintf(str + size, " %llu", node->_data);

  //   // printf("%llu %llu %llu >> ", node->_level, node->_par, node->_data);

  //   // printf("%ld %llu >> ", strlen(str), cap);

  //   node = node->next;

  //   if (cap == 0)
  //   {
  //     // printf("%llu %llu %llu >> ", node->_level, node->_par, node->_data);
  //     break;
  //   }
  // }

  // // printf("\n");

  // if (node == NULL)
  //   printf("A 200 IQ play.\nKill:%s\n", str);
  // else if (cap < 1)
  // {
  //   if (prevpar != node->_par)
  //     printf("A 200 IQ play.\nKill:%s\n", str);
  //   else
  //     printf("Retard.\n");
  // }
  
  return 0;
}