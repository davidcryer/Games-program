//
//  main.cpp
//  Noughts and Crosses
//
//  Created by David Cryer on 27/03/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#include "naughts_and_crosses.h"
#include "connect_four.h"
#include "chess.h"

#include <iostream>
#include <sstream>

int get_integer();
void remove_whitespace_EOL(std::string& line);
std::string get_Y_or_N(std::string question);


int main(int argc, const char * argv[]) {

    int player1_wins(0), player2_wins(0);
    
    bool stop_playing(false);
    while (!stop_playing) {
        game* game1(0);
        std::string game_choice_response;
        bool valid_game_choice_response(false);
        while (!valid_game_choice_response) {
            std::cout<<"What game would you like to play? (N)oughts and Crosses, Connect (F)our, (C)hess: ";
            std::cin>>game_choice_response;
            if (game_choice_response=="N"||game_choice_response=="F"||game_choice_response=="C") {
                valid_game_choice_response=true;
                if (game_choice_response=="N")
                    game1 = new naughts_and_crosses;
                else if (game_choice_response=="F")
                    game1 = new connect_four;
                else if (game_choice_response=="C")
                    game1 = new chess;
                game1->print_game();
            }
            else
                std::cout<<"Input error! Invalid input.\n";
        }
        
        bool game_won(false),game_drawn(false);
        while (!game_won && !game_drawn) {
            game1->player1_turn();
            game_won=game1->check_for_win_as_true();
            if (game_won) {
                std::cout<<"Player1 has won the game!\n";
                player1_wins++;
            }
            else if (!game1->check_for_turn_remaining_as_true()) {
                game_drawn = true;
                std::cout<<"Game has been drawn.\n";
            }
            else {
                game1->player2_turn();
                game_won=game1->check_for_win_as_true();
                if (game_won) {
                    std::cout<<"Player2 has won the game!\n";
                    player2_wins++;
                }
                else if (!game1->check_for_turn_remaining_as_true()) {
                    game_drawn = true;
                    std::cout<<"Game has been drawn.\n";
                }
            }
        }
        delete game1;
        std::string play_again_question = "Would you like to play another game? (Y/N): ";
        std::string play_again_response = get_Y_or_N(play_again_question);
        if (play_again_response == "N" || play_again_response == "n")
            stop_playing = true;
    }
    
    if (player1_wins > player2_wins)
        std::cout<<"Player1 wins with "<<player1_wins<<" game(s) to "<<player2_wins<<".\n";
    else if (player1_wins < player2_wins)
        std::cout<<"Player2 wins with "<<player2_wins<<" game(s) to "<<player1_wins<<".\n";
    else if (player1_wins == player2_wins)
        std::cout<<"Draw with "<<player1_wins<<" win(s) each.\n";
    
    
    std::cout<<"Thank you for using this program.\n";
    return 0;
}


int get_integer() {
    int integer(0);
    bool good_input(false);
    while (good_input == false) {
        std::string input;
        std::cin>>input;
        remove_whitespace_EOL(input);
        std::stringstream ss;
        ss<<input;
        
        while (!ss.eof()){
            std::string tempstring;
            bool ss_error(false);
            ss>>tempstring;
            if (ss.fail()) {
                ss.ignore();
                ss.clear();
                std::cerr<<"Error! Stringstream failed.\n";
                ss_error=true;
            }
            else if (!ss.eof()) {
                ss.clear();
                std::cout<<"Input error! Input contains more than one substring separated by whitespace.\n";
                ss_error=true;
            }
            if (ss_error == false) {
                try {
                    integer = std::stoi(tempstring);
                    good_input = true;
                }
                catch (std::invalid_argument&) {
                    std::cerr<<"Input error! Input could not be converted to integer value.\n";
                }
            }
            else {
                std::cout<<"Please enter the tile number you would like to go on: ";
            }
        }
    }
    return integer;
}

void remove_whitespace_EOL(std::string& line) {
    if (!line.empty()) {
        bool no_white_space(false);
        while(no_white_space == false) {
            if (line.substr(line.size()-1,line.size())==" ") {
                line.erase(line.size()-1);
            }
            else
                no_white_space=true;
        }
    }
}

std::string get_Y_or_N(std::string question) {
    std::string input;
    bool good_input(false);
    while (good_input == false){
        std::cout<<question;
        std::cin>>input;
        if (input!="Y" && input!="y" && input!="N" && input!="n") {
            std::cout<<"Input error! That is not a valid input.\n";
        }
        else
            good_input = true;
    }
    std::cin.clear();
    std::cin.ignore();
    return input;
}
