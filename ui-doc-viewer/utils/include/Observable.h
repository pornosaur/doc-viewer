//
// Created by pornosaur on 4.4.19.
//

#ifndef PROJECT_OBSERVABLE_H
#define PROJECT_OBSERVABLE_H

#include <vector>
#include <mutex>
#include <memory>
#include <QtCore/QObject>

#include "Observer.h"

namespace utils {

    enum NotifyType {
        NONE,
    };

    class Observable {

    private:
        std::vector<Observer *> observer_list;
        std::mutex list_mutex;

    public:
        ~Observable();

        virtual void connect_signals() = 0;

        void notify(void *data, NotifyType type);

        void subscribe_and_connect(Observer *observer, QObject *obj);

        void subscribe(Observer *observer);

        void unsubscribe(Observer *observer);
    };

}

#endif //PROJECT_OBSERVABLE_H
