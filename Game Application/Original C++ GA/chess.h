//
//  chess.h
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#ifndef __Noughts_and_Crosses__chess__
#define __Noughts_and_Crosses__chess__

#include "game.h"
#include <string>

class chess: public game {
protected:
    std::string tiles,taken_pieces,tiles_under_threat_lower_case,tiles_under_threat_upper_case,move_history;
    bool can_castle_r_k,can_castle_k_r,can_castle_R_K,can_castle_K_R;
public:
    chess();
    ~chess();
    
    void move_piece_at_1st_arg_to_2nd_arg(int first_position,int second_position);
    void return_theoretical_move_piece_at_1st_arg_to_2nd_arg(int first_position,int second_position,std::string &theoretical_tiles) const;
    void calculate_tiles_under_threat();
    std::string return_theoretical_tiles_under_threat_lower_case(std::string const& theoretical_tiles) const;
    std::string return_theoretical_tiles_under_threat_upper_case(std::string const& theoretical_tiles) const;
    
    bool check_for_legal_movement(int first_position,int second_position) const;
    bool check_for_legal_movement_for_theoretical_tiles(int first_position,int second_position,std::string const& theoretical_tiles) const;
    int get_board_element_from_algebraic_position(std::string const& move) const;
    
    bool check_for_check_on_K_as_true() const;
    bool check_for_check_on_k_as_true() const;
    bool check_for_check_on_K_as_true(std::string const& theoretical_tiles) const;
    bool check_for_check_on_k_as_true(std::string const& theoretical_tiles) const;
    bool check_for_turn_remaining_as_true() const;
    bool check_for_draw_as_true() const;
    bool check_for_win_as_true() const;
    
    void player1_turn();
    void player2_turn();
    void ai_turn();
    void put_taken_piece_to_side(char piece);
    void add_move_to_move_history(std::string const& move);
    void print_game() const;
    void print_game(std::string const& board) const;
    void print_tiles_under_threat_upper_case() const;
};

#endif /* defined(__Noughts_and_Crosses__chess__) */
