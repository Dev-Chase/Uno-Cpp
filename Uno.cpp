// Uno.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <thread>
#include "Deck.h"
#include "Player.h"

char suits[4] = { 'R', 'G', 'B', 'Y' };
char pile[2] = { 'R', '0' };
bool is_player_turn = true;
bool is_game_over = false;
bool is_player_winner = false;
Deck deck;
Player Human;
Player Computer;

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
void get_user_input(char[2], bool&);
int* get_available_cards(Player, char[2]);
int get_length_of_available_cards(Player, char[2]);
int get_card_vals(Player, char[2], int[], int);

void new_game() {
    is_player_turn = true;
    is_game_over = false;
    is_player_winner = false;
    deck.fill_new(suits);
    deck.shuffle();
    Human.size_of_hand = 0;
    Human.debt = 0;
    Computer.size_of_hand = 0;
    Computer.debt = 0;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        Human.cards[i][0] = 0, Human.cards[i][1] = 0;
        Computer.cards[i][0] = 0, Computer.cards[i][1] = 0;
    }
    while (deck.arr[DECK_SIZE - 1][0] == '+' || deck.arr[DECK_SIZE - 1][0] == 'W' || deck.arr[DECK_SIZE - 1][1] == '@' || deck.arr[DECK_SIZE - 1][1] == 'r' || deck.arr[DECK_SIZE - 1][1] == 'S')
    {
        deck.shuffle();
    }
    deck.add_card_to_pile(pile);
    for (int i = 0; i < 7; i++)
    {
        Human.add_card(deck.arr, deck.size, deck);
        Computer.add_card(deck.arr, deck.size, deck);
    }

    while (!is_game_over)
    {
        show_situation(Human, Computer, pile, is_player_turn);
        std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        if (is_player_turn)
        {
            get_user_input(pile, is_player_turn);
            show_situation(Human, Computer, pile, is_player_turn);
            std::this_thread::sleep_for(std::chrono::nanoseconds(10));
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        }
        if (Human.size_of_hand == 0)
        {
            is_game_over = true;
            is_player_winner = true;
            break;
        }
        if(!is_player_turn)
        {
            if (Computer.can_player_play(pile))
            {
                Computer.gen_colours();
                int* available_cards_ind = get_available_cards(Computer, pile);
                int size_of_available_cards = get_length_of_available_cards(Computer, pile);
                for (int i = 0; i < size_of_available_cards; i++)
                {
                    std::cout << Computer.cards[available_cards_ind[i]][0] << Computer.cards[available_cards_ind[i]][1] << "\n";
                }
                std::cout << size_of_available_cards << "\n";
                Computer.gen_catagories(available_cards_ind, size_of_available_cards);
                int highest_val_card_ind = get_card_vals(Computer, pile, available_cards_ind, size_of_available_cards);
                char card[2] = { Computer.cards[highest_val_card_ind][0], Computer.cards[highest_val_card_ind][1] };
                std::cout << card[0] << card[1] << "\n";
                bool is_wild = is_wild_switcher(card[1]);
                is_player_turn = Computer.play_card(card, highest_val_card_ind, Human, is_wild, Computer.pick_ideal_colour(), pile, is_player_turn, deck);
            }
            else
            {
                Computer.add_card(deck.arr, deck.size, deck);
                std::cout << "The computer is drawing." << "\n";
                if (!Computer.can_player_play(pile))
                {
                    is_player_turn = !is_player_turn;
                }
            }
        }

        if (Computer.size_of_hand == 0)
        {
            is_game_over = true;
            is_player_turn = false;
            break;
        }
    }

    if (is_game_over && is_player_winner)
    {
        std::cout << "-------------------------------" << "\n";
        std::cout << "-------Congrats! You won!------" << "\n";
        std::cout << "-------------------------------" << "\n";
    }
    else if(is_game_over && !is_player_winner)
    {
        std::cout << "-------------------------------" << "\n";
        std::cout << "--------Sorry. You lost.-------" << "\n";
        std::cout << "-------------------------------" << "\n";
    }
}

