//
// Created by pornosaur on 4.4.19.
//

#ifndef PROJECT_OBSERVABLE_H
#define PROJECT_OBSERVABLE_H

#include <vector>
#include <mutex>

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
        virtual ~Observable();

        virtual void notify(void *data, NotifyType type);

        void subscribe(Observer *observer);

        void unsubscribe(Observer *observer);
    };
};

#endif //PROJECT_OBSERVABLE_H
