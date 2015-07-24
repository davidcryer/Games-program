//
//  game.h
//  Noughts and Crosses
//
//  Created by David Cryer on 18/06/2015.
//  Copyright (c) 2015 David Cryer. All rights reserved.
//

#ifndef __Noughts_and_Crosses__game__
#define __Noughts_and_Crosses__game__

class game {
public:
    virtual ~game() {}
    virtual bool check_for_turn_remaining_as_true() const = 0;
    virtual bool check_for_draw_as_true() const = 0;
    virtual bool check_for_win_as_true() const = 0;
    virtual void player1_turn() = 0;
    virtual void player2_turn() = 0;
    virtual void ai_turn() = 0;
    virtual void print_game() const = 0;
};

#endif /* defined(__Noughts_and_Crosses__game__) */
