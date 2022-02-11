#pragma once
#include "Deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include<iostream>

class Player
{
public:
    int size_of_hand = 0;
    char cards[108][2] = {{0, 0}};
    int debt = 0;
    int reds = 0;
    int greens = 0;
    int blues = 0;
    int yellows = 0;
    int a_cards = 0;
    int r_cards = 0;
    int w_cards = 0;
    Player();
    void add_card(char[][2], int& size, Deck deck);
    void gen_colours();
    void gen_catagories();
    char pick_ideal_colour();
    bool play_card(char[2], int, Player, bool, char, char[2], bool&, Deck);

};

