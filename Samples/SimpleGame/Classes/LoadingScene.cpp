#include "LoadingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GreedyGameAgent.h"

USING_NS_CC;


class AgentListener : public greedygame::IAgentListener {
    public:
        void onInit(int response){
            if (response == greedygame::CAMPAIGN_AVAILABLE) {
            /**
             * TODO: Campaign is available is downloading in background. 
             * Progress can be shown.
             **/

            } else if (response == greedygame::CAMPAIGN_NOT_AVAILABLE) {
            /**
             * TODO: Not campaign is available, procede with normal follow of game.
             **/
                auto scene = HelloWorld::createScene();
                auto director = Director::getInstance();
                director->replaceScene(scene);
            }
        };

        void onProgress(float progress){
        /**
         * TODO: progress will show value from o to 100,
         * which can be used to render loading bar.
         **/
        };

        void onDownload(){
          /**
           * TODO: New campaign has been loaded, move to next scene
           **/
            auto scene = HelloWorld::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);

          /**
           * TODO: getActivePath can be added to searchpath to renderer all NativeUnits in single hook
           **/
           std::string path = greedygame::GreedyGameAgent::getActivePath();
          FileUtils::getInstance ()->addSearchPath(path.c_str());

        };

        void onError(){
          /**
           * TODO: There is some error while fetching campaign. Please see the application running logs
           * to identify the cause.
           **/
            auto scene = HelloWorld::createScene();
            auto director = Director::getInstance();
            director->replaceScene(scene);
        };

};


Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    greedygame::GreedyGameAgent::init(new AgentListener());

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "Loading" splash screen"
    auto sprite = Sprite::create("loading.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

