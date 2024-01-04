/**
 * @brief Weather UI
 * @details NewsUI encapsulates behaviours for rendering the weather
 * forecast for the week and getting this information.
 * @author Jun Shao
 */

#ifndef WEATHERUI_H
#define WEATHERUI_H 

#include <unordered_map>
#include "../../web/WeatherRequester.h"
#include "../../data/location/LocationInfo.h"
#include "Feed.h"

class LocationInfo;

class WeatherUI : public Wt::WContainerWidget, public Feed {
    private:
        std::string username;
        std::vector<Wt::WContainerWidget *> days;
        std::vector<std::vector<std::string>> weather;
        std::unordered_map<std::string, std::string> icons;
        void buildFeedItem(Wt::WContainerWidget *day, const int index);

    public:
        WeatherUI(std::string username);
        ~WeatherUI();
};

#endif