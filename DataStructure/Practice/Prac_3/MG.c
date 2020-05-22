#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct AVLNode_t
{
    int data;
    struct AVLNode_t *left,*right;
    int height;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _max(int a,int b){
    return (a > b)? a : b;
}

int search_iter(AVLNode *node, int value)
{
  int i = 0;
  while (node != NULL)
  {
    i++;

    if (node->data > value)
      node = node->left;
    if (node->data < value)
      node = node->right;
    if (node->data == value)
      break;
  }
  
  if (node == NULL)
    return 0;
    
  return i;
}

AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                      _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                       _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value){
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
    	node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
		return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
    	node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
    	node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

	if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);
  
    if(balanceFactor<-1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor<-1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void avl_init(AVL *avl) {
    avl->_root = NULL;
    avl->_size = 0u;
}

bool avl_isEmpty(AVL *avl) {
    return avl->_root == NULL;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->_root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->_root=_insert_AVL(avl,avl->_root,value);
        avl->_size++;
    }

}

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }

}

int search_num(AVLNode *root, int val, int *ur) {
    int key;
    int num1;
    int num2;

    if (root) {
        if (root->data == val)
        {
          *ur = 0;
          return 1;
        }

        if (root->data > val)
        {
          if (root->left != NULL)
          {
            if (root->left->data == val)
            {
              *ur = root->data;
              return 1;
            }
            else
            {
              if (root->left->right != NULL)
              {
                if (root->left->right->data == val)
                {
                  if (root->right != NULL)
                    *ur = root->left->data - root->right->data;
                  else
                    *ur = root->left->data;
                  
                  return 1;
                }
              }
              
              if (root->left->left != NULL)
              {
                if (root->left->left->data == val)
                {
                  if (root->right != NULL)
                    *ur = root->left->data - root->right->data;
                  else
                    *ur = root->left->data;

                  return 1;
                }
              }
            } 
          }
          else if (root->left == NULL)
          {
            return 0;
          }
          
          key = search_num(root->left, val, ur);

          if (key)
            return key;
        }
        
        if (root->data < val)
        {
          if (root->right != NULL)
          {
            if (root->right->data == val)
            {
              *ur = root->data;
              return 1;
            }
            else
            {
              if (root->right->right != NULL)
              {
                if (root->right->right->data == val)
                {
                  if (root->left != NULL)
                    *ur = root->left->data - root->right->data;
                  else
                    *ur = root->right->data;

                  return 1;
                }
              }
              
              if (root->right->left != NULL)
              {
                if (root->right->left->data == val)
                {
                  if (root->left != NULL)
                    *ur = root->left->data - root->right->data;
                  else
                    *ur = root->right->data;

                  return 1;
                }
              }
            }
          }
          else if (root->right == NULL)
          {
            return 0;
          }
          
          key = search_num(root->right, val, ur);

          if (key)
            return key;
        }
    }

    return 0;
}

int
search_rec (AVLNode *node, int root_val, int val, int *counter, int *dif)
{
  int key = 0;

  // printf("masuk\n");

  if (node == NULL)
    return 0;
  
  if (node != NULL)
  {
    if (node->data == val)
    {
      *counter -= 1;
      // printf("counter\n");

      return 1;
    }
    else if (node->data < val)
    {
      key = search_rec(node->right, root_val, val, counter, dif);

      if (key)
      {
        *counter -= 1;

        if (root_val == node->data && *counter > 0)
          *dif = node->data;
        else if (*counter == 0)
        {
          if (node->left != NULL && node->right != NULL)
            *dif = abs(node->left->data - node->right->data);
          else if (node->left != NULL && node->right == NULL)
            *dif = abs(node->left->data);
          else if (node->left == NULL && node->right != NULL)
            *dif = abs(node->right->data);
        }

        return key;
      }
    }
    else if(node->data > val)
    {
      key = search_rec(node->left, root_val, val, counter, dif);

      if (key)
      {
        *counter -= 1;
        
        if (root_val == node->data && *counter > 0)
          *dif = node->data;
        if (*counter == 0)
        {
          if (node->left != NULL && node->right != NULL)
            *dif = abs(node->left->data - node->right->data);
          else if (node->left != NULL && node->right == NULL)
            *dif = abs(node->left->data);
          else if (node->left == NULL && node->right != NULL)
            *dif = abs(node->right->data);
        }

        return key;
      }
    }
  }

  return key;
}

int
main () {
  AVL avlku;
  int t;
  int num;
  int i;
  int n;
  int has;
  int counter = 3;

  avl_init(&avlku);

  scanf("%d %d", &t, &n);

  while (t--)
  {
    // printf("%d ..\n", t);
    scanf("%d", &num);

    avl_insert(&avlku, num);
  }

  while (n--)
  {
    has = 0;
    counter = 3;
    scanf("%d", &i);

    if (search_rec(avlku._root, avlku._root->data, i, &counter, &has))
      printf("%d ", abs(has));
  }

  return 0;
}