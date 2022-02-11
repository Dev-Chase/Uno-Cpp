// Uno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "Deck.h"
#include "Player.h"

char suits[4] = { 'R', 'G', 'B', 'Y' };
char pile[2] = { 'R', '0' };
bool is_player_turn = true;

std::string name_switcher(char value){
    switch (value)
    {
        case 'R':
            return "Red";
            break;
        case 'G':
            return "Green";
            break;
        case 'B':
            return "Blue";
            break;
        case 'Y':
            return "Yellow";
            break;
        case '+':
            return "";
            break;
        case 'W':
            return "";
            break;
        case '0':
            return " 0";
            break;
        case '1':
            return "1";
            break;
        case '2':
            return "2";
            break;
        case '3':
            return "3";
            break;
        case '4':
            return "4";
            break;
        case '5':
            return "5";
            break;
        case '6':
            return "6";
            break;
        case '7':
            return "7";
            break;
        case '8':
            return "8";
            break;
        case '9':
            return "9";
            break;
        case '@':
            return "+2";
            break;
        case 'r':
            return "Reverse";
            break;
        case 'S':
            return "Skip";
            break;
        case '$':
            return "+4";
            break;
        case 'C':
            return "Wildcard";
            break;
        default:
            return "Error";
            break;
    }
}

bool is_wild_switcher(char value){
    switch (value)
    {
    case '$':
        return true;
        break;
    case 'C':
        return true;
        break;
    default:
        return false;
        break;
    }
}

int main() {
    srand(NULL);
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
    std::cout << "Current card is a: " << pile[0] << pile[1] << "\n";
    std::cout << "You are attempting to play a " << name_switcher(Chase.cards[4][0]) << name_switcher(Chase.cards[4][1]) << "\n";
    char card[2] = {Chase.cards[4][0], Chase.cards[4][1]};
    bool is_wild = is_wild_switcher(Chase.cards[4][1]);
    is_player_turn = Chase.play_card(card, 4, Computer, is_wild, 'B', pile, is_player_turn, deck);
    std::cout << "Current card is a " << name_switcher(pile[0]) << name_switcher(pile[1]) << "\n";

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