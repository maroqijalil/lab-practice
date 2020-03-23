#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct bstnode_t {
  int key;
  int way;
  int dist;
  int l_min, r_min;
  int w_min;
  int ad_marker;
  struct bstnode_t *left, *right;
} BSTNode;

typedef struct bst_t {
  BSTNode *_root;
  unsigned int _size;
} BST;

BSTNode* __bst__createNode(int value, int way, int dist, int left, int right) {
  BSTNode *newNode = (BSTNode*) malloc(sizeof(BSTNode));
  newNode->key = value;
  newNode->way = way;
  newNode->dist = dist + way;
  newNode->l_min = left;
  newNode->r_min = right;
  newNode->w_min = 0;
  newNode->ad_marker = 0;
  newNode->left = newNode->right = NULL;
  return newNode;
}

BSTNode* __bst__insert(BSTNode *root, int value, int way, int dist, int left, int right) {
  if (root == NULL)
  {
    return __bst__createNode(value, way, dist, left, right);
  }

  dist += root->way;

  if (value < root->key)
  {
    root->left = __bst__insert(root->left, value, way, dist, left, right);

    root->ad_marker = 1;

    if (root->left)
    {
      // printf("before %d .. %d\n", root->key, root->l_min);

      if (root->left->left == NULL && root->left->right == NULL)
        root->l_min = root->left->way;
      else if (root->left->left == NULL && root->left->right != NULL)
        root->l_min = root->left->way + root->left->r_min;
      else if (root->left->left != NULL && root->left->right == NULL)
        root->l_min = root->left->way + root->left->l_min;
      else if (root->left->left != NULL && root->left->right != NULL)
      {
        if (root->left->ad_marker == 1)
        {
          if (root->left->l_min < root->left->r_min)
            root->l_min = root->left->l_min + root->left->way;
        }
        else if (root->left->ad_marker == 2)
        {
          if (root->left->r_min < root->left->l_min)
            root->l_min = root->left->r_min + root->left->way;
        }
      }

      root->left->w_min = root->l_min - root->left->way;
      // printf("after %d .. %d\n", root->key, root->l_min);
    }
  }
  else if (value > root->key)
  {
    // printf("flag\n");
    root->right = __bst__insert(root->right, value, way, dist, left, right);

    root->ad_marker = 2;

    if (root->right)
    {
      // printf("before %d .. %d\n", root->key, root->r_min);

      if (root->right->left == NULL && root->right->right == NULL)
        root->r_min = root->right->way;
      else if (root->right->left == NULL && root->right->right != NULL)
        root->r_min = root->right->way + root->right->r_min;
      else if (root->right->left != NULL && root->right->right == NULL)
        root->r_min = root->right->way + root->right->l_min;
      else if (root->right->left != NULL && root->right->right != NULL)
      {
        if (root->right->ad_marker == 1)
        {
          if (root->right->l_min < root->right->r_min)
            root->r_min = root->right->l_min + root->right->way;
        }
        else if (root->right->ad_marker == 2)
        {
          if (root->right->r_min < root->right->l_min)
            root->r_min = root->right->r_min + root->right->way;
        }
      }

      root->right->w_min = root->r_min - root->right->way;
      // printf("after %d .. %d\n", root->key, root->r_min);
    }
  }
  
  return root;
}

int search_recur(BSTNode *root, int value, int *result)
{  
  if (root != NULL)
  {
    int way;

    if (root->key == value)
    {
      *result = root->w_min;
      return root->way;
    }
    
    if (root->key > value)
    {
      way = search_recur(root->left, value, result);
      
      if (way)
      {
        if (root->right != NULL)
        {
          if ((root->r_min + way) < *result)
            *result = root->r_min + way;
        }

        // printf("%d\n", way);
        
        return (root->way + way);
      }
    }
    else if (root->key < value)
    {
      way = search_recur(root->right, value, result);
      
      if (way)
      {
        if (root->left != NULL)
        {
          if ((root->l_min + way) < *result)
            *result = root->l_min + way;
        }

        // printf("%d\n", way);

        return (root->way + way);
      }
    }
  }

  return 0;
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

void printminmax(BSTNode* root, int level)
{
	if (root == NULL)
  {
		return;
  }
	if (level == 1)
  {
    printf("%d %d l-%d r-%d w-%d >> ", root->key, root->way, root->l_min, root->r_min, root->w_min);
  } 
	else if (level > 1) 
	{
    printminmax(root->left, level-1);
    printminmax(root->right, level-1);
	}
  return;
} 

void bfs_traversal(BSTNode* root) 
{
	int h = height(root); 
	int i;
  
	for (i=1; i<=h; i++)
  {
    printf("%d: ", i);
		printminmax(root, i);
    printf("\n");
  }
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
    printf("%d %d l-%d r-%d >> ", root->key, root->dist, root->l_min, root->r_min);
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

void bst_insert(BST *bst, int value, int way) {
  if (!bst_find(bst, value)) {
    bst->_root = __bst__insert(bst->_root, value, way, 0, 0, 0);
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

int se_rec (BST *bst, int value)
{
  int w_result;
  if (bst->_root->key == value)
  {
    if (bst->_root->l_min < bst->_root->r_min)
      w_result = bst->_root->l_min;
    else
      w_result = bst->_root->r_min;
  }
  else
    search_recur(bst->_root, value, &w_result);
  
  return w_result;
}

void bst_bfs(BST *bst)
{
  bfs_traversal(bst->_root);
}
 
int main()
{
  BST set;
  bst_init(&set);

  int num;
  int way;
  int wanted;
  int input;
  int w_min;

  scanf("%d", &num);

  while (num--)
  {
    scanf("%d %d", &input, &way);

    bst_insert(&set, input, way);
  }

  scanf("%d", &wanted);
  bst_bfs(&set);
  // printf("\n");

  printf("%d\n", se_rec(&set, wanted));
  
  return 0;
}