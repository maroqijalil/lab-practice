#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstnode_t {
    int key;
    struct bstnode_t \
        *left, *right;
} BSTNode;

typedef struct bst_t {
    BSTNode *_root;
    unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value) {
    BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->key = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int search_iter(BSTNode *root, int value) {
  while (root != NULL)
  {
    if (root->key == value)
      return -1;
    
    if (root->left != NULL)
    {
      if (root->left->key == value)
        return root->key;
    }

    if (root->right != NULL)
    {
      if (root->right->key == value)
        return root->key;
    }

    if (value < root->key)
      root = root->left;
    else if (value > root->key)
      root = root->right;
  }

  return 0;
}

int search_recur(BSTNode *root, int value)
{  
  if (root != NULL)
  {
    if (root->key == value)
      return -1;
    
    if (root->left != NULL)
    {
      if (root->left->key == value)
        return root->key;
    }

    if (root->right != NULL)
    {
      if (root->right->key == value)
        return root->key;
    }
    
    int key = search_recur(root->left, value);
    
    if (key)
      return key;

    key = search_recur(root->right, value);
    
    if (key)
      return key;
  }

  return 0;
}

void bst_init(BST *bst) {
    bst->_root = NULL;
    bst->_size = 0u;
}

bool bst_find(BST *bst, int value) {
  int temp = search_iter(bst->_root, value);
  
  if (temp)
    return true;
  else
    return false;
}

BSTNode* __bst__insert(BSTNode *root, int value)
{
  if (root == NULL) 
    return __bst__createNode(value);

  if (value < root->key)
    root->left = __bst__insert(root->left, value);
  else if (value > root->key)
    root->right = __bst__insert(root->right, value);
  
  return root;
}

void bst_insert(BST *bst, int value)
{
  if (!bst_find(bst, value)) {
    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
  }
}

int search_r(BST *bst, int value)
{
  return search_recur(bst->_root, value);
}

int search_i(BST *bst, int value)
{
  return search_iter(bst->_root, value);
}
 
int main()
{
    BST set;
    bst_init(&set);

    int query;
    int cmd;
    int input;

    scanf("%d", &query);

    while (query--)
    {
      scanf("%d %d", &cmd, &input);

      if (cmd == 1)
        bst_insert(&set, input);
      else if (cmd == 2)
        printf("%d\n", search_i(&set, input));
    }

    return 0;
}