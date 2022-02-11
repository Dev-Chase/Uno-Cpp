// Uno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Deck.h"
#include "Player.h"

char suits[4] = { 'R', 'G', 'B', 'Y' };
char pile[2] = { 'R', '0' };
bool is_player_turn = true;

bool does_player_have_card(Player player, char value) {
    for (int i = 0; i < player.size_of_hand; i++)
    {
        if (i + 1 != player.size_of_hand && player.cards[i][1] == value) {
            return true;
        };
    }
    return false;
};

int main() {
    srand(time(NULL));
    Deck deck;
    deck.fill_new(suits);
    deck.shuffle();
    Player Chase;
    Player Computer;
    /*for (int i = 0; i < 108; i++)
    {
        std::cout << deck.arr[i][0] << deck.arr[i][1] << "\n";
    }*/
    for (int i = 0; i < 7; i++)
    {
        Chase.add_card(deck.arr, deck.size, deck);
        Computer.add_card(deck.arr, deck.size, deck);
    }
    for (int i = 0; i < Chase.size_of_hand; i++)
    {
        std::cout << Chase.cards[i][0] << Chase.cards[i][1] << "\n";
    }
    std::cout << "--------------------------" << "\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file