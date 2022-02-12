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

void show_situation(Player, Player, char[2], bool);
void get_user_input(char[2], Player&, Player&, bool&, Deck);

int main() {
    srand(time(0));
    Deck deck;
    deck.fill_new(suits);
    deck.shuffle();
    Player Human;
    Player Computer;
    while (deck.arr[DECK_SIZE-1][0] == '+' || deck.arr[DECK_SIZE-1][0] == 'W' || deck.arr[DECK_SIZE - 1][1] == '@' || deck.arr[DECK_SIZE - 1][1] == 'r' || deck.arr[DECK_SIZE - 1][1] == 'S')
    {
        deck.shuffle();
    }
    deck.add_card_to_pile(pile);
    /*for (int i = 0; i < 108; i++)
    {
        std::cout << deck.arr[i][0] << deck.arr[i][1] << "\n";
    }*/
    for (int i = 0; i < 7; i++)
    {
        Human.add_card(deck.arr, deck.size, deck);
        Computer.add_card(deck.arr, deck.size, deck);
    }
    show_situation(Human, Computer, pile, is_player_turn);
    get_user_input(pile, Human, Computer, is_player_turn, deck);
    show_situation(Human, Computer, pile, is_player_turn);

    return 0;
}

void show_situation(Player player, Player computer, char pile[2], bool is_player_turn) {
    std::cout << "--------------------------" << "\n";
    std::cout << "The Computer has " << computer.size_of_hand << " cards: ";
    for (int i = 0; i < computer.size_of_hand; i++)
    {
        std::cout << name_switcher(computer.cards[i][0]) << " " << name_switcher(computer.cards[i][1]) << "   ";
    }
    std::cout << "\n" << "Current card is a: " << name_switcher(pile[0]) << " " << name_switcher(pile[1]) << "\n";
    std::cout << "You have " << player.size_of_hand << " cards: ";
    for (int i = 0; i < player.size_of_hand; i++)
    {
        std::cout << name_switcher(player.cards[i][0]) << " " << name_switcher(player.cards[i][1]) << "   ";
    }
    if (is_player_turn)
    {
        std::cout << "\n" << "It's your turn." << "\n";
    }
    else {
        std::cout << "\n" << "It's the computer's turn." << "\n";
    }
    std::cout << "--------------------------" << "\n";

}

void get_user_input(char pile[2], Player &player, Player &computer, bool &is_player_turn, Deck deck) {
    int user_in;
    std::cout << "What card would you like to play?(Number of Card from left to right, 110=draw): ";
    std::cin >> user_in;
    if (user_in && user_in <= player.size_of_hand && !std::cin.fail())
    {
        char card[2] = {player.cards[user_in-1][0], player.cards[user_in-1][1]};
        char colour_choice = 'B';
        bool is_wild = is_wild_switcher(card[1]);
        if (is_wild)
        {
            bool valid = false;
            while (!valid)
            {
                valid = true;
                std::cout << "What colour would you like to play?(R,G,B,Y): ";
                std::cin >> colour_choice;
                if (std::cin.fail() || colour_choice != 'R' && colour_choice != 'G' && colour_choice != 'B' && colour_choice != 'Y')
                {
                    std::cin.clear(); //This corrects the stream.
                    std::cin.ignore(); //This skips the left over stream data.
                    std::cout << "\n" << "Sorry that isn't an option. Try again" << "\n";
                    valid = false;
                }
            }
        }
        is_player_turn = player.play_card(card, user_in-1, computer, is_wild, colour_choice, pile, is_player_turn, deck);
    }
    else if (!user_in && user_in == 0 && !std::cin.fail()) {
        std::cout << "You are drawing." << "\n";
        player.add_card(deck.arr, deck.size, deck);
    }
    else if(std::cin.fail()) {
        std::cout << "Sorry that wasn't an integer and didn't work. Try again." << "\n";
        std::cin.clear();
        std::cin.ignore();
        is_player_turn = true;
    }
};

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file