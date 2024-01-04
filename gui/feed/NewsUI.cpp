#include "NewsUI.h"

using std::string;
using std::cout;
using std::endl;
using std::make_unique;
using namespace Wt;

namespace
{
    const int PUBLISHER = 0; // Publisher column from data table
    const int TITLE = 1; // Title column in API data table
    const int LINK = 2; // Publisher column in API data table
    const int IMG = 3; // Image column in API data table
    const int DATE = 4; // Date column in API data table
}

/**
 * @brief Default destructor.
 * @details Default destructor for NewsUI but does nothing
 * @return Nothing.
 */
NewsUI::~NewsUI() {}

/**
 * @brief Constructor.
 * @details Constructor for NewsUI that initializes all members and renders the UI.
 * @return Nothing.
 */
NewsUI::NewsUI() : WContainerWidget()
{
    // render news feed
    setStyleClass("text-white newsfeed mt-4 content");

     // get news API data table
    NewsRequester *nr = new NewsRequester();
    Request r(nr->getHost(), nr->getHeaders(), nr);
    news = r.getData();

    if (news.size() > 0)
    {
        // render news articles
        for (int i = 0; i < news.size(); i++)
        {
            // create one article
            if (news[i][IMG] != "null") {
                WContainerWidget *article = this->addWidget(make_unique<WContainerWidget>());
                buildFeedItem(article, i);
            }
        }
    } else {
        this->addWidget(make_unique<WText>("Too many News API calls: Limited to 100 per day."));
    }
}

/**
 * @brief Render one news article.
 * @details Builds the element that renders one news article of the day.
 * @param article is the container holding the graphical component.
 * @param index is the item index of the article news.
 * @return Nothing.
 */
void NewsUI::buildFeedItem(WContainerWidget *article, const int index)
{
    article->setStyleClass("newscolor d-flex flex-column");

    // Create an anchor that links to a URL through an image.
    WLink link = WLink(news[index][LINK]);
    link.setTarget(LinkTarget::NewWindow);
    WAnchor *anchor = article->addWidget(make_unique<WAnchor>(link));
    WImage *image = anchor->addNew<WImage>(WLink(news[index][IMG]));
    image->setStyleClass("img-fluid");

    WContainerWidget *publish = article->addWidget(make_unique<WContainerWidget>());
    publish->setStyleClass("d-flex flex-row px-2 text-left mt-4 mb-3");
    WText *site = publish->addWidget(make_unique<WText>(news[index][PUBLISHER]));
    site->setStyleClass("p-2");
    WText *date = publish->addWidget(make_unique<WText>(news[index][DATE]));
    date->setStyleClass("p-2 pl-2 low-font");

    WText *title = article->addWidget(make_unique<WText>(news[index][TITLE]));
    title->setStyleClass("px-3 mb-3 high-font");
}