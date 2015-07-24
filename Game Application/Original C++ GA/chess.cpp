//
//  chess.cpp
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#include "chess.h"
#include <iostream>

//Do list:
//En passant and promotion

//Input could be official notation. Keep moves in string

chess::chess() {tiles="RNBQKBNRPPPPPPPP";taken_pieces=" ";for(int i(0);i<32;i++){tiles+=" ";taken_pieces+=" ";} tiles+="pppppppprnbqkbnr";tiles_under_threat_lower_case="";tiles_under_threat_upper_case="";for(int i(0);i<64;i++){tiles_under_threat_upper_case+=" ";tiles_under_threat_lower_case+=" ";}can_castle_K_R=true;can_castle_k_r=true;can_castle_R_K=true;can_castle_r_k=true;}
chess::~chess() {}

void chess::ai_turn() {
    std::string move = "";
    
    //do AI stuff
    
    print_game();
}

void chess::player1_turn() {
    
    bool valid_move(false);
    while (!valid_move) {
        //input move as string using convention a2a4 (at beginning is pawn at a2 moving to a4)
        //change input to first_position and second_position as integers corresponding to tiles elements
        //check if valid move: lots of rules for moves; check for board dimensions; some moves cannot take opponents pieces (pawn going forwards); cannot move onto tile with own piece on.
        std::cout<<"Player1, please enter your move: ";
        std::string input_move;
        std::cin>>input_move;
        
        if (input_move.size() != 4 && input_move.at(0) > 'h' && input_move.at(0) < 'a' && !isdigit(input_move.at(1)) && input_move.at(2) > 'h' && input_move.at(2) < 'a' && !isdigit(input_move.at(3))) {
            if (input_move.size()!=4)
                std::cout<<"Input error! Input must be 4 characters long.\n";
            if (input_move.at(0) > 'h' || input_move.at(0) < 'a' || input_move.at(2) > 'h' || input_move.at(2) < 'a')
                std::cout<<"Input error! First and third character must be a letter in range a to h.\n";
            if (!isdigit(input_move.at(1)) && !isdigit(input_move.at(3)))
                std::cout<<"Input error! Second and fourth character must be a number (e.g. 'a5').\n";
        }
        
        else {
            if (int(input_move.at(1)) < 1 && int(input_move.at(1)) > 8 && int(input_move.at(3)) < 1 && int(input_move.at(3)) > 8) {
                std::cout<<"Input error! Numbers in coordinates must be in range 1 - 8.\n";
            }
            else {
                int first_position = get_board_element_from_algebraic_position(input_move.substr(0,2));
                int second_position = get_board_element_from_algebraic_position(input_move.substr(2,2));
                //Have board elements for first and second position
                //check is valid
                std::string player_1_pieces = "PRNBQK";
                if (player_1_pieces.find(tiles.at(first_position)) == std::string::npos)
                    std::cout<<"Input error! Player one is using upper case pieces.\n";
                else if (player_1_pieces.find(tiles.at(second_position)) != std::string::npos)
                    std::cout<<"Input error! Cannot move piece onto a tile already controlled by own piece.\n";
                else if (!check_for_legal_movement(first_position, second_position))
                    std::cout<<"Input error! Move not valid.\n";
                
                else {
                    std::string theoretical_board_with_move = tiles;
                    return_theoretical_move_piece_at_1st_arg_to_2nd_arg(first_position,second_position,theoretical_board_with_move);
                    if (check_for_check_on_K_as_true(theoretical_board_with_move))
                        std::cout<<"Input error! King cannot finish in checked position.\n";
                    else {
                        valid_move = true;
                        add_move_to_move_history(input_move);
                        move_piece_at_1st_arg_to_2nd_arg(first_position, second_position);
                        calculate_tiles_under_threat();
                    }
                }
            }
        }
    }
    if (check_for_check_on_k_as_true()) {
        std::cout<<"k in check.\n";
        if (can_castle_k_r)
            can_castle_k_r = false;
        if (can_castle_r_k)
            can_castle_r_k =false;
    }
    print_game();
}

void chess::player2_turn() {
    int first_position(0),second_position(0);
    bool valid_move(false);
    while (!valid_move) {
        //input move as string using convention a2a4 (at beginning is pawn at a2 moving to a4)
        //change input to first_position and second_position as integers corresponding to tiles elements
        //check if valid move: lots of rules for moves; check for board dimensions; some moves cannot take opponents pieces (pawn going forwards); cannot move onto tile with own piece on.
        std::cout<<"Player2, please enter your move: ";
        std::string input_move;
        std::cin>>input_move;
        
        if (input_move.size() != 4 && input_move.at(0) > 'h' && input_move.at(0) < 'a' && !isdigit(input_move.at(1)) && input_move.at(2) > 'h' && input_move.at(2) < 'a' && !isdigit(input_move.at(3))) {
            if (input_move.size()!=4)
                std::cout<<"Input error! Input must be 4 characters long.\n";
            if (input_move.at(0) > 'h' || input_move.at(0) < 'a' || input_move.at(2) > 'h' || input_move.at(2) < 'a')
                std::cout<<"Input error! First and third character must be a letter in range a to h.\n";
            if (!isdigit(input_move.at(1)) && !isdigit(input_move.at(3)))
                std::cout<<"Input error! Second and fourth character must be a number (e.g. 'a5').\n";
        }
        
        else {
            if (int(input_move.at(1)) < 1 && int(input_move.at(1)) > 8 && int(input_move.at(3)) < 1 && int(input_move.at(3)) > 8) {
                std::cout<<"Input error! Numbers in coordinates must be in range 1 - 8.\n";
            }
            else {
                first_position = get_board_element_from_algebraic_position(input_move.substr(0,2));
                second_position = get_board_element_from_algebraic_position(input_move.substr(2,2));
                //Have board elements for first and second position
                //check is valid
                std::string player_2_pieces = "prnbqk";
                if (player_2_pieces.find(tiles.at(first_position)) == std::string::npos)
                    std::cout<<"Input error! Player two is using lower case pieces.\n";
                else if (player_2_pieces.find(tiles.at(second_position)) != std::string::npos)
                    std::cout<<"Input error! Cannot move piece onto a tile already controlled by own piece.\n";
                else if (!check_for_legal_movement(first_position, second_position))
                    std::cout<<"Input error! Move not valid.\n";
                else if (check_for_check_on_k_as_true())
                    std::cout<<"Input error! King cannot finish in checked position.\n";
                else {
                    std::string theoretical_board_with_move = tiles;
                    return_theoretical_move_piece_at_1st_arg_to_2nd_arg(first_position,second_position,theoretical_board_with_move);
                    if (check_for_check_on_k_as_true(theoretical_board_with_move))
                        std::cout<<"Input error! King cannot finish in checked position.\n";
                    else {
                        valid_move = true;
                        add_move_to_move_history(input_move);
                        move_piece_at_1st_arg_to_2nd_arg(first_position, second_position);
                    }
                }
            }
        }
    }
    calculate_tiles_under_threat();
    if (check_for_check_on_K_as_true()) {
        std::cout<<"K in check.\n";
        if (can_castle_K_R)
            can_castle_K_R = false;
        if (can_castle_R_K)
            can_castle_R_K = false;
    }
    print_game();
}

void chess::calculate_tiles_under_threat() {
    std::string theoretical_tiles_under_threat_lower_case = "";
    std::string theoretical_tiles_under_threat_upper_case = "";
    for (int i(0);i<64;i++) {
        theoretical_tiles_under_threat_lower_case += " ";
        theoretical_tiles_under_threat_upper_case += " ";
    }
    for (int i(0);i<64;i++) {
        std::string lower_case_pieces = "prnbqk";
        if (lower_case_pieces.find(tiles.at(i)) != std::string::npos) {
            for (int j(0);j<64;j++) {
                if (theoretical_tiles_under_threat_lower_case.at(j) != 'L') {
                    if (check_for_legal_movement_for_theoretical_tiles(i,j,tiles)) {
                        std::string tiles_with_move = tiles;
                        return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,tiles_with_move);
                        
                        std::string create_tiles_under_threat_by_lower_case_pieces = "";
                        for (int k(0);k<64;k++)
                            create_tiles_under_threat_by_lower_case_pieces += " ";
                        
                        for (int k(0);k<64;k++) {
                            if (tiles_with_move.at(k) != ' ' && lower_case_pieces.find(tiles_with_move.at(k)) == std::string::npos) {
                                for (int l(0);l<64;l++) {
                                    if (!(tiles_with_move.at(k) == 'P' && (k-l)%8 == 0)) {
                                        if (check_for_legal_movement_for_theoretical_tiles(k,l,tiles_with_move)) {
                                            create_tiles_under_threat_by_lower_case_pieces.at(l) = 'U';
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (tiles.at(i) == 'p' && (i-j)%8 == 0) {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(tiles.find('k')) != 'U')
                                theoretical_tiles_under_threat_lower_case.at(j) = 'P';
                        }
                        else {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(tiles.find('k')) != 'U')
                                theoretical_tiles_under_threat_lower_case.at(j) = 'L';
                            else {
                                if (theoretical_tiles_under_threat_lower_case.at(j) != 'l')
                                    theoretical_tiles_under_threat_lower_case.at(j) = 'l';
                            }
                        }
                    }
                }
            }
        }
        else if (lower_case_pieces.find(tiles.at(i)) == std::string::npos && tiles.at(i) != ' ') {
            for (int j(0);j<64;j++) {
                if (theoretical_tiles_under_threat_upper_case.at(j) != 'U') {
                    if (check_for_legal_movement_for_theoretical_tiles(i,j,tiles)) {
                        std::string tiles_with_move = tiles;
                        return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,tiles_with_move);
                        
                        std::string create_tiles_under_threat_by_lower_case_pieces = "";
                        for (int k(0);k<64;k++)
                            create_tiles_under_threat_by_lower_case_pieces += " ";
                        
                        for (int k(0);k<64;k++) {
                            if (lower_case_pieces.find(tiles.at(k)) != std::string::npos) {
                                for (int l(0);l<64;l++) {
                                    if (!(tiles_with_move.at(k) == 'p' && (k-l)%8 == 0)) {
                                        if (check_for_legal_movement_for_theoretical_tiles(k,l,tiles_with_move)) {
                                            create_tiles_under_threat_by_lower_case_pieces.at(l) = 'L';
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (tiles.at(i) == 'P' && (i-j)%8 == 0) {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(tiles.find('K')) != 'L')
                                theoretical_tiles_under_threat_upper_case.at(j) = 'P';
                        }
                        else {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(tiles.find('K')) != 'L')
                                theoretical_tiles_under_threat_upper_case.at(j) = 'U';
                            else {
                                if (theoretical_tiles_under_threat_upper_case.at(j) != 'u')
                                    theoretical_tiles_under_threat_upper_case.at(j) = 'u';
                            }
                        }
                    }
                }
            }
        }
    }
    tiles_under_threat_lower_case = theoretical_tiles_under_threat_lower_case;
    tiles_under_threat_upper_case = theoretical_tiles_under_threat_upper_case;
}

std::string chess::return_theoretical_tiles_under_threat_lower_case(std::string const& using_tiles) const {
    std::string theoretical_tiles_under_threat_lower_case = "";
    for (int i(0);i<64;i++)
        theoretical_tiles_under_threat_lower_case += " ";
    for (int i(0);i<64;i++) {
        std::string lower_case_pieces = "prnbqk";
        if (lower_case_pieces.find(using_tiles.at(i)) != std::string::npos) {
            for (int j(0);j<64;j++) {
                if (theoretical_tiles_under_threat_lower_case.at(j) != 'L') {
                    if (check_for_legal_movement_for_theoretical_tiles(i,j,using_tiles)) {
                        std::string using_tiles_with_move = using_tiles;
                        return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,using_tiles_with_move);
                        
                        std::string create_tiles_under_threat_by_lower_case_pieces = "";
                        for (int k(0);k<64;k++)
                            create_tiles_under_threat_by_lower_case_pieces += " ";
                        
                        for (int k(0);k<64;k++) {
                            if (using_tiles_with_move.at(k) != ' ' && lower_case_pieces.find(using_tiles_with_move.at(k)) == std::string::npos && using_tiles_with_move.at(k) != 'k') {
                                for (int l(0);l<64;l++) {
                                    if (!(using_tiles_with_move.at(k) == 'P' && (k-l)%8 == 0)) {
                                        if (check_for_legal_movement_for_theoretical_tiles(k,l,using_tiles_with_move)) {
                                            create_tiles_under_threat_by_lower_case_pieces.at(l) = 'U';
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (using_tiles.at(i) == 'p' && (i-j)%8 == 0) {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(using_tiles.find('k')) != 'U')
                                theoretical_tiles_under_threat_lower_case.at(j) = 'P';
                        }
                        else {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(using_tiles.find('k')) != 'U')
                                theoretical_tiles_under_threat_lower_case.at(j) = 'L';
                            else {
                                if (theoretical_tiles_under_threat_lower_case.at(j) != 'l')
                                    theoretical_tiles_under_threat_lower_case.at(j) = 'l';
                            }
                        }
                    }
                }
            }
        }
    }
    return theoretical_tiles_under_threat_lower_case;
}

std::string chess::return_theoretical_tiles_under_threat_upper_case(std::string const& using_tiles) const {
    std::string theoretical_tiles_under_threat_upper_case = "";
    for (int i(0);i<64;i++)
        theoretical_tiles_under_threat_upper_case += " ";
    for (int i(0);i<64;i++) {
        std::string upper_case_pieces = "PRNBQK";
        if (upper_case_pieces.find(using_tiles.at(i)) != std::string::npos) {
            for (int j(0);j<64;j++) {
                if (theoretical_tiles_under_threat_upper_case.at(j) != 'U') {
                    if (check_for_legal_movement_for_theoretical_tiles(i,j,using_tiles)) {
                        std::string using_tiles_with_move = using_tiles;
                        return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,using_tiles_with_move);
                        
                        std::string create_tiles_under_threat_by_lower_case_pieces = "";
                        for (int k(0);k<64;k++)
                            create_tiles_under_threat_by_lower_case_pieces += " ";
                        
                        for (int k(0);k<64;k++) {
                            if (using_tiles_with_move.at(k) != ' ' && upper_case_pieces.find(using_tiles_with_move.at(k)) == std::string::npos && using_tiles_with_move.at(k) != 'K') {
                                for (int l(0);l<64;l++) {
                                    if (!(using_tiles_with_move.at(k) == 'p' && (k-l)%8 == 0)) {
                                        if (check_for_legal_movement_for_theoretical_tiles(k,l,using_tiles_with_move)) {
                                            create_tiles_under_threat_by_lower_case_pieces.at(l) = 'L';
                                        }
                                    }
                                }
                            }
                        }
                        
                        if (using_tiles.at(i) == 'P' && (i-j)%8 == 0) {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(using_tiles.find('K')) != 'L')
                                theoretical_tiles_under_threat_upper_case.at(j) = 'P';
                        }
                        else {
                            if (create_tiles_under_threat_by_lower_case_pieces.at(using_tiles.find('K')) != 'L')
                                theoretical_tiles_under_threat_upper_case.at(j) = 'U';
                            else {
                                if (theoretical_tiles_under_threat_upper_case.at(j) != 'u')
                                    theoretical_tiles_under_threat_upper_case.at(j) = 'u';
                            }
                        }
                    }
                }
            }
        }
    }
    return theoretical_tiles_under_threat_upper_case;}

bool chess::check_for_legal_movement_for_theoretical_tiles(int first_position,int second_position,std::string const& using_tiles) const {
    if (first_position!=second_position) {
        std::string upper_case_pieces = "PRNBQK", lower_case_pieces = "prnbqk";
        if ((upper_case_pieces.find(using_tiles.at(first_position)) != std::string::npos && upper_case_pieces.find(using_tiles.at(second_position)) == std::string::npos) || (lower_case_pieces.find(using_tiles.at(first_position)) != std::string::npos && lower_case_pieces.find(using_tiles.at(second_position)) == std::string::npos)) {
            
            if (using_tiles.at(first_position)=='p') {
                if (second_position == first_position - 8 && using_tiles.at(second_position) == ' ') //moving forwards one
                    return true;
                else if (first_position >= 48 && first_position <=55) { //moving forwards two only if in original position
                    if (second_position == first_position - 16 && using_tiles.at(second_position) == ' ')
                        return true;
                }
                else if ( (second_position==first_position-7 || second_position==first_position-9 ) && upper_case_pieces.find(using_tiles.at(second_position)) != std::string::npos) { //taking piece diagonally
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8) //Pawn has gone forward only one line
                        return true;
                }
            }
            else if (using_tiles.at(first_position)=='P') {
                if (second_position == first_position + 8 && using_tiles.at(second_position) == ' ')
                    return true;
                else if (first_position >= 8 && first_position <=15) {
                    if (second_position == first_position + 16 && using_tiles.at(second_position) == ' ')
                        return true;
                }
                else if ( (second_position==first_position+7 || second_position==first_position+9 ) && lower_case_pieces.find(using_tiles.at(second_position)) != std::string::npos) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)
                        return true;
                }
            }
            
            else if (using_tiles.at(first_position)=='r' || using_tiles.at(first_position)=='R') {
                if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8) {//moving sideways
                    if (second_position > first_position) {
                        if (using_tiles.substr(first_position+1,second_position-first_position-1).find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                            return true;
                    }
                    else {
                        if (using_tiles.substr(second_position+1,first_position-second_position-1).find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
                else if ((first_position-second_position) % 8 == 0) {//moving forwards/backwards
                    if (second_position > first_position) {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position+8);i<second_position;i+=8) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                    else {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position-8);i>second_position;i-=8) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
            }
            
            else if (using_tiles.at(first_position)=='n' || using_tiles.at(first_position)=='N') {
                if (second_position==first_position+6 || second_position==first_position+10) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)//knight moves forward by one row
                        return true;
                }
                else if (second_position==first_position-6 || second_position==first_position-10) {
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8)//knight backwards forward by one row
                        return true;
                }
                else if (second_position==first_position+15 || second_position==first_position+17) {
                    if (second_position-16<=first_position+7-first_position%8 && second_position-16>=first_position-first_position%8)//knight moves forwards by two rows
                        return true;
                }
                else if (second_position==first_position-15 || second_position==first_position-17) {
                    if (second_position+16<=first_position+7-first_position%8 && second_position+16>=first_position-first_position%8)//knight moves backwards by two rows
                        return true;
                }
            }
            
            else if (using_tiles.at(first_position)=='b' || using_tiles.at(first_position)=='B') {
                if ((first_position-second_position)%9 == 0) {//moving up-right diagonally
                    if (second_position-((second_position-first_position)%8)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%8)*8>=first_position-first_position%8) {//Has not moved out of board
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+9);i<second_position;i+=9) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-9);i>second_position;i-=9) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
                else if ((first_position-second_position)%7 == 0) {//moving up-left diagonally
                    if (second_position-((second_position-first_position)%6)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%6)*8>=first_position-first_position%8) {
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+7);i<second_position;i+=7) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-7);i>second_position;i-=7) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
            }
            
            else if (using_tiles.at(first_position)=='q' || using_tiles.at(first_position)=='Q') {
                if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8) {//moving sideways
                    if (second_position > first_position) {
                        if (using_tiles.substr(first_position+1,second_position-first_position-1).find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                            return true;
                    }
                    else {
                        if (using_tiles.substr(second_position+1,first_position-second_position-1).find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
                else if ((first_position-second_position) % 8 == 0) {//moving forwards/backwards
                    if (second_position > first_position) {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position+8);i<second_position;i+=8) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                    else {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position-8);i>second_position;i-=8) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)                            return true;
                    }
                }
                else if ((first_position-second_position)%9 == 0) {//moving up-right diagonally
                    if (second_position-((second_position-first_position)%8)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%8)*8>=first_position-first_position%8) {//Has not moved out of board
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+9);i<second_position;i+=9) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-9);i>second_position;i-=9) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
                else if ((first_position-second_position) % 7 == 0) {//moving up-left diagonally
                    if (second_position-((second_position-first_position)%6)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%6)*8>=first_position-first_position%8) {
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+7);i<second_position;i+=7) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-7);i>second_position;i-=7) path_inbetween_intial_final_positions.append(using_tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
            }
            
            else if (using_tiles.at(first_position)=='k' || using_tiles.at(first_position)=='K') {//king will not move into check
                if (second_position==first_position+7 || second_position==first_position+8 || second_position==first_position+9) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)
                        return true;
                }
                else if (second_position==first_position-7 || second_position==first_position-8 || second_position==first_position-9) {
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8)
                        return true;
                }
                else if (second_position==first_position+1 || second_position==first_position-1) {
                    if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8)
                        return true;
                }
                else if (can_castle_K_R && first_position == 4 && second_position == 6 && using_tiles.substr(5,2) == "  ") {
                    if (return_theoretical_tiles_under_threat_upper_case(using_tiles).substr(5,1).find('U') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 4 && second_position == 2 && using_tiles.substr(1,3) == "   ") {
                    if (return_theoretical_tiles_under_threat_upper_case(using_tiles).substr(3,1).find('U') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 60 && second_position == 62 && using_tiles.substr(61,2) == "  ") {
                    if (return_theoretical_tiles_under_threat_upper_case(using_tiles).substr(61,1).find('L') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 60 && second_position == 58 && using_tiles.substr(57,3) == "   ") {
                    if (return_theoretical_tiles_under_threat_upper_case(using_tiles).substr(59,1).find('L') == std::string::npos)
                        return true;
                }
            }
        }
    }
    return false;
}

bool chess::check_for_legal_movement(int first_position,int second_position) const { //assume first and second position inside scope of board and ignoring case of piece landing on piece of same team or finishing in check position
    if (first_position!=second_position) {
        std::string upper_case_pieces = "PRNBQK", lower_case_pieces = "prnbqk";
        if ((upper_case_pieces.find(tiles.at(first_position)) != std::string::npos && upper_case_pieces.find(tiles.at(second_position)) == std::string::npos) || (lower_case_pieces.find(tiles.at(first_position)) != std::string::npos && lower_case_pieces.find(tiles.at(second_position)) == std::string::npos)) {
            
            if (tiles.at(first_position)=='p') {
                if (second_position == first_position - 8 && tiles.at(second_position) == ' ') //moving forwards one
                    return true;
                else if (first_position >= 48 && first_position <=55) { //moving forwards two only if in original position
                    if (second_position == first_position - 16 && tiles.at(second_position) == ' ')
                        return true;
                }
                else if ( (second_position==first_position-7 || second_position==first_position-9 ) && upper_case_pieces.find(tiles.at(second_position)) != std::string::npos) { //taking piece diagonally
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8) //Pawn has gone forward only one line
                        return true;
                }
            }
            else if (tiles.at(first_position)=='P') {
                if (second_position == first_position + 8 && tiles.at(second_position) == ' ')
                    return true;
                else if (first_position >= 8 && first_position <=15) {
                    if (second_position == first_position + 16 && tiles.at(second_position) == ' ')
                        return true;
                }
                else if ( (second_position==first_position+7 || second_position==first_position+9 ) && lower_case_pieces.find(tiles.at(second_position)) != std::string::npos) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)
                        return true;
                }
            }
            
            else if (tiles.at(first_position)=='r' || tiles.at(first_position)=='R') {
                if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8) {//moving sideways
                    if (second_position > first_position) {
                        if (tiles.substr(first_position+1,second_position-first_position-1).find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                            return true;
                    }
                    else {
                        if (tiles.substr(second_position+1,first_position-second_position-1).find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
                else if ((first_position-second_position) % 8 == 0) {//moving forwards/backwards
                    if (second_position > first_position) {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position+8);i<second_position;i+=8) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                    else {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position-8);i>second_position;i-=8) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
            }
            
            else if (tiles.at(first_position)=='n' || tiles.at(first_position)=='N') {
                if (second_position==first_position+6 || second_position==first_position+10) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)//knight moves forward by one row
                        return true;
                }
                else if (second_position==first_position-6 || second_position==first_position-10) {
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8)//knight backwards forward by one row
                        return true;
                }
                else if (second_position==first_position+15 || second_position==first_position+17) {
                    if (second_position-16<=first_position+7-first_position%8 && second_position-16>=first_position-first_position%8)//knight moves forwards by two rows
                        return true;
                }
                else if (second_position==first_position-15 || second_position==first_position-17) {
                    if (second_position+16<=first_position+7-first_position%8 && second_position+16>=first_position-first_position%8)//knight moves backwards by two rows
                        return true;
                }
            }
            
            else if (tiles.at(first_position)=='b' || tiles.at(first_position)=='B') {
                if ((first_position-second_position)%9 == 0) {//moving up-right diagonally
                    if (second_position-((second_position-first_position)%8)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%8)*8>=first_position-first_position%8) {//Has not moved out of board
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+9);i<second_position;i+=9) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-9);i>second_position;i-=9) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
                else if ((first_position-second_position)%7 == 0) {//moving up-left diagonally
                    if (second_position-((second_position-first_position)%6)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%6)*8>=first_position-first_position%8) {
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+7);i<second_position;i+=7) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-7);i>second_position;i-=7) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
            }
            
            else if (tiles.at(first_position)=='q' || tiles.at(first_position)=='Q') {
                if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8) {//moving sideways
                    if (second_position > first_position) {
                        if (tiles.substr(first_position+1,second_position-first_position-1).find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                            return true;
                    }
                    else {
                        if (tiles.substr(second_position+1,first_position-second_position-1).find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
                else if ((first_position-second_position) % 8 == 0) {//moving forwards/backwards
                    if (second_position > first_position) {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position+8);i<second_position;i+=8) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                    else {
                        std::string path_inbetween_intial_final_positions;
                        for (int i(first_position-8);i>second_position;i-=8) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                        if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                            return true;
                    }
                }
                else if ((first_position-second_position)%9 == 0) {//moving up-right diagonally
                    if (second_position-((second_position-first_position)%8)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%8)*8>=first_position-first_position%8) {//Has not moved out of board
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+9);i<second_position;i+=9) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)//path must be clear, else illegal
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-9);i>second_position;i-=9) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
                else if ((first_position-second_position) % 7 == 0) {//moving up-left diagonally
                    if (second_position-((second_position-first_position)%6)*8<=first_position+7-first_position%8 && second_position-((second_position-first_position)%6)*8>=first_position-first_position%8) {
                        if (second_position > first_position) {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position+7);i<second_position;i+=7) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                        else {
                            std::string path_inbetween_intial_final_positions;
                            for (int i(first_position-7);i>second_position;i-=7) path_inbetween_intial_final_positions.append(tiles.substr(i,1));
                            if (path_inbetween_intial_final_positions.find_first_not_of(' ') == std::string::npos)
                                return true;
                        }
                    }
                }
            }
            
            else if (tiles.at(first_position)=='k' || tiles.at(first_position)=='K') {//king will not move into check
                if (second_position==first_position+7 || second_position==first_position+8 || second_position==first_position+9) {
                    if (second_position-8<=first_position+7-first_position%8 && second_position-8>=first_position-first_position%8)
                        return true;
                }
                else if (second_position==first_position-7 || second_position==first_position-8 || second_position==first_position-9) {
                    if (second_position+8<=first_position+7-first_position%8 && second_position+8>=first_position-first_position%8)
                        return true;
                }
                else if (second_position==first_position+1 || second_position==first_position-1) {
                    if (second_position<=first_position+7-first_position%8 && second_position>=first_position-first_position%8)
                        return true;
                }
                else if (can_castle_K_R && first_position == 4 && second_position == 6 && tiles.substr(5,2) == "  ") {
                    if (tiles_under_threat_upper_case.substr(5,1).find('U') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 4 && second_position == 2 && tiles.substr(1,3) == "   ") {
                    if (tiles_under_threat_upper_case.substr(3,1).find('U') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 60 && second_position == 62 && tiles.substr(61,2) == "  ") {
                    if (tiles_under_threat_lower_case.substr(61,1).find('L') == std::string::npos)
                        return true;
                }
                else if (can_castle_K_R && first_position == 60 && second_position == 58 && tiles.substr(57,3) == "   ") {
                    if (tiles_under_threat_lower_case.substr(59,1).find('L') == std::string::npos)
                        return true;
                }
            }
        }
    }
    return false;
}

bool chess::check_for_check_on_k_as_true() const {
    std::size_t king_position = tiles.find('k');
    if (tiles_under_threat_upper_case.at(king_position) == 'U' || tiles_under_threat_upper_case.at(king_position) =='u') {
        return true;
    }
    else
        return false;
}

bool chess::check_for_check_on_K_as_true() const {
    std::size_t king_position = tiles.find('K');
    if (tiles_under_threat_lower_case.at(king_position) == 'L' || tiles_under_threat_lower_case.at(king_position) =='l') {
        return true;
    }
    else
        return false;
}

bool chess::check_for_check_on_K_as_true(std::string const& theoretical_tiles) const {
    std::size_t king_position = theoretical_tiles.find('K');
    std::string theoretical_tiles_under_threat_lower_case = return_theoretical_tiles_under_threat_lower_case(theoretical_tiles);
    if (theoretical_tiles_under_threat_lower_case.at(king_position) == 'L' || theoretical_tiles_under_threat_lower_case.at(king_position) == 'l') {
        return true;
    }
    else
        return false;
}

bool chess::check_for_check_on_k_as_true(std::string const& theoretical_tiles) const {
    std::size_t king_position = theoretical_tiles.find('k');
    std::string theoretical_tiles_under_threat_upper_case = return_theoretical_tiles_under_threat_upper_case(theoretical_tiles);
    if (theoretical_tiles_under_threat_upper_case.at(king_position) == 'U' || theoretical_tiles_under_threat_upper_case.at(king_position) == 'u') {
        return true;
    }
    else
        return false;
}

bool chess::check_for_turn_remaining_as_true() const {
    for (int i(0);i<64;i++) {
        if (tiles.at(i) != ' ') {
            std::string upper_case_pieces = "PRNBQK";
            if (upper_case_pieces.find(tiles.at(get_board_element_from_algebraic_position(move_history.substr(move_history.size()-3,2)))) != std::string::npos) {
                if (upper_case_pieces.find(tiles.at(i)) == std::string::npos) {
                    for (int j(0);j<64;j++) {
                        if (check_for_legal_movement(i,j)) {
                            std::string move_on_tiles = tiles;
                            return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,move_on_tiles);
                            if (!check_for_check_on_k_as_true(move_on_tiles)) {
                                //print_game(move_on_tiles);
                                return true;
                            }
                        }
                    }
                }
            }
            else {
                if (upper_case_pieces.find(tiles.at(i)) != std::string::npos) {
                    for (int j(0);j<64;j++) {
                        if (check_for_legal_movement(i,j)) {
                            std::string move_on_tiles = tiles;
                            return_theoretical_move_piece_at_1st_arg_to_2nd_arg(i,j,move_on_tiles);
                            if (!check_for_check_on_K_as_true(move_on_tiles))
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool chess::check_for_draw_as_true() const {
    if (!check_for_turn_remaining_as_true()) {
        std::string upper_case_pieces = "PRNBQK";
        if (upper_case_pieces.find(tiles.at(get_board_element_from_algebraic_position(move_history.substr(move_history.size()-3,2)))) != std::string::npos) {
            if (!check_for_check_on_k_as_true())
                return true;
        }
        else {
            if (!check_for_check_on_K_as_true())
                return true;
        }
    }
    return false;
}

bool chess::check_for_win_as_true() const {
    if (!check_for_turn_remaining_as_true()) {
        std::string upper_case_pieces = "PRNBQK";
        if (upper_case_pieces.find(tiles.at(get_board_element_from_algebraic_position(move_history.substr(move_history.size()-3,2)))) != std::string::npos) {
            if (check_for_check_on_k_as_true()) {
                std::cout<<"Checkmate!\n";
                return true;
            }
        }
        else {
            if (check_for_check_on_K_as_true()) {
                std::cout<<"Checkmate!\n";
                return true;
            }
        }
    }
    return false;
}

void chess::move_piece_at_1st_arg_to_2nd_arg(int first_position,int second_position) {
    if (tiles.at(first_position) == 'r' && first_position == 56 && can_castle_r_k)
        can_castle_r_k = false;
    else if (tiles.at(first_position) == 'r' && first_position == 63 && can_castle_k_r)
        can_castle_k_r = false;
    else if (tiles.at(first_position) == 'R' && first_position == 0 && can_castle_R_K)
        can_castle_R_K = false;
    else if (tiles.at(first_position) == 'R' && first_position == 7 && can_castle_K_R)
        can_castle_K_R = false;
    else if (tiles.at(first_position) == 'k') {
        if (can_castle_k_r) {
            can_castle_k_r = false;
            if (second_position == 62)
                move_piece_at_1st_arg_to_2nd_arg(63,61); //move rook
        }
        if (can_castle_r_k) {
            can_castle_r_k = false;
            if (second_position == 58)
                move_piece_at_1st_arg_to_2nd_arg(56,59);
        }
    }
    else if (tiles.at(first_position) == 'K') {
        if (can_castle_K_R) {
            can_castle_K_R = false;
            if (second_position == 6)
                move_piece_at_1st_arg_to_2nd_arg(7,5);
        }
        if (can_castle_R_K) {
            can_castle_R_K = false;
            if (second_position == 2)
                move_piece_at_1st_arg_to_2nd_arg(0,3);
        }
    }
    
    else if (tiles.at(second_position)!=' ') {
        put_taken_piece_to_side(tiles.at(second_position));
    }
    tiles.at(second_position)=tiles.at(first_position);
    tiles.at(first_position)=' ';
}

void chess::return_theoretical_move_piece_at_1st_arg_to_2nd_arg(int first_position,int second_position,std::string &theoretical_tiles) const {
    theoretical_tiles.at(second_position)=theoretical_tiles.at(first_position);
    theoretical_tiles.at(first_position)=' ';
}

int chess::get_board_element_from_algebraic_position(std::string const& move) const{
    if (move.size()==2 && move.at(0) <= 'h' && isdigit(move.at(1))) {
        int board_element = move.at(0) - 'a' + 8*(move.at(1)-'0'-1);
        return board_element;
    }
    else {
        if (move.size()!=2)
            std::cerr<<"Error! Algebraic position given by two characters (e.g. 'a5'). Program terminating with 1...\n";
        if (move.at(0) >= 'h')
            std::cerr<<"Error! Algebraic position given by letter from a-h followed by a number. Program terminating with 1...\n";
        if (!isdigit(move.at(1)))
            std::cerr<<"Error! Second character must be a number (e.g. 'a5'). Program terminating with 1...\n";
        exit(1);
    }
}

void chess::put_taken_piece_to_side(char piece) {
    if (piece=='p') {
        for (int i(0);i<8;i++) {
            if (taken_pieces.at(16+i)==' ') {
                taken_pieces.at(16+i)=piece;
                break;
            }
        }
    }
    if (piece=='P') {
        for (int i(0);i<8;i++) {
            if (taken_pieces.at(8+i)==' ') {
                taken_pieces.at(8+i)=piece;
                break;
            }
        }
    }
    if (piece=='r') {
        if (taken_pieces.at(24)==' ')
            taken_pieces.at(24)=piece;
        else if (taken_pieces.at(31) == ' ')
            taken_pieces.at(31)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(16+i)==' ') {
                    taken_pieces.at(16+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='R') {
        if (taken_pieces.at(0)==' ')
            taken_pieces.at(0)=piece;
        else if (taken_pieces.at(7) == ' ')
            taken_pieces.at(7)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(8+i)==' ') {
                    taken_pieces.at(8+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='n') {
        if (taken_pieces.at(25)==' ')
            taken_pieces.at(25)=piece;
        else if (taken_pieces.at(30) == ' ')
            taken_pieces.at(30)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(16+i)==' ') {
                    taken_pieces.at(16+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='N') {
        if (taken_pieces.at(1)==' ')
            taken_pieces.at(1)=piece;
        else if (taken_pieces.at(6) == ' ')
            taken_pieces.at(6)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(8+i)==' ') {
                    taken_pieces.at(8+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='b') {
        if (taken_pieces.at(26)==' ')
            taken_pieces.at(26)=piece;
        else if (taken_pieces.at(29) == ' ')
            taken_pieces.at(29)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(16+i)==' ') {
                    taken_pieces.at(16+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='B') {
        if (taken_pieces.at(2)==' ')
            taken_pieces.at(2)=piece;
        else if (taken_pieces.at(5) == ' ')
            taken_pieces.at(5)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(8+i)==' ') {
                    taken_pieces.at(8+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='q') {
        if (taken_pieces.at(27)==' ')
            taken_pieces.at(27)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(16+i)==' ') {
                    taken_pieces.at(16+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='Q') {
        if (taken_pieces.at(3)==' ')
            taken_pieces.at(3)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(8+i)==' ') {
                    taken_pieces.at(8+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='k') {
        if (taken_pieces.at(28)==' ')
            taken_pieces.at(28)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(16+i)==' ') {
                    taken_pieces.at(16+i)=piece;
                    break;
                }
            }
        }
    }
    if (piece=='K') {
        if (taken_pieces.at(4)==' ')
            taken_pieces.at(4)=piece;
        else {
            for (int i(0);i<8;i++) {
                if (taken_pieces.at(8+i)==' ') {
                    taken_pieces.at(8+i)=piece;
                    break;
                }
            }
        }
    }
}

void chess::add_move_to_move_history(std::string const& move) {
    move_history += move + " ";
}

void chess::print_game() const {
    std::cout<<" =============================== \n";
    std::cout<<"| "<<tiles.at(56)<<" | "<<tiles.at(57)<<" | "<<tiles.at(58)<<" | "<<tiles.at(59)<<" | "<<tiles.at(60)<<" | "<<tiles.at(61)<<" | "<<tiles.at(62)<<" | "<<tiles.at(63)<<" | 8    "<<taken_pieces.at(24)<<" "<<taken_pieces.at(25)<<" "<<taken_pieces.at(26)<<" "<<taken_pieces.at(27)<<" "<<taken_pieces.at(28)<<" "<<taken_pieces.at(29)<<" "<<taken_pieces.at(30)<<" "<<taken_pieces.at(31)<<"\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(48)<<" | "<<tiles.at(49)<<" | "<<tiles.at(50)<<" | "<<tiles.at(51)<<" | "<<tiles.at(52)<<" | "<<tiles.at(53)<<" | "<<tiles.at(54)<<" | "<<tiles.at(55)<<" | 7    "<<taken_pieces.at(16)<<" "<<taken_pieces.at(17)<<" "<<taken_pieces.at(18)<<" "<<taken_pieces.at(19)<<" "<<taken_pieces.at(20)<<" "<<taken_pieces.at(21)<<" "<<taken_pieces.at(22)<<" "<<taken_pieces.at(23)<<"\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(40)<<" | "<<tiles.at(41)<<" | "<<tiles.at(42)<<" | "<<tiles.at(43)<<" | "<<tiles.at(44)<<" | "<<tiles.at(45)<<" | "<<tiles.at(46)<<" | "<<tiles.at(47)<<" | 6\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(32)<<" | "<<tiles.at(33)<<" | "<<tiles.at(34)<<" | "<<tiles.at(35)<<" | "<<tiles.at(36)<<" | "<<tiles.at(37)<<" | "<<tiles.at(38)<<" | "<<tiles.at(39)<<" | 5\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(24)<<" | "<<tiles.at(25)<<" | "<<tiles.at(26)<<" | "<<tiles.at(27)<<" | "<<tiles.at(28)<<" | "<<tiles.at(29)<<" | "<<tiles.at(30)<<" | "<<tiles.at(31)<<" | 4\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(16)<<" | "<<tiles.at(17)<<" | "<<tiles.at(18)<<" | "<<tiles.at(19)<<" | "<<tiles.at(20)<<" | "<<tiles.at(21)<<" | "<<tiles.at(22)<<" | "<<tiles.at(23)<<" | 3\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(8)<<" | "<<tiles.at(9)<<" | "<<tiles.at(10)<<" | "<<tiles.at(11)<<" | "<<tiles.at(12)<<" | "<<tiles.at(13)<<" | "<<tiles.at(14)<<" | "<<tiles.at(15)<<" | 2    "<<taken_pieces.at(8)<<" "<<taken_pieces.at(9)<<" "<<taken_pieces.at(10)<<" "<<taken_pieces.at(11)<<" "<<taken_pieces.at(12)<<" "<<taken_pieces.at(13)<<" "<<taken_pieces.at(14)<<" "<<taken_pieces.at(15)<<"\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles.at(0)<<" | "<<tiles.at(1)<<" | "<<tiles.at(2)<<" | "<<tiles.at(3)<<" | "<<tiles.at(4)<<" | "<<tiles.at(5)<<" | "<<tiles.at(6)<<" | "<<tiles.at(7)<<" | 1    "<<taken_pieces.at(0)<<" "<<taken_pieces.at(1)<<" "<<taken_pieces.at(2)<<" "<<taken_pieces.at(3)<<" "<<taken_pieces.at(4)<<" "<<taken_pieces.at(5)<<" "<<taken_pieces.at(6)<<" "<<taken_pieces.at(7)<<"\n";
    std::cout<<" =============================== \n";
    std::cout<<"  A   B   C   D   E   F   G   H\n";
}

void chess::print_tiles_under_threat_upper_case() const { //useful for debugging
    std::cout<<" =============================== \n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(56)<<" | "<<tiles_under_threat_upper_case.at(57)<<" | "<<tiles_under_threat_upper_case.at(58)<<" | "<<tiles_under_threat_upper_case.at(59)<<" | "<<tiles_under_threat_upper_case.at(60)<<" | "<<tiles_under_threat_upper_case.at(61)<<" | "<<tiles_under_threat_upper_case.at(62)<<" | "<<tiles_under_threat_upper_case.at(63)<<" | 8\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(48)<<" | "<<tiles_under_threat_upper_case.at(49)<<" | "<<tiles_under_threat_upper_case.at(50)<<" | "<<tiles_under_threat_upper_case.at(51)<<" | "<<tiles_under_threat_upper_case.at(52)<<" | "<<tiles_under_threat_upper_case.at(53)<<" | "<<tiles_under_threat_upper_case.at(54)<<" | "<<tiles_under_threat_upper_case.at(55)<<" | 7\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(40)<<" | "<<tiles_under_threat_upper_case.at(41)<<" | "<<tiles_under_threat_upper_case.at(42)<<" | "<<tiles_under_threat_upper_case.at(43)<<" | "<<tiles_under_threat_upper_case.at(44)<<" | "<<tiles_under_threat_upper_case.at(45)<<" | "<<tiles_under_threat_upper_case.at(46)<<" | "<<tiles_under_threat_upper_case.at(47)<<" | 6\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(32)<<" | "<<tiles_under_threat_upper_case.at(33)<<" | "<<tiles_under_threat_upper_case.at(34)<<" | "<<tiles_under_threat_upper_case.at(35)<<" | "<<tiles_under_threat_upper_case.at(36)<<" | "<<tiles_under_threat_upper_case.at(37)<<" | "<<tiles_under_threat_upper_case.at(38)<<" | "<<tiles_under_threat_upper_case.at(39)<<" | 5\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(24)<<" | "<<tiles_under_threat_upper_case.at(25)<<" | "<<tiles_under_threat_upper_case.at(26)<<" | "<<tiles_under_threat_upper_case.at(27)<<" | "<<tiles_under_threat_upper_case.at(28)<<" | "<<tiles_under_threat_upper_case.at(29)<<" | "<<tiles_under_threat_upper_case.at(30)<<" | "<<tiles_under_threat_upper_case.at(31)<<" | 4\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(16)<<" | "<<tiles_under_threat_upper_case.at(17)<<" | "<<tiles_under_threat_upper_case.at(18)<<" | "<<tiles_under_threat_upper_case.at(19)<<" | "<<tiles_under_threat_upper_case.at(20)<<" | "<<tiles_under_threat_upper_case.at(21)<<" | "<<tiles_under_threat_upper_case.at(22)<<" | "<<tiles_under_threat_upper_case.at(23)<<" | 3\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(8)<<" | "<<tiles_under_threat_upper_case.at(9)<<" | "<<tiles_under_threat_upper_case.at(10)<<" | "<<tiles_under_threat_upper_case.at(11)<<" | "<<tiles_under_threat_upper_case.at(12)<<" | "<<tiles_under_threat_upper_case.at(13)<<" | "<<tiles_under_threat_upper_case.at(14)<<" | "<<tiles_under_threat_upper_case.at(15)<<" | 2\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<tiles_under_threat_upper_case.at(0)<<" | "<<tiles_under_threat_upper_case.at(1)<<" | "<<tiles_under_threat_upper_case.at(2)<<" | "<<tiles_under_threat_upper_case.at(3)<<" | "<<tiles_under_threat_upper_case.at(4)<<" | "<<tiles_under_threat_upper_case.at(5)<<" | "<<tiles_under_threat_upper_case.at(6)<<" | "<<tiles_under_threat_upper_case.at(7)<<" | 1\n";
    std::cout<<" =============================== \n";
    std::cout<<"  A   B   C   D   E   F   G   H\n";
}

void chess::print_game(std::string const& board) const { //useful for debugging
    std::cout<<"Here";
    std::cout<<" =============================== \n";
    std::cout<<"| "<<board.at(56)<<" | "<<board.at(57)<<" | "<<board.at(58)<<" | "<<board.at(59)<<" | "<<board.at(60)<<" | "<<board.at(61)<<" | "<<board.at(62)<<" | "<<board.at(63)<<" | 8\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(48)<<" | "<<board.at(49)<<" | "<<board.at(50)<<" | "<<board.at(51)<<" | "<<board.at(52)<<" | "<<board.at(53)<<" | "<<board.at(54)<<" | "<<board.at(55)<<" | 7\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(40)<<" | "<<board.at(41)<<" | "<<board.at(42)<<" | "<<board.at(43)<<" | "<<board.at(44)<<" | "<<board.at(45)<<" | "<<board.at(46)<<" | "<<board.at(47)<<" | 6\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(32)<<" | "<<board.at(33)<<" | "<<board.at(34)<<" | "<<board.at(35)<<" | "<<board.at(36)<<" | "<<board.at(37)<<" | "<<board.at(38)<<" | "<<board.at(39)<<" | 5\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(24)<<" | "<<board.at(25)<<" | "<<board.at(26)<<" | "<<board.at(27)<<" | "<<board.at(28)<<" | "<<board.at(29)<<" | "<<board.at(30)<<" | "<<board.at(31)<<" | 4\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(16)<<" | "<<board.at(17)<<" | "<<board.at(18)<<" | "<<board.at(19)<<" | "<<board.at(20)<<" | "<<board.at(21)<<" | "<<board.at(22)<<" | "<<board.at(23)<<" | 3\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(8)<<" | "<<board.at(9)<<" | "<<board.at(10)<<" | "<<board.at(11)<<" | "<<board.at(12)<<" | "<<board.at(13)<<" | "<<board.at(14)<<" | "<<board.at(15)<<" | 2\n";
    std::cout<<"|-------------------------------|\n";
    std::cout<<"| "<<board.at(0)<<" | "<<board.at(1)<<" | "<<board.at(2)<<" | "<<board.at(3)<<" | "<<board.at(4)<<" | "<<board.at(5)<<" | "<<board.at(6)<<" | "<<board.at(7)<<" | 1\n";
    std::cout<<" =============================== \n";
    std::cout<<"  A   B   C   D   E   F   G   H\n";
}