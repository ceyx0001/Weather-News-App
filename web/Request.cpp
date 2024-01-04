#include "Request.h"
#include "Requester.h"

using std::list;
using std::string;
using std::vector;

/**
 * @brief Constructor.
 * @details Constructor for Request that initializes all members except
 * the request headers
 * @param host is the API host address
 * @param requester is a Requester
 * @return Nothing.
 */
Request::Request(string host, Requester *requester) : _host(host), _requester(requester)
{
}

/**
 * @brief Constructor.
 * @details Constructor for Request that initializes all members.
 * @param host is the API host address.
 * @param requester is a Requester.
 * @param headers is the required headers in the API request.
 * @return Nothing.
 */
Request::Request(string host, list<string> headers, Requester *requester) : _host(host), _requester(requester), _headers(headers)
{
}

/**
 * @brief Default destructor.
 * @details Default destructor for Request that deletes its Requester.
 * @return Nothing.
 */
Request::~Request()
{
    delete this->_requester;
}

/**
 * @brief Set a Requester.
 * @details Changes the Requester of the Request which
 * functionally means that the algorithm used by Request is updated.
 * @param requester is the new Requester.
 * @return Nothing.
 */
void Request::setRequester(Requester *requester)
{
    delete this->_requester;
    this->_requester = requester;
}


/**
 * @brief Set headers.
 * @details Changes the headers of Request
 * @param headers is the list of new headers required for the API request.
 * @return Nothing.
 */
void Request::setHeaders(list<string> headers)
{
    this->_headers = headers;
}

/**
 * @brief Set host.
 * @details Changes the host of Request
 * @param host is the new host address.
 * @return Nothing.
 */
void Request::setHost(string host)
{
    this->_host = host;
}

/**
 * @brief Get host.
 * @details Returns the host address of the Request
 * @return The host address of Request.
 */
string Request::getHost()
{
    return _host;
}

/**
 * @brief Get headers.
 * @details Returns the headers of the Request
 * @return The headers of Request.
 */
list<std::string> Request::getHeaders()
{
    return _headers;
}

/**
 * @brief Get data.
 * @details Returns the result of the API request to a host endpoint
 * as a data table represented by a 2d vector.
 * @return The resulting API request data in a table as 2d vector.
 */
vector<vector<string>> Request::getData()
{
    return this->_requester->getData(this);
}