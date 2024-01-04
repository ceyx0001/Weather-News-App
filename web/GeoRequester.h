/**
 * @brief Geolocation API requester.
 * @details Contains the algorithms of sending
 * requests to a geolocation API and parsing the geo-coordinate data.
 * @author Jun Shao
 */

#ifndef GEOREQUESTER_H
#define GEOREQUESTER_H

#include <boost/algorithm/string/replace.hpp>
#include "Requester.h"
#include "Request.h"

class GeoRequester : public Requester
{
private:
    std::string host;

public:
    std::vector<std::vector<std::string>> getData(Request *request);
    std::string getHost();
    GeoRequester(std::string location);
    GeoRequester(std::string lat, std::string lon);
    ~GeoRequester();
};

#endif