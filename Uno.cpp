#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "Deck.h"

char suits[4] = { 'R', 'G', 'B', 'Y' };

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

char colour_switcher(int input){
    switch(input){
        case 0:
            return 'R';
            break;
        case 1:
            return 'G';
            break;
        case 2:
            return 'B';
            break;
        case 3:
            return 'Y';
            break;
        default:
            return 'B';
            break;
    }
}

class Deck{
    public:
        char arr[108][2];
        int size = 108;
        // Deck();
        // ~Deck();
        void fill_new(char suits[4]){
            int deck_i = 0;
            for(int i = 0; i > size; ++i){
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
        void shuffle(){
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
        char *get_next_card(){
            static char card_to_return[2] = {arr[size-1][0], arr[size-1][1]};
            arr[size-1][0] = 0, arr[size-1][1] = 0;
            --size;
            if(size == 0){
                char suits[4] = {'R', 'G', 'B', 'Y'};
                fill_new(suits);
            }
            return card_to_return;
        }
        
};

class Player{
    public:
        int size_of_hand = 0;
        char cards[108][2];
        int debt = 0;
        int reds = 0;
        int greens = 0;
        int blues = 0;
        int yellows = 0;
        int a_cards = 0;
        int r_cards = 0;
        int w_cards = 0;
        void add_card(char arr[][2], int &size, Deck deck){
            char new_card[2] = {arr[size-1][0], arr[size-1][1]};
            arr[size-1][0] = 0, arr[size-1][1] = 0;
            --size;
            if(size == 0){
                char suits[4] = {'R', 'G', 'B', 'Y'};
                deck.fill_new(suits);
                deck.shuffle();
            }
            cards[size_of_hand][0] = new_card[0], cards[size_of_hand][1] = new_card[1];
            ++size_of_hand;
        }
        void gen_colours(){
            for (int i = 0; i < size_of_hand; i++)
            {
                std::cout << cards[i][0] << cards[i][1] <<"\n";
            }
            for (int i = 0; i < size_of_hand; i++)
            {
                switch (cards[i][0])
                {
                    case 'R':
                        ++reds;
                        break;
                    case 'G':
                        ++greens;
                        break;
                    case 'B':
                        ++blues;
                        break;
                    case 'Y':
                        ++yellows;
                        break;
                    case '+':
                        break;
                    case 'W':
                        break;
                    default:
                        ++blues;
                        break;
                    }   
            }
        }
        char pick_ideal_colour(){
            int colours[4] = {reds, greens, blues, yellows};
            int most_amount_of_colours = 2;

            if(reds > blues && reds > yellows && reds > greens){
                return 'R';
            }
            else if(greens > reds && greens > blues && greens > yellows){
                return 'G';
            }
            else if(blues > greens && blues > reds && blues > yellows){
                return 'B';
            }
            else if(yellows > reds && yellows > blues && yellows > greens){
                return 'Y';
            }
            else{
                for(int i = 0; i < 4; ++i){
                    if(i != 3){
                        if(colours[i] > colours[i+1]){
                            most_amount_of_colours = i;
                        }
                        else{
                            most_amount_of_colours = i+1;
                        }
                    }
                }
                return colour_switcher(most_amount_of_colours);
            }
        }
};

int main(){
    srand(time(NULL));
    Deck deck;
    deck.fill_new(suits);
    deck.shuffle();
    Player Chase;
    Player Computer;
    for (int i = 0; i < 108; i++)
    {
        std::cout << deck.arr[i][0] << deck.arr[i][1] << "\n";
    }
    Chase.add_card(deck.arr, deck.size, deck);
    Chase.add_card(deck.arr, deck.size, deck);
    Chase.add_card(deck.arr, deck.size, deck);
    std::cout << "--------------------------" << "\n";
    
    return 0;
}