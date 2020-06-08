#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "array_deck.h"

int main() {

  ArrayCard deck[3][7];
  arr_get_deck(deck);
  arr_print_deck(deck);

  for (int i = 0; i < 3; i++) {

    int column = arr_select_column();
    arr_reorder_columns(deck, column);
    arr_redeal_cards(deck);
    arr_print_deck(deck);
  }

  ArrayCard selected = {deck[1][3].value, deck[1][3].suit};
  printf("\nYour selected card was ");
  arr_print_card(selected);
  printf(".\n");

}