int main() {
    srand(time(0));
    while (true)
    {
        new_game();
    }

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

void get_user_input(char pile[2], bool &is_player_turn) {
    int user_in;
    std::cout << "What card would you like to play?(Number of Card from left to right, 0=draw): ";
    std::cin >> user_in;
    if (user_in && user_in <= Human.size_of_hand && !std::cin.fail() && user_in != 0)
    {
        char card[2] = {Human.cards[user_in-1][0], Human.cards[user_in-1][1]};
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
        is_player_turn = Human.play_card(card, user_in-1, Computer, is_wild, colour_choice, pile, is_player_turn, deck);
    }
    else if (!user_in && user_in == 0 && !std::cin.fail()) {
        std::cout << "You are drawing." << "\n";
        Human.add_card(deck.arr, deck.size, deck);
        if (!Human.can_player_play(pile))
        {
            is_player_turn = !is_player_turn;
        }
    }
    else if(std::cin.fail()) {
        std::cout << "Sorry that wasn't an integer and didn't work. Try again." << "\n";
        std::cin.clear();
        std::cin.ignore();
        is_player_turn = true;
    }
};

int* get_available_cards(Player player, char pile[2]) {
    static int list_of_card_ind[108];
    int size_of_list = 0;
    for (int i = 0; i < player.size_of_hand; i++)
    {
        if (player.cards[i][0] == pile[0] || player.cards[i][0] == '+' || player.cards[i][0] == 'W' || player.cards[i][1] == pile[1])
        {
            list_of_card_ind[size_of_list] = i;
            ++size_of_list;
        }
    }
    return list_of_card_ind;
}

int get_length_of_available_cards(Player player, char pile[2]) {
    int size_of_list = 0;
    for (int i = 0; i < player.size_of_hand; i++)
    {
        if (player.cards[i][0] == pile[0] || player.cards[i][0] == '+' || player.cards[i][0] == 'W' || player.cards[i][1] == pile[1])
        {
            ++size_of_list;
        }
    }
    return size_of_list;
}

int get_card_vals(Player player, char pile[2], int avail_cards[], int size_of_avail_cards) {
    int highest_val_card = 0;
    int card_vals[108];
    if (player.r_cards+player.a_cards != 0)
    {
        for (int i = 0; i < size_of_avail_cards; i++)
        {
            if (player.cards[avail_cards[i]][0] == pile[0] || player.cards[avail_cards[i]][1] == pile[1] && player.cards[avail_cards[i]][1] != '$' && player.cards[avail_cards[i]][1] != 'C')
            {
                if (player.cards[avail_cards[i]][1] == 'r' || player.cards[avail_cards[i]][1] == 'S')
                {
                    card_vals[i] = 6;
                }
                else if (player.cards[avail_cards[i]][1] == '@')
                {
                    if (pile[1] == '@')
                    {
                        card_vals[i] = 8;
                    }
                    else {
                        card_vals[i] = 4;
                    }
                }
                else {
                    card_vals[i] = 2;
                }
            }
            else {
                card_vals[i] = 1;
            }
        }
    }
    else if (player.r_cards + player.a_cards == 0 && player.w_cards > 0)
    {
        for (int i = 0; i < size_of_avail_cards; i++)
        {
            if (player.cards[avail_cards[i]][1] == 'C')
            {
                card_vals[i] = 4;
            }
            else if (player.cards[avail_cards[i]][1] == '$' && pile[1] != '$')
            {
                card_vals[i] = 6;
            }
            else if (player.cards[avail_cards[i]][1] == '$' && pile[1] == '$')
            {
                card_vals[i] = 8;
            }
            else
            {
                card_vals[i] = 2;
            }
        }
    }
    else
    {
        std::cout << "You should not be here." << "\n";
        card_vals[0] = 2;
    }

    if (size_of_avail_cards != 1)
    {
        for (int i = 0; i < size_of_avail_cards; i++)
        {
            if (i != size_of_avail_cards-1) {
                if (card_vals[i] > card_vals[i+1])
                {
                    highest_val_card = avail_cards[i];
                }
                else {
                    highest_val_card = avail_cards[i+1];
                }
            }
        }
    }
    else {
        highest_val_card = avail_cards[0];
    }

    return highest_val_card;
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