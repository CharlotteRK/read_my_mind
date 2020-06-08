#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "array_deck.h"


void arr_get_deck(ArrayCard deck[3][7]) {
  ArrayCard full_deck[52];
  for (int s = 1; s < 5; s++) {
    for (int v = 1; v < 14; v++) {
      full_deck[v + 13*(s-1)].value = v;
      full_deck[v + 13*(s-1)].suit = s;
    }
  }

  srand(time(NULL));
  int n = 0;
  for (int c = 0; c < 3; c++) {
    for (int r = 0; r < 7; r++) {
      int random_array_card = 0;
      while (random_array_card == 0) {
        random_array_card = rand() % (52 - n);
      }
      deck[c][r].value = full_deck[random_array_card].value;
      deck[c][r].suit = full_deck[random_array_card].suit;
      n++;
      for (int i = random_array_card; i < 52; i++) {
        full_deck[i] = full_deck[i + 1];
      }
    }
  }
}

void arr_print_card(ArrayCard array_card) {
  switch(array_card.value) {
    case (1) :
      printf("A");
      break;
    case (2) :
      printf("2");
      break;
    case (3) :
      printf("3");
      break;
    case (4) :
      printf("4");
      break;
    case (5) :
      printf("5");
      break;
    case (6) :
      printf("6");
      break;
    case (7) :
      printf("7");
      break;
    case (8) :
      printf("8");
      break;
    case (9) :
      printf("9");
      break;
    case (10) :
      printf("10");
      break;
    case (11) :
      printf("J");
      break;
    case (12) :
      printf("Q");
      break;
    case (13) :
      printf("K");
      break;
    default :
      printf("Error printing card value:%d,", array_card.value);
      return;
  }
  switch(array_card.suit) {
    case (1) :
      printf("♥");
      break;
    case (2) :
      printf("♦");
      break;
    case (3) :
      printf("♣");
      break;
    case (4) :
      printf("♠");
      break;
    default :
      printf("Error printing card suit:%d,", array_card.value);
      return;
  }
}

void arr_print_deck(ArrayCard deck[3][7]) {
  for (int r = 0; r < 7; r++) {
    printf("\n");
    for (int c = 0; c < 3; c++) {
      arr_print_card(deck[c][r]);
      printf("\t\t");
    }
  }
  printf("\n");
}

int arr_select_column() {
  int column;
  while (1) {
    column = 0;
    printf("\nWhich column is your card in? ");
    scanf("%d", &column);
    if (column == 1 || column == 2 || column == 3) {
      break;
    }
    else {
      printf("\nInvalid input.");
      char c = 0;
      while (c != EOF && c != '\n') {
        c = getchar();
      }
    }
  }
  printf("\n");
  return column;
}

void arr_reorder_columns(ArrayCard deck[3][7], int column) {
  if (column != 2) {
    for (int r = 0; r < 7; r++) {
      ArrayCard temp;
      temp = deck[1][r];
      deck[1][r] = deck[column-1][r];
      deck[column-1][r] = temp;
    }
  }
}

void arr_redeal_cards(ArrayCard deck[3][7]) {
  ArrayCard previous_deck[21];
  for (int c = 0; c < 3; c++) {
    for (int r = 0; r < 7; r++) {
      previous_deck[r + 7*c].value = deck[c][r].value;
      previous_deck[r + 7*c].suit = deck[c][r].suit;
    }
  }
  for (int r = 0; r < 7; r++) {
    for (int c = 0; c < 3; c++) {
      deck[c][r].value = previous_deck[c + 3*r].value;
      deck[c][r].suit = previous_deck[c + 3*r].suit;
    }
  }
}
