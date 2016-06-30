
/****************************************************************************
 Copyright (c) 2014      GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#include "GreedyGameAgent.h"
#include "cocos2d.h"
#include <iostream>
#include <vector>



#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

#define  GreedyGame_CLASS_NAME "com/greedygame/android/cocos2dx/AdsGreedyGame"

namespace greedygame
{

    IAgentListener *listener;

	extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

		JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onInit(JNIEnv* env, jobject thiz, jint ret)
		{
			listener->onInit(ret);
		}
        
		JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onProgress(JNIEnv* env, jobject thiz, jfloat ret)
		{
			listener->onProgress(ret);
		}

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onDownload(JNIEnv* env, jobject thiz)
        {
            listener->onDownload();
        }

        JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onError(JNIEnv* env, jobject thiz)
        {
            listener->onError();
        }
#endif
        
	}


    void GreedyGameAgent::init(IAgentListener* _listener)
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"init"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
            listener = _listener;
            
        }
#endif
    }



    std::string GreedyGameAgent::getActivePath(){
    	std::string path("");
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActivePath"
                                                    ,"()Ljava/lang/String;"))
        {
        	jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID);
        	path = JniHelper::jstring2string(str);
        }
#endif
        return path;
    }

    
    void GreedyGameAgent::fetchFloatAd(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"fetchFloatAd"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif
    }


    void GreedyGameAgent::forcedExit(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"forcedExit"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }


     void GreedyGameAgent::showEngagementWindow(const char *unit_id){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"showEngagementWindow"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif        
    }


std::string GreedyGameAgent::getActiveUnitById(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActiveUnitById"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }


std::string GreedyGameAgent::getActiveUnitByName(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActiveUnitByName"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticObjectMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }


    


}
