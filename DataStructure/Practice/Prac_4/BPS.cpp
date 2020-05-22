#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

using namespace std; 

typedef struct queueNode_t {
    int data;
    struct queueNode_t *next;
} QueueNode;

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

bool search_key (Queue *q, int val)
{
  QueueNode *node = q->_front;
  while (node != NULL)
  {
    if (val == node->data)
      return true;

    node = node->next;
  }
  
  return false;
}

void queue_push(Queue *queue, int value)
{
  if (!search_key(queue, value))
  {
    QueueNode *newNode = (QueueNode*) malloc(sizeof(QueueNode));
    if (newNode) {
        queue->_size++;
        newNode->data = value;
        newNode->next = NULL;
        
        if (queue_isEmpty(queue))                 
            queue->_front = queue->_rear = newNode;
        else {
            queue->_rear->next = newNode;
            queue->_rear = newNode;
        }
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

int queue_front(Queue *queue)
{
    if (!queue_isEmpty(queue)) {
        return (queue->_front->data);
    }
    return (int)0;
}

int queue_size(Queue *queue) {
    return queue->_size;
}

void pushAdj_list(vector<int> adj_l[], int u, int v) 
{ 
	adj_l[u].push_back(v); 
	// adj_l[v].push_back(u); 
}

// queue<int> copy_queue(const std::queue<int> &Q) {    
//                         // ^^^^^
//     queue<int>Q2 = Q; 
//     return Q2;
// }


// queue<int> queue_push (queue<int> q, int val)
// {
//   queue<int> nQ = copy_queue(q);

//   while (!nQ.empty())
//   {
//     printf("masuk\n");
//     if (val == nQ.front())
//       return q;
//   }

//   q.push(val);

//   return q;
// }

void bfs(vector<int> adj[], int startNode, int n)
{
  bool visited[n];
  Queue ql;
  queue<int> q;

  q.push(startNode);
  queue_push(&ql, startNode);
  // visited[startNode] = 1;
  while (!q.empty())
  {
    int curNode = q.front();
    queue_push(&ql, curNode);

    // printf("%d ", curNode);

    q.pop();
    for (int i = 0; i < adj[curNode].size(); i++)
    {
      int nextNode = adj[curNode][i];
      queue_push(&ql, nextNode);
      // printf("%d\n", nextNode);
      // if (!visited[nextNode])
      // {
        q.push(nextNode);
        // visited[nextNode] = 1;
      // }
    }

    // printf("-> ");
  }

  while (!queue_isEmpty(&ql))
  {
    // printf("masuk\n");
    printf("%d -> ", queue_front(&ql));
    queue_pop(&ql);
  }
  
  printf("END\n");
}

int main() 
{ 
	int V;
  int E;
  int Vi;
  int Vj;
  int X;

  scanf("%d %d", &V, &E);
	vector<int> adj[V];

  while (E--)
  {
    scanf("%d %d", &Vi, &Vj);
    
  	pushAdj_list(adj, Vi, Vj);
  }

  scanf("%d", &X);

  bfs(adj, X, V);

	return 0; 
} 
