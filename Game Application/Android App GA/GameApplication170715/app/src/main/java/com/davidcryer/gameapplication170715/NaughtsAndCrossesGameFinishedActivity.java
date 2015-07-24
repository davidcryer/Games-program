package com.davidcryer.gameapplication170715;

import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;


public class NaughtsAndCrossesGameFinishedActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_naughts_and_crosses_game_finished);
        Intent intent = getIntent();
        String game_announcement = intent.getStringExtra(NaughtsAndCrossesActivity.EXTRA_MESSAGE);
        TextView textview = (TextView)findViewById(R.id.n_and_c_game_finished_announcement);
        textview.setText(game_announcement);
        textview.setTextSize(16);
    }

    public void n_and_c_button_yes_click(View view) {
        finish();
    }

    public void n_and_c_button_no_click(View view) {
        Intent intent = new Intent(this, MainActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
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
}
