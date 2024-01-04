/**
 * @brief Location settings page UI
 * @details LocationUI encapsulates the behaviour for rendering
 * the location settings page UI and listens to user input
 * to update their location information.
 * @author Jun Shao
 */

#ifndef LOCATIONUI_H
#define LOCATIONUI_H

#include <Wt/WContainerWidget.h>
#include <Wt/WValidator.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WGoogleMap.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include <string>
#include "Subject.h"
#include "../../data/location/LocationInfo.h"
#include "../../web/GeoRequester.h"

using namespace std;
using namespace Wt;

class LocationUI : public Wt::WContainerWidget, public Subject
{
private:
    std::string username;
    Wt::WGoogleMap *map;
    double _lat;
    double _lon;
    void googleMapClicked(Wt::WGoogleMap::Coordinate c);
    void pan(std::string location);
    void saveLocation();

public:
    LocationUI(std::string username);
    ~LocationUI();
};

#endif