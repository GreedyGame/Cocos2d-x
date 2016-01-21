GreedyGame Cocos2d-x Integration Guide
===================

## Setup Units

All the units can be setup easily from panel.greedygame.com

### Native Ad-units
* Goto, sidemenu, AdUnit then drag and drop assets which has to be used for branding.
* ![Adding Native Unit](screen-shots/naive-ads-upload.gif?raw=true "Adding Native Unit" )


### Floating Ad-units
* Goto, sidemenu, AdUnit then click on "Add float unit" to create one unit.
* ![Adding Float Unit](screen-shots/float-ad-create.gif?raw=true "Adding Float Unit" )


---------------------------------------

## Initialisation

* Download [Android library project](Current_sdk/proj.android) from Current_sdk/proj.android.
* You will find a folder named [Classes](Current_sdk/Classes).
* In this folder you will find *GreedyGameSDK.h* . **iOS** and **Android** will share this header file. Add this to your cocos2d-x project.
* Put all branded assets under folder Resources/greedygame

> **Note:**
> Resources/greedygame directory should only contain images and no sub-directories
 
 Declare the following string in strings.xml file  under the res/values folder.
```xml
<string name="greedy_game_profile">"your-game-id-without-quotes"</string>
```
 
## Fetching Campaigns

In your Splash scene (very first scene of game), add following code in method `SplashScene::init()`. Where `onInit` is callback function. 

```cpp
greedygame::GreedyGameSDK::initialize(&onInit, &onProgress);

```

### Define callback functions as

#### onInit

```cpp
void on_init(int event) {
	CCLog( "> on_init %d", event);
	/*
	 * GG_CAMPAIGN_NOT_FOUND, -1 = using no campaign
	 * GG_CAMPAIGN_CACHED, 0 = campaign already cached
	 * GG_CAMPAIGN_FOUND, 1 = new campaign found to Download
	 * GG_CAMPAIGN_DOWNLOADED, 2 = new campaign is Downloaded
	 * GG_ADUNIT_OPENED, 3 = AdUnit Opened
	 * GG_ADUNIT_CLOSED, 4 = AdUnit Closed
	 */
    
	int isBranded = -1;
	if(event == GG_CAMPAIGN_CACHED || event == GG_CAMPAIGN_DOWNLOADED){
		isBranded = 1;
	}else if(event == GG_CAMPAIGN_NOT_FOUND){
		isBranded = 0;
	}

	if(isBranded > -1){
		greedygame::GreedyGameSDK::fetchAdHead("<floating unit-id>");
		CCDirector *pDirector = CCDirector::sharedDirector();
		CCScene *pScene = HelloWorld::scene();
		pDirector->replaceScene(pScene);
	}

	if(event == GG_ADUNIT_OPENED){
		//Make pause
	}else if(event == GG_ADUNIT_CLOSED){
		//Make unpause
	}
}
```

#### onProgress
```cpp
void onProgress(float f) {
	CCLog( "downloadProgress > : %f", f);
	ostringstream myString;
	myString << "Loading progress " << f <<"%";
	std::string s = myString.str();
	pLabel->setString(s.c_str());
}
```

#### ReportCustomEvent
`greedygame::GreedyGameSDK::onCustomEvent("<event name>");`


## Floating Ads
#### Fetch floating units
`greedygame::GreedyGameSDK::fetchAdHead("<floating unit-id>");`

#### Remove floating units
`greedygame::GreedyGameSDK::removeAdHead();`

Android
----------
* Copy android folder (found in greedygame folder) to your project.
* In your project's jni/Android.mk file, add an entry for `GreedyGameSDK.cpp` file.
* Add required permissions in **AndroidManifest.xml** file as shown below:-

```xml
<uses-permission android:name="android.permission.READ_PHONE_STATE" />
<uses-permission android:name="android.permission.GET_ACCOUNTS" />
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />

<application >      
    <activity
	    android:name="com.greedygame.android.AdHeadActivity"			
	    android:theme="@style/Theme.Transparent" >
	</activity>
    
    <service
        android:name="com.greedygame.android.GreedyBackgroundService"
        android:enabled="true" >
    </service>
    
    <receiver 
            android:name="com.greedygame.android.GreedyRefReceiver" 
            android:enabled="true" 
            android:priority="100">
      <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
        <action android:name="android.net.conn.CONNECTIVITY_CHANGE" />
      </intent-filter>
    </receiver>
</application>
```

* In your main activity's life cycle functions, add the following code:-
```java
AdsGreedyGame.setup(this, Cocos2dxGLSurfaceView.getInstance()); 
```

----
**Analytics Methods**
As name suggest, put following method inside Andorid main acitivity method.

##### `public void AdsGreedyGame.onResume()`
##### `public void AdsGreedyGame.onResume(String name)`
##### `public void AdsGreedyGame.onPause()`
##### `public void AdsGreedyGame.onPause(String name)`


For example
```java
@Override
protected void onResume(){
    super.onResume();
    AdsGreedyGame.onResume();
}
```
##### CALLBACK METHOD IN WRAPPER : unAvailablePermissions(ArrayList<String> permissions)
* This method needs to be used only if your game is targetting SDK version 23 or
  higher. This callback gives a list of permissions that are not available at runtime and is invoked after GreedyGameAgent initialization.

  NB : Only performs check for 4 dangerous permissions that are required by GreedyGameSDK. 

  Permissions that are checked : 

   * Manifest.permission.ACCESS_COARSE_LOCATION
   * Manifest.permission.WRITE_EXTERNAL_STORAGE
   * Manifest.permission.GET_ACCOUNTS
   * Manifest.permission.READ_PHONE_STATE

   NB : The above strings itself are returned in the argument if they are not available.

--------
Congratulations! You just completed the integration. Now you can test your game with GreedyGame integrated, by making an theme at panel.greedygame.com

------

### For more help please see [FAQ] (https://github.com/GreedyGame/unity-plugin/wiki/FAQs)
