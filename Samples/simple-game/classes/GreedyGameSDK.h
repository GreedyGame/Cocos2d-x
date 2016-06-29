
/****************************************************************************
 Copyright (c) 2014  GreedyGame
 
 http://www.greedygame.com
 
 ****************************************************************************/

#ifndef GreedyGameSDK_h
#define GreedyGameSDK_h

#include <iostream>
#include <vector>

using namespace std;

#define CAMPAIGN_NOT_AVAILABLE -1
#define CAMPAIGN_AVAILABLE 1

namespace greedygame {

    class IAgentListener {
        public:
            virtual void onInit(int event);
            virtual void onDownload();
            virtual void onError();
            virtual void onProgress(float progress);
    };

    class GreedyGameSDK {
        IAgentListener *listener;

        public:

            static void init(IAgentListener *agentListener);

            static void setPath();

            static void setDebug(bool b);

            static std::string getActiveUnitById(const char *unit_id);

            static std::string getActiveUnitByName(const char *unit_id);

            static void fetchAdHead(const char *unit_id);

            static void removeAdHead();
            
            static void showEngagementWindow(const char *unit_id);

            static std::string getActivePath();

            static void forcedExit();
 
    };
}


#endif
