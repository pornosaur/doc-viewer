//
// Created by pornosaur on 4.4.19.
//

#ifndef PROJECT_OBSERVER_H
#define PROJECT_OBSERVER_H

class Observer {
public:
    virtual ~Observer() {};
    virtual void update() = 0;
};

#endif //PROJECT_OBSERVER_H
