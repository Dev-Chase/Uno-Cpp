#include "Deck.h"
#include<iostream>

char num_switch(char input){
    switch (input)
    {
    case 1:
        return '1';
        break;
    case 2:
        return '2';
        break;
    case 3:
        return '3';
        break;
    case 4:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    default:
        return '1';
        break;
    }
}

void Deck::fill_new(char suits[4]){
    int deck_i = 0;
    for (int i = 0; i > size; ++i){
        arr[i][0] = 0;
        arr[i][1] = 0;
    }
    for (int nul = 0; nul < 2; nul++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int x = 0; x < 9; x++)
            {
                arr[deck_i][0] = suits[i], arr[deck_i][1] = num_switch(x+1);
                ++deck_i;
            }
            arr[deck_i][0] = suits[i], arr[deck_i][1] = '@';
            ++deck_i;
            arr[deck_i][0] = suits[i], arr[deck_i][1] = 'r';
            ++deck_i;
            arr[deck_i][0] = suits[i], arr[deck_i][1] = 'S';
            ++deck_i;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        arr[deck_i][0] = suits[i], arr[deck_i][1] = '0';
        ++deck_i;
        arr[deck_i][0] = 'W', arr[deck_i][1] = 'C';
        ++deck_i;
        arr[deck_i][0] = '+', arr[deck_i][1] = '$';
        ++deck_i;
    }
}
void Deck::shuffle(){
    srand(NULL);
    int swap_idx;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        swap_idx = rand()%107+1;
        char temp_card[2] = {arr[i][0], arr[i][1]};
        char rand_card[2] = {arr[swap_idx][0], arr[swap_idx][1]};

        arr[swap_idx][0] = temp_card[0], arr[swap_idx][1] = temp_card[1];

        arr[i][0] = rand_card[0], arr[i][1] = rand_card[1];
    }
    
}
char* Deck::get_next_card(){
    static char card_to_return[2] = {arr[size-1][0], arr[size-1][1]};
    arr[size-1][0] = 0, arr[size-1][1] = 0;
    --size;
    if(size == 0){
        char suits[4] = {'R', 'G', 'B', 'Y'};
        fill_new(suits);
    }
    return card_to_return;
}