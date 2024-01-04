#include "WeatherUI.h"

using std::string;
using std::cout;
using std::endl;
using std::make_unique;
using namespace Wt;

namespace
{
    const int HOURLY = 8; // # of forecasts per day from the API
    const int DAILY = 5; // # of forecasts per week from the API
    const int DATELEN = 11; // how many characters the date format is
    const int DATE = 0; // Date column in API data table
    const int MAX = 1; // Max temp column in API data table
    const int MIN = 2; // Min temp column in API data table
    const int TYPE = 3; // Weather type column in API data table
    const int COND = 4; // Condition column in API data table
}

/**
 * @brief Constructor.
 * @details Constructor for WeatherUI that initializes all members and renders the UI.
 * @param username is the session username.
 * @return Nothing.
 */
WeatherUI::WeatherUI(string username) : WContainerWidget(), username(username)
{
    // render weather forecast
    setStyleClass("text-white d-flex flex-row justify-content-center w-auto");

    // image map names to their paths
    icons["Clouds"] = "../images/weather/cloud.png";
    icons["Rain"] = "../images/weather/rain.png";
    icons["Snow"] = "../images/weather/snow.png";
    icons["Clear"] = "../images/weather/sun.png";

    LocationInfo info(username); // get session location information
    if (!info.getLat().empty())
    {
        // get weather API data table
        WeatherRequester *wr = new WeatherRequester(info.getLat(), info.getLon());
        Request r(wr->getHost(), wr);
        weather = r.getData();

        if (weather.size() > 0)
        {
            // render forecast
            const int LEN = weather.size();
            for (int i = 0; i < LEN; i++)
            {
                if (i % 8 == 0)
                {
                    // create day
                    WContainerWidget *day = this->addWidget(make_unique<WContainerWidget>());
                    day->setStyleClass("text-left mx-4 d-flex flex-column justify-content-between");
                    buildFeedItem(day, i);
                    days.push_back(day);
                }
            }
        }
        else
        {
            this->addWidget(make_unique<WText>("Save your location settings to display weather forecasts."));
        }
    }
    else
    {
        this->addWidget(make_unique<WText>("Save your location settings to display weather forecasts."));
    }
}

/**
 * @brief Default destructor.
 * @details Default destructor for WeatherUI but does nothing.
 * @return Nothing.
 */
WeatherUI::~WeatherUI() {}

/**
 * @brief Render one weather day.
 * @details Builds the element that renders one day of the weather forecast.
 * @param day is the container holding the graphical component.
 * @param index is the item index of the day in weather.
 * @return Nothing.
 */
void WeatherUI::buildFeedItem(WContainerWidget *day, const int index)
{
    WText *date = day->addWidget(make_unique<WText>(weather[index][DATE].substr(0, DATELEN)));

    WContainerWidget *mid = day->addWidget(make_unique<WContainerWidget>());
    mid->setStyleClass("text-left d-flex flex-row");

    WImage *image = mid->addWidget(make_unique<WImage>(WLink(icons[weather[index][TYPE]])));
    image->setWidth(50);
    image->setHeight(50);

    WContainerWidget *temperature = mid->addWidget(make_unique<WContainerWidget>());
    temperature->setStyleClass("d-flex flex-column text-center");
    WText *high = temperature->addWidget(make_unique<WText>(weather[index][MAX] + "°"));
    high->setStyleClass("px-3 high-font");
    WText *low = temperature->addWidget(make_unique<WText>(weather[index][MIN] + "°"));
    low->setStyleClass("low-font");

    WText *condition = day->addWidget(make_unique<WText>(weather[index][COND]));
}