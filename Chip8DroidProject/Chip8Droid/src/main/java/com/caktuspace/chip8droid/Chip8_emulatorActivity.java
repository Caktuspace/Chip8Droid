package com.caktuspace.chip8droid;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;

public class Chip8_emulatorActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Intent myIntent = getIntent();
		filename = myIntent.getStringExtra("filename");
		mGLView = new Chip8GLSurfaceView(this, filename);
		setContentView(mGLView);
		b0 = new Button(this);
		b1 = new Button(this);
		b2 = new Button(this);
		b3 = new Button(this);
		b4 = new Button(this);
		b5 = new Button(this);
		b6 = new Button(this);
		b7 = new Button(this);
		b8 = new Button(this);
		b9 = new Button(this);
		ba = new Button(this);
		bb = new Button(this);
		bc = new Button(this);
		bd = new Button(this);
		be = new Button(this);
		bf = new Button(this);
		ll = new LinearLayout(this);
		b0.setText("0");
		b1.setText("1");
		b2.setText("2");
		b3.setText("3");
		b4.setText("4");
		b5.setText("5");
		b6.setText("6");
		b7.setText("7");
		b8.setText("8");
		b9.setText("9");
		ba.setText("A");
		bb.setText("B");
		bc.setText("C");
		bd.setText("D");
		be.setText("E");
		bf.setText("F");
		setAlpha((float) 0.5);
		ll.setGravity(Gravity.TOP);
		addContentView(ll,
		            new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
	}

	protected void setAlpha(float x)
	{

	//	ll.removeAllViews();
		b0.setHighlightColor(Color.BLACK);
		b1.setHighlightColor(Color.BLACK);
		b2.setHighlightColor(Color.BLACK);
		b3.setHighlightColor(Color.BLACK);
		b4.setHighlightColor(Color.BLACK);
		b5.setHighlightColor(Color.BLACK);
		b6.setHighlightColor(Color.BLACK);
		b7.setHighlightColor(Color.BLACK);
		b8.setHighlightColor(Color.BLACK);
		b9.setHighlightColor(Color.BLACK);
		ba.setHighlightColor(Color.BLACK);
		bb.setHighlightColor(Color.BLACK);
		bc.setHighlightColor(Color.BLACK);
		bd.setHighlightColor(Color.BLACK);
		be.setHighlightColor(Color.BLACK);
		bf.setHighlightColor(Color.BLACK);
		b0.setAlpha(x);
		b1.setAlpha(x);
		b2.setAlpha(x);
		b3.setAlpha(x);
		b4.setAlpha(x);
		b5.setAlpha(x);
		b6.setAlpha(x);
		b7.setAlpha(x);
		b8.setAlpha(x);
		b9.setAlpha(x);
		ba.setAlpha(x);
		bb.setAlpha(x);
		bc.setAlpha(x);
		bd.setAlpha(x);
		be.setAlpha(x);
		bf.setAlpha(x);

		ll.addView(b0);
		ll.addView(b1);
		ll.addView(b2);
		ll.addView(b3);
		ll.addView(b4);
		ll.addView(b5);
		ll.addView(b6);
		ll.addView(b7);
		ll.addView(b8);
		ll.addView(b9);
		ll.addView(ba);
		ll.addView(bb);
		ll.addView(bc);
		ll.addView(bd);
		ll.addView(be);
		ll.addView(bf);
		
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		if (mGLView != null)
			mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		if (mGLView != null)
			mGLView.onResume();
	}

	public static final int CODE_RETOUR = 0;
	private GLSurfaceView mGLView = null;
	private String filename;
	private Button b0 = null;
	private Button b1 = null;
	private Button b2 = null;
	private Button b3 = null;
	private Button b4 = null;
	private Button b5 = null;
	private Button b6 = null;
	private Button b7 = null;
	private Button b8 = null;
	private Button b9 = null;
	private Button ba = null;
	private Button bb = null;
	private Button bc = null;
	private Button bd = null;
	private Button be = null;
	private Button bf = null;
	private LinearLayout ll = null;

	static {
		System.loadLibrary("Chip8");
	}
}

class Chip8GLSurfaceView extends GLSurfaceView {

	private boolean running = false;

	public Chip8GLSurfaceView(Context context, String name) {
		super(context);
		mRenderer = new Chip8Renderer(name);
		setRenderer(mRenderer);
		gameLoop = new Runnable() {
			public void run() {
				nativePlayGame();
			}
		};
		gameLoopHandle = scheduler.scheduleAtFixedRate(gameLoop, 10, 3,
				TimeUnit.MILLISECONDS);
		running = true;
	}

	@Override
	public void onPause() {
		nativePause();
		gameLoopHandle.cancel(true);
	}

	 @Override 
	    public boolean onTouchEvent(MotionEvent ev) {
		 super.onTouchEvent(ev);
	        // MotionEvent reports input details from the touch screen
	        // and other input controls. In this case, you are only
	        // interested in events where the touch position changed.
	     if ((ev.getAction() & 0x5) == 5 || (ev.getAction() == 0))
	    	 Log.d("Touch Event", "touch pressed");
	     if ((ev.getAction() & 0x6) == 6 || (ev.getAction() == 1))
	    	 Log.d("Touch Event", "touch released");
	        return true;
	    } 
	 
	Chip8Renderer mRenderer;

	private final Runnable gameLoop;
	private ScheduledFuture<?> gameLoopHandle;
	private final ScheduledExecutorService scheduler = Executors
			.newScheduledThreadPool(1);

	private static native void nativePause();

	private static native void nativePlayGame();

}

class Chip8Renderer implements GLSurfaceView.Renderer {

	private boolean initialized = false; // avoid multiple calls to nativeInit
	private String filename;
	private Thread gameThread = null;

	public Chip8Renderer(String name) {
		filename = name;
		if (!initialized) {
			Log.d("surface created", "created the surface");
			nativeInit(filename);
			initialized = true;
		}
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		nativeInitGL();
	}

	public void onSurfaceChanged(GL10 gl, int w, int h) {
		nativeResize(w, h);
	}

	public void onDrawFrame(GL10 gl) {
		nativeRender();
	}

	private static native void nativeInit(String filename);

	private static native void nativeInitGL();

	private static native void nativeResize(int w, int h);

	private static native void nativeRender();
}