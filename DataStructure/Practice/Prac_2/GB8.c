#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct bstnode_t {
  int key;
  int par;
  int level;
  unsigned int size;
  struct bstnode_t *left, *right;
  struct bstnode_t *l_sibling, *r_sibling;
} BSTNode;

typedef struct pqueueNode_t {
  int _data;
  int _par;
  int _level;
  struct pqueueNode_t *next;
  struct pqueueNode_t *prev;
} PQueueNode;

typedef struct pq_bst
{
  PQueueNode *_head;
  PQueueNode *_tail;
  unsigned int _size;
} pQue_bst;

typedef struct bst_t {
  BSTNode *_root;
  unsigned int _size;
  unsigned int _pqueue_size;
} BST;

BSTNode* __bst__createNode(int value, int prevval, int level) {
  // printf("flag4\n");
  BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
  newNode->key = value;
  newNode->par = prevval;
  newNode->level = level;
  newNode->size = 0u;
  newNode->left = newNode->right = NULL;
  newNode->l_sibling = newNode->r_sibling = NULL;
  // printf("flag5\n");
  return newNode;
}

BSTNode* insert_node(BSTNode* root, int key) 
{
  int prevval = 0;
  int level = 1;

  BSTNode* node = root; 

  BSTNode* parent = NULL; 

  while (node != NULL) {
    prevval = node->key;
    // printf("%d %d\n", node->key, node->level);
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

PQueueNode* pqueue_push(pQue_bst *pqueue, int data, int prev, int lev)
{
  // printf("pq push\n");
  PQueueNode *temp = pqueue->_head;
  PQueueNode *newNode = (PQueueNode*)malloc(sizeof(PQueueNode));

  pqueue->_size++;

  newNode->_data = data;
  newNode->_par = prev;
  newNode->_level = lev;
  newNode->next = NULL;
  newNode->prev = NULL;

  // printf("new\n");

  if (pqueue_isEmpty(pqueue))
  {
    // printf("new2\n");
    pqueue->_head = pqueue->_tail = newNode;
    return newNode;
  }

  if (pqueue->_head == pqueue->_tail)
  {
    // printf("head tail\n");
    if (lev > pqueue->_head->_level) {
      // printf("flag\n");
      newNode->next = pqueue->_head;
      pqueue->_head->prev = newNode;
      pqueue->_head = newNode;
    }
    else if (pqueue->_head->_level > lev)
    {
      // printf("flag1\n");
      pqueue->_head->next = newNode;
      newNode->prev = pqueue->_head;
      pqueue->_tail = newNode;
    }
    else if (pqueue->_head->_level == lev)
    {
      // printf("flag2\n");
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
    }

    return newNode;
  }
  else
  {
    // printf("non ht\n");
    if (lev > pqueue->_head->_level)
    {
      newNode->next = pqueue->_head;
      pqueue->_head->prev = newNode;
      pqueue->_head = newNode;
    }
    else
    {
      while (temp->next != NULL && temp->_level > lev)
        temp = temp->next;
      
      if (temp == pqueue->_head)
      {
        if (pqueue->_head->_level < newNode->_level)
        {
          // printf("flag 2\n");
          newNode->next = pqueue->_head;
          pqueue->_head->prev = newNode;
          pqueue->_head = newNode;
          // return newNode;
        }
        else if (pqueue->_head->_level == newNode->_level)
        {
          // printf("head = new\n");
          if (pqueue->_head->_data > newNode->_data)
          {
            // printf("flag 2\n");
            newNode->next = pqueue->_head;
            pqueue->_head->prev = newNode;
            pqueue->_head = newNode;
            // return newNode;
          }
          else
          {
            while (temp->next != NULL && temp->_data < newNode->_data && temp->_level == newNode->_level)
              temp = temp->next;

            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
          }
        }
      }
      else if (temp->_level < newNode->_level)
      {
        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
      }
      else if (temp->_level == newNode->_level)
      {
        // printf("lev = lev\n");
        while (temp->next != NULL && temp->_data < data && temp->_level == lev)
          temp = temp->next;

        newNode->next = temp;
        newNode->prev = temp->prev;
        temp->prev->next = newNode;
        temp->prev = newNode;
      }
    }
    return newNode;
  }
  // printf("done\n");
}

bool search_recur(BSTNode *root, int value)
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

BSTNode* __bst__search(BSTNode *root, int value) {
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

BSTNode* __bst__remove(BSTNode *root, int value) {
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
    printf("%d ", root->key);
    __bst__inorder(root->right);
  }
}

void __bst__postorder(BSTNode *root) {
  // printf("flag1\n");
  if (root) {
    // printf("falg\n");
    __bst__postorder(root->left);
    __bst__postorder(root->right);
    printf("%d ", root->key);
  }
}

void __bst__preorder(BSTNode *root) {
  if (root) {
    if (root->par != 0)
      printf("%d..%d >> ", root->key, root->par);
        
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
  bst->_pqueue_size = 0u;
}

bool bst_isEmpty(BST *bst) {
  return bst->_root == NULL;
}

bool bst_find(BST *bst, int value) {
  BSTNode *temp = __bst__search(bst->_root, value);
  if (temp == NULL)
    return false;
  
  if (temp->key == value)
    return true;
  else
    return false;
}

void bst_insert(BST *bst, pQue_bst *pQ, int value) {
  if (!bst_find(bst, value)) {
    bst->_size++;
    if (bst->_root == NULL)
    {
      bst->_root = insert_node(bst->_root, value);
      bst->_pqueue_size += 1;
      pqueue_push(pQ, value, bst->_root->par, bst->_root->level);
      // printf("%d\n", pqueue->_head->key);
      
      return;
    }

    BSTNode *newNode = insert_node(bst->_root, value);
    pqueue_push(pQ, value, newNode->par, newNode->level);

    // printf("lev %d siz %d\n", newNode->level, (pqueue + (newNode->level - 1))->_size);
  }
}

void bst_remove(BST *bst, int value) {
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

bool se_rec (BST *bst, int value)
{
  return search_recur(bst->_root, value);
}

int main()
{
  BST set;
  pQue_bst pqueue;
  bst_init(&set);
  pqueue_init(&pqueue);

  int num;
  int amu;
  int input;
  int mag;
  int cap;
  int count = 0;
  int prevpar;
  int size;

  scanf("%d", &num);

  while (num--)
  {
    scanf("%d", &input);

    bst_insert(&set, &pqueue, input);
  }

  // printf("%d\n", set._size);

  scanf("%d %d", &amu, &mag);
  // bst_inorder(&set);
  // printf("\n");

  cap = amu + (int)(amu * mag);

  PQueueNode *node = pqueue._head;
  char *str = (char*)malloc(sizeof(char) * 5);
  
  while (node != NULL)
  {
    cap--;
    prevpar = node->_par;
    count += ((int)log10(node->_data) + 1);
    count++;
    size = strlen(str);

    if (size <= count)
      str = realloc(str, sizeof(char*) * (count + 3 ));

    if (node->next != NULL && cap > 0)
      sprintf(str + size, "%d ", node->_data);
    else if (node->next == NULL || cap == 0)
      sprintf(str + size, "%d", node->_data);

    // printf("%d %d %d >> ", node->_level, node->_par, node->_data);

    // printf("%ld %d >> ", strlen(str), cap);

    node = node->next;

    if (cap == 0)
    {
      // printf("%d %d %d >> ", node->_level, node->_par, node->_data);
      break;
    }
  }

  // printf("\n");

  if (node == NULL)
    printf("A 200 IQ play.\nKill: %s\n", str);
  else if (cap < 1)
  {
    if (prevpar != node->_par)
      printf("A 200 IQ play.\nKill: %s\n", str);
    else
      printf("Retard.\n");
  }
  
  return 0;
}