/**
 * @brief Strategy interface for API requests
 * @details Requester is the interface that allows for
 * the separation of algorithm classes from clients that use them
 * @author Jun Shao
 * @author Saud Rehman
 */

#ifndef REQUESTER_H
#define REQUESTER_H
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include "GetRequest.h"

class Request;

class Requester
{
public:
    /**
     * @brief Get API data.
     * @details Returns the API response stored in a data table of 2d vector form
     * with keys as headers
     * @param request is the Request context
     * @return The API response data table in 2d vector form.
     */
    virtual std::vector<std::vector<std::string>> getData(Request *request) = 0;

    /**
     * @brief Get API host.
     * @details Returns the API host address of the Requester
     * @return The API host address of the requester.
     */
    virtual std::string getHost() = 0;
};

#endif