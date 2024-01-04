#include "WeatherRequester.h"
#include "Request.h"

using std::put_time;
using std::string;
using std::stringstream;
using std::vector;

/**
 * @brief Constructor.
 * @details Constructor for WeatherRequester that initializes all members.
 * @return Nothing.
 */
WeatherRequester::WeatherRequester(string lat, string lon)
{
    host = "https://api.openweathermap.org/data/2.5/forecast?lat=" + lat + "&lon=" + lon + "&appid=869a570166961fb2a676c717eb550b92&units=metric";
}

/**
 * @brief Default destructor.
 * @details Default destructor for WeatherRequester but does nothing.
 * @param nothing
 * @return Nothing.
 */
WeatherRequester::~WeatherRequester() {}

/**
 * @brief Get weather API data.
 * @details Queries against the host API endpoint and returns
 * the data that was extracted as a table represented by 2d vector.
 * with columns separated by the data name/type.
 * @param request is the Request object.
 * @return the weather data table as 2d vector.
 */
vector<vector<string>> WeatherRequester::getData(Request *request)
{
    boost::property_tree::ptree ptWeather;
    stringstream result = GetRequest::query(request);
    boost::property_tree::read_json(result, ptWeather);
    auto itW = ptWeather.get_child("list");
    vector<vector<string>> forecast;
    for (auto it2 = itW.begin(); it2 != itW.end(); ++it2)
    {
        vector<string> daily;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            if (it3->first == "dt")
            {
                // std::cout << it3->first; // [1]
                time_t rawtime;
                rawtime = strtoul(it3->second.data().c_str(), NULL, 0);
                stringstream ss;
                time_t const now_c = time(NULL);
                ss << put_time(std::localtime(&rawtime), "%c %Z");
                daily.push_back(ss.str());
            }
            else if (it3->first == "main")
            {
                // std::cout << it3->first; // [1]
                // std::cout << " : " << it3->second.data() << std::endl;
                for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
                {
                    if (it4->first == "temp")
                    {
                        // std::cout << "\t" << it4->first; // [1]
                        daily.push_back(it4->second.data());
                    }
                    else if (it4->first == "feels_like")
                    {
                        // std::cout << "\t" << it4->first; // [1]
                        daily.push_back(it4->second.data());
                    }
                }
            }

            else if (it3->first == "weather")
            {
                // std::cout << it3->first << " :" << std::endl;
                for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "main")
                        {
                            // std::cout << "\t" << it5->first; // [1]
                            daily.push_back(it5->second.data());
                        }
                        if (it5->first == "description")
                        {
                            // std::cout << "\t" << it5->first; // [1]
                            daily.push_back(it5->second.data());
                        }
                    }
                }
            }
        }
        forecast.push_back(daily);
        // [2]
    }
    return forecast;
}

/**
 * @brief Get host.
 * @details Returns the host address of the WeatherRequester.
 * @param nothing
 * @return the host of the WeatherRequester as string.
 */
string WeatherRequester::getHost()
{
    return host;
}
