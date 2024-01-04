/**
 * @brief News UI
 * @details NewsUI encapsulates behaviours for rendering all
 * of the daily news articles and getting this information.
 * @author Jun Shao
 */

#ifndef NEWSUI_H
#define NEWSUI_H

#include <Wt/WAnchor.h>
#include <Wt/WRectArea.h>
#include <string>
#include "Feed.h"
#include "../../web/NewsRequester.h"

class NewsUI : public Wt::WContainerWidget, public Feed {
    private:
        std::vector<Wt::WContainerWidget *> articles;
        std::vector<std::vector<std::string>> news;
        void buildFeedItem(Wt::WContainerWidget *article, const int index);

    public:
        NewsUI();
        ~NewsUI();

};

#endif