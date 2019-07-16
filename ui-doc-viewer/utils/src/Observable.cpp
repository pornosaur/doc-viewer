//
// Created by pornosaur on 4.4.19.
//

#include <QtCore/QMetaMethod>
#include "Observable.h"

using namespace utils;

Observable::~Observable() {
    for (auto it : observer_list) {
        delete it;
    }

    observer_list.clear();
}

void Observable::subscribe(Observer *observer) {
    std::lock_guard<std::mutex> lock(list_mutex);
    observer_list.emplace_back(observer);
}

void Observable::subscribe_and_connect(Observer *observer, QObject *obj) {
    subscribe(observer);

    const QMetaObject *meta = obj->metaObject();

    for (int i = meta->methodOffset(); i < meta->methodCount(); ++i) {
        QMetaMethod method = meta->method(i);

        //TODO: do later!
    }
}

void Observable::unsubscribe(Observer *observer) {
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

void Observable::notify(void *data, NotifyType type) {
    for (auto it : observer_list) {
        it->update(data);
    }
}