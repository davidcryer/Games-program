package com.davidcryer.gameapplication170715;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.content.Intent;

import java.util.Random;


public class NaughtsAndCrossesActivity extends ActionBarActivity {

    private String mGrid;
    private boolean mTurns_player_1_as_true_player_2_as_false;
    private int mNumber_of_wins_player_1, mNumber_of_wins_player_2;

    public final static String EXTRA_MESSAGE = "com.davidcryer.gameapplication170715.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_naughts_and_crosses);
        mNumber_of_wins_player_1 = 0; mNumber_of_wins_player_2 = 0;
        new_naughts_and_crosses();
    }

    private void new_naughts_and_crosses() {
        mGrid = getString(R.string.n_and_c_grid);
        mTurns_player_1_as_true_player_2_as_false = true;

        TextView textview = (TextView)findViewById(R.id.n_and_c_text_player_one_wins_numbers);
        textview.setText(String.valueOf(mNumber_of_wins_player_1));
        textview = (TextView)findViewById(R.id.n_and_c_text_player_two_wins_numbers);
        textview.setText(String.valueOf(mNumber_of_wins_player_2));

        Button button_1 = (Button)findViewById(R.id.n_and_c_button_1);
        button_1.setText(String.valueOf(mGrid.charAt(0)));
        Button button_2 = (Button)findViewById(R.id.n_and_c_button_2);
        button_2.setText(String.valueOf(mGrid.charAt(1)));
        Button button_3 = (Button)findViewById(R.id.n_and_c_button_3);
        button_3.setText(String.valueOf(mGrid.charAt(2)));
        Button button_4 = (Button)findViewById(R.id.n_and_c_button_4);
        button_4.setText(String.valueOf(mGrid.charAt(3)));
        Button button_5 = (Button)findViewById(R.id.n_and_c_button_5);
        button_5.setText(String.valueOf(mGrid.charAt(4)));
        Button button_6 = (Button)findViewById(R.id.n_and_c_button_6);
        button_6.setText(String.valueOf(mGrid.charAt(5)));
        Button button_7 = (Button)findViewById(R.id.n_and_c_button_7);
        button_7.setText(String.valueOf(mGrid.charAt(6)));
        Button button_8 = (Button)findViewById(R.id.n_and_c_button_8);
        button_8.setText(String.valueOf(mGrid.charAt(7)));
        Button button_9 = (Button)findViewById(R.id.n_and_c_button_9);
        button_9.setText(String.valueOf(mGrid.charAt(8)));
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public void n_and_c_button_1_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(1);
    }
    public void n_and_c_button_2_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(2);
    }
    public void n_and_c_button_3_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(3);
    }
    public void n_and_c_button_4_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(4);
    }
    public void n_and_c_button_5_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(5);
    }
    public void n_and_c_button_6_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(6);
    }
    public void n_and_c_button_7_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(7);
    }
    public void n_and_c_button_8_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(8);
    }
    public void n_and_c_button_9_click(View view) {
        change_and_disable_button_and_check_game_state_and_swap_players(9);
    }

    private void change_and_disable_button_and_check_game_state_and_swap_players(int grid_number) {
        if (mTurns_player_1_as_true_player_2_as_false)
            mGrid = mGrid.substring(0, grid_number - 1) + "X" + mGrid.substring(grid_number);
        else
            mGrid = mGrid.substring(0,grid_number-1) + "O" + mGrid.substring(grid_number);

        Button button = null;
        if (grid_number==1)
            button = (Button)findViewById(R.id.n_and_c_button_1);
        else if (grid_number==2)
            button = (Button)findViewById(R.id.n_and_c_button_2);
        else if (grid_number==3)
            button = (Button)findViewById(R.id.n_and_c_button_3);
        else if (grid_number==4)
            button = (Button)findViewById(R.id.n_and_c_button_4);
        else if (grid_number==5)
            button = (Button)findViewById(R.id.n_and_c_button_5);
        else if (grid_number==6)
            button = (Button)findViewById(R.id.n_and_c_button_6);
        else if (grid_number==7)
            button = (Button)findViewById(R.id.n_and_c_button_7);
        else if (grid_number==8)
            button = (Button)findViewById(R.id.n_and_c_button_8);
        else if (grid_number==9)
            button = (Button)findViewById(R.id.n_and_c_button_9);
        else {
            //report error and close. (grid_number should be in range 1-9
        }
        button.setText(String.valueOf(mGrid.charAt(grid_number-1)));
        button.setEnabled(false);

        if (mTurns_player_1_as_true_player_2_as_false)
            mTurns_player_1_as_true_player_2_as_false = false;
        else
            mTurns_player_1_as_true_player_2_as_false = true;

        if (!check_for_turn_remaining_as_true() || check_for_win_as_true()) {
            Intent game_finished = new Intent(this, NaughtsAndCrossesGameFinishedActivity.class);
            String game_finished_message = null;
            if (check_for_win_as_true()) {
                if (!mTurns_player_1_as_true_player_2_as_false) {
                    //TextView textview = (TextView)findViewById(R.id.Text_player_one_wins_numbers);
                    //textview.setText("Winner!");

                    mNumber_of_wins_player_1++;
                    //textview = (TextView)findViewById(R.id.Text_player_one_wins_numbers);
                    //textview.setText(mNumber_of_wins_player_1);
                    game_finished_message = "Player 1 has won the game!";
                }
                else {
                    //TextView textview = (TextView)findViewById(R.id.naughts_and_crosses_end_of_game_text_view);
                    //textview.setText(R.string.player_two_no_of_wins_text);

                    mNumber_of_wins_player_2++;
                    //textview = (TextView)findViewById(R.id.Text_player_two_wins_numbers);
                    //textview.setText(mNumber_of_wins_player_2);
                    game_finished_message = "Player 2 has won the game!";
                }
            }
            else {
                //TextView textview = (TextView)findViewById(R.id.naughts_and_crosses_end_of_game_text_view);
                //textview.setText(R.string.draw_text);
                game_finished_message = "Game drawn.";
            }
            //prompt_for_new_game_or_quit();
            game_finished.putExtra(EXTRA_MESSAGE, game_finished_message);
            startActivity(game_finished);
            click_for_new_game();
        }
    }

    private boolean check_for_win_as_true() {
        if (mGrid.charAt(0)==mGrid.charAt(3) && mGrid.charAt(3)==mGrid.charAt(6))
            return true;
        else if (mGrid.charAt(1)==mGrid.charAt(4) && mGrid.charAt(4)==mGrid.charAt(7))
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(5) && mGrid.charAt(5)==mGrid.charAt(8))
            return true;
        else if (mGrid.charAt(0)==mGrid.charAt(1) && mGrid.charAt(1)==mGrid.charAt(2))
            return true;
        else if (mGrid.charAt(3)==mGrid.charAt(4) && mGrid.charAt(4)==mGrid.charAt(5))
            return true;
        else if (mGrid.charAt(6)==mGrid.charAt(7) && mGrid.charAt(7)==mGrid.charAt(8))
            return true;
        else if (mGrid.charAt(0)==mGrid.charAt(4) && mGrid.charAt(4)==mGrid.charAt(8))
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(4) && mGrid.charAt(4)==mGrid.charAt(6))
            return true;
        else
            return false;
    }

    private boolean check_for_draw_as_true() {
        if (!check_for_turn_remaining_as_true() && !check_for_win_as_true())
            return true;
        else
            return false;
    }

    private boolean check_for_turn_remaining_as_true() {
        for (int i=0;i<9;i++) {
            if (mGrid.charAt(i) != 'O' && mGrid.charAt(i) != 'X')
                return true;
        }
        return false;
    }

    private void prompt_for_new_game_or_quit() {
        disable_grid_buttons();

        //Prompt question "play again?" with Buttons for yes and no

    }

    private void click_for_new_game() {
        //Hide "Play again? question and yes/no buttons


        enable_grid_buttons();
        new_naughts_and_crosses();
    }

    private void disable_grid_buttons() {
        Button button = (Button)findViewById(R.id.n_and_c_button_1);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_2);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_3);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_4);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_5);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_6);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_7);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_8);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.n_and_c_button_9);
        if (button.isEnabled())
            button.setEnabled(false);
    }

    private void enable_grid_buttons() {
        Button button = (Button)findViewById(R.id.n_and_c_button_1);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_2);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_3);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_4);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_5);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_6);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_7);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_8);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.n_and_c_button_9);
        if (!button.isEnabled())
            button.setEnabled(true);
    }

    //************ AI ***************

    private void ai_turn() {
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
        else if (mGrid.charAt(4) != 'X' && mGrid.charAt(4) != 'O')
            grid_number = 4;
        else {
            int number_of_possible_moves = 0;
            for (int i=0;i<9;i++) {
                if (mGrid.charAt(i) != 'O' && mGrid.charAt(i) != 'X') {
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
                if (mGrid.charAt(i) == 'X' || mGrid.charAt(i) == 'O')
                    grid_number++;
            }
        }

        grid_number++;
        change_and_disable_button_and_check_game_state_and_swap_players(grid_number);
    }

    private boolean ai_opponent_almost_filled_line_as_true() {
        for (int i=0;i<3;i++) {
            if (mGrid.charAt(i*3)==mGrid.charAt(i*3+1) && mGrid.charAt(i*3) == 'X' && mGrid.charAt(i*3+2) != 'O')
                return true;
            else if (mGrid.charAt(i*3)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3) == 'X' && mGrid.charAt(i*3+1) != 'O')
                return true;
            else if (mGrid.charAt(i*3+1)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3+1) == 'X' && mGrid.charAt(i*3) != 'O')
                return true;
            else if (mGrid.charAt(i)==mGrid.charAt(i+3) && mGrid.charAt(i) == 'X' && mGrid.charAt(i+6) != 'O')
                return true;
            else if (mGrid.charAt(i)==mGrid.charAt(i+6) && mGrid.charAt(i) == 'X' && mGrid.charAt(i+3) != 'O')
                return true;
            else if (mGrid.charAt(i+3)==mGrid.charAt(i+6) && mGrid.charAt(i+3) == 'X' && mGrid.charAt(i) != 'O')
                return true;
        }
        if (mGrid.charAt(0)==mGrid.charAt(4) && mGrid.charAt(0) == 'X' && mGrid.charAt(8) != 'O')
            return true;
        else if (mGrid.charAt(0)==mGrid.charAt(8) && mGrid.charAt(0) == 'X' && mGrid.charAt(4) != 'O')
            return true;
        else if (mGrid.charAt(4)==mGrid.charAt(8) && mGrid.charAt(4) == 'X' && mGrid.charAt(0) != 'O')
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(4) && mGrid.charAt(2) == 'X' && mGrid.charAt(6) != 'O')
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(6) && mGrid.charAt(2) == 'X' && mGrid.charAt(4) != 'O')
            return true;
        else if (mGrid.charAt(4)==mGrid.charAt(6) && mGrid.charAt(4) == 'X' && mGrid.charAt(2) != 'O')
            return true;
        else
            return false;
    }

    private boolean ai_self_almost_filled_line_as_true() {
        for (int i=0;i<3;i++) {
            if (mGrid.charAt(i*3)==mGrid.charAt(i*3+1) && mGrid.charAt(i*3) == 'O' && mGrid.charAt(i*3+2) != 'X')
                return true;
            else if (mGrid.charAt(i*3)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3) == 'O' && mGrid.charAt(i*3+1) != 'X')
                return true;
            else if (mGrid.charAt(i*3+1)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3+1) == 'O' && mGrid.charAt(i*3) != 'X')
                return true;
            else if (mGrid.charAt(i)==mGrid.charAt(i+3) && mGrid.charAt(i) == 'O' && mGrid.charAt(i+6) != 'X')
                return true;
            else if (mGrid.charAt(i)==mGrid.charAt(i+6) && mGrid.charAt(i) == 'O' && mGrid.charAt(i+3) != 'X')
                return true;
            else if (mGrid.charAt(i+3)==mGrid.charAt(i+6) && mGrid.charAt(i+3) == 'O' && mGrid.charAt(i) != 'X')
                return true;
        }
        if (mGrid.charAt(0)==mGrid.charAt(4) && mGrid.charAt(0) == 'O' && mGrid.charAt(8) != 'X')
            return true;
        else if (mGrid.charAt(0)==mGrid.charAt(8) && mGrid.charAt(0) == 'O' && mGrid.charAt(4) != 'X')
            return true;
        else if (mGrid.charAt(4)==mGrid.charAt(8) && mGrid.charAt(4) == 'O' && mGrid.charAt(0) != 'X')
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(4) && mGrid.charAt(2) == 'O' && mGrid.charAt(6) != 'X')
            return true;
        else if (mGrid.charAt(2)==mGrid.charAt(6) && mGrid.charAt(2) == 'O' && mGrid.charAt(4) != 'X')
            return true;
        else if (mGrid.charAt(4)==mGrid.charAt(6) && mGrid.charAt(4) == 'O' && mGrid.charAt(2) != 'X')
            return true;
        else
            return false;
    }

    private int ai_return_remaining_tile_of_line_almost_filled_by_opponent() {
        for (int i=0;i<3;i++) {
            if (mGrid.charAt(i*3)==mGrid.charAt(i*3+1) && mGrid.charAt(i*3) == 'X' && mGrid.charAt(i*3+2) != 'O')
                return i*3+2;
            else if (mGrid.charAt(i*3)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3) == 'X' && mGrid.charAt(i*3+1) != 'O')
                return i*3+1;
            else if (mGrid.charAt(i*3+1)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3+1) == 'X' && mGrid.charAt(i*3) != 'O')
                return i*3;
            else if (mGrid.charAt(i)==mGrid.charAt(i+3) && mGrid.charAt(i) == 'X' && mGrid.charAt(i+6) != 'O')
                return i+6;
            else if (mGrid.charAt(i)==mGrid.charAt(i+6) && mGrid.charAt(i) == 'X' && mGrid.charAt(i+3) != 'O')
                return i+3;
            else if (mGrid.charAt(i+3)==mGrid.charAt(i+6) && mGrid.charAt(i+3) == 'X' && mGrid.charAt(i) != 'O')
                return i;
        }
        if (mGrid.charAt(0)==mGrid.charAt(4) && mGrid.charAt(0) == 'X' && mGrid.charAt(8) != 'O')
            return 8;
        else if (mGrid.charAt(0)==mGrid.charAt(8) && mGrid.charAt(0) == 'X' && mGrid.charAt(4) != 'O')
            return 4;
        else if (mGrid.charAt(4)==mGrid.charAt(8) && mGrid.charAt(4) == 'X' && mGrid.charAt(0) != 'O')
            return 0;
        else if (mGrid.charAt(2)==mGrid.charAt(4) && mGrid.charAt(2) == 'X' && mGrid.charAt(6) != 'O')
            return 6;
        else if (mGrid.charAt(2)==mGrid.charAt(6) && mGrid.charAt(2) == 'X' && mGrid.charAt(4) != 'O')
            return 4;
        else if (mGrid.charAt(4)==mGrid.charAt(6) && mGrid.charAt(4) == 'X' && mGrid.charAt(2) != 'O')
            return 2;
        System.out.println("Error! ai_return_remaining_tile_of_line_almost_filled_by_opponent() has been used but not returned an integer. Returning -1 -> catch exception!");
        return -1;
    }

    private int ai_return_remaining_tile_of_line_almost_filled_by_self() {
        for (int i=0;i<3;i++) {
            if (mGrid.charAt(i*3)==mGrid.charAt(i*3+1) && mGrid.charAt(i*3) == 'O' && mGrid.charAt(i*3+2) != 'X')
                return i*3+2;
            else if (mGrid.charAt(i*3)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3) == 'O' && mGrid.charAt(i*3+1) != 'X')
                return i*3+1;
            else if (mGrid.charAt(i*3+1)==mGrid.charAt(i*3+2) && mGrid.charAt(i*3+1) == 'O' && mGrid.charAt(i*3) != 'X')
                return i*3;
            else if (mGrid.charAt(i)==mGrid.charAt(i+3) && mGrid.charAt(i) == 'O' && mGrid.charAt(i+6) != 'X')
                return i+6;
            else if (mGrid.charAt(i)==mGrid.charAt(i+6) && mGrid.charAt(i) == 'O' && mGrid.charAt(i+3) != 'X')
                return i+3;
            else if (mGrid.charAt(i+3)==mGrid.charAt(i+6) && mGrid.charAt(i+3) == 'O' && mGrid.charAt(i) != 'X')
                return i;
        }
        if (mGrid.charAt(0)==mGrid.charAt(4) && mGrid.charAt(0) == 'O' && mGrid.charAt(8) != 'X')
            return 8;
        else if (mGrid.charAt(0)==mGrid.charAt(8) && mGrid.charAt(0) == 'O' && mGrid.charAt(4) != 'X')
            return 4;
        else if (mGrid.charAt(4)==mGrid.charAt(8) && mGrid.charAt(4) == 'O' && mGrid.charAt(0) != 'X')
            return 0;
        else if (mGrid.charAt(2)==mGrid.charAt(4) && mGrid.charAt(2) == 'O' && mGrid.charAt(6) != 'X')
            return 6;
        else if (mGrid.charAt(2)==mGrid.charAt(6) && mGrid.charAt(2) == 'O' && mGrid.charAt(4) != 'X')
            return 4;
        else if (mGrid.charAt(4)==mGrid.charAt(6) && mGrid.charAt(4) == 'O' && mGrid.charAt(2) != 'X')
            return 2;
        System.out.println("Error! ai_return_remaining_tile_of_line_almost_filled_by_self() has been used but not returned an integer. Returning -1 -> catch exception!");
        return -1;
    }
}
