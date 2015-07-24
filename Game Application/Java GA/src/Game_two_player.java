import java.util.Scanner;

public abstract class Game_two_player {
    abstract boolean check_for_turn_remaining_as_true();
    abstract boolean check_for_draw_as_true();
    abstract boolean check_for_win_as_true();
    abstract void player_1_turn(Scanner user_input);
    abstract void player_2_turn(Scanner user_input);
    abstract void ai_turn();
    abstract void print_game();
}
