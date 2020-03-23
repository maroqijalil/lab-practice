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

typedef struct dynamicstr_t
{
  char *_str;
  unsigned _size, _capacity;
} dStr;

typedef struct gun_t
{
  int amu;
  int mag;
  int cap;
  dStr *arr;
} gun;

typedef struct pq_bst
{
  BSTNode *_head;
  BSTNode *_tail;
  unsigned int _size;
} pQue_bst;

typedef struct bst_t {
  BSTNode *_root;
  pQue_bst *_pqueue;
  unsigned int _size;
  unsigned int _pqueue_size;
} BST;

void dStr_init(dStr *dstring)
{
  dstring->_capacity = 4u;
  dstring->_size = 0u;
  dstring->_str = (char*)malloc(sizeof(char) * 5);
}

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
    printf("%d %d\n", node->key, node->level);
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

BSTNode* __bst__insert(BSTNode *root, BSTNode *head, int head_s, BSTNode *node_l, BSTNode *node_r, int value, int prevval, int level) {
  if (root == NULL)
  {
    // printf("flag2\n");
    return __bst__createNode(value, prevval, level);
  }

  prevval = root->key;

  if (value < root->key)
  {
    // printf("flag\n");
    if (root->left == NULL)
    {
      if (root->right != NULL)
      {
        node_r = root->right;
        node_l = NULL;
      }
    }

    root->left = __bst__insert(root->left, head, head_s, node_l, node_r, value, prevval, level+1);
    // printf("flag6\n");

    if (root->right != NULL)
    {
      if (root->right->l_sibling == NULL)
        root->right->l_sibling = root->left;
    }
    // printf("flag3\n");
  }
  else if (value > root->key)
  {
    if (root->right == NULL)
    {
      if (root->left != NULL)
        node_l = root->left;
    }

    root->right = __bst__insert(root->right, head, head_s, node_l, node_r, value, prevval, level+1);

    if (root->left != NULL)
    {
      if (root->left->l_sibling == NULL)
        root->left->l_sibling = root->right;
    }
  }
  
  return root;
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

int height(BSTNode* node) 
{ 
	if (node==NULL) 
		return 0; 
	else
	{
		int lheight = height(node->left); 
		int rheight = height(node->right); 

		if (lheight > rheight) 
			return(lheight+1); 
		else return(rheight+1); 
	} 
} 

bool printminmax(BSTNode* root, int level, gun *fire)
{
	if (root == NULL)
  {
    // printf("ret\n");
		return true;
  }
	if (level == 1)
  {
    // printf("%d %d. %d\n", prevpar, root->par, root->key);
    fire->cap -= 1;
    
    fire->arr->_size += ((int)log10(root->key) + 1);
    // printf("%d\n", (int)log10(root->key) + 1);
    if (fire->arr->_size > fire->arr->_capacity)
    {
      // printf("flag1\n");
      fire->arr->_capacity += 3 * ((int)log10(root->key) + 1);
      fire->arr->_str = realloc(fire->arr->_str, sizeof(char*) * fire->arr->_capacity);
    }
    // printf("flag\n");
    if (fire->cap > 0)
      sprintf(fire->arr->_str + strlen(fire->arr->_str), "%d ", root->key);
    if (fire->cap == 0)
      sprintf(fire->arr->_str + strlen(fire->arr->_str), "%d", root->key);
    // printf("%s %ld\n", num, strlen(num));
    // printf("%d %ld %d..\n", fire->cap, strlen(num), fire->arr->_capacity);
    root->key = -1;
    
    if (fire->cap == 0)
    {
      if (root->l_sibling != NULL)
      {
        if (root->l_sibling->key != root->key)
          return false;
      }
    }
  } 
	else if (level > 1) 
	{
    if (fire->cap > 0)
    {
      // printf("flag3 %d..%d\n", level, root->key);
      if (!printminmax(root->left, level-1, fire))
        return false;
      // printf("%d..%d\n", level, root->key);
      if (!printminmax(root->right, level-1, fire))
        return false;
    }
	}

  return true;
} 

void bfs_traversal(BSTNode* root, gun *fire) 
{
	int h = height(root); 
	int i;
  
  // printf("...%d\n", h);
	for (i=h; i>=1; i--)
  {
    // printf("%d\n", i);
		if (printminmax(root, i, fire))
    {
      if (fire->cap == 0)
      {
        printf("A 200 IQ play.\nKill: %s\n", fire->arr->_str);
        break;
      }
      else if (fire->cap != 0 && i == 1)
        printf("A 200 IQ play.\nKill: %s\b\n", fire->arr->_str);
    }
    else
    {
      printf("Retard.\n");
      break;
    }
  }
  // printf("%d %d\n", fire->arr->_capacity, fire->arr->_size);
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

bool pqueue_isEmpty(pQue_bst *pqueue) {
  return (pqueue->_head == NULL && pqueue->_tail == NULL);
}

void pque_init(pQue_bst *pQ)
{
  // printf("pq init\n");
  pQ->_head = pQ->_tail = NULL;
  pQ->_size = 0u;
}

void bst_init(BST *bst) {
  bst->_root = NULL;
  bst->_size = 0u;
  bst->_pqueue_size = 0u;
  bst->_pqueue = NULL;
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

void bst_insert(BST *bst, int value) {
  if (!bst_find(bst, value)) {
    bst->_size++;
    if (bst->_root == NULL)
    {
      bst->_root = insert_node(bst->_root, value);
      bst->_pqueue = (pQue_bst*)malloc(sizeof(pQue_bst));
    
      pQue_bst *pqueue = bst->_pqueue;

      pque_init(pqueue);
      bst->_pqueue_size += 1;
      pqueue->_head = pqueue->_tail = bst->_root;
      pqueue->_size += 1;
      // printf("%d\n", pqueue->_head->key);
      
      return;
    }

    BSTNode *newNode = insert_node(bst->_root, value);

    // printf(" %d\n", newNode->level);

    if (bst->_pqueue_size < newNode->level)
      bst->_pqueue = (pQue_bst*)malloc(sizeof(pQue_bst) * newNode->level);
    
    pQue_bst *pqueue = bst->_pqueue;

    while (bst->_pqueue_size < newNode->level)
    {
      pque_init((pqueue + bst->_pqueue_size));
      bst->_pqueue_size += 1;
      // printf("%d\n", bst->_pqueue_size);
    }

    BSTNode *temp = (pqueue + (newNode->level - 1))->_head;
    (pqueue + (newNode->level - 1))->_size++;

    // printf("lev %d siz %d\n", newNode->level, (pqueue + (newNode->level - 1))->_size);

    if (pqueue_isEmpty((pqueue + (newNode->level - 1))))
    {
      (pqueue + (newNode->level - 1))->_head = (pqueue + (newNode->level - 1))->_tail = newNode;
      return;
    }

    // return;

    if ((pqueue + (newNode->level - 1))->_head == (pqueue + (newNode->level - 1))->_tail)
    {
      if (value < (pqueue + (newNode->level - 1))->_head->key) {
        newNode->r_sibling = (pqueue + (newNode->level - 1))->_head;
        (pqueue + (newNode->level - 1))->_head->l_sibling = newNode;
        (pqueue + (newNode->level - 1))->_head = newNode;
      }
      else
      {
        (pqueue + (newNode->level - 1))->_head->r_sibling = newNode;
        newNode->l_sibling = (pqueue + (newNode->level - 1))->_head;
        (pqueue + (newNode->level - 1))->_tail = newNode;
      }
    }
    else
    {
      if (value < (pqueue + (newNode->level - 1))->_head->key) {
        newNode->r_sibling = (pqueue + (newNode->level - 1))->_head;
        (pqueue + (newNode->level - 1))->_head->l_sibling = newNode;
        (pqueue + (newNode->level - 1))->_head = newNode;
      }
      else {
        while (temp->r_sibling != NULL && temp->r_sibling->key < value)
          temp = temp->r_sibling;
        if (temp == (pqueue + (newNode->level - 1))->_tail)
        {
          if ((pqueue + (newNode->level - 1))->_tail->key < newNode->key)
          {
            // printf("flag 1\n");
            newNode->l_sibling = (pqueue + (newNode->level - 1))->_tail;
            (pqueue + (newNode->level - 1))->_tail->r_sibling = newNode;
            (pqueue + (newNode->level - 1))->_tail = newNode;
          }
          else
          {
            // printf("flag 2\n");
            newNode->l_sibling = (pqueue + (newNode->level - 1))->_tail->l_sibling;
            (pqueue + (newNode->level - 1))->_tail->l_sibling->r_sibling = newNode;
            (pqueue + (newNode->level - 1))->_tail->l_sibling = newNode;
            newNode->r_sibling = (pqueue + (newNode->level - 1))->_tail;
          }
        }
        else
        {
            // printf("flag 3\n");
          newNode->l_sibling = temp;
          newNode->r_sibling = temp->r_sibling;
          temp->r_sibling->l_sibling = newNode;
          temp->r_sibling = newNode; 
        }
      }
    }
    // printf("%d..\n", pqueue->_head->key);
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

void bst_bfs(BST *bst, gun *fire)
{
  bfs_traversal(bst->_root, fire);
}
 
int main()
{
  BST set;
  bst_init(&set);

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

    bst_insert(&set, input);
  }

  scanf("%d %d", &amu, &mag);
  // bst_inorder(&set);
  // printf("\n");

  // gun fire;
  // fire.amu = amu;
  // fire.mag = mag;
  // fire.cap = amu + (amu*mag);
  // dStr_init(fire.arr);

  cap = amu + (amu * mag);
  pQue_bst *pqueue = set._pqueue;

  int i = 0;
  while (i < set._pqueue_size)
  {
    printf("%d %d: ", i+1, (pqueue + i)->_size);
    BSTNode *node = (pqueue + i)->_head;
    while (node != NULL)
    {
      printf("%d ", node->key);
      node = node->r_sibling;
    }
    printf("\n\n");
    i++;
    // sprintf( + strlen(fire->arr->_str), "%d", root->key)
  }

  // bst_bfs(&set, &fire);
  
  return 0;
}