#include "AddressRequester.h"

using std::string;
using std::vector;

/**
 * @brief Constructor.
 * @details Constructor for AddressRequester that initializes all members.
 * @param lat is the latitude coordinate.
 * @param lon is the longitude coordinate.
 * @return Nothing.
 */
AddressRequester::AddressRequester(string lat, string lon)
{
    host =
        "https://maps.googleapis.com/maps/api/geocode/json?latlng=" + lat +
        "," + lon + "&key=AIzaSyBsaxHAEYOD0stq-0Smzwr1lGQ14KkOxKg";
}

/**
 * @brief Default destructor.
 * @details Default destructor for AddressRequester but does nothing.
 * @param nothing
 * @return Nothing.
 */
AddressRequester::~AddressRequester() {}

/**
 * @brief Get address API data.
 * @details Queries against the host API endpoint and returns
 * the data that was extracted as a table represented by 2d vector.
 * with columns separated by the data name/type.
 * @param request is the Request object.
 * @return the address data table as 2d vector.
 */
vector<vector<string>> AddressRequester::getData(Request *request)
{
    boost::property_tree::ptree ptLocation;
    std::stringstream result = GetRequest::query(request);
    boost::property_tree::read_json(result, ptLocation);
    auto itN = ptLocation;
    vector<vector<string>> all;
    vector<string> location;

    // parsing json
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            if (it3->first == "compound_code")
            {
                string code = it3->second.data();
                code = code.substr(code.find_first_of(" ") + 1);
                location.push_back(code);
                break;
            }
        }
    }
    all.push_back(location);
    return all;
}

/**
 * @brief Get host.
 * @details Returns the host address of the AddressRequester.
 * @param nothing
 * @return the host of the AddressRequester as string.
 */
string AddressRequester::getHost()
{
    return host;
}