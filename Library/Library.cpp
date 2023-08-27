#include "Library.h"

ManagingSystem Library::managingSystem() {
    ManagingSystem system(&db);
    return system;
}

SearchSystem Library::searchSystem() {
    SearchSystem searchSystem(&db);
    return searchSystem;
}

SortSystem Library::sortSystem() {
    SortSystem system(&db);
    return system;
}

Authentication Library::authSystem() {
    Authentication system(&db);
    return system;
}