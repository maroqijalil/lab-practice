#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct pqueueNode_t {
  int _hp;
  int _atk;
  int _spd;
  struct pqueueNode_t *next;
  struct pqueueNode_t *prev;
} PQueueNode;

typedef struct pqueue_t {
  PQueueNode *_top;
  PQueueNode *_down;
  unsigned _size;
} PriorityQueue;

void pqueue_init(PriorityQueue *pqueue)
{
  pqueue->_top = pqueue->_down = NULL;
  pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
  return (pqueue->_top == NULL && pqueue->_down == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int hp, int atk, int spd)
{
  PQueueNode *temp = pqueue->_top;
  PQueueNode *newNode = (PQueueNode*) malloc (sizeof(PQueueNode));

  pqueue->_size++;

  newNode->_hp = hp;
  newNode->_atk = atk;
  newNode->_spd = spd;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (pqueue_isEmpty(pqueue)) {
    pqueue->_top = pqueue->_down = newNode;
    return;
  }

  if (pqueue->_top == pqueue->_down)
  {
    if (spd > pqueue->_top->_spd) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else
    {
      pqueue->_top->next = newNode;
      newNode->prev = pqueue->_top;
      pqueue->_down = newNode;
    }
  }
  else
  {
    if (spd > pqueue->_top->_spd) {
      newNode->next = pqueue->_top;
      pqueue->_top->prev = newNode;
      pqueue->_top = newNode;
    }
    else {
      while ( temp->next != NULL && temp->next->_spd > spd)
        temp = temp->next;
      if (temp == pqueue->_down)
      {
        if (pqueue->_down->_spd > newNode->_spd)
        {
          // printf("flag 1\n");
          newNode->prev = pqueue->_down;
          pqueue->_down->next = newNode;
          pqueue->_down = newNode;
        }
        else
        {
          // printf("flag 2\n");
          newNode->prev = pqueue->_down->prev;
          pqueue->_down->prev->next = newNode;
          pqueue->_down->prev = newNode;
          newNode->next = pqueue->_down;
        }
      }
      else
      {
          // printf("flag 3\n");
        newNode->prev = temp;
        newNode->next = temp->next;
        temp->next->prev = newNode;
        temp->next = newNode; 
      }
    }
  }
}

void pqueue_popup(PriorityQueue *pqueue)
{
  if (!pqueue_isEmpty(pqueue)) {
    PQueueNode *temp = pqueue->_top;
    pqueue->_size--;

    if (pqueue->_top == pqueue->_down)
      pqueue->_top = pqueue->_down = NULL;
    else
    {
      pqueue->_top = pqueue->_top->next;
      pqueue->_top->prev = NULL;
    }
    free(temp);
  }
}

void pqueue_popdown(PriorityQueue *pqueue)
{
  if (!pqueue_isEmpty(pqueue)) {
    PQueueNode *temp;
    pqueue->_size--;

    if (pqueue->_top == pqueue->_down)
    {
      temp = pqueue->_top;
      pqueue->_top = pqueue->_down = NULL;
    }
    else
    {
      temp = pqueue->_down;
      pqueue->_down = pqueue->_down->prev;
      pqueue->_down->next = NULL;
    }
    free(temp);
  }
}

int pqueue_top(PriorityQueue *pqueue, int flag) {
  if (!pqueue_isEmpty(pqueue))
  {
    if (flag == 1)
      return pqueue->_top->_hp;
    else if (flag == 2)
      return pqueue->_top->_atk;
    else if (flag == 3)
      return pqueue->_top->_spd;
  }
  else return 0;
}

int pqueue_down(PriorityQueue *pqueue, int flag) {
  if (!pqueue_isEmpty(pqueue))
  {
    if (flag == 1)
      return pqueue->_down->_hp;
    else if (flag == 2)
      return pqueue->_down->_atk;
    else if (flag == 3)
      return pqueue->_down->_spd;
  }
  else return 0;
}

int main(int argc, char const *argv[])
{
  PriorityQueue player;
  PriorityQueue enemy;

  pqueue_init(&player);
  pqueue_init(&enemy);

  int jumlah_p;
  int jumlah_e;
  int jumlah;
  int i = 0;
  int hp, atk, spd;
  int bar_player = 0;
  int bar_enemy = 0;
  float spd_player = 0;
  float spd_enemy = 0;
  float hp_enemy = 0;
  float hp_player = 0;
  float atk_player = 0;
  float atk_enemy = 0;

  scanf("%d %d", &jumlah_p, &jumlah_e);

  jumlah = jumlah_e + jumlah_p;
  
  while (i < jumlah)
  {
    i++;

    scanf("%d %d %d", &hp, &atk, &spd);

    if (i <= jumlah_p)
    {
      pqueue_push(&player, hp, atk, spd);
      spd_player += (float)spd;
      hp_player += (float)hp;
      atk_player += (float)atk;
    }
    else
    {
      pqueue_push(&enemy, hp, atk, spd);
      spd_enemy += (float)spd;
      hp_enemy += (float)hp;
      atk_enemy += (float)atk;
    }
  }

  hp_player/=jumlah_p, hp_enemy/=jumlah_e;
  spd_player/=jumlah_p, spd_enemy/=jumlah_e;
  atk_player/=jumlah_p, atk_enemy/=jumlah_e;

  if (spd_player > spd_enemy)
  {
    spd_player /= spd_enemy;
    spd_enemy = 1.0;
  }
  else
  {
    spd_enemy /= spd_player;
    spd_player = 1.0;
  }
  // printf("%f %f\n", spd_player, spd_enemy);

  while (true)
  {
    hp_player -= (spd_enemy*atk_enemy);
    hp_enemy -= (spd_player*atk_player);

    if (hp_enemy < 0.0)
    {
      printf("You Won!\n");
      break;
    }
    else if (hp_player < 0.0)
    {
      printf("Game Over.\n");
      break;
    }
  }

  return 0;
}
