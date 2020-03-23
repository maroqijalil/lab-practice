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
      while (temp->next != NULL && temp->next->_level > lev)
        temp = temp->next;
      if (temp == pqueue->_tail)
      {
        // printf("tail\n");
        if (pqueue->_tail->_level > newNode->_level)
        {
          // printf("flag 1\n");
          newNode->prev = pqueue->_tail;
          pqueue->_tail->next = newNode;
          pqueue->_tail = newNode;
        }
        else if (pqueue->_tail->_level < newNode->_level)
        {
          // printf("flag 2\n");
          newNode->prev = pqueue->_tail->prev;
          pqueue->_tail->prev->next = newNode;
          pqueue->_tail->prev = newNode;
          newNode->next = pqueue->_tail;
        }
        else if (pqueue->_tail->_level == newNode->_level)
        {
          if (newNode->_data < pqueue->_tail->_data) {
            pqueue->_tail->prev->next = newNode;
            newNode->prev = pqueue->_tail->prev;
            newNode->next = pqueue->_tail;
            pqueue->_tail->prev = newNode;
          }
          else
          {
            pqueue->_tail->next = newNode;
            newNode->prev = pqueue->_tail;
            pqueue->_tail = newNode;
          }
        }
      }
      else if (temp->next->_level < newNode->_level)
      {
        // printf("lev < lev\n");
        if (temp->_data < newNode->_data)
        {
          newNode->prev = temp;
          newNode->next = temp->next;
          temp->next->prev = newNode;
          temp->next = newNode;
        }
        else
        {
          if (temp == pqueue->_head)
          {
            newNode->next = pqueue->_head;
            pqueue->_head->prev = newNode;
            pqueue->_head = newNode;
          }
          else
          {
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            newNode->next = temp;
            temp->prev = newNode;
          }
        }
      }
      else if (temp->next->_level == newNode->_level)
      {
        // printf("lev = lev\n");
        while (temp->next != NULL && temp->next->_data < data && temp->next->_level == lev)
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
          newNode->prev = temp;
          newNode->next = temp->next;
          temp->next->prev = newNode;
          temp->next = newNode;
        }
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

  scanf("%d", &num);

  while (num--)
  {
    scanf("%d", &input);

    bst_insert(&set, &pqueue, input);
  }

  scanf("%d %d", &amu, &mag);
  // bst_inorder(&set);
  // printf("\n");

  cap = amu + (amu * mag);

  PQueueNode *node = pqueue._head;
  
  int i = 0;
  while (i < pqueue._size)
  {
    printf("%d %d >> ", node->_level, node->_data);
    node = node->next;
    i++;
  // return 0;
    // sprintf( + strlen(fire->arr->_str), "%d", root->key)
  }

  // bst_bfs(&set, &fire);
  
  return 0;
}