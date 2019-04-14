package org.libsdl.app.ui;

import android.app.Activity;
import android.os.Bundle;
import android.view.SurfaceView;

import org.libsdl.app.R;
import org.libsdl.app.SDL;
import org.libsdl.app.SDLActivity;

import androidx.annotation.Nullable;

public class PlayerActivity extends Activity {


    SurfaceView surfaceView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_player);

        SDL.loadLibrary("SDL2");
        SDL.loadLibrary("main");

        init();
    }

    void init() {
        surfaceView = findViewById(R.id.surfaceView);

        SDLActivity.nativeRunMain("libmain.so", "SDL_main", new String[0]);
//        String subPath = "AAAAA/ff_media_encode.mp4";//"AAAAA/ff_video_encode.h264";
//        String mfp = new File(Environment.getExternalStorageDirectory(), subPath).getAbsolutePath();
//        sdlplay(mfp);
    }


//    public static native int play(String mfp);
//
//    public static native int sdlplay(String mfp);

}
