#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

#define N 102

using namespace std;

int way_adj(vector<int> adj[], vector<int> ad, int index, int n)
{
  int i;
  int way;
  int way1 = 0;
  // printf("%d: ", index);

  if (n == 0)
    return 0;

  for (i = 0; i < n; i++)
  {
    way = 1 + way_adj(adj, adj[adj[index][i]], adj[index][i], adj[adj[index][i]].size());

    if (way > way1)
      way1 = way;

    // printf("%d, ", way1);
  }

  return way1;
}

void pushAdj_list(vector<int> adj_l[], int u, int v) 
{ 
	adj_l[u].push_back(v); 
	// adj_l[v].push_back(u); 
}

int main() 
{
  int T;
  int ver[N];
  int n = 0;
  int input[2];
  int i;
  int k;
  int marker;
  int way = 0;
  int way1 = 0;

  scanf("%d", &T);

  vector<int> adj[N];

  while (n < T)
  {
    scanf("%d %d", &input[0], &input[1]);

    for (i = 0; i < 2; i++)
    {
      marker = 0;
      for (k = 0; k < n; k++)
      {
        if (input[i] == ver[k])
        {
          marker = 1;
          break;
        }
      }

      if (marker == 0)
        ver[n++] = input[i];
    }

    pushAdj_list(adj, input[0], input[1]);
  }

  for (i = 0; i < N; i++)
  {
    way = way_adj(adj, adj[i], i, adj[i].size());

    if (way > way1)
      way1 = way;
  }

  printf("%d\n", way1);

	return 0; 
} 
