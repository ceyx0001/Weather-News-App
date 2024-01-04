/**
 * @brief Creating and using GET requests
 * @details Creates GET requests which is then queried against an API 
 * from the Request contexts to and returns the data to clients
 * @author Saud Rehman
 */

#ifndef GETREQUEST_H
#define GETREQUEST_H

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include "Request.h"

namespace GetRequest
{
    std::stringstream query(Request *request);
}

#endif