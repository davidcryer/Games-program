//
//  connect_four.cpp
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#include "connect_four.h"
#include <iostream>
#include <random>

extern int get_integer();

connect_four::connect_four() {for(int i(0);i<42;i++){tiles.append(" ");}}

connect_four::~connect_four() {}

void connect_four::ai_turn() {
    int column(0);
    //random ai
    int number_of_possible_moves(0);
    for (int i(0);i<7;i++) {
        if (tiles.at(7*5+i) == ' ')
            number_of_possible_moves++;
    }
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uid(1,number_of_possible_moves);
    column = uid(rng);
    
    for (int i(0);i<column;i++) {
        if (tiles.at(7*5+i) != ' ')
            column++;
    }
    
    change_tile_player2(column);
    print_game();
}

void connect_four::player1_turn() {
    int column(0);
    bool valid_integer_input(false);
    while (!valid_integer_input) {
        std::cout<<"Player1, please enter the column you would like to go on: ";
        column = get_integer();
        if (column > 7 || column < 1)
            std::cout<<"Input error! Integer not in range 1-7.\n";
        else if (tiles.at(column-1+7*5) != ' ')
            std::cout<<"Input error! Column is completely filled, choose another column.\n";
        else if (tiles.at(column-1+7*5) == ' ' && column >= 1 && column <= 7)
            valid_integer_input = true;
    }
    change_tile_player1(column);
    print_game();
}

void connect_four::player2_turn() {
    
    int column(0);
    bool valid_integer_input(false);
    while (!valid_integer_input) {
        std::cout<<"Player2, please enter the column you would like to go on: ";
        column = get_integer();
        if (column > 7 || column < 1)
            std::cout<<"Input error! Integer not in range 1-7.\n";
        else if (tiles.at(column-1+7*5) != ' ')
            std::cout<<"Input error! Column is completely filled, choose another column.\n";
        else if (tiles.at(column-1+7*5) == ' ' && column >= 1 && column <= 7)
            valid_integer_input = true;
    }
    change_tile_player2(column);
    print_game();
}

bool connect_four::check_for_turn_remaining_as_true() const {
    for (int i(0);i<42;i++) {
        if (tiles.at(i)!='0'&&tiles.at(i)!='X') {
            return true;
        }
    }
    return false;
}

bool connect_four::check_for_draw_as_true() const {std::cout<<"Do not need to use this function - instead check for win and then if there are any turns remaining if no winners. Exiting with 1...\n";exit(1);}

bool connect_four::check_for_win_as_true() const {
    for (int i(0);i<6;i++) {
        for (int j(0);j<4;j++) {
            if (tiles.at(i*7+j)==tiles.at(i*7+j+1) && tiles.at(i*7+j+1)==tiles.at(i*7+j+2) && tiles.at(i*7+j+2)==tiles.at(i*7+j+3)&&(tiles.at(i*7+j)=='0'||tiles.at(i*7+j)=='X'))
                return true;
            if (i<3) {
                if (tiles.at(i*7+j)==tiles.at((i+1)*7+j+1) && tiles.at((i+1)*7+j+1)==tiles.at((i+2)*7+j+2) && tiles.at((i+2)*7+j+2)==tiles.at((i+3)*7+j+3)&&(tiles.at(i*7+j)=='0'||tiles.at(i*7+j)=='X'))
                    return true;
                else if (tiles.at((i+3)*7+j)==tiles.at((i+2)*7+j+1) && tiles.at((i+2)*7+j+1)==tiles.at((i+1)*7+j+2) && tiles.at((i+1)*7+j+2)==tiles.at((i)*7+j+3)&&(tiles.at((i+3)*7+j)=='0'||tiles.at((i+3)*7+j)=='X'))
                    return true;
            }
        }
    }
    for (int i(0);i<7;i++) {
        for (int j(0);j<3;j++) {
            if (tiles.at(i+j*7)==tiles.at(i+(j+1)*7) && tiles.at(i+(j+1)*7)==tiles.at(i+(j+2)*7) && tiles.at(i+(j+2)*7)==tiles.at(i+(j+3)*7)&&(tiles.at(i+j*7)=='0'||tiles.at(i+j*7)=='X'))
                return true;
        }
    }
    return false;
}

void connect_four::change_tile_player1(int column) {
    if (column >= 1 && column <= 7) {
        if (tiles[column-1]!='0'&&tiles[column-1]!='X') {
            tiles[column-1]='X';
        }
        else if (tiles[column-1+7]!='0'&&tiles[column-1+7]!='X') {
            tiles[column-1+7]='X';
        }
        else if (tiles[column-1+7*2]!='0'&&tiles[column-1+7*2]!='X') {
            tiles[column-1+7*2]='X';
        }
        else if (tiles[column-1+7*3]!='0'&&tiles[column-1+7*3]!='X') {
            tiles[column-1+7*3]='X';
        }
        else if (tiles[column-1+7*4]!='0'&&tiles[column-1+7*4]!='X') {
            tiles[column-1+7*4]='X';
        }
        else if (tiles[column-1+7*5]!='0'&&tiles[column-1+7*5]!='X') {
            tiles[column-1+7*5]='X';
        }
    }
}

void connect_four::change_tile_player2(int column) {
    if (column >= 1 && column <= 7) {
        if (tiles[column-1]!='0'&&tiles[column-1]!='X') {
            tiles[column-1]='0';
        }
        else if (tiles[column-1+7]!='0'&&tiles[column-1+7]!='X') {
            tiles[column-1+7]='0';
        }
        else if (tiles[column-1+7*2]!='0'&&tiles[column-1+7*2]!='X') {
            tiles[column-1+7*2]='0';
        }
        else if (tiles[column-1+7*3]!='0'&&tiles[column-1+7*3]!='X') {
            tiles[column-1+7*3]='0';
        }
        else if (tiles[column-1+7*4]!='0'&&tiles[column-1+7*4]!='X') {
            tiles[column-1+7*4]='0';
        }
        else if (tiles[column-1+7*5]!='0'&&tiles[column-1+7*5]!='X') {
            tiles[column-1+7*5]='0';
        }
    }
}

void connect_four::print_game() const{
    std::cout<<" =========================== \n";
    std::cout<<"| "<<tiles[35]<<" | "<<tiles[36]<<" | "<<tiles[37]<<" | "<<tiles[38]<<" | "<<tiles[39]<<" | "<<tiles[40]<<" | "<<tiles[41]<<" |\n";
    std::cout<<"|---------------------------|\n";
    std::cout<<"| "<<tiles[28]<<" | "<<tiles[29]<<" | "<<tiles[30]<<" | "<<tiles[31]<<" | "<<tiles[32]<<" | "<<tiles[33]<<" | "<<tiles[34]<<" |\n";
    std::cout<<"|---------------------------|\n";
    std::cout<<"| "<<tiles[21]<<" | "<<tiles[22]<<" | "<<tiles[23]<<" | "<<tiles[24]<<" | "<<tiles[25]<<" | "<<tiles[26]<<" | "<<tiles[27]<<" |\n";
    std::cout<<"|---------------------------|\n";
    std::cout<<"| "<<tiles[14]<<" | "<<tiles[15]<<" | "<<tiles[16]<<" | "<<tiles[17]<<" | "<<tiles[18]<<" | "<<tiles[19]<<" | "<<tiles[20]<<" |\n";
    std::cout<<"|---------------------------|\n";
    std::cout<<"| "<<tiles[7]<<" | "<<tiles[8]<<" | "<<tiles[9]<<" | "<<tiles[10]<<" | "<<tiles[11]<<" | "<<tiles[12]<<" | "<<tiles[13]<<" |\n";
    std::cout<<"|---------------------------|\n";
    std::cout<<"| "<<tiles[0]<<" | "<<tiles[1]<<" | "<<tiles[2]<<" | "<<tiles[3]<<" | "<<tiles[4]<<" | "<<tiles[5]<<" | "<<tiles[6]<<" |\n";
    std::cout<<" =========================== \n";
    std::cout<<"  1   2   3   4   5   6   7\n";
}