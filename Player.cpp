#include "Player.h"

char colour_switcher(int input) {
    switch (input) {
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

Player::Player() {
    std::cout << "Made new Player" << "\n";
}

void Player::add_card(char arr[][2], int& size, Deck deck) {
    char new_card[2] = { arr[size - 1][0], arr[size - 1][1] };
    arr[size - 1][0] = 0, arr[size - 1][1] = 0;
    --size;
    if (size == 0) {
        char suits[4] = { 'R', 'G', 'B', 'Y' };
        deck.fill_new(suits);
        deck.shuffle();
    }
    cards[size_of_hand][0] = new_card[0], cards[size_of_hand][1] = new_card[1];
    ++size_of_hand;
}
void Player::gen_colours() {
    for (int i = 0; i < size_of_hand; i++)
    {
        std::cout << cards[i][0] << cards[i][1] << "\n";
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

void Player::gen_catagories() {
    for (int i = 0; i < size_of_hand; i++)
    {
        switch (cards[i][1])
        {
        case '@':
            ++a_cards;
            break;
        case 'S':
            ++a_cards;
            break;
        case 'r':
            ++a_cards;
            break;
        case '$':
            ++w_cards;
            break;
        case 'C':
            ++w_cards;
            break;
        default:
            ++r_cards;
            break;
        }
    }
}

char Player::pick_ideal_colour() {
    int colours[4] = { reds, greens, blues, yellows };
    int most_amount_of_colours = 2;

    if (reds > blues && reds > yellows && reds > greens) {
        return 'R';
    }
    else if (greens > reds && greens > blues && greens > yellows) {
        return 'G';
    }
    else if (blues > greens && blues > reds && blues > yellows) {
        return 'B';
    }
    else if (yellows > reds && yellows > blues && yellows > greens) {
        return 'Y';
    }
    else {
        for (int i = 0; i < 4; ++i) {
            if (i != 3) {
                if (colours[i] > colours[i + 1]) {
                    most_amount_of_colours = i;
                }
                else {
                    most_amount_of_colours = i + 1;
                }
            }
        }
        return colour_switcher(most_amount_of_colours);
    }
}

void Player::play_card(char card[2], int cardind, Player other_player, bool is_wild, char colour, char pile[2], bool& is_player_turn, Deck deck) {
    if (pile[0] == card[0] || pile[1] == card[1] && is_wild != true)
    {
        if (card[1] == '@')
        {

        }
    }
}