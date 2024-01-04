#include "GetRequest.h"

using namespace curlpp::options;

/**
 * @brief Query API endpoint and return response
 * @details Queries the host of a Request and returns the response
 * @param request is the API request context
 * @return The stringstream containing the API response.
 */
std::stringstream GetRequest::query(Request* request)
{
    std::stringstream ss;
    try
    {
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;

        // Our request to be sent.
        curlpp::Easy myRequest;

        // Set the URL.
        curlpp::options::Url myUrl(request->getHost());
        // myRequest.setOpt<curlpp::options::Url>(hostname);
        myRequest.setOpt(new HttpHeader(request->getHeaders()));
        myRequest.setOpt(myUrl);

        // Send request and get a result.
        // By default the result goes to standard output.
        // myRequest.perform();

        // curlpp::options::WriteStream ws(&os);
        // myRequest.setOpt(ws);
        // myRequest.perform();
        ss << myRequest;

        // boost::property_tree::ptree pt;
        // boost::property_tree::read_json(ss, pt);

        //std::cout << ss.str() << std::endl;
        // std::cout << pt.get_child << std::endl;
    }

    catch (curlpp::RuntimeError &e)
    {
        std::cout << e.what() << std::endl;
    }

    catch (curlpp::LogicError &e)
    {
        std::cout << e.what() << std::endl;
    }
    return ss;
}