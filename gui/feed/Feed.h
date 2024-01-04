/**
 * @brief Creating feed content.
 * @details Feed describes the behaviour for rendering feed containers
 * @author Jun Shao
 */

#ifndef FEED_H
#define FEED_H

#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WImage.h>
#include <Wt/WFont.h>
#include <vector>
#include "../../data/location/LocationInfo.h"
#include "../../web/Request.h"

class Feed
{
public:
    /**
     * @brief Render generic feed item.
     * @details Builds the feed item that renders one element of the feed.
     * @param item is the container holding the graphical component.
     * @param index is the container position inside the feed.
     * @return Nothing.
     */
    virtual void buildFeedItem(Wt::WContainerWidget *item, const int index) = 0;
};

#endif