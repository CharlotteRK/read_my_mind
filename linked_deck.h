typedef struct Cards {
  int value;
  int suit;
  struct Cards* previous_card;
  struct Cards* next_card;
} Card;

void free_deck(Card* deck);

void get_deck(Card* deck);

void get_next(Card* this_card);

void get_previous(Card* this_card);

void print_card(Card card);

void print_deck(Card* deck);

int select_column();

void reorder_columns(Card* deck, int column);

void redeal_cards(Card* deck);
