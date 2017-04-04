package ucla.glomguo.privacy_hadoop;

import android.app.Activity;
import android.net.wifi.p2p.WifiP2pInfo;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.util.Map;

public class HadoopActivity extends Activity {

    private WifiP2pInfo info = null;
    private ExecutionLayer executionLayer = null;
    private ControlLayer controlLayer = null;
    private ControlLayerInfo controlLayerInfo = null;
    private View mContentView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hadoop);

    }
}