//
//  naughts_and_crosses.h
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#ifndef __Noughts_and_Crosses__naughts_and_crosses__
#define __Noughts_and_Crosses__naughts_and_crosses__

#include "game.h"
#include <string>

class naughts_and_crosses: public game {
protected:
    std::string tiles;
public:
    naughts_and_crosses();
    ~naughts_and_crosses();
    
    bool check_for_turn_remaining_as_true() const;
    bool check_for_draw_as_true() const;
    bool check_for_win_as_true() const;
    void player1_turn();
    void player2_turn();
    void ai_turn();
    void change_tile_player1(int tile);
    void change_tile_player2(int tile);
    void print_game() const;
    
    
    
    bool ai_opponent_almost_filled_line() const;
    bool ai_self_almost_filled_line() const;
    int ai_return_remaining_tile_of_line_almost_full_by_opponent() const;
    int ai_return_remaining_tile_of_line_almost_full_by_self() const;
    int ai_number_of_turns_gone() const;
};

#endif /* defined(__Noughts_and_Crosses__naughts_and_crosses__) */
