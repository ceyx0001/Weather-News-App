/**
 * @brief Context object for an API request
 * @details Request is the context object holding information 
 * needed for an API request to an endpoint and 
 * the functionalities for executing a set request algorithm
 * @author Jun Shao
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <list>
#include <vector>

class Requester;

class Request
{
public:
    Request(std::string host, Requester *);
    Request(std::string host, std::list<std::string> headers, Requester *);
    ~Request();
    void setRequester(Requester *);
    void setHost(std::string host);
    void setHeaders(std::list<std::string> headers);
    std::vector<std::vector<std::string>> getData();
    std::string getHost();
    std::list<std::string> getHeaders();

private:
    std::string _host;
    Requester *_requester;
    std::list<std::string> _headers;
};

#endif