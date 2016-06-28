
/****************************************************************************
 Copyright (c) 2014      GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#include "GreedyGameSDK.h"
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
	void (*onInitCallback)(int);
	void (*onDownloadCallback)(float);

	extern "C" {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onEvent(JNIEnv* env, jobject thiz, jint ret)
		{
			if(ret == GG_CAMPAIGN_CACHED || ret == GG_CAMPAIGN_DOWNLOADED){
				GreedyGameSDK::setPath();
			}

			onInitCallback(ret);
		}
        
		JNIEXPORT void JNICALL Java_com_greedygame_android_cocos2dx_AdsGreedyGame_onDownload(JNIEnv* env, jobject thiz, jfloat ret)
		{
			onDownloadCallback(ret);
		}
#endif
        
	}


    void GreedyGameSDK::initialize(void (*init_callback)(int), void (*progress_callback)(float))
    {
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"initialize"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
            onInitCallback = init_callback;
            onDownloadCallback = progress_callback;

            /**Setting pref**/
            std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();;
            searchPaths.push_back("greedygame");
            CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        }
#endif
    }



    std::string GreedyGameSDK::_getActivePath(){
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

    
    void GreedyGameSDK::fetchFloatAd(const char *unit_id){
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



    void GreedyGameSDK::remove(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"remove"
                                                    ,"()V"))
        {
            
            t.env->CallStaticVoidMethod(t.classID,t.methodID);
        }
#endif
    }

    void GreedyGameSDK::setPath() {
    	std::string path = GreedyGameSDK::_getActivePath();
    	CCLOG("activepath %s", path.c_str());
    	
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        searchPaths.insert (searchPaths.begin(), path);
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }

    void GreedyGameSDK::onCustomEvent(const char *event_name){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"onCustomEvent"
                                                    ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(event_name);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
#endif        
    }



     void GreedyGameSDK::showEngagementWindow(const char *unit_id){
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


     void GreedyGameSDK::forcedExit(){
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


std::string GreedyGameSDK::getActiveUnitById(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActiveUnitById"
                                                    ,"(Ljava/lang/String;)V")))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticVoidMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }


std::string GreedyGameSDK::getActiveUnitByName(const char *unit_id){
    std::string path("");
            
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        cocos2d::JniMethodInfo t;
        if (cocos2d::JniHelper::getStaticMethodInfo(t, GreedyGame_CLASS_NAME
                                                    ,"getActiveUnitByName"
                                                    ,"(Ljava/lang/String;)V")))
        {
            jstring StringArg1 = t.env->NewStringUTF(unit_id);
            jstring str = (jstring) t.env->CallStaticVoidMethod(t.classID,t.methodID,StringArg1);
            path = JniHelper::jstring2string(str);
        }
#endif      
return path;  
    }


    


}
