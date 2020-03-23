#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct bstnode_t {
  int key;
  struct bstnode_t \
    *left, *right;
} BSTNode;

typedef struct result
{
  int num;
  int jml;
} re;

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

BSTNode* __bst__insert(BSTNode *root, int value) {
  if (root == NULL) 
    return __bst__createNode(value);

  if (value < root->key)
    root->left = __bst__insert(root->left, value);
  else if (value > root->key)
    root->right = __bst__insert(root->right, value);
  
  return root;
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

void __bst__inorder(BSTNode *root, int value, int* count) {
  if (root) {
    *count++;
    __bst__inorder(root->right, value, count);

    printf("%d %d ", root->key, *count);

    if (root->key == value)
      return;
    
    __bst__inorder(root->left, value, count);
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
    printf("%d ", root->key);
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

void bst_insert(BST *bst, int value) {
  if (!bst_find(bst, value)) {
    bst->_root = __bst__insert(bst->_root, value);
    bst->_size++;
  }
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

void printminmax(BSTNode* root, int level, re *res) 
{
	if (root == NULL) 
		return; 
	if (level == 1)
  {
    // printf("%d..", root->key);
    res->num += root->key;
    res->jml+=1;
  } 
	else if (level > 1) 
	{ 
    // printf("flag3\n");
		printminmax(root->left, level-1, res); 
		printminmax(root->right, level-1, res); 
	} 
} 

void bfs_traversal(BSTNode* root) 
{
  re result;
	int h = height(root); 
	int i;
  float jml_l;
  
  // printf("...%d\n", h);
	for (i=1; i<=h; i++)
  {
    result.jml = 0;
    result.num = 0;
    // printf("flag\n");
		printminmax(root, i, &result);
    jml_l = result.num/pow(2, i-1);
    // printf("\n");
    printf("Level %d = %.2f\n", i-1, jml_l);
  }
} 

void bst_remove(BST *bst, int value) {
  if (bst_find(bst, value)) {
    bst->_root = __bst__remove(bst->_root, value);
    bst->_size--;
  }
}

void bst_inorder(BST *bst, int value, int* count) {
  __bst__inorder(bst->_root, value, count);
}

void bst_postorder(BST *bst) {
  __bst__postorder(bst->_root);
}

void bst_preorder(BST *bst) {
  __bst__preorder(bst->_root);
}

void bst_bfs(BST *bst)
{
  bfs_traversal(bst->_root);
}
 
int main()
{
  int query;
  int cmd;
  int input;
  int count = 0;

  scanf("%d", &query);
  BST *set = (BST*)malloc(sizeof(BST));

  while (query--)
  {
    scanf("%d", &cmd);

    bst_init(&set[count]);

    while (cmd--)
    {
      scanf("%d", &input);
      bst_insert(&set[count], input);
    }

    bst_bfs(&set[count]);
    count++;
  }
  
  return 0;
}