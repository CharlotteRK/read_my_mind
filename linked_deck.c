#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "linked_deck.h"

//function to free a deck of cards (from the given pointer onwards)
void free_deck(Card* deck) {
  do {
    deck = deck->next_card;
    free(deck->previous_card);
  } while (deck->next_card != NULL);
  free(deck);
}

//function to create a deck of 21 random cards in a double linked list structure
void get_deck(Card* deck) {
  //create full deck of 52 cards
  deck->next_card = NULL;
  deck->previous_card = NULL;
  deck->value = 0;
  deck->suit = 0;
  Card* start = (Card*)malloc(sizeof(Card));
  start->next_card = NULL;
  start->previous_card = NULL;
  start->value = 0;
  start->suit = 0;
  Card* start_ptr = start;
  for (int s = 1; s < 5; s++) {
    for (int v = 1; v < 14; v++) {
      Card* nxt = (Card*)malloc(sizeof(Card));
      nxt->value = v;
      nxt->suit = s;
      nxt->next_card = NULL;
      nxt->previous_card = NULL;
      if (start->next_card == NULL) {
        start->next_card = nxt;
      }
      else {
        Card* this_card = start;
        while (1) {
          if(this_card->next_card == NULL) {
            nxt->previous_card = this_card;
            this_card->next_card = nxt;
            break;
          }
          assert(this_card->next_card != NULL);
          this_card = this_card->next_card;
        };
      }
    }
  }
  //select random card from the full deck
  srand(time(NULL));
  for (int c = 0; c < 21; c++) {
    int random_card = 0;
    while (random_card == 0) {
      random_card = rand() % (52 - c);
    }
    Card* selected_card = (Card*)malloc(sizeof(Card));
    selected_card = start_ptr;
    selected_card = selected_card->next_card;
    for (int i = 0; i < random_card; i++) {
      selected_card = selected_card->next_card;
    }
    Card* nxt = (Card*)malloc(sizeof(Card));
    nxt->value = selected_card->value;
    nxt->suit = selected_card->suit;
    //remove card from the full deck
    if (random_card > 0 && random_card < 51 - c) {
      selected_card->previous_card->next_card = selected_card->next_card;
      selected_card->next_card->previous_card = selected_card->previous_card;
    }
    else if (random_card == 1) {
      selected_card->next_card->previous_card = selected_card->previous_card;
    }
    else if (random_card == 52 - c) {
      selected_card->previous_card->next_card = selected_card->next_card;
    }
    //free(selected_card);
    //add selected card to the smaller 'selected' deck
    nxt->next_card = NULL;
    nxt->previous_card = NULL;
    if (deck->next_card == NULL) {
      deck->next_card = nxt;
    }
    else {
      Card* this_card = deck;
      while (1) {
        if(this_card->next_card == NULL) {
          nxt->previous_card = this_card;
          this_card->next_card = nxt;
          break;
        }
        this_card = this_card->next_card;
      };
    }
    free(selected_card);
  }
  //free the full deck (that no longer has the selected cards in it)
  free_deck(start);
}

//function to print out a single card
void print_card(Card card) {
  switch(card.value) {
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
      printf("Error printing card value:%d,", card.value);
      return;
  }
  switch(card.suit) {
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
    printf("Error printing card suit:%d,", card.value);
    return;
  }
}

//funcion to print out the deck
void print_deck(Card* deck) {
  Card* start = deck->next_card;
  for (int j = 0; j < 7; j++) {
    print_card(*start);
    printf("\t\t");
    for (int i = 0; i < 7; i++) {
      start = start->next_card;
    }
    print_card(*start);
    printf("\t\t");
    for (int i = 0; i < 7; i++) {
      start = start->next_card;
    }
    print_card(*start);
    printf("\t\t");
    for (int i = 0; i < 7; i++) {
      start = start->previous_card;
    }
    for (int i = 0; i < 7; i++) {
      start = start->previous_card;
    }
    printf("\n");
    if (start->next_card != NULL) {
      start = start->next_card;
    }
  }
}

//function to take user input of the column the card is in
int select_column() {
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

//function to switch the selected column to the middle of the deck
void reorder_columns(Card* deck, int column) {
  Card* pointer;
  pointer = deck->next_card;
  if (column != 2) {
    Card* column_end = 0x0;
    Card* column_start = 0x0;
    for (int i = 0; i < column*7 -1; i++) {
      if (i == column*7 - 7) {
        column_start = pointer;
      }
      pointer = pointer->next_card;
    }
    column_end = pointer;
    pointer = deck->next_card;
    Card* column2_end = 0x0;
    Card* column2_start = 0x0;
    for (int i = 0; i < 13; i++) {
      if (i == 7) {
        column2_start = pointer;
      }
      pointer = pointer->next_card;
    }
    column2_end = pointer;
    if (column == 1) {
      column2_start->previous_card = column_start->previous_card;
      column_start->previous_card = column2_end;
      column_end->next_card = column2_end->next_card;
      column2_end->next_card = column_start;
      deck->next_card = column2_start;
      column_end->next_card->previous_card = column_end;
    }
    else if (column == 3) {
      column_start->previous_card = column2_start->previous_card;
      column2_start->previous_card = column_end;
      column2_end->next_card = column_end->next_card;
      column_end->next_card = column2_start;
      column_start->previous_card->next_card = column_start;
    }
  }
}

//function to re-order the cards
//(i.e. after they've been collected in, they are set out again in a different order)
void redeal_cards(Card* deck) {
  //build new deck
  Card* new_deck = (Card*)malloc(sizeof(Card));
  new_deck->previous_card = NULL;
  new_deck->next_card = NULL;
  new_deck->value = 0;
  new_deck->suit = 0;
  Card* deck_ptr = deck->next_card;
  for (int i = 0; i < 21; i++) {
    Card* nxt = (Card*)malloc(sizeof(Card));
    nxt->value = 0;
    nxt->suit = 0;
    nxt->next_card = NULL;
    nxt->previous_card = NULL;
    if (deck_ptr->next_card == NULL) {
      deck_ptr->next_card = nxt;
    }
    else {
      Card* this_card = new_deck;
      while (1) {
        if(this_card->next_card == NULL) {
          nxt->previous_card = this_card;
          this_card->next_card = nxt;
          break;
        }
        this_card = this_card->next_card;
      };
    }
  }
  Card* new_deck_ptr = new_deck->next_card;
  for (int j = 0; j < 7; j++) {
    //add deck_ptr atts to new_deck_ptr
    new_deck_ptr->value = deck_ptr->value;
    new_deck_ptr->suit = deck_ptr->suit;
    for (int i = 0; i < 7; i++) {
      new_deck_ptr = new_deck_ptr->next_card;
    }
    deck_ptr = deck_ptr->next_card;
    //add deck_ptr atts to new_deck_ptr
    new_deck_ptr->value = deck_ptr->value;
    new_deck_ptr->suit = deck_ptr->suit;
    for (int i = 0; i < 7; i++) {
      new_deck_ptr = new_deck_ptr->next_card;
    }
    deck_ptr = deck_ptr->next_card;
    //add deck_ptr atts to new_deck_ptr
    new_deck_ptr->value = deck_ptr->value;
    new_deck_ptr->suit = deck_ptr->suit;
    deck_ptr = deck_ptr->next_card;
    //return to left hand column
    for (int i = 0; i < 7; i++) {
      new_deck_ptr = new_deck_ptr->previous_card;
    }
    for (int i = 0; i < 7; i++) {
      new_deck_ptr = new_deck_ptr->previous_card;
    };
    //move to next row
    if (new_deck_ptr->next_card != NULL) {
      new_deck_ptr = new_deck_ptr->next_card;
    }
  }
  //switch out decks and free old deck
  free_deck(deck->next_card);
  deck->next_card = new_deck->next_card;
  new_deck->previous_card = NULL;
}
