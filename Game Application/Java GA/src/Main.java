import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		int player_1s_wins = 0, player_2s_wins = 0;
		Scanner user_input = new Scanner(System.in);
		boolean playing_games = true;
		while(playing_games) {
			Game_two_player game=null;
			String input_game_option = "";
			while (!input_game_option.equals("N") && !input_game_option.equals("F") && !input_game_option.equals("C")) {
				
				System.out.print("Would you like to play (N)aughts and Crosses, Connect (F)our, or (C)hess? ");
				input_game_option = user_input.next();
				if (input_game_option.equals("N")) {
					System.out.println("Starting Naughts and Crosses.");
					game = new Naughts_and_Crosses();
				}
				else if (input_game_option.equals("F")) {
					System.out.println("Starting Connect Four.");
					game = new Connect_Four();
				}
				else if (input_game_option.equals("C")) {
					//create chess
					System.out.println("Starting Naughts and Crosses anyway.");
					game = new Naughts_and_Crosses();
				}
				else {
					System.out.println("Input error! Input must be 'N', 'F', or 'C' for the corresponding game.");
				}
			}
			
			game.print_game();
			boolean game_won = false, game_drawn = false;
			while(!game_won && !game_drawn) {
				game.player_1_turn(user_input);
	            game_won=game.check_for_win_as_true();
	            if (game_won) {
	                System.out.println("Player1 has won the game!");
	                player_1s_wins++;
	            }
	            else if (!game.check_for_turn_remaining_as_true()) {
	                game_drawn = true;
	                System.out.println("Game has been drawn.");
	            }
	            else {
	                game.player_2_turn(user_input);
	                game_won=game.check_for_win_as_true();
	                if (game_won) {
	                    System.out.println("Player2 has won the game!");
	                    player_2s_wins++;
	                }
	                else if (!game.check_for_turn_remaining_as_true()) {
	                    game_drawn = true;
	                    System.out.println("Game has been drawn.");
	                }
	            }
			}
			
			String input_play_again = "";
			while (!input_play_again.equals("Y") && !input_play_again.equals("N")) {
				System.out.print("Would you like to play another game? (Y/N) ");
				input_play_again = user_input.next();
				if (input_play_again.equals("N")) {
					playing_games = false;
				}
				else if (!input_play_again.equals("N") && !input_play_again.equals("Y")) {
					System.out.println("Input error! Input must be 'Y' or 'N'.");
				}
			}
		}
		
		if (player_1s_wins > player_2s_wins)
	        System.out.println("Player1 wins with "+player_1s_wins+" game(s) to "+player_2s_wins+".");
	    else if (player_1s_wins < player_2s_wins)
	        System.out.println("Player2 wins with "+player_2s_wins+" game(s) to "+player_1s_wins+".");
	    else if (player_1s_wins == player_2s_wins)
	        System.out.println("Draw with "+player_1s_wins+" win(s) apiece.");
		
		System.out.println("Thank you for using this program.");
		user_input.close();
	}

}
