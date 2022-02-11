#pragma once
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int DECK_SIZE = 108;

class Deck {
    public:
        char arr[108][2];
        int size = 108;
        void fill_new(char[4]);
        void shuffle();
        char* get_next_card();
};