#include <stdio.h>
#include <stdlib.h>
#include "linked_deck.h"

int main() {

  //create the deck of 21 random cards, and print it out (ordered into 3 columns)
  Card* deck = (Card*)malloc(sizeof(Card));
  get_deck(deck);
  print_deck(deck);

  //three repeats of the reordering
  for (int i = 0; i < 3; i++) {

    //user selects column containing their card
    int column = select_column();

    //cards are manipulated
    reorder_columns(deck, column);
    redeal_cards(deck);

    //new order of cards is printed
    print_deck(deck);
  }

  //centre card is found
  Card* selected = (Card*)malloc(sizeof(Card));
  selected = deck;
  for (int i = 0; i <= 10; i++) {
    selected = selected->next_card;
  }

  //program outputs centre card
  printf("\nYour selected card was ");
  print_card(*selected);
  printf(".\n");

  //all remaining cards are freed
  free_deck(deck);
  free(selected);

}
