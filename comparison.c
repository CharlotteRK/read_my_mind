#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_deck.h"
#include "array_deck.h"

int main() {

  clock_t total = 0;
  for (int i = 0; i < 10000000; i++) {
    ArrayCard deck[3][7];
    clock_t start_time = clock();
    arr_get_deck(deck);
    total = total + (clock() - start_time);
  }
  printf("\nArray setup time: %0.3fms\n", (double)total/10000000);

  total = 0;
  ArrayCard arr_deck[3][7];
  arr_get_deck(arr_deck);
  for (int i = 0; i < 10000000; i++) {
    clock_t start_time = clock();
    arr_reorder_columns(arr_deck, 1);
    total = total + (clock() - start_time);
  }
  printf("Array column switch time: %0.3fms\n", (double)total/10000000);

  total = 0;
  for (int i = 0; i < 10000000; i++) {
    clock_t start_time = clock();
    arr_redeal_cards(arr_deck);
    total = total + (clock() - start_time);
  }
  printf("Array deck re-deal time: %0.3fms\n", (double)total/10000000);

  total = 0;
  Card* deck = (Card*)malloc(sizeof(Card));
  for (int i = 0; i < 1000000; i++) {
    clock_t start_time = clock();
    get_deck(deck);
    total = total + (clock() - start_time);
  }
  printf("\nLinked setup time: %0.3fms\n", (double)total/1000000);

  total = 0;
  for (int i = 0; i < 1000000; i++) {
    clock_t start_time = clock();
    reorder_columns(deck, 1);
    total = total + (clock() - start_time);
  }
  printf("Linked column switch time: %0.3fms\n", (double)total/1000000);

  total = 0;
  for (int i = 0; i < 1000000; i++) {
    clock_t start_time = clock();
    redeal_cards(deck);
    total = total + (clock() - start_time);
  }
  free_deck(deck);
  printf("Linked deck re-deal time: %0.3fms\n\n", (double)total/1000000);
}
