#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct queueNode_t {
    int data;
    int ap;
    struct queueNode_t *next;
} QueueNode;

/* Struktur ADT Queue */

typedef struct queue_t {
    QueueNode   *_front, 
                *_rear;
    unsigned _size;
} Queue;

void queue_init(Queue *queue)
{
    queue->_size = 0;
    queue->_front = NULL;
    queue->_rear = NULL;
}

bool queue_isEmpty(Queue *queue) {
    return (queue->_front == NULL && queue->_rear == NULL);
}

void queue_push(Queue *queue, int value, int ap)
{
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->ap = ap;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
    }
}

void queue_pop(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        QueueNode *temp = queue->_front;
        queue->_front = queue->_front->next;
        free(temp);
        
        if (queue->_front == NULL)
            queue->_rear = NULL;
        queue->_size--;
    }
}

typedef struct pqueueNode_t {
    int data;
    int ap;
    struct pqueueNode_t *next;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

// Prioritas default: nilai minimum
typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value, int ap);
void pqueue_pop(PriorityQueue *pqueue);
PQueueNode*  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value, int ap)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = \
        (PQueueNode*) malloc (sizeof(PQueueNode));
    
    pqueue->_size++;
    newNode->data = value;
    newNode->ap = ap;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        return;
    }

    if (value < pqueue->_top->data) {
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;
    }
    else {
        while ( temp->next != NULL && 
                temp->next->data < value)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        pqueue->_size--;
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        free(temp);
    }
}

PQueueNode* pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top;
    else return NULL;
}

typedef struct AVLNode_t
{
    int data;
    int _ap;
    struct AVLNode_t *left,*right;
    int height;
    int r_child;
    int l_child;
    int l_height;
    int r_height;
    int num_child;
}AVLNode;

typedef struct AVL_t
{
    AVLNode *_root;
    unsigned int _size;
}AVL;

AVLNode* _avl_createNode(int value, int ap) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->_ap = ap;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    newNode->r_child = newNode->l_child =\
    newNode->num_child = newNode->l_height =\
    newNode->r_height = 0;
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

int _calculateChildNum (AVLNode* node)
{
    if(node == NULL)
        return 0;

    if (node->left != NULL)
      node->l_child = 1 + node->left->num_child;
    else
      node->l_child = 0;

    if (node->right != NULL)
      node->r_child = 1 + node->right->num_child;
    else
      node->r_child = 0;
    
    return node->r_child + node->l_child;
}

int _calculateHeight (AVLNode* node)
{
    if(node == NULL)
        return 0;

    node->l_height = 1 + _getHeight(node->left);
    node->r_height = 1 + _getHeight(node->right);

    return _max(node->l_height, node->r_height);
}

AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent = pivotNode->left;
    pivotNode->left = newParrent->right;
    newParrent->right = pivotNode;

    pivotNode->height = _calculateHeight(pivotNode);  
    pivotNode->num_child = _calculateChildNum(pivotNode);

    newParrent->height = _calculateHeight(newParrent); 
    newParrent->num_child = _calculateChildNum(newParrent);
    
    return newParrent;
}

AVLNode* _leftRotate(AVLNode* pivotNode) {

    AVLNode* newParrent = pivotNode->right;
    pivotNode->right = newParrent->left;
    newParrent->left = pivotNode;

    pivotNode->height = _calculateHeight(pivotNode);
    pivotNode->num_child = _calculateChildNum(pivotNode);

    newParrent->height = _calculateHeight(newParrent);
    newParrent->num_child = _calculateChildNum(newParrent);
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left = _leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right = _rightRotate(node->right);
    return _leftRotate(node);
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _setRight (AVLNode* node, int balanceFactor)
{    
    if(node == NULL)
        return node;

    if (balanceFactor <= 1 && balanceFactor >= -1)
    {
      if (balanceFactor == 1)
      {
        if (node->left->r_height > node->left->l_height)
          node = _leftRightCaseRotate(node);
        else
          node = _leftCaseRotate(node);
      }
      else if (balanceFactor == 0 && (node->l_child > node->r_child))
      {
        if (node->left->r_height > node->left->l_height)
          node = _leftRightCaseRotate(node);
        else
          node = _leftCaseRotate(node);
      }
    }
    
    return node;
}

void avl_setRight (AVL *avl)
{
  AVLNode *node = avl->_root;

  if(node)
  {
    int balanceFactor = _getBalanceFactor(node);

    if (balanceFactor == 0 || balanceFactor == 1)
      avl->_root = _setRight(node, balanceFactor);
  }
}

AVLNode* _insert_AVL (AVL *avl, AVLNode* node, int value, int ap)
{    
    if(node == NULL)
        return _avl_createNode(value, ap);
    if(value < node->data)
        node->left = _insert_AVL(avl, node->left, value, ap);
    else if(value > node->data)
    	  node->right = _insert_AVL(avl, node->right, value, ap);
    
    node->height= _calculateHeight(node);
    node->num_child = _calculateChildNum(node);

    int balanceFactor = _getBalanceFactor(node);

    // if (balanceFactor == 0 || balanceFactor == 1)
    //   node = _setRight(node, balanceFactor);
    // else
    // {
      if(balanceFactor > 1 && value < node->left->data)
        node = _leftCaseRotate(node);
      else if(balanceFactor > 1 && value > node->left->data)
        node = _leftRightCaseRotate(node);
      else if(balanceFactor < -1 && value > node->right->data)
        node = _rightCaseRotate(node);
      else if(balanceFactor < -1 && value < node->right->data)
        node = _rightLeftCaseRotate(node);
    // }
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node)
{
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

void avl_insert(AVL *avl,int value, int ap)
{
    if(!avl_find(avl, value)){
        avl->_root=_insert_AVL(avl, avl->_root, value, ap);
        avl->_size++;
    }
}

void avl_remove(AVL *avl,int value){
    if(avl_find(avl,value)){
        avl->_root=_remove_AVL(avl->_root,value);
        avl->_size--;
    }

}

void printCharacter(int id){
	if(id == -1){
		printf("Tidak ada pemenang\n");
		return;
	}
	switch(id){
		case 1: printf("Elpis\n");
				break;
		case 2: printf("Leonard\n");
				break;
		case 3: printf("Haza\n");
				break;
		case 4: printf("Pupuro\n");
				break;
		case 5: printf("Horus\n");
				break;
		case 6: printf("Xiwangmu\n");
				break;
		case 7: printf("Nuwa\n");
				break;
		case 8: printf("Yog\n");
				break;
		case 9: printf("Giemsa\n");
				break;
		case 10: printf("Reimu\n");
				break;
		case 11: printf("Cang Bi\n");
				break;
		case 12: printf("Radha\n");
				break;
		case 13: printf("Aurora\n");
				break;
		case 14: printf("Astrid\n");
				break;
		case 15: printf("Ralph\n");
				break;
		case 16: printf("Shamash\n");
				break;
		case 17: printf("Enlil\n");
				break;
		case 18: printf("Marduk\n");
				break;
		case 19: printf("Veronica\n");
				break;
		case 20: printf("Marisa\n");
				break;
		case 21: printf("Spencer\n");
				break;
		case 22: printf("Diamond\n");
				break;
		case 23: printf("Amber\n");
				break;
		case 24: printf("Jade\n");
				break;
		case 25: printf("Sapphire\n");
				break;
		case 26: printf("Ruby\n");
				break;
		case 27: printf("Lyndis\n");
				break;
		case 28: printf("Florina\n");
				break;
		case 29: printf("Fiora\n");
				break;
		case 30: printf("Sakuya\n");
				break;
		case 31: printf("Farina\n");
				break;
		case 32: printf("Nino\n");
				break;
		case 33: printf("Renault\n");
				break;
		case 34: printf("Eirika\n");
				break;
		case 35: printf("Vanessa\n");
				break;
		case 36: printf("Tana\n");
				break;
		case 37: printf("Syrene\n");
				break;
		case 38: printf("Amelia\n");
				break;
		case 39: printf("Joshua\n");
				break;
		case 40: printf("Alice\n");
				break;
		case 41: printf("Hansekyo\n");
				break;
		case 42: printf("Dwuaykicong\n");
				break;
		case 43: printf("NETral\n");
				break;
		case 44: printf("iNSANiTY\n");
				break;
		case 45: printf("Vinseks\n");
				break;
		case 46: printf("Aiedail\n");
				break;
		case 47: printf("Heisser\n");
				break;
		case 48: printf("MAXiMUSE\n");
				break;
		case 49: printf("p03tato\n");
				break;
		case 50: printf("Youmu\n");
				break;
		case 51: printf("Ikta\n");
				break;
		case 52: printf("Franz\n");
				break;
		case 53: printf("Zephiel\n");
				break;
		case 54: printf("Idunn\n");
				break;
		case 55: printf("Shanna\n");
				break;
		case 56: printf("thea\n");
				break;
		case 57: printf("Juno\n");
				break;
		case 58: printf("Yaisyeky\n");
				break;
		case 59: printf("Gerik\n");
				break;
		case 60: printf("Mayumi\n");
				break;
		case 61: printf("Cecilia\n");
				break;
		case 62: printf("Sophia\n");
				break;
		case 63: printf("Douglas\n");
				break;
		case 64: printf("Duessel\n");
				break;
	}
}

void printStat (int id, int data, int ur)
{

  if (data != 0)
  {
    printf("Pemenang pertarungan ke-%d: ", ur);
    printCharacter(id);
  }
  else 
    printf("Pemenang pertarungan ke-%d: Tidak ada pemenang\n", ur);
}

void gameplay (AVLNode *node, int prev, int *ur)
{
  if (node)
  {
    gameplay(node->left, 1, ur);

    if (prev > 0)
    {
      if (node->left != NULL)
      {
        *ur += 1;
        
        if ((node->_ap -= node->left->_ap) < 0)
        {
          node->data = node->left->data;
          node->_ap = abs(node->_ap);
        }

        printStat(node->data, node->_ap, *ur);
      }
    }
    else if (prev < 0)
    {
      if (node->right != NULL)
      {
        *ur += 1;

        if ((node->_ap -= node->right->_ap) < 0)
        {
          node->data = node->right->data;
          node->_ap = abs(node->_ap);
        }

        printStat(node->data, node->_ap, *ur);
      }

      if (node->left != NULL)
      {
        *ur += 1;
        
        if ((node->_ap -= node->left->_ap) < 0)
        {
          node->data = node->left->data;
          node->_ap = abs(node->_ap);
        }

        printStat(node->data, node->_ap, *ur);
      }
    }
    
    gameplay(node->right, -1, ur);

    if (node->right != NULL)
    {
      *ur += 1;
      
      if ((node->_ap -= node->right->_ap) < 0)
      {
        node->data = node->right->data;
        node->_ap = abs(node->_ap);
      }

      printStat(node->data, node->_ap, *ur);
    }
  }
}

void preorder(AVLNode *root) {
    if (root)
    {
        preorder(root->left);
        // printf("%d n:%d l:%d r:%d h:%d\n", root->data,\
        //       root->num_child, root->l_child, root->r_child,\
        //       root->height);
        // printf("%d ", root->data);
        preorder(root->right);
    }
}


int height(AVLNode* node) 
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

void printminmax(AVLNode* root, int level) 
{
	if (root == NULL) 
		return; 
	if (level == 1)
  {
    printf("%d ", root->data);
    return;
  } 
	else if (level > 1) 
	{ 
		printminmax(root->left, level-1); 
		printminmax(root->right, level-1); 
	} 
} 

void bfs_traversal(AVLNode* root) 
{
	int h = height(root); 
	int i;
  double jml_l;
  
	for (i=1; i<=h; i++)
  {
    printf("Level-%d: ", i);
    printminmax(root, i);
    printf("\n");
  }
} 

int main()
{
  AVL avlku;
  PriorityQueue myPQ;
  Queue myQ;

  int t;
  int num;
  int ap;
  int ur = 0;
  int mux = 1;

  avl_init(&avlku);
  pqueue_init(&myPQ);
  queue_init(&myQ);

  scanf("%d", &t);

  while (t--)
  {
    scanf("%d %d", &num, &ap);

    pqueue_push(&myPQ, num, ap);
  }

  while (myPQ._size > 0)
  {
    PQueueNode* node = pqueue_top(&myPQ);

    queue_push(&myQ, node->data, node->ap);
    avl_insert(&avlku, node->data, node->ap);

    pqueue_pop(&myPQ);
  }

  Queue ql;
  QueueNode *node1;
  QueueNode *node2;

  queue_init(&ql);

  while (avlku._root->l_child >= 0)
  {
    node1 = myQ._front;
    queue_pop(&myQ);
    avlku._root->l_child -= 1;

    if (node1->data != avlku._root->data && avlku._root->l_child > 1)
    {
      node2 = myQ._front;
      queue_pop(&myQ);
      avlku._root->l_child -= 1;

      // if (node2->data != avlku._root->data && avlku._root->l_child > 0)
      // {
        if (node1->ap -= node2->ap < 0)
        {
          node1->data = node2->data;
          node1->ap = abs(node1->ap);
        }

        queue_push(&ql, node1->data, node1->ap);
      // }
      // else
      // {
      //   queue_push(&ql, node1->data, node1->ap);
      // }
    }
    else
    {
      if (avlku._root->l_child == 1)
        queue_push(&ql, node1->data, node1->ap);
      else if (avlku._root->l_child == 0)
      {
        node2 = myQ._front;
        queue_pop(&myQ);
        avlku._root->l_child -= 1;

        if (node1->ap -= node2->ap < 0)
        {
          node1->data = node2->data;
          node1->ap = abs(node1->ap);
        }

        queue_push(&ql, node1->data, node1->ap);
      }
    }

    if (ql._size == 2 && avlku._root->l_child > 1)
    {
      node1 = ql._front;
      node2 = ql._rear;
    }
  }

  preorder(avlku._root);

  return 0;
}