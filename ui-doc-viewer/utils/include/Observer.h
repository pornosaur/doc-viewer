//
// Created by pornosaur on 4.4.19.
//

#ifndef PROJECT_OBSERVER_H
#define PROJECT_OBSERVER_H

#include <QtCore>

class Observer : public QObject {
    Q_OBJECT

public:
    virtual void update(void *data) = 0;
};



#endif //PROJECT_OBSERVER_H
