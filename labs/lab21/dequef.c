#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef * deque = (dequef*) malloc(sizeof(dequef));
   if (deque == NULL) 
      return NULL;
   deque->data = malloc(capacity * sizeof(float));
   deque->first = 0;
   deque->size = 0;
   deque->cap = capacity;    
   deque->mincap = capacity;
   deque->factor = factor;
   return deque;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   printf("Free\n");
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return D->size;
}



int df_resize(dequef* D, long new_cap) {
   return printf("Resize\n");;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   if (D->size == 0) {
      D->data[0] = x;
      D->size++;
      return 1;
   }
   else if (D->cap != D->size){
      int cont = 1, index = D->first;
      while (cont < D->size + 1){
         cont++;
         index++;
         if (index == D->cap){
            index = 0;
         }
      }
      
      D->data[index] = x;
      D->size++;
      return 1;
   }
   float * antigo = D->data;
   D->data = malloc(D->cap * D->factor * sizeof(float));
   int i = 1, j = D->first;
   while (i < D->size){
      D->data[i] = antigo[j];
      j++;
      if (j == D->cap){
         j = 0;
      }
      i++;
   }
   D->data[D->size] = x;
   D->size += 1;
   D->first = 0;
   free(antigo);
   D->cap *= D->factor;
   return 1;
}



/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef* D) {
   if (D->size) {
      float item;
      int cont = 0, index = D->first;
      while (cont < D->size) {
         cont++;
         index++;
         if (index == D->cap){
            index = 0;
         }
      }
      item = D->data[index];
      D->size--;
      return item;
   }
   return 0;
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
   if (D->size == 0) {
      D->data[D->first] = x;
      D->size += 1;
      return 1;
   } else if (D->cap != D->size){
      D->first--;
      if (D->first < 0){
         D->first = D->cap - 1;
      }
      D->data[D->first] = x;
      D->size += 1;
      return 1;
   }
   float * antigo = D->data;
   D->data = malloc(D->cap * D->factor * sizeof(float));
   D->data[0] = x;
   int i = 1, j = D->first;
   while (i < D->size + 1){
      D->data[i] = antigo[j];
      j++;
      if (j == D->cap){
         j = 0;
      }
      i++;
   }
   D->size += 1;
   D->first = 0;
   free(antigo);
   D->cap *= D->factor;
   return 1;
}



/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef* D) {
   if (D->size) {
      float item;

      item = D->data[D->first];
      D->first--;
      if (D->first < 0)
         D->first = D->cap - 1;

      D->size--;

      return item;
   }
   return 0;
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef* D, long i, float x) {
   printf("Set\n");
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef* D, long i) {
   if(i >= 0 && i < D->cap){
      int cont = 0, index = D->first;
      while (cont < i){
         cont++;
         index++;
         if (index == D->cap){
            index = 0;
         }
      }
      return D->data[index];
   }
   return 0;
}



/**
   Print the elements of D in a line.
**/
void df_print(dequef* D) {
   int cont = 0, index = D->first;
   printf("deque (%ld): ", D->size);
   while (cont < D->size){
      printf("%.1f ", D->data[index]);
      index++;
      if (index == D->cap){
         index = 0;
      }
      cont++;
   }
   printf("\n");
}
