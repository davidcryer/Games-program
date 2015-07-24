import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.Random;

public class Naughts_and_Crosses extends Game_two_player{
	private String grid;
	
	Naughts_and_Crosses() {grid="";for (int i=0;i<9;i++) {grid+=String.valueOf(i+1);}}

	public void player_1_turn(Scanner user_input) {
		int grid_number=0;
	    while (grid_number < 1 || grid_number > 9) {
	        System.out.print("Player1, please enter the tile number you would like to go on (1-9): ");
	        try {
	        	grid_number = user_input.nextInt();
	        	if (grid_number < 1 || grid_number > 9)
		            System.out.println("Input error! Integer not in range 1-9.");
		        else if (grid.charAt(grid_number-1) == 'X' || grid.charAt(grid_number-1) == 'O')
		            System.out.println("Input error! Tile already inhabited.");
		        else if (grid_number >= 1 && grid_number <= 9)
		            change_tile_player_1(grid_number);
	        }
	        catch (InputMismatchException In_Ex) {
	        	System.out.println("Input error! An integer was not inputted.");
	        	user_input.nextLine();
	        }
	    }
	    print_game();
	}
	
	public void player_2_turn(Scanner user_input) {
		int grid_number=0;
	    while (grid_number < 1 || grid_number > 9) {
	        System.out.print("Player2, please enter the tile number you would like to go on (1-9): ");
	        try {
	        	grid_number = user_input.nextInt();
	        	if (grid_number < 1 || grid_number > 9)
		            System.out.println("Input error! Integer not in range 1-9.");
		        else if (grid.charAt(grid_number-1) == 'X' || grid.charAt(grid_number-1) == 'O')
		            System.out.println("Input error! Tile already inhabited.");
		        else if (grid_number >= 1 && grid_number <= 9)
		            change_tile_player_2(grid_number);
	        }
	        catch (InputMismatchException In_Ex) {
	        	System.out.println("Input error! An integer was not inputted.");
	        	user_input.nextLine();
	        }
	    }
	    print_game();
	}
	
	public void ai_turn() {
		int grid_number = 0;
	    
	    if (ai_self_almost_filled_line_as_true()) {
	        grid_number = ai_return_remaining_tile_of_line_almost_filled_by_self();
    		if (grid_number == -1) {
    			System.out.println("Catching -1 return. Exiting with -1...");
    			System.exit(-1);
    		}
	    }
	    else if (ai_opponent_almost_filled_line_as_true()) {
	        grid_number = ai_return_remaining_tile_of_line_almost_filled_by_opponent();
	        if (grid_number == -1) {
    			System.out.println("Catching -1 return. Exiting with -1...");
    			System.exit(-1);
    		}
	    }
	    else if (grid.charAt(4) != 'X' && grid.charAt(4) != 'O')
	        grid_number = 4;
	    else {
	        int number_of_possible_moves = 0;
	        for (int i=0;i<9;i++) {
	            if (grid.charAt(i) != 'O' && grid.charAt(i) != 'X') {
	                /*
	                if (ai_number_of_turns_gone()==3) {
	                    if (tiles.at(0) == 'X' && tiles.at(8) == '0' && tiles.at(4) == '0') {
	                        
	                    }
	                }*/
	                number_of_possible_moves++;
	            }
	        }
	        
	        Random random = new Random();
	        grid_number = random.nextInt(number_of_possible_moves);
	        
	        for (int i=0;i<grid_number+1;i++) {
	            if (grid.charAt(i) == 'X' || grid.charAt(i) == 'O')
	                grid_number++;
	        }
	    }
	    
	    grid_number++;
	    change_tile_player_2(grid_number);
	    print_game();
	}
	
	boolean ai_opponent_almost_filled_line_as_true() {
	    for (int i=0;i<3;i++) {
	        if (grid.charAt(i*3)==grid.charAt(i*3+1) && grid.charAt(i*3) == 'X' && grid.charAt(i*3+2) != 'O')
	            return true;
	        else if (grid.charAt(i*3)==grid.charAt(i*3+2) && grid.charAt(i*3) == 'X' && grid.charAt(i*3+1) != 'O')
	            return true;
	        else if (grid.charAt(i*3+1)==grid.charAt(i*3+2) && grid.charAt(i*3+1) == 'X' && grid.charAt(i*3) != 'O')
	            return true;
	        else if (grid.charAt(i)==grid.charAt(i+3) && grid.charAt(i) == 'X' && grid.charAt(i+6) != 'O')
	            return true;
	        else if (grid.charAt(i)==grid.charAt(i+6) && grid.charAt(i) == 'X' && grid.charAt(i+3) != 'O')
	            return true;
	        else if (grid.charAt(i+3)==grid.charAt(i+6) && grid.charAt(i+3) == 'X' && grid.charAt(i) != 'O')
	            return true;
	    }
	    if (grid.charAt(0)==grid.charAt(4) && grid.charAt(0) == 'X' && grid.charAt(8) != 'O')
	        return true;
	    else if (grid.charAt(0)==grid.charAt(8) && grid.charAt(0) == 'X' && grid.charAt(4) != 'O')
	        return true;
	    else if (grid.charAt(4)==grid.charAt(8) && grid.charAt(4) == 'X' && grid.charAt(0) != 'O')
	        return true;
	    else if (grid.charAt(2)==grid.charAt(4) && grid.charAt(2) == 'X' && grid.charAt(6) != 'O')
	        return true;
	    else if (grid.charAt(2)==grid.charAt(6) && grid.charAt(2) == 'X' && grid.charAt(4) != 'O')
	        return true;
	    else if (grid.charAt(4)==grid.charAt(6) && grid.charAt(4) == 'X' && grid.charAt(2) != 'O')
	        return true;
	    else
	        return false;
	}

	boolean ai_self_almost_filled_line_as_true() {
	    for (int i=0;i<3;i++) {
	        if (grid.charAt(i*3)==grid.charAt(i*3+1) && grid.charAt(i*3) == 'O' && grid.charAt(i*3+2) != 'X')
	            return true;
	        else if (grid.charAt(i*3)==grid.charAt(i*3+2) && grid.charAt(i*3) == 'O' && grid.charAt(i*3+1) != 'X')
	            return true;
	        else if (grid.charAt(i*3+1)==grid.charAt(i*3+2) && grid.charAt(i*3+1) == 'O' && grid.charAt(i*3) != 'X')
	            return true;
	        else if (grid.charAt(i)==grid.charAt(i+3) && grid.charAt(i) == 'O' && grid.charAt(i+6) != 'X')
	            return true;
	        else if (grid.charAt(i)==grid.charAt(i+6) && grid.charAt(i) == 'O' && grid.charAt(i+3) != 'X')
	            return true;
	        else if (grid.charAt(i+3)==grid.charAt(i+6) && grid.charAt(i+3) == 'O' && grid.charAt(i) != 'X')
	            return true;
	    }
	    if (grid.charAt(0)==grid.charAt(4) && grid.charAt(0) == 'O' && grid.charAt(8) != 'X')
	        return true;
	    else if (grid.charAt(0)==grid.charAt(8) && grid.charAt(0) == 'O' && grid.charAt(4) != 'X')
	        return true;
	    else if (grid.charAt(4)==grid.charAt(8) && grid.charAt(4) == 'O' && grid.charAt(0) != 'X')
	        return true;
	    else if (grid.charAt(2)==grid.charAt(4) && grid.charAt(2) == 'O' && grid.charAt(6) != 'X')
	        return true;
	    else if (grid.charAt(2)==grid.charAt(6) && grid.charAt(2) == 'O' && grid.charAt(4) != 'X')
	        return true;
	    else if (grid.charAt(4)==grid.charAt(6) && grid.charAt(4) == 'O' && grid.charAt(2) != 'X')
	        return true;
	    else
	        return false;
	}

	int ai_return_remaining_tile_of_line_almost_filled_by_opponent() {
	    for (int i=0;i<3;i++) {
	        if (grid.charAt(i*3)==grid.charAt(i*3+1) && grid.charAt(i*3) == 'X' && grid.charAt(i*3+2) != 'O')
	            return i*3+2;
	        else if (grid.charAt(i*3)==grid.charAt(i*3+2) && grid.charAt(i*3) == 'X' && grid.charAt(i*3+1) != 'O')
	            return i*3+1;
	        else if (grid.charAt(i*3+1)==grid.charAt(i*3+2) && grid.charAt(i*3+1) == 'X' && grid.charAt(i*3) != 'O')
	            return i*3;
	        else if (grid.charAt(i)==grid.charAt(i+3) && grid.charAt(i) == 'X' && grid.charAt(i+6) != 'O')
	            return i+6;
	        else if (grid.charAt(i)==grid.charAt(i+6) && grid.charAt(i) == 'X' && grid.charAt(i+3) != 'O')
	            return i+3;
	        else if (grid.charAt(i+3)==grid.charAt(i+6) && grid.charAt(i+3) == 'X' && grid.charAt(i) != 'O')
	            return i;
	    }
	    if (grid.charAt(0)==grid.charAt(4) && grid.charAt(0) == 'X' && grid.charAt(8) != 'O')
	        return 8;
	    else if (grid.charAt(0)==grid.charAt(8) && grid.charAt(0) == 'X' && grid.charAt(4) != 'O')
	        return 4;
	    else if (grid.charAt(4)==grid.charAt(8) && grid.charAt(4) == 'X' && grid.charAt(0) != 'O')
	        return 0;
	    else if (grid.charAt(2)==grid.charAt(4) && grid.charAt(2) == 'X' && grid.charAt(6) != 'O')
	        return 6;
	    else if (grid.charAt(2)==grid.charAt(6) && grid.charAt(2) == 'X' && grid.charAt(4) != 'O')
	        return 4;
	    else if (grid.charAt(4)==grid.charAt(6) && grid.charAt(4) == 'X' && grid.charAt(2) != 'O')
	        return 2;
	    System.out.println("Error! ai_return_remaining_tile_of_line_almost_filled_by_opponent() has been used but not returned an integer. Returning -1 -> catch exception!");
	   	return -1;
	}

	int ai_return_remaining_tile_of_line_almost_filled_by_self() {
	    for (int i=0;i<3;i++) {
	        if (grid.charAt(i*3)==grid.charAt(i*3+1) && grid.charAt(i*3) == 'O' && grid.charAt(i*3+2) != 'X')
	            return i*3+2;
	        else if (grid.charAt(i*3)==grid.charAt(i*3+2) && grid.charAt(i*3) == 'O' && grid.charAt(i*3+1) != 'X')
	            return i*3+1;
	        else if (grid.charAt(i*3+1)==grid.charAt(i*3+2) && grid.charAt(i*3+1) == 'O' && grid.charAt(i*3) != 'X')
	            return i*3;
	        else if (grid.charAt(i)==grid.charAt(i+3) && grid.charAt(i) == 'O' && grid.charAt(i+6) != 'X')
	            return i+6;
	        else if (grid.charAt(i)==grid.charAt(i+6) && grid.charAt(i) == 'O' && grid.charAt(i+3) != 'X')
	            return i+3;
	        else if (grid.charAt(i+3)==grid.charAt(i+6) && grid.charAt(i+3) == 'O' && grid.charAt(i) != 'X')
	            return i;
	    }
	    if (grid.charAt(0)==grid.charAt(4) && grid.charAt(0) == 'O' && grid.charAt(8) != 'X')
	        return 8;
	    else if (grid.charAt(0)==grid.charAt(8) && grid.charAt(0) == 'O' && grid.charAt(4) != 'X')
	        return 4;
	    else if (grid.charAt(4)==grid.charAt(8) && grid.charAt(4) == 'O' && grid.charAt(0) != 'X')
	        return 0;
	    else if (grid.charAt(2)==grid.charAt(4) && grid.charAt(2) == 'O' && grid.charAt(6) != 'X')
	        return 6;
	    else if (grid.charAt(2)==grid.charAt(6) && grid.charAt(2) == 'O' && grid.charAt(4) != 'X')
	        return 4;
	    else if (grid.charAt(4)==grid.charAt(6) && grid.charAt(4) == 'O' && grid.charAt(2) != 'X')
	        return 2;
	    System.out.println("Error! ai_return_remaining_tile_of_line_almost_filled_by_self() has been used but not returned an integer. Returning -1 -> catch exception!");
	    return -1;
	}
	
	public void change_tile_player_1(int grid_number) {
		grid = grid.substring(0, grid_number-1) + "X" + grid.substring(grid_number);
	}
	
	public void change_tile_player_2(int grid_number) {
		grid = grid.substring(0, grid_number-1) + "O" + grid.substring(grid_number);
	}
	
	public void print_game() {
		System.out.println(" =========== ");
		System.out.println("| "+grid.charAt(0)+" | "+grid.charAt(1)+" | "+grid.charAt(2)+" |");
		System.out.println("|-----------|");
		System.out.println("| "+grid.charAt(3)+" | "+grid.charAt(4)+" | "+grid.charAt(5)+" |");
		System.out.println("|-----------|");
		System.out.println("| "+grid.charAt(6)+" | "+grid.charAt(7)+" | "+grid.charAt(8)+" |");
		System.out.println(" =========== ");
	}
	
	public boolean check_for_win_as_true() {
		if (grid.charAt(0)==grid.charAt(3) && grid.charAt(3)==grid.charAt(6))
	        return true;
	    else if (grid.charAt(1)==grid.charAt(4) && grid.charAt(4)==grid.charAt(7))
	        return true;
	    else if (grid.charAt(2)==grid.charAt(5) && grid.charAt(5)==grid.charAt(8))
	        return true;
	    else if (grid.charAt(0)==grid.charAt(1) && grid.charAt(1)==grid.charAt(2))
	        return true;
	    else if (grid.charAt(3)==grid.charAt(4) && grid.charAt(4)==grid.charAt(5))
	        return true;
	    else if (grid.charAt(6)==grid.charAt(7) && grid.charAt(7)==grid.charAt(8))
	        return true;
	    else if (grid.charAt(0)==grid.charAt(4) && grid.charAt(4)==grid.charAt(8))
	        return true;
	    else if (grid.charAt(2)==grid.charAt(4) && grid.charAt(4)==grid.charAt(6))
	        return true;
	    else
	        return false;
	}
	
	public boolean check_for_draw_as_true() {
		if (!check_for_turn_remaining_as_true() && !check_for_win_as_true())
			return true;
		else 
			return false;
	}
	
	public boolean check_for_turn_remaining_as_true() {
		for (int i=0;i<9;i++) {
			if (grid.charAt(i) != 'O' && grid.charAt(i) != 'X')
				return true;
		}
		return false;
	}
}
