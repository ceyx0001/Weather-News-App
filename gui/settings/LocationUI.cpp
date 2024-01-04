#include "LocationUI.h"

using std::find;
using std::make_unique;
using namespace Wt;

/**
 * @brief Constructor.
 * @details Constructor for LocationUI that initializes all members and renders the UI.
 * @param username is the session username.
 * @return Nothing.
 */
LocationUI::LocationUI(string username) : WContainerWidget(), username(username)
{
    // render location page
    setHeight(900);
    WLabel *help =
        this->addWidget(make_unique<WLabel>("Enter your location information, or click on the map, and press save to utilize location services such as showing the weather."));
    help->setStyleClass("text-white mt-4 mx-5");
    WContainerWidget *top = this->addWidget(make_unique<WContainerWidget>());
    top->setStyleClass("mx-5 mt-5 d-flex flex-row");
    WLineEdit *location = top->addWidget(make_unique<WLineEdit>());
    location->setWidth(500);
    location->enterPressed().connect([=]
                                     { this->pan(location->text().toUTF8()); });
    auto validator = make_shared<WValidator>(true);
    location->setValidator(validator);

    WPushButton *view = top->addWidget(make_unique<WPushButton>("View on map"));
    view->clicked().connect([=]
                            { this->pan(location->text().toUTF8()); });

    WPushButton *save = top->addWidget(make_unique<WPushButton>("Save"));
    save->clicked().connect([=]
                            {
        pan(location->text().toUTF8());
        this->saveLocation(); });
    save->setStyleClass("mx-5");

    location->setPlaceholderText("Enter a location...");

    WContainerWidget *maparea = this->addWidget(make_unique<WContainerWidget>());
    maparea->setHeight(900);
    WVBoxLayout *layout = maparea->setLayout(make_unique<WVBoxLayout>());
    map = layout->addWidget(make_unique<WGoogleMap>(GoogleMapsVersion::v3));
    map->setMapTypeControl(MapTypeControl::Default);
    map->enableScrollWheelZoom();
    map->enableDoubleClickZoom();
    map->enableDragging();
    map->clicked().connect([=](WGoogleMap::Coordinate c)
                           { this->googleMapClicked(c); });
    map->setStyleClass("mx-3 mt-3");
}

/**
 * @brief Default destructor.
 * @details Default destructor for LocationUI but does nothing.
 * @return Nothing.
 */
LocationUI::~LocationUI() {}

/**
 * @brief Clicking google map event.
 * @details Updates LocationUI to point to the new coordinates where
 * the user clicked on the Google map.
 * @param c is the Google map coordinate.
 * @return Nothing.
 */
void LocationUI::googleMapClicked(WGoogleMap::Coordinate c)
{
    map->clearOverlays();
    map->addMarker(WGoogleMap::Coordinate(c.latitude(), c.longitude()));
    _lat = c.latitude();
    _lon = c.longitude();
    cout << "MAPS COORDINATE SAVE:" << endl;
    cout << "lat: " << _lat << endl;
    cout << "lon: " << _lon << endl;
}

/**
 * @brief Save location event.
 * @details Updates the user's location information after they click on save.
 * @return Nothing.
 */
void LocationUI::saveLocation()
{
    LocationInfo l(username);
    l.changeLocation(_lat, _lon);
    this->notify();
}

/**
 * @brief Pan on map.
 * @details Updates the Google map to pan to the location.
 * @param location is the keyword of the location to pan to.
 * @return Nothing.
 */
void LocationUI::pan(string location)
{
    // get location API data
    GeoRequester *gr = new GeoRequester(location);
    Request r(gr->getHost(), gr);
    vector<vector<string>> loc = r.getData();

    if (loc.size() > 0)
    {
        // pan on Google map
        double lat = stod(loc[0][0]);
        double lon = stod(loc[0][1]);
        map->panTo(WGoogleMap::Coordinate(lat, lon));
        map->addMarker(WGoogleMap::Coordinate(lat, lon));
        _lat = lat;
        _lon = lon;
    }
}
