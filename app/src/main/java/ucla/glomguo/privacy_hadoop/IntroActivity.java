package ucla.glomguo.privacy_hadoop;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;

import com.github.paolorotolo.appintro.AppIntro;
import com.github.paolorotolo.appintro.AppIntroFragment;

/**
 * Created by Glom on 11/22/2016.
 */

public class IntroActivity extends AppIntro {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Note here that we DO NOT use setContentView();

        // Add your slide fragments here.
        // AppIntro will automatically generate the dots indicator and buttons.
//        addSlide(firstFragment);
//        addSlide(secondFragment);
//        addSlide(thirdFragment);
//        addSlide(fourthFragment);

        // Instead of fragments, you can also use our default slide
        // Just set a title, description, background and image. AppIntro will do the rest.
        addSlide(AppIntroFragment.newInstance("Privacy-Aware\nMobile Hadoop", "A Safe Mobile Cloud Computing App", R.drawable.wifi_hadoop, Color.parseColor("#66CCFF")));
        addSlide(AppIntroFragment.newInstance("Distribute your program & data encrypted, while peers can still implement!", "The magic is homomorphic encryption...", R.drawable.lock, Color.parseColor("#66CCFF")));

        addSlide(AppIntroFragment.newInstance("Click \"DISCOVER PEERS\" at the homepage, and wait for your friends!", "Make sure you open P2P first", R.drawable.wifi, Color.parseColor("#66CCFF")));
        addSlide(AppIntroFragment.newInstance("Check our app and run sample word count code.", "More applications coming soon...", R.drawable.word_count, Color.parseColor("#66CCFF")));
        addSlide(AppIntroFragment.newInstance("Let's get started!", "", R.drawable.wifi_hadoop, Color.parseColor("#66CCFF")));


        // OPTIONAL METHODS
        // Override bar/separator color.
        setBarColor(Color.parseColor("#3F51B5"));
        setSeparatorColor(Color.parseColor("#2196F3"));

        setBarColor(Color.parseColor("#3F51B5"));
        setSeparatorColor(Color.parseColor("#2196F3"));

        // Hide Skip/Done button.
        showSkipButton(true);
        setProgressButtonEnabled(true);

        // Turn vibration on and set intensity.
        // NOTE: you will probably need to ask VIBRATE permission in Manifest.
        //setVibrate(true);
        //setVibrateIntensity(30);

    }



    @Override
    public void onSkipPressed(Fragment currentFragment) {
        super.onSkipPressed(currentFragment);

        Intent i = new Intent();
        i.setClass(IntroActivity.this,MainActivity.class);
        startActivity(i);
    }

    @Override
    public void onDonePressed(Fragment currentFragment) {
        super.onDonePressed(currentFragment);

        Intent i = new Intent();
        i.setClass(IntroActivity.this,MainActivity.class);
        startActivity(i);
    }

    @Override
    public void onSlideChanged(@Nullable Fragment oldFragment, @Nullable Fragment newFragment) {
        super.onSlideChanged(oldFragment, newFragment);
        // Do something when the slide changes.

    }
}
