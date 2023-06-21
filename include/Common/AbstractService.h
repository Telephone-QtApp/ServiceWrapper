#ifndef ABSTRACTSERVICE_H
#define ABSTRACTSERVICE_H

#include "Event/CallbackEvent.h"

class AbstractService
{
public:
    AbstractService();

    ~AbstractService();

    CallbackEvent<std::function<void()>> connectEvent;

    CallbackEvent<std::function<void()>> disconnectEvent;

protected:
    char const *SERVICE_NAME = "";
};

#endif