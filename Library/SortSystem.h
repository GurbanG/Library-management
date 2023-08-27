#pragma once

#include <iostream>
#include "ManagingSystem.h"

class SortSystem {
private:
    DATABASE *db;
public:
    SortSystem(DATABASE *dp);

    void sortByName();

    void sortByGenre();

    void sortByPopularity();
};
