//
//  connect_four.h
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#ifndef __Noughts_and_Crosses__connect_four__
#define __Noughts_and_Crosses__connect_four__

#include "game.h"
#include <string>

class connect_four: public game {
protected:
    std::string tiles;
public:
    connect_four();
    ~connect_four();
    
    bool check_for_turn_remaining_as_true() const;
    bool check_for_draw_as_true() const;
    bool check_for_win_as_true() const;
    void player1_turn();
    void player2_turn();
    void ai_turn();
    void change_tile_player1(int tile);
    void change_tile_player2(int tile);
    void print_game() const;
    
};
#endif /* defined(__Noughts_and_Crosses__connect_four__) */
