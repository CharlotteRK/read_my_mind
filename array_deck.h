typedef struct ArrayCards {
  int value;
  int suit;
} ArrayCard;

void arr_get_deck(ArrayCard deck[3][7]);

void arr_print_card(ArrayCard card);

void arr_print_deck(ArrayCard deck[3][7]);

int arr_select_column();

void arr_reorder_columns(ArrayCard deck[3][7], int column);

void arr_redeal_cards(ArrayCard deck[3][7]);
