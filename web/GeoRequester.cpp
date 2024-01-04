#include "GeoRequester.h"

using std::string;
using std::vector;

/**
 * @brief Default destructor
 * @details Default destructor for GeoRequester but does nothing
 * @param nothing
 * @return nothing
 */
GeoRequester::~GeoRequester() {}

/**
 * @brief Constructor
 * @details Constructor for GeoRequester that initializes all members
 * @param location is the location keyword
 * @return nothing
 */
GeoRequester::GeoRequester(string location)
{
    boost::replace_all(location, " ", "%20");
    host =
        "https://maps.googleapis.com/maps/api/geocode/json?address=" + location +
        "&key=AIzaSyBsaxHAEYOD0stq-0Smzwr1lGQ14KkOxKg";
}

/**
 * @brief Get geo-coordinate API data.
 * @details Queries against the host API endpoint and returns
 * the data that was extracted as a table represented by 2d vector.
 * with columns separated by the data name/type.
 * However, there is only 1 row as the request is for 1 location.
 * @param request is the Request object.
 * @return the geo-coordinate data table as 2d vector.
 */
vector<vector<string>> GeoRequester::getData(Request *request)
{
    boost::property_tree::ptree ptLocation;
    std::stringstream result = GetRequest::query(request);
    boost::property_tree::read_json(result, ptLocation);
    auto itN = ptLocation;
    vector<vector<string>> all;
    vector<string> coordinates;

    // parsing json object
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        // std::cout << it2->first; // [1]
        //  std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            // std::cout << " : " << it3->second.data() << std::endl;
            for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
            {
                if (it4->first == "geometry")
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "location")
                        {
                            for (auto it6 = it5->second.begin(); it6 != it5->second.end(); ++it6)
                            {
                                coordinates.push_back(it6->second.data());
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    all.push_back(coordinates);
    return all;
}

/**
 * @brief Get host.
 * @details Returns the host address of the AddressRequester.
 * @param nothing
 * @return the host of the AddressRequester as string.
 */
string GeoRequester::getHost()
{
    return host;
}