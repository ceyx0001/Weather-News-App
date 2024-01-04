/**
 * @brief Data object interface
 * @details The Data interface describes the behaviour of a Data object
 * @author Jun Shao
 */

#ifndef DATA_H
#define DATA_H

#include "db/Database.h"
#include <string>

class Data
{
public:
    /**
     * @brief Save data
     * @details Generic method to save some member data
     * @param nothing
     * @return nothing
     */
    virtual void saveData() = 0;

    /**
     * @brief Delete data
     * @details Generic method to delete some member data
     * @param nothing
     * @return nothing
     */
    virtual void delData() = 0;
};

#endif