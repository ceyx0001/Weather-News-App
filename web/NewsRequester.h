/**
 *  @author Saud Rehman
 * 251025014
 * @date November 29 2022
 * @brief Contains logic to make request to news api and return data in usable format
 */

#ifndef NEWSREQUESTER_H
#define NEWSREQUESTER_H

#include <chrono>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include "Requester.h"

class Request;

class NewsRequester : public Requester {
    private:
        std::string host;
        std::list<std::string> headers;

    public:
        std::vector<std::vector<std::string>> getData(Request* request);
        std::string getHost();
        std::list<std::string> getHeaders();
        NewsRequester();
        ~NewsRequester();
};

#endif