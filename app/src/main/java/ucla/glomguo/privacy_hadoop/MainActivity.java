package ucla.glomguo.privacy_hadoop;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.net.wifi.p2p.WifiP2pManager;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;

public class MainActivity extends AppCompatActivity{


    protected static final String TAG = "Privacy Hadoop";
    private WifiP2pManager manager;
    private WifiP2pManager.Channel channel;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);


        Button btn_discover = (Button) findViewById(R.id.btn_discover_peers);
        btn_discover.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent i = new Intent();
                i.setClass(MainActivity.this,WifiDirectActivity.class);
                startActivity(i);
            }
        });


        //  Declare a new thread to do a preference check
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                //  Initialize SharedPreferences
                SharedPreferences getPrefs = PreferenceManager
                        .getDefaultSharedPreferences(getBaseContext());

                //  Create a new boolean and preference and set it to true
                boolean isFirstStart = getPrefs.getBoolean("firstStart", true);

                //  If the activity has never started before...
                if (isFirstStart) {

                    //  Launch app intro
                    Intent i = new Intent(MainActivity.this, IntroActivity.class);
                    startActivity(i);

                    //  Make a new preferences editor
                    SharedPreferences.Editor e = getPrefs.edit();

                    //  Edit preference to make it false because we don't want this to run again
                    e.putBoolean("firstStart", false);

                    //  Apply changes
                    e.apply();
                }
            }
        });

        // Start the thread
        t.start();



//        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
//        fab.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                        .setAction("Action", null).show();
//            }
//        });



    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        switch (item.getItemId()) {
            case R.id.item_show_status:
                // Launch browser to display Hadoop status
                String url = "http://www.google.com";
                Intent i = new Intent(Intent.ACTION_VIEW);
                i.setData(Uri.parse(url));
                startActivity(i);
                return true;

            case R.id.item_p2p_on_off:
//                if (manager != null && channel != null) {
//
//                    // Since this is the system wireless settings activity, it's
//                    // not going to send us a result. We will be notified by
//                    // WiFiDeviceBroadcastReceiver instead.
//
//                    startActivity(new Intent(Settings.ACTION_WIRELESS_SETTINGS));
//                }
//                else {
//                    Log.e(TAG, "channel or manager is null");
//                }
                startActivity(new Intent(Settings.ACTION_WIRELESS_SETTINGS));
                return true;

            case R.id.item_quit:
                //Close App
                System.exit(0);
                return true;

            case R.id.item_tutorial:
                Intent i2 = new Intent();
                i2.setClass(MainActivity.this,IntroActivity.class);
                startActivity(i2);
                return true;

            case R.id.item_about_us:
//                Intent i3 = new Intent();
//                i3.setClass(MainActivity.this,AboutUsActivity.class);
//                startActivity(i3);
                new AlertDialog.Builder(this)
                        .setMessage("This is the project from UCLA CS211, which is built on the previous version from a CS211 team last year. \n\nOur group has the following members: \n \n" +
                                "Guo, Cheng (glomguo@g.ucla.edu),\n" +
                                "Lin, Jonathan (jonathan.lin@cs.ucla.edu),\n" +
                                "Tan, Zhaowei (tan@cs.ucla.edu),\n" +
                                "Xia, Yumin (yumin@cs.ucla.edu). \n\n" +
                                "We would like to thank our Tutor Zengwen Yuan and our Professor Songwu Lu for their mentoring. \n\n" +
                                "Thank you for using our app. \n\n" +
                                "Privacy Aware Mobile Hadoop Group")
                        .setPositiveButton("OK",
                                new DialogInterface.OnClickListener(){
                                    public void onClick(DialogInterface dialoginterface, int i){
                                        //Click Event
                                    }
                                })
                        .show();
                return true;

            case R.id.item_version:
                new AlertDialog.Builder(this)
                        .setMessage("Version Privacy-Hadoop 1.0")
                        .setPositiveButton("OK",
                                new DialogInterface.OnClickListener(){
                                    public void onClick(DialogInterface dialoginterface, int i){
                                        //Click Event
                                    }
                                })
                        .show();
        }
        return super.onOptionsItemSelected(item);
    }

}
