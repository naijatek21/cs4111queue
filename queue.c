#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
  void *item;
  struct node *next;

} *node_t;

node_t node_init()
{
  node_t n = malloc(sizeof(node_t));
  n->item = NULL;
  n->next = NULL;
  return n;
}
typedef struct queue
{
  node_t head;
  int size;
  node_t current;

} *queue_t;

queue_t queue_new()
{

  queue_t q = malloc(sizeof(queue_t));
  q->head = NULL;
  q->current = NULL;
  q->size = 0;
  return q;
}

int queue_enqueue(queue_t queue, void *item)
{
  if (item == NULL)
    return -1;
  node_t n = node_init();
  n->item = item;

  if (queue->head == NULL)
  {
    queue->head = n;
    queue->current = n;
  }
  else
  {
    queue->current->next = n;
    queue->current = queue->current->next;
  }
  queue->size += 1;
  return 0;
  // Must be O(1) (performance does not depend on length of queue)
}

int queue_insert(queue_t queue, void *item)
{
  node_t n = node_init();
  n->item = item;
  if (n == NULL)
    return -1;
  if (queue->head == NULL)
  {
    queue->head = n;
    queue->current = queue->head;
  }
  else
  {
    node_t t = queue->head;
    queue->head = n;
    queue->head->next = t;
  }
  queue->size += 1;
  return 0;

  // your code here
  // Must be O(1) (performance does not depend on length of queue)
}

int queue_dequeue(queue_t queue, void **pitem)
{
  if (queue->size == 0)
  {
    return -1;
  }
  node_t i = queue->head;
  queue->head = i->next;
  if (pitem != NULL)
    *pitem = (i->item);
  free(i);
  queue->size -= 1;
  return 0;
  // Must be O(1) (performance does not depend on length of queue)
}

void queue_iterate(const queue_t queue, queue_func_t f, void *context)
{
  node_t curr = queue->head;
  while (curr != NULL)
  {
    f(curr->item, context);
    curr = curr->next;
  }
}

int queue_free(queue_t queue)
{
  if (queue->size == 0)
  {
    free(queue);
    return 0;
  }
  return -1;
  // Must be O(1) (performance does not depend on length of queue)
}
int queue_length(const queue_t queue)
{
  return queue->size;
  // Must be O(1) (performance does not depend on length of queue)
}

int queue_delete(queue_t queue, void *item)
{
  node_t curr = queue->head;
  if (queue->size == 0)
    return -1;
  if (queue->size == 1)
  {
    if (curr->item == item)
    {
      free(curr);
      queue->head = NULL;
      queue->size -= 1;
      return 0;
    }
    return -1;
  }
  while (curr != NULL && curr->next != NULL)
  {
    if (curr->next->item == item)
    {
      node_t temp = curr->next;
      curr->next = curr->next->next;
      free(temp);
      queue->size -= 1;
      return 0;
    }
    curr = curr->next;
  }
  return -1;
}
