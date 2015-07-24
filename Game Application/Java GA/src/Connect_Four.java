import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.Random;

public class Connect_Four extends Game_two_player {
	private String grid;
	
	public Connect_Four() {grid="";for(int i=0;i<42;i++) {grid+=" ";}}
	
	public void ai_turn() {
	    int column=0;
	    //random ai
	    int number_of_possible_moves=0;
	    for (int i=0;i<7;i++) {
	        if (grid.charAt(7*5+i) == ' ')
	            number_of_possible_moves++;
	    }
	    
	    Random random = new Random();
	    column = random.nextInt(number_of_possible_moves);
	    
	    for (int i=0;i<column;i++) {
	        if (grid.charAt(7*5+i) != ' ')
	            column++;
	    }
	    
	    change_tile_player_2(column);
	    print_game();
	}

	public void player_1_turn(Scanner user_input) {
	    int column=0;
	    boolean valid_integer_input=false;
	    while (!valid_integer_input) {
	        System.out.print("Player1, please enter the column you would like to go on: ");
	        try {
		        column = user_input.nextInt();
		        if (column > 7 || column < 1)
		            System.out.println("Input error! Integer not in range 1-7.");
		        else if (grid.charAt(column-1+7*5) != ' ')
		            System.out.println("Input error! Column is completely filled, choose another column.");
		        else if (grid.charAt(column-1+7*5) == ' ' && column >= 1 && column <= 7) {
		            valid_integer_input = true;
		            change_tile_player_1(column);
		        }
		    }
	        catch (InputMismatchException In_Ex) {
	        	System.out.println("Input error! Integer was not inputted.");
	        	user_input.nextLine();
	        }
	    }
	    print_game();
	}

	public void player_2_turn(Scanner user_input) {
		int column=0;
	    boolean valid_integer_input=false;
	    while (!valid_integer_input) {
	        System.out.print("Player2, please enter the column you would like to go on: ");
	        try {
		        column = user_input.nextInt();
		        if (column > 7 || column < 1)
		            System.out.println("Input error! Integer not in range 1-7.");
		        else if (grid.charAt(column-1+7*5) != ' ')
		            System.out.println("Input error! Column is completely filled, choose another column.");
		        else if (grid.charAt(column-1+7*5) == ' ' && column >= 1 && column <= 7) {
		            valid_integer_input = true;
		            change_tile_player_2(column);
		        }
		    }
	        catch (InputMismatchException In_Ex) {
	        	System.out.println("Input error! Integer was not inputted.");
	        	user_input.nextLine();
	        }
	    }
	    print_game();
	}

	public boolean check_for_turn_remaining_as_true() {
	    for (int i=0;i<42;i++) {
	        if (grid.charAt(i)!='O'&&grid.charAt(i)!='X') {
	            return true;
	        }
	    }
	    return false;
	}

	public boolean check_for_draw_as_true()  {System.out.println("Do not need to use this function - instead check for win and then if there are any turns remaining if no winners. Returning with false...");return false;}

	public boolean check_for_win_as_true() {
	    for (int i=0;i<6;i++) {
	        for (int j=0;j<4;j++) {
	            if (grid.charAt(i*7+j)==grid.charAt(i*7+j+1) && grid.charAt(i*7+j+1)==grid.charAt(i*7+j+2) && grid.charAt(i*7+j+2)==grid.charAt(i*7+j+3)&&(grid.charAt(i*7+j)=='O'||grid.charAt(i*7+j)=='X'))
	                return true;
	            if (i<3) {
	                if (grid.charAt(i*7+j)==grid.charAt((i+1)*7+j+1) && grid.charAt((i+1)*7+j+1)==grid.charAt((i+2)*7+j+2) && grid.charAt((i+2)*7+j+2)==grid.charAt((i+3)*7+j+3)&&(grid.charAt(i*7+j)=='O'||grid.charAt(i*7+j)=='X'))
	                    return true;
	                else if (grid.charAt((i+3)*7+j)==grid.charAt((i+2)*7+j+1) && grid.charAt((i+2)*7+j+1)==grid.charAt((i+1)*7+j+2) && grid.charAt((i+1)*7+j+2)==grid.charAt((i)*7+j+3)&&(grid.charAt((i+3)*7+j)=='O'||grid.charAt((i+3)*7+j)=='X'))
	                    return true;
	            }
	        }
	    }
	    for (int i=0;i<7;i++) {
	        for (int j=0;j<3;j++) {
	            if (grid.charAt(i+j*7)==grid.charAt(i+(j+1)*7) && grid.charAt(i+(j+1)*7)==grid.charAt(i+(j+2)*7) && grid.charAt(i+(j+2)*7)==grid.charAt(i+(j+3)*7)&&(grid.charAt(i+j*7)=='O'||grid.charAt(i+j*7)=='X'))
	                return true;
	        }
	    }
	    return false;
	}

	public void change_tile_player_1(int column) {
	    if (column >= 1 && column <= 7) {
	        if (grid.charAt(column-1)!='O'&&grid.charAt(column-1)!='X')
	        	grid = grid.substring(0, column-1) + 'X' + grid.substring(column);
	        else if (grid.charAt(column-1+7)!='O'&&grid.charAt(column-1+7)!='X')
	        	grid = grid.substring(0, column-1+7) + 'X' + grid.substring(column+7);
	        else if (grid.charAt(column-1+7*2)!='O'&&grid.charAt(column-1+7*2)!='X')
	        	grid = grid.substring(0, column-1+7*2) + 'X' + grid.substring(column+7*2);
	        else if (grid.charAt(column-1+7*3)!='O'&&grid.charAt(column-1+7*3)!='X')
	        	grid = grid.substring(0, column-1+7*3) + 'X' + grid.substring(column+7*3);
	        else if (grid.charAt(column-1+7*4)!='O'&&grid.charAt(column-1+7*4)!='X')
	        	grid = grid.substring(0, column-1+7*4) + 'X' + grid.substring(column+7*4);
	        else if (grid.charAt(column-1+7*5)!='O'&&grid.charAt(column-1+7*5)!='X')
	        	grid = grid.substring(0, column-1+7*5) + 'X' + grid.substring(column+7*5);
	    }
	}

	public void change_tile_player_2(int column) {
	    if (column >= 1 && column <= 7) {
	    	if (grid.charAt(column-1)!='O'&&grid.charAt(column-1)!='X')
	    		grid = grid.substring(0, column-1) + 'O' + grid.substring(column);
	        else if (grid.charAt(column-1+7)!='O'&&grid.charAt(column-1+7)!='X')
	        	grid = grid.substring(0, column-1+7) + 'O' + grid.substring(column+7);
	        else if (grid.charAt(column-1+7*2)!='O'&&grid.charAt(column-1+7*2)!='X')
	        	grid = grid.substring(0, column-1+7*2) + 'O' + grid.substring(column+7*2);
	        else if (grid.charAt(column-1+7*3)!='O'&&grid.charAt(column-1+7*3)!='X')
	        	grid = grid.substring(0, column-1+7*3) + 'O' + grid.substring(column+7*3);
	        else if (grid.charAt(column-1+7*4)!='O'&&grid.charAt(column-1+7*4)!='X')
	        	grid = grid.substring(0, column-1+7*4) + 'O' + grid.substring(column+7*4);
	        else if (grid.charAt(column-1+7*5)!='O'&&grid.charAt(column-1+7*5)!='X')
	        	grid = grid.substring(0, column-1+7*5) + 'O' + grid.substring(column+7*5);
	    }
	}

	public void print_game() {
	    System.out.println(" =========================== ");
	    System.out.println("| "+grid.charAt(35)+" | "+grid.charAt(36)+" | "+grid.charAt(37)+" | "+grid.charAt(38)+" | "+grid.charAt(39)+" | "+grid.charAt(40)+" | "+grid.charAt(41)+" |");
	    System.out.println("|---------------------------|");
	    System.out.println("| "+grid.charAt(28)+" | "+grid.charAt(29)+" | "+grid.charAt(30)+" | "+grid.charAt(31)+" | "+grid.charAt(32)+" | "+grid.charAt(33)+" | "+grid.charAt(34)+" |");
	    System.out.println("|---------------------------|");
	    System.out.println("| "+grid.charAt(21)+" | "+grid.charAt(22)+" | "+grid.charAt(23)+" | "+grid.charAt(24)+" | "+grid.charAt(25)+" | "+grid.charAt(26)+" | "+grid.charAt(27)+" |");
	    System.out.println("|---------------------------|");
	    System.out.println("| "+grid.charAt(14)+" | "+grid.charAt(15)+" | "+grid.charAt(16)+" | "+grid.charAt(17)+" | "+grid.charAt(18)+" | "+grid.charAt(19)+" | "+grid.charAt(20)+" |");
	    System.out.println("|---------------------------|");
	    System.out.println("| "+grid.charAt(7)+" | "+grid.charAt(8)+" | "+grid.charAt(9)+" | "+grid.charAt(10)+" | "+grid.charAt(11)+" | "+grid.charAt(12)+" | "+grid.charAt(13)+" |");
	    System.out.println("|---------------------------|");
	    System.out.println("| "+grid.charAt(0)+" | "+grid.charAt(1)+" | "+grid.charAt(2)+" | "+grid.charAt(3)+" | "+grid.charAt(4)+" | "+grid.charAt(5)+" | "+grid.charAt(6)+" |");
	    System.out.println(" =========================== ");
	    System.out.println("  1   2   3   4   5   6   7");
	}
}
