//
// Created by pornosaur on 4.4.19.
//

#include "Observable.h"

void utils::Observable::subscribe(Observer *observer) {
    std::lock_guard<std::mutex> lock(list_mutex);
    observer_list.emplace_back(observer);
}

void utils::Observable::unsubscribe(Observer *observer) {
    std::lock_guard<std::mutex> lock(list_mutex);

    auto item = observer_list.end();
    for (auto it = observer_list.begin(); it != observer_list.end(); ++it) {
        if ((*it) == observer) {
            item = it;
            break;
        }
    }

    if (item != observer_list.end()) observer_list.erase(item);
}