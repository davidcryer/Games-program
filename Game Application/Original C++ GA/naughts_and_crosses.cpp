//
//  naughts_and_crosses.cpp
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#include "naughts_and_crosses.h"
#include <iostream>
#include <random>

extern int get_integer();

naughts_and_crosses::naughts_and_crosses() {tiles="123456789";}
naughts_and_crosses::~naughts_and_crosses() {}

void naughts_and_crosses::ai_turn() {
    int tile(0);
    
    if (ai_self_almost_filled_line())
        tile = ai_return_remaining_tile_of_line_almost_full_by_self();
    else if (ai_opponent_almost_filled_line())
        tile = ai_return_remaining_tile_of_line_almost_full_by_opponent();
    else if (tiles.at(4) != 'X' && tiles.at(4) != '0')
        tile = 4;
    else {
        int number_of_possible_moves(0);
        for (int i(0);i<9;i++) {
            if (tiles.at(i) != '0' && tiles.at(i) != 'X') {
                /*
                if (ai_number_of_turns_gone()==3) {
                    if (tiles.at(0) == 'X' && tiles.at(8) == '0' && tiles.at(4) == '0') {
                        
                    }
                }*/
                number_of_possible_moves++;
            }
        }
        
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uid(0,number_of_possible_moves-1);
        tile = uid(rng);
        
        for (int i(0);i<tile+1;i++) {
            if (tiles.at(i) == 'X' || tiles.at(i) == '0')
                tile++;
        }
    }
    
    tile++;
    std::cout<<tile<<std::endl;
    change_tile_player2(tile);
    print_game();
}

void naughts_and_crosses::player1_turn() {
    int tile(0);
    bool valid_integer_input(false);
    while (!valid_integer_input) {
        std::cout<<"Player1, please enter the tile number you would like to go on: ";
        tile = get_integer();
        if (tile > 9 || tile < 1)
            std::cout<<"Input error! Integer not in range 1-9.\n";
        else if (tiles.at(tile-1) == 'X' || tiles.at(tile-1) == '0')
            std::cout<<"Input error! Tile already inhabited.\n";
        else if (tile >= 1 && tile <= 9)
            valid_integer_input = true;
    }
    change_tile_player1(tile);
    print_game();
}

void naughts_and_crosses::player2_turn() {
    
    int tile(0);
    bool valid_integer_input(false);
    while (!valid_integer_input) {
        std::cout<<"Player2, please enter the tile number you would like to go on: ";
        tile = get_integer();
        if (tile > 9 || tile < 1)
            std::cout<<"Input error! Integer not in range 1-9.\n";
        else if (tiles.at(tile-1) == 'X' || tiles.at(tile-1) == '0')
            std::cout<<"Input error! Tile already inhabited.\n";
        else if (tile >= 1 && tile <= 9)
            valid_integer_input = true;
    }
    change_tile_player2(tile);
    print_game();
}

bool naughts_and_crosses::ai_opponent_almost_filled_line() const {
    for (int i(0);i<3;i++) {
        if (tiles.at(i*3)==tiles.at(i*3+1) && tiles.at(i*3) == 'X' && tiles.at(i*3+2) != '0')
            return true;
        else if (tiles.at(i*3)==tiles.at(i*3+2) && tiles.at(i*3) == 'X' && tiles.at(i*3+1) != '0')
            return true;
        else if (tiles.at(i*3+1)==tiles.at(i*3+2) && tiles.at(i*3+1) == 'X' && tiles.at(i*3) != '0')
            return true;
        else if (tiles.at(i)==tiles.at(i+3) && tiles.at(i) == 'X' && tiles.at(i+6) != '0')
            return true;
        else if (tiles.at(i)==tiles.at(i+6) && tiles.at(i) == 'X' && tiles.at(i+3) != '0')
            return true;
        else if (tiles.at(i+3)==tiles.at(i+6) && tiles.at(i+3) == 'X' && tiles.at(i) != '0')
            return true;
    }
    if (tiles.at(0)==tiles.at(4) && tiles.at(0) == 'X' && tiles.at(8) != '0')
        return true;
    else if (tiles.at(0)==tiles.at(8) && tiles.at(0) == 'X' && tiles.at(4) != '0')
        return true;
    else if (tiles.at(4)==tiles.at(8) && tiles.at(4) == 'X' && tiles.at(0) != '0')
        return true;
    else if (tiles.at(2)==tiles.at(4) && tiles.at(2) == 'X' && tiles.at(6) != '0')
        return true;
    else if (tiles.at(2)==tiles.at(6) && tiles.at(2) == 'X' && tiles.at(4) != '0')
        return true;
    else if (tiles.at(4)==tiles.at(6) && tiles.at(4) == 'X' && tiles.at(2) != '0')
        return true;
    else
        return false;
}

bool naughts_and_crosses::ai_self_almost_filled_line() const {
    for (int i(0);i<3;i++) {
        if (tiles.at(i*3)==tiles.at(i*3+1) && tiles.at(i*3) == '0' && tiles.at(i*3+2) != 'X')
            return true;
        else if (tiles.at(i*3)==tiles.at(i*3+2) && tiles.at(i*3) == '0' && tiles.at(i*3+1) != 'X')
            return true;
        else if (tiles.at(i*3+1)==tiles.at(i*3+2) && tiles.at(i*3+1) == '0' && tiles.at(i*3) != 'X')
            return true;
        else if (tiles.at(i)==tiles.at(i+3) && tiles.at(i) == '0' && tiles.at(i+6) != 'X')
            return true;
        else if (tiles.at(i)==tiles.at(i+6) && tiles.at(i) == '0' && tiles.at(i+3) != 'X')
            return true;
        else if (tiles.at(i+3)==tiles.at(i+6) && tiles.at(i+3) == '0' && tiles.at(i) != 'X')
            return true;
    }
    if (tiles.at(0)==tiles.at(4) && tiles.at(0) == '0' && tiles.at(8) != 'X')
        return true;
    else if (tiles.at(0)==tiles.at(8) && tiles.at(0) == '0' && tiles.at(4) != 'X')
        return true;
    else if (tiles.at(4)==tiles.at(8) && tiles.at(4) == '0' && tiles.at(0) != 'X')
        return true;
    else if (tiles.at(2)==tiles.at(4) && tiles.at(2) == '0' && tiles.at(6) != 'X')
        return true;
    else if (tiles.at(2)==tiles.at(6) && tiles.at(2) == '0' && tiles.at(4) != 'X')
        return true;
    else if (tiles.at(4)==tiles.at(6) && tiles.at(4) == '0' && tiles.at(2) != 'X')
        return true;
    else
        return false;
}

int naughts_and_crosses::ai_return_remaining_tile_of_line_almost_full_by_opponent() const {
    for (int i(0);i<3;i++) {
        if (tiles.at(i*3)==tiles.at(i*3+1) && tiles.at(i*3) == 'X' && tiles.at(i*3+2) != '0')
            return i*3+2;
        else if (tiles.at(i*3)==tiles.at(i*3+2) && tiles.at(i*3) == 'X' && tiles.at(i*3+1) != '0')
            return i*3+1;
        else if (tiles.at(i*3+1)==tiles.at(i*3+2) && tiles.at(i*3+1) == 'X' && tiles.at(i*3) != '0')
            return i*3;
        else if (tiles.at(i)==tiles.at(i+3) && tiles.at(i) == 'X' && tiles.at(i+6) != '0')
            return i+6;
        else if (tiles.at(i)==tiles.at(i+6) && tiles.at(i) == 'X' && tiles.at(i+3) != '0')
            return i+3;
        else if (tiles.at(i+3)==tiles.at(i+6) && tiles.at(i+3) == 'X' && tiles.at(i) != '0')
            return i;
    }
    if (tiles.at(0)==tiles.at(4) && tiles.at(0) == 'X' && tiles.at(8) != '0')
        return 8;
    else if (tiles.at(0)==tiles.at(8) && tiles.at(0) == 'X' && tiles.at(4) != '0')
        return 4;
    else if (tiles.at(4)==tiles.at(8) && tiles.at(4) == 'X' && tiles.at(0) != '0')
        return 0;
    else if (tiles.at(2)==tiles.at(4) && tiles.at(2) == 'X' && tiles.at(6) != '0')
        return 6;
    else if (tiles.at(2)==tiles.at(6) && tiles.at(2) == 'X' && tiles.at(4) != '0')
        return 4;
    else if (tiles.at(4)==tiles.at(6) && tiles.at(4) == 'X' && tiles.at(2) != '0')
        return 2;
    else {
        std::cout<<"Error! ai_return_remaining_tile_of_line_almost_full_by_opponent has been used but not returned an integer. Exiting with 1...\n";
        exit(1);
    }
}

int naughts_and_crosses::ai_return_remaining_tile_of_line_almost_full_by_self() const {
    for (int i(0);i<3;i++) {
        if (tiles.at(i*3)==tiles.at(i*3+1) && tiles.at(i*3) == '0' && tiles.at(i*3+2) != 'X')
            return i*3+2;
        else if (tiles.at(i*3)==tiles.at(i*3+2) && tiles.at(i*3) == '0' && tiles.at(i*3+1) != 'X')
            return i*3+1;
        else if (tiles.at(i*3+1)==tiles.at(i*3+2) && tiles.at(i*3+1) == '0' && tiles.at(i*3) != 'X')
            return i*3;
        else if (tiles.at(i)==tiles.at(i+3) && tiles.at(i) == '0' && tiles.at(i+6) != 'X')
            return i+6;
        else if (tiles.at(i)==tiles.at(i+6) && tiles.at(i) == '0' && tiles.at(i+3) != 'X')
            return i+3;
        else if (tiles.at(i+3)==tiles.at(i+6) && tiles.at(i+3) == '0' && tiles.at(i) != 'X')
            return i;
    }
    if (tiles.at(0)==tiles.at(4) && tiles.at(0) == '0' && tiles.at(8) != 'X')
        return 8;
    else if (tiles.at(0)==tiles.at(8) && tiles.at(0) == '0' && tiles.at(4) != 'X')
        return 4;
    else if (tiles.at(4)==tiles.at(8) && tiles.at(4) == '0' && tiles.at(0) != 'X')
        return 0;
    else if (tiles.at(2)==tiles.at(4) && tiles.at(2) == '0' && tiles.at(6) != 'X')
        return 6;
    else if (tiles.at(2)==tiles.at(6) && tiles.at(2) == '0' && tiles.at(4) != 'X')
        return 4;
    else if (tiles.at(4)==tiles.at(6) && tiles.at(4) == '0' && tiles.at(2) != 'X')
        return 2;
    else
        return false;
}

bool naughts_and_crosses::check_for_turn_remaining_as_true() const {
    for (int i(0);i<9;i++) {
        if (tiles.at(i)!='0'&&tiles.at(i)!='X') {
            return true;
        }
    }
    return false;
}

bool naughts_and_crosses::check_for_draw_as_true() const {std::cerr<<"Do not need to use this function - instead check for win and then if there are any turns remaining if no winners. Exiting with 1...\n";exit(1);}

bool naughts_and_crosses::check_for_win_as_true() const {
    
    if (tiles.at(0)==tiles.at(3) && tiles.at(3)==tiles.at(6))
        return true;
    else if (tiles.at(1)==tiles.at(4) && tiles.at(4)==tiles.at(7))
        return true;
    else if (tiles.at(2)==tiles.at(5) && tiles.at(5)==tiles.at(8))
        return true;
    else if (tiles.at(0)==tiles.at(1) && tiles.at(1)==tiles.at(2))
        return true;
    else if (tiles.at(3)==tiles.at(4) && tiles.at(4)==tiles.at(5))
        return true;
    else if (tiles.at(6)==tiles.at(7) && tiles.at(7)==tiles.at(8))
        return true;
    else if (tiles.at(0)==tiles.at(4) && tiles.at(4)==tiles.at(8))
        return true;
    else if (tiles.at(2)==tiles.at(4) && tiles.at(4)==tiles.at(6))
        return true;
    else
        return false;
}

void naughts_and_crosses::change_tile_player1(int tile) {
    if (tile >= 1 && tile <= 9)
        tiles.at(tile-1)='X';
}

void naughts_and_crosses::change_tile_player2(int tile) {
    if (tile >= 1 && tile <= 9)
        tiles.at(tile-1)='0';
}

int naughts_and_crosses::ai_number_of_turns_gone() const {
    int number_of_turns_counter(0);
    for(int i(0);i<9;i++) {
        if (tiles.at(i) == 'X' || tiles.at(i) != '0')
            number_of_turns_counter++;
    }
    return number_of_turns_counter;
}

void naughts_and_crosses::print_game() const {
    std::cout<<" =========== \n";
    std::cout<<"| "<<tiles.at(0)<<" | "<<tiles.at(1)<<" | "<<tiles.at(2)<<" |\n";
    std::cout<<"|-----------|\n";
    std::cout<<"| "<<tiles.at(3)<<" | "<<tiles.at(4)<<" | "<<tiles.at(5)<<" |\n";
    std::cout<<"|-----------|\n";
    std::cout<<"| "<<tiles.at(6)<<" | "<<tiles.at(7)<<" | "<<tiles.at(8)<<" |\n";
    std::cout<<" =========== \n";
}