#include "SplashScene.h"
#include "HelloWorldScene.h"
#include "AppMacros.h"

#include "../../../current-sdk/classes/GreedyGameSDK.h"



USING_NS_CC;



CCLabelTTF* pLabel;

CCScene* SplashScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScene *layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


class AgentListener: public IAgentListener {
	int isBranded = -1;
	public:
	void onInit(int event){
		CCLog( "on_init %d", event);
		/*
		 * CAMPAIGN_NOT_AVAILABLE, -1 = using no campaign
		 * CAMPAIGN_AVAILABLE, 0 = campaign already cached
		 */
	    
		isBranded = -1;
		if(r == CAMPAIGN_NOT_AVAILABLE){
			isBranded = -1;
		}else if(r == CAMPAIGN_AVAILABLE){
			//Start showing progress bar
		}

		if(isBranded > -1){
			CCDirector *pDirector = CCDirector::sharedDirector();
			CCScene *pScene = HelloWorld::scene();
			pDirector->replaceScene(pScene);
		}
	}

	void onDownload(){
		isBranded = 1;

		if(isBranded > -1){
			CCDirector *pDirector = CCDirector::sharedDirector();
			CCScene *pScene = HelloWorld::scene();
			pDirector->replaceScene(pScene);
		}

	}

	void onError(){
		isBranded = -1;
	}

	void onProgress(float progress){
		CCLog( "downloadProgress > : %f", progress);
		ostringstream myString;
		myString << "Loading progress " << progress <<"%";
		std::string s = myString.str();
		pLabel->setString(s.c_str());		
	}
};


// on "init" you need to initialize your instance
bool SplashScene::init()
{		
	greedygame::GreedyGameSDK::init(*(new AgentListener()));

    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // add "SplashScene" splash screen"
    CCSprite* pSprite = CCSprite::create("splash.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
    
    pLabel = CCLabelTTF::create("Loading...", "Arial", 48);
    pLabel->setPosition(ccp(visibleSize.width/2 + origin.x,
                            visibleSize.height/2 + origin.y - 200));
    pLabel->setColor(ccc3(0,0,0));
    this->addChild(pLabel, 1);


    return true;
}




