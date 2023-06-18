#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include "Event/CallbackEvent.h"

class SystemSettingService
{
public:
    void connectService();

    void disconnectService();

    CallbackEvent<void()> connectEvent;

    CallbackEvent<void()> disconnectEvent;

private:
    SystemSettingService();

    ~SystemSettingService();
};

#endif