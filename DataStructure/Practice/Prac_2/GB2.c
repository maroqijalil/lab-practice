#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct bstnode_t {
  int key;
  int par;
  struct bstnode_t *left, *right;
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

typedef struct bst_t {
  BSTNode *_root;
  unsigned int _size;
} BST;

void dStr_init(dStr *dstring)
{
  dstring->_capacity = 4u;
  dstring->_size = 0u;
  dstring->_str = (char*)malloc(sizeof(char) * 5);
}

BSTNode* __bst__createNode(int value, int prevval) {
  BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
  newNode->key = value;
  newNode->par = prevval;
  newNode->left = newNode->right = NULL;
  return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int prevval) {
  if (root == NULL)
  {
    return __bst__createNode(value, prevval);
  }

  prevval = root->key;

  if (value < root->key)
    root->left = __bst__insert(root->left, value, prevval);
  else if (value > root->key)
    root->right = __bst__insert(root->right, value, prevval);
  
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

bool printminmax(BSTNode* root, BSTNode* par, int level, gun *fire)
{
	if (root == NULL)
  {
    // printf("ret\n");
		return true;
  }
	if (level == 1)
  {
    // printf("%d %d. %d\n", prevpar, root->par, root->key);
    if ((fire->cap -= 1) >= 0)
    {
      fire->arr->_size += ((int)log10(root->key) + 1);
      // printf("%d\n", (int)log10(root->key) + 1);
      if (fire->arr->_size > fire->arr->_capacity)
      {
        // printf("flag1\n");
        fire->arr->_capacity += 3 * ((int)log10(root->key) + 1);
        fire->arr->_str = (char*)realloc(fire->arr->_str, sizeof(char) * fire->arr->_capacity);
      }
      // printf("flag\n");
      if (fire->cap > 0)
        sprintf(fire->arr->_str + strlen(fire->arr->_str), "%d ", root->key);
      if (fire->cap == 0)
        sprintf(fire->arr->_str + strlen(fire->arr->_str), "%d", root->key);
      // printf("%s %ld\n", num, strlen(num));
      // printf("%d %ld %d..\n", fire->cap, strlen(num), fire->arr->_capacity);
    }

    if (fire->cap == 0 && root != par)
    {
      if (root != par->right && par->right != NULL)
      {
      //  printf("lose");
       return false;
      }
    }
  } 
	else if (level > 1) 
	{
    if (fire->cap > 0)
    {
      par = root;
      // printf("flag3 %d..%d\n", level, root->key);
      if (!printminmax(root->left, par, level-1, fire))
        return false;
      // printf("%d..%d\n", level, root->key);
      if (!printminmax(root->right, par, level-1, fire))
        return false;
    }
	}

  return true;
} 

void bfs_traversal(BSTNode* root, gun *fire) 
{
	int h = height(root); 
	int i;
  float jml_l;
  
  // printf("...%d\n", h);
	for (i=h; i>=1; i--)
  {
    // printf("%d\n", i);
		if (printminmax(root, root, i, fire))
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
  if (root) {
    __bst__postorder(root->left);
    __bst__postorder(root->right);
    printf("%d ", root->key);
  }
}

void __bst__preorder(BSTNode *root) {
  if (root) {
    if (root->par != 0)
      printf("%d..%d ", root->key, root->par);
    __bst__preorder(root->left);
    __bst__preorder(root->right);
  }
}

void bst_init(BST *bst) {
  bst->_root = NULL;
  bst->_size = 0u;
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

void bst_insert(BST *bst, int value, int prevval) {
  if (!bst_find(bst, value)) {
    bst->_root = __bst__insert(bst->_root, value, prevval);
    bst->_size++;
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
  int count = 0;

  scanf("%d", &num);

  while (num--)
  {
    scanf("%d", &input);

    bst_insert(&set, input, 0);
  }

  scanf("%d %d", &amu, &mag);
  // bst_preorder(&set);
  // printf("\n");

  gun fire;
  fire.amu = amu;
  fire.mag = mag;
  fire.cap = amu + (amu*mag);
  dStr_init(fire.arr);

  bst_bfs(&set, &fire);
  
  return 0;
}