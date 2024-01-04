#include "NewsRequester.h"
#include "Request.h"

using std::string;
using std::stringstream;
using std::vector;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace
{
    string clean(string date)
    {
        replace(date.begin(), date.end(), 'T', ' ');
        date.erase(remove(date.begin(), date.end(), 'Z'), date.end());

        // boost utc to local conversion: https://www.boost.org/doc/libs/1_31_0/libs/date_time/doc/exp-local_utc_conversion.html
        // eastern timezone is utc-5
        typedef boost::date_time::local_adjustor<ptime, -5, us_dst> us_eastern;
        ptime t(time_from_string(date));
        ptime est = us_eastern::utc_to_local(t);
        date = to_simple_string(est);
        string cal, time;
        stringstream s(date);
        s >> cal >> time;
        time = time.substr(0, time.find_last_of(':'));
        cal = cal.substr(cal.find("-") + 1);
        replace(cal.begin(), cal.end(), '-', ' ');
        return cal + " " + time;
    }
}

/**
 * @brief Constructor.
 * @details Constructor for NewsRequester that initializes all members.
 * @return Nothing.
 */
NewsRequester::NewsRequester()
{
    headers.push_back("User-Agent: myproject");
    host = "https://newsapi.org/v2/top-headlines?country=ca&apiKey=4e6f18ed836d4194ac55c12097e5d6ca";
}

/**
 * @brief Default destructor.
 * @details Default destructor for NewsRequester but does nothing.
 * @param nothing
 * @return Nothing.
 */
NewsRequester::~NewsRequester() {}

/**
 * @brief Get news API data.
 * @details Queries against the host API endpoint and returns
 * the data that was extracted as a table represented by 2d vector.
 * with columns separated by the data name/type.
 * @param request is the Request object.
 * @return the news data table as 2d vector.
 */
vector<vector<string>> NewsRequester::getData(Request *request)
{
    boost::property_tree::ptree ptNews;
    std::stringstream result = GetRequest::query(request);
    boost::property_tree::read_json(result, ptNews);
    auto itN = ptNews;
    vector<vector<string>> all;
    for (auto it2 = itN.begin(); it2 != itN.end(); ++it2)
    {
        // std::cout << it2->first; // [1]
        //  std::cout << " : " << it2->second.data() << std::endl;
        for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3)
        {
            vector<string> article;
            // std::cout << " : " << it3->second.data() << std::endl;
            for (auto it4 = it3->second.begin(); it4 != it3->second.end(); ++it4)
            {
                if (it4->first == "source")
                {
                    for (auto it5 = it4->second.begin(); it5 != it4->second.end(); ++it5)
                    {
                        if (it5->first == "name")
                        {
                            // std::cout << it5->first; // [1]
                            article.push_back(it5->second.data());
                        }
                    }
                }
                else if (it4->first == "title")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "url")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "urlToImage")
                {
                    // std::cout << it4->first; // [1]
                    article.push_back(it4->second.data());
                }
                else if (it4->first == "publishedAt")
                {
                    article.push_back(clean(it4->second.data()));
                }
            }
            all.push_back(article);
        }
    }
    return all;
}

/**
 * @brief Get host.
 * @details Returns the host address of the NewsRequester.
 * @param nothing
 * @return the host of the NewsRequester as string.
 */
string NewsRequester::getHost()
{
    return host;
}

/**
 * @brief Get headers.
 * @details Returns the headers of NewsRequester.
 * @param nothing
 * @return the headers of the NewsRequester as string.
 */
std::list<std::string> NewsRequester::getHeaders()
{
    return headers;
}
