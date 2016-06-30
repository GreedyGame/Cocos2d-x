
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>

using namespace std;




namespace greedygame {

    const int CAMPAIGN_NOT_AVAILABLE = -1;
    const int CAMPAIGN_AVAILABLE = 1;

    class IAgentListener {
        public:
            virtual void onInit(int event){};
            virtual void onDownload(){};
            virtual void onError(){};
            virtual void onProgress(float progress){};
    };

    class GreedyGameAgent {


        public:

            static void init(IAgentListener *agentListener);

            static void setDebugLog(bool b);

            static std::string getActivePath();

            static std::string getActiveUnitById(const char *unit_id);

            static std::string getActiveUnitByName(const char *unit_id);

            static void fetchFloatAd(const char *unit_id);

            static void removeFloatAd();
            
            static void showEngagementWindow(const char *unit_id);

            static void forcedExit();
 
    };
}


#endif
