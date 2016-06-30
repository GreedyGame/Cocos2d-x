package com.greedygame.android.cocos2dx;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.widget.FrameLayout;

import com.greedygame.android.adhead.FloatUnitLayout;
import com.greedygame.android.agent.GreedyGameAgent;
import com.greedygame.android.agent.GreedyGameAgent.OnInitEvent;
import com.greedygame.android.agent.IAgentListener;

import java.util.ArrayList;
import java.util.List;


public class AdsGreedyGame {

    protected static GLSurfaceView sGLSurfaceView = null;
    protected static String TAG = "AdsGreedyGame";
    static boolean isEnable = true;
    private static Context mContext = null;
    private static GreedyGameAgent ggAgent = null;
    private static FloatUnitLayout floatUnitLayout = null;
    private static boolean isDebug = false;

    public static void setup(Activity activity, GLSurfaceView value) {

        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return;

            }
            LogD("GreedyGame is started");
            mContext = activity;

            ggAgent = GreedyGameAgent.install((Activity) mContext, new AdsGreedyGame.GreedyListener());
            ggAgent.gameEngine = "cocos2dx";
            sGLSurfaceView = value;
            floatUnitLayout = new FloatUnitLayout((Activity) mContext);
            ((Activity) mContext).runOnUiThread(
                    new Runnable() {
                        public void run() {
                            FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
                                    FrameLayout.LayoutParams.WRAP_CONTENT,
                                    FrameLayout.LayoutParams.WRAP_CONTENT);
                            ((Activity) mContext).addContentView(floatUnitLayout, params);
                        }
                    });
        } catch (Exception e) {
            LogE("Aborting this session", e);
        }
    }

    public static void setEnable(boolean s) {
        isEnable = s;
    }

    public static void init() {
        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return;
            }
            ggAgent.init();
            ggAgent.setDebugLog(true);
            LogD("init");

        } catch (Exception e) {
            LogE("Aborting this session", e);
        }
    }

    public static String getActivePath() {
        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return null;
            }
            return ggAgent.getActivePath();
        } catch (Exception e) {
            LogE("Aborting this session", e);
            return null;
        }
    }


    public static void fetchFloatAd(final String unit_id) {
        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return;
            }
            ((Activity) mContext).runOnUiThread(
                    new Runnable() {
                        public void run() {
                            floatUnitLayout.fetchFloatAd(unit_id);
                        }
                    });

        } catch (Exception e) {
            LogE("Aborting this session", e);
            return;
        }
    }

    public static void showEngagementWindow(String unitId) {
        LogD("ShowEngagementWindow Called from Wrapper ");
        floatUnitLayout.showEngagementWindow(unitId);
    }


    public static String getActiveUnitById(String id) {
        LogD("getActiveUnitById");
        return ggAgent.getActiveUnitById(id);
    }

    public static String getActiveUnitByName(String filename) {
        LogD("getActiveUnitByName Called from Wrapper ");
        return ggAgent.getActiveUnitByName(filename);
    }

    public static void removeFloatAd() {
        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return;
            }

            ((Activity) mContext).runOnUiThread(
                    new Runnable() {
                        public void run() {
                            floatUnitLayout.removeFloatAd();
                        }
                    });
        } catch (Exception e) {
            LogE("Aborting this session", e);
            return;
        }
    }

    public static void setDebugLog(boolean b) {

        try {
            LogD("GreedyGame Debug logs turned on from cocos wrapper");
            ggAgent.setDebugLog(b);
        } catch (Exception e) {
            LogE("Aporting this session", e);
        }
    }


    public static void setDebugCampaign(boolean b) {

        try {
            if (!isEnable) {
                LogD("GreedyGame has been disabled manually");
                return;
            }
            isDebug = b;
            ggAgent.setDebugCampaign(b);
        } catch (Exception e) {
            LogE("Aporting this session", e);
        }
    }


    private static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();

        //Start without campaign
        isEnable = false;
        runOnGLThread(new Runnable() {
            @Override
            public void run() {
                AdsGreedyGame.onInit(-1);
            }
        });
    }


    public static void forcedExit() {

        try {
            ggAgent.forcedExit((Activity) mContext);
            LogD(TAG + " Uninstall inside Wrapper called !");
        } catch (Exception e) {
            LogE("Aporting this session error in unInstall", e);
        }
    }


    private static void LogD(String msg) {

        Log.d(TAG, msg);

    }


    private static void runOnGLThread(Runnable r) {
        if (null != sGLSurfaceView) {
            sGLSurfaceView.queueEvent(r);
        } else {
            LogD("runOnGLThread sGLSurfaceView is null");
            r.run();
        }
    }


    //For Callbacks
    public static native void onInit(int a);

    public static native void onDownload();

    public static native void onError();

    public static native void onProgress(float p);

    private static class GreedyListener implements IAgentListener {


        @Override
        public void onInit(final OnInitEvent arg) {


			/*
             * -1 = campaign not available
			 * 1 = new campaign found to download
			 */

            runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    if (OnInitEvent.CAMPAIGN_NOT_AVAILABLE == arg) {
                        AdsGreedyGame.onInit(-1);
                    } else if (OnInitEvent.CAMPAIGN_AVAILABLE == arg) {
                        AdsGreedyGame.onInit(1);
                    }


                }
            });
        }


        @Override
        public void onDownload() {
            runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    AdsGreedyGame.onDownload();
                }
            });
        }

        @Override
        public void onError() {
            runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    AdsGreedyGame.onError();
                }
            });
        }

        @Override
        public void onProgress(final float p) {
            runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    AdsGreedyGame.onProgress(p);
                }
            });

        }

        @Override
        public void onPermissionsUnavailable(ArrayList<String> arg0) {
            // TODO Auto-generated method stub

        }

    }


}


