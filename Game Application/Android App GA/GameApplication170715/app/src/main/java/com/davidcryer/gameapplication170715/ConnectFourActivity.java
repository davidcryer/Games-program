package com.davidcryer.gameapplication170715;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class ConnectFourActivity extends ActionBarActivity {

    private String mGrid;
    private boolean mTurns_player_1_as_true_player_2_as_false;
    private int mNumber_of_wins_player_1, mNumber_of_wins_player_2;

    public final static String EXTRA_MESSAGE = "com.davidcryer.gameapplication170715.MESSAGE";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect_four);
        mNumber_of_wins_player_1 = 0; mNumber_of_wins_player_2 = 0;
        new_connect_four();
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

    private void new_connect_four() {
        mGrid = "";
        for (int i=0;i<42;i++) {
            mGrid += " ";
        }
        mTurns_player_1_as_true_player_2_as_false = true;

        TextView textview = (TextView)findViewById(R.id.c_f_text_player_one_wins_numbers);
        textview.setText(String.valueOf(mNumber_of_wins_player_1));
        textview = (TextView)findViewById(R.id.c_f_text_player_two_wins_numbers);
        textview.setText(String.valueOf(mNumber_of_wins_player_2));

        reset_board();
    }

    public void c_f_button_1_click(View view) {
        change_grid_and_check_game_state_and_swap_players(1);
    }
    public void c_f_button_2_click(View view) {
        change_grid_and_check_game_state_and_swap_players(2);
    }
    public void c_f_button_3_click(View view) {
        change_grid_and_check_game_state_and_swap_players(3);
    }
    public void c_f_button_4_click(View view) {
        change_grid_and_check_game_state_and_swap_players(4);
    }
    public void c_f_button_5_click(View view) {
        change_grid_and_check_game_state_and_swap_players(5);
    }
    public void c_f_button_6_click(View view) {
        change_grid_and_check_game_state_and_swap_players(6);
    }
    public void c_f_button_7_click(View view) {
        change_grid_and_check_game_state_and_swap_players(7);
    }

    private boolean check_for_turn_remaining_as_true() {
        for (int i=0;i<42;i++) {
            if (mGrid.charAt(i)!='O'&&mGrid.charAt(i)!='X') {
                return true;
            }
        }
        return false;
    }

    private boolean check_for_draw_as_true()  {System.out.println("Do not need to use this function - instead check for win and then if there are any turns remaining if no winners. Returning with false...");return false;}

    private boolean check_for_win_as_true() {
        for (int i=0;i<6;i++) {
            for (int j=0;j<4;j++) {
                if (mGrid.charAt(i*7+j)==mGrid.charAt(i*7+j+1) && mGrid.charAt(i*7+j+1)==mGrid.charAt(i*7+j+2) && mGrid.charAt(i*7+j+2)==mGrid.charAt(i*7+j+3)&&(mGrid.charAt(i*7+j)=='O'||mGrid.charAt(i*7+j)=='X'))
                    return true;
                if (i<3) {
                    if (mGrid.charAt(i*7+j)==mGrid.charAt((i+1)*7+j+1) && mGrid.charAt((i+1)*7+j+1)==mGrid.charAt((i+2)*7+j+2) && mGrid.charAt((i+2)*7+j+2)==mGrid.charAt((i+3)*7+j+3)&&(mGrid.charAt(i*7+j)=='O'||mGrid.charAt(i*7+j)=='X'))
                        return true;
                    else if (mGrid.charAt((i+3)*7+j)==mGrid.charAt((i+2)*7+j+1) && mGrid.charAt((i+2)*7+j+1)==mGrid.charAt((i+1)*7+j+2) && mGrid.charAt((i+1)*7+j+2)==mGrid.charAt((i)*7+j+3)&&(mGrid.charAt((i+3)*7+j)=='O'||mGrid.charAt((i+3)*7+j)=='X'))
                        return true;
                }
            }
        }
        for (int i=0;i<7;i++) {
            for (int j=0;j<3;j++) {
                if (mGrid.charAt(i+j*7)==mGrid.charAt(i+(j+1)*7) && mGrid.charAt(i+(j+1)*7)==mGrid.charAt(i+(j+2)*7) && mGrid.charAt(i+(j+2)*7)==mGrid.charAt(i+(j+3)*7)&&(mGrid.charAt(i+j*7)=='O'||mGrid.charAt(i+j*7)=='X'))
                    return true;
            }
        }
        return false;
    }

    private void change_grid_and_check_game_state_and_swap_players(int column) {

        if (column >= 1 && column <= 7) {
            String X_or_O;
            if (mTurns_player_1_as_true_player_2_as_false)
                X_or_O = "X";
            else
                X_or_O = "O";
            if (mGrid.charAt(column-1)!='O'&&mGrid.charAt(column-1)!='X') {
                mGrid = mGrid.substring(0, column-1) + X_or_O + mGrid.substring(column);
                change_button_text_and_disable_column_if_full(column,0);
            }
            else if (mGrid.charAt(column-1+7)!='O'&&mGrid.charAt(column-1+7)!='X') {
                mGrid = mGrid.substring(0, column-1+7) + X_or_O + mGrid.substring(column+7);
                change_button_text_and_disable_column_if_full(column,1);
            }
            else if (mGrid.charAt(column-1+7*2)!='O'&&mGrid.charAt(column-1+7*2)!='X') {
                mGrid = mGrid.substring(0, column-1+7*2) + X_or_O + mGrid.substring(column+7*2);
                change_button_text_and_disable_column_if_full(column,2);
            }
            else if (mGrid.charAt(column-1+7*3)!='O'&&mGrid.charAt(column-1+7*3)!='X') {
                mGrid = mGrid.substring(0, column-1+7*3) + X_or_O + mGrid.substring(column+7*3);
                change_button_text_and_disable_column_if_full(column,3);
            }
            else if (mGrid.charAt(column-1+7*4)!='O'&&mGrid.charAt(column-1+7*4)!='X') {
                mGrid = mGrid.substring(0, column-1+7*4) + X_or_O + mGrid.substring(column+7*4);
                change_button_text_and_disable_column_if_full(column,4);
            }
            else if (mGrid.charAt(column-1+7*5)!='O'&&mGrid.charAt(column-1+7*5)!='X') {
                mGrid = mGrid.substring(0, column-1+7*5) + X_or_O + mGrid.substring(column+7*5);
                change_button_text_and_disable_column_if_full(column,5);
            }
        }

        if (mTurns_player_1_as_true_player_2_as_false)
            mTurns_player_1_as_true_player_2_as_false = false;
        else
            mTurns_player_1_as_true_player_2_as_false = true;

        if (!check_for_turn_remaining_as_true() || check_for_win_as_true()) {
            Intent game_finished = new Intent(this, ConnectFourGameFinishedActivity.class);
            String game_finished_message;
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

    private void change_button_text_and_disable_column_if_full(int column, int row) {
        Button button = null;
        if (row == 0) {
            if (column == 1)
                button = (Button) findViewById(R.id.c_f_button_1);
            else if (column == 2)
                button = (Button) findViewById(R.id.c_f_button_2);
            else if (column == 3)
                button = (Button) findViewById(R.id.c_f_button_3);
            else if (column == 4)
                button = (Button) findViewById(R.id.c_f_button_4);
            else if (column == 5)
                button = (Button) findViewById(R.id.c_f_button_5);
            else if (column == 6)
                button = (Button) findViewById(R.id.c_f_button_6);
            else if (column == 7)
                button = (Button) findViewById(R.id.c_f_button_7);
        }
        else if (row == 1) {
            if (column == 1)
                button = (Button) findViewById(R.id.c_f_button_8);
            else if (column == 2)
                button = (Button) findViewById(R.id.c_f_button_9);
            else if (column == 3)
                button = (Button) findViewById(R.id.c_f_button_10);
            else if (column == 4)
                button = (Button) findViewById(R.id.c_f_button_11);
            else if (column == 5)
                button = (Button) findViewById(R.id.c_f_button_12);
            else if (column == 6)
                button = (Button) findViewById(R.id.c_f_button_13);
            else if (column == 7)
                button = (Button) findViewById(R.id.c_f_button_14);
        }
        else if (row == 2) {
            if (column == 1)
                button = (Button) findViewById(R.id.c_f_button_15);
            else if (column == 2)
                button = (Button) findViewById(R.id.c_f_button_16);
            else if (column == 3)
                button = (Button) findViewById(R.id.c_f_button_17);
            else if (column == 4)
                button = (Button) findViewById(R.id.c_f_button_18);
            else if (column == 5)
                button = (Button) findViewById(R.id.c_f_button_19);
            else if (column == 6)
                button = (Button) findViewById(R.id.c_f_button_20);
            else if (column == 7)
                button = (Button) findViewById(R.id.c_f_button_21);
        }
        else if (row == 3) {
            if (column == 1)
                button = (Button) findViewById(R.id.c_f_button_22);
            else if (column == 2)
                button = (Button) findViewById(R.id.c_f_button_23);
            else if (column == 3)
                button = (Button) findViewById(R.id.c_f_button_24);
            else if (column == 4)
                button = (Button) findViewById(R.id.c_f_button_25);
            else if (column == 5)
                button = (Button) findViewById(R.id.c_f_button_26);
            else if (column == 6)
                button = (Button) findViewById(R.id.c_f_button_27);
            else if (column == 7)
                button = (Button) findViewById(R.id.c_f_button_28);
        }
        else if (row == 4) {
            if (column == 1)
                button = (Button) findViewById(R.id.c_f_button_29);
            else if (column == 2)
                button = (Button) findViewById(R.id.c_f_button_30);
            else if (column == 3)
                button = (Button) findViewById(R.id.c_f_button_31);
            else if (column == 4)
                button = (Button) findViewById(R.id.c_f_button_32);
            else if (column == 5)
                button = (Button) findViewById(R.id.c_f_button_33);
            else if (column == 6)
                button = (Button) findViewById(R.id.c_f_button_34);
            else if (column == 7)
                button = (Button) findViewById(R.id.c_f_button_35);
        }
        else if (row == 5) {
            Button disable_column_button = null;
            if (column == 1) {
                button = (Button) findViewById(R.id.c_f_button_36);
                disable_column_button = (Button)findViewById(R.id.c_f_button_1);
            }
            else if (column == 2) {
                button = (Button) findViewById(R.id.c_f_button_37);
                disable_column_button = (Button)findViewById(R.id.c_f_button_2);
            }
            else if (column == 3) {
                button = (Button) findViewById(R.id.c_f_button_38);
                disable_column_button = (Button)findViewById(R.id.c_f_button_3);
            }
            else if (column == 4) {
                button = (Button) findViewById(R.id.c_f_button_39);
                disable_column_button = (Button)findViewById(R.id.c_f_button_4);
            }
            else if (column == 5) {
                button = (Button) findViewById(R.id.c_f_button_40);
                disable_column_button = (Button)findViewById(R.id.c_f_button_5);
            }
            else if (column == 6) {
                button = (Button) findViewById(R.id.c_f_button_41);
                disable_column_button = (Button)findViewById(R.id.c_f_button_6);
            }
            else if (column == 7) {
                button = (Button) findViewById(R.id.c_f_button_42);
                disable_column_button = (Button)findViewById(R.id.c_f_button_7);
            }
            disable_column_button.setEnabled(false);
        }
        button.setText(String.valueOf(mGrid.charAt(column-1+7*row)));
    }

    private void prompt_for_new_game_or_quit() {
        disable_grid_buttons();

        //Prompt question "play again?" with Buttons for yes and no

    }

    private void click_for_new_game() {
        //Hide "Play again? question and yes/no buttons


        enable_grid_buttons();
        new_connect_four();
    }

    private void disable_grid_buttons() {
        Button button = (Button)findViewById(R.id.c_f_button_1);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_2);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_3);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_4);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_5);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_6);
        if (button.isEnabled())
            button.setEnabled(false);
        button = (Button)findViewById(R.id.c_f_button_7);
        if (button.isEnabled())
            button.setEnabled(false);
    }

    private void enable_grid_buttons() {
        Button button = (Button)findViewById(R.id.c_f_button_1);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_2);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_3);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_4);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_5);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_6);
        if (!button.isEnabled())
            button.setEnabled(true);
        button = (Button)findViewById(R.id.c_f_button_7);
        if (!button.isEnabled())
            button.setEnabled(true);
    }

    private void reset_board() {
        Button button = (Button)findViewById(R.id.c_f_button_1);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(0)));
        button = (Button)findViewById(R.id.c_f_button_2);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(1)));
        button = (Button)findViewById(R.id.c_f_button_3);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(2)));
        button  = (Button)findViewById(R.id.c_f_button_4);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(3)));
        button  = (Button)findViewById(R.id.c_f_button_5);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(4)));
        button  = (Button)findViewById(R.id.c_f_button_6);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(5)));
        button = (Button)findViewById(R.id.c_f_button_7);
        button.setText(String.valueOf(getString(R.string.c_f_columns).charAt(6)));

        button = (Button)findViewById(R.id.c_f_button_8);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_9);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_10);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_11);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_12);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_13);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_14);
        button.setText(" ");

        button = (Button)findViewById(R.id.c_f_button_15);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_16);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_17);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_18);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_19);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_20);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_21);
        button.setText(" ");

        button = (Button)findViewById(R.id.c_f_button_22);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_23);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_24);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_25);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_26);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_27);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_28);
        button.setText(" ");

        button = (Button)findViewById(R.id.c_f_button_29);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_30);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_31);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_32);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_33);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_34);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_35);
        button.setText(" ");

        button = (Button)findViewById(R.id.c_f_button_36);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_37);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_38);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_39);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_40);
        button.setText(" ");
        button  = (Button)findViewById(R.id.c_f_button_41);
        button.setText(" ");
        button = (Button)findViewById(R.id.c_f_button_42);
        button.setText(" ");
    }
}
