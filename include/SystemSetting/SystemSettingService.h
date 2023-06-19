#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include "Event/Event.h"

class SystemSettingService
{
public:
    static SystemSettingService* instance();

    void connectService();

    void disconnectService();

    // Event<> connectEvent;

    // Event<> disconnectEvent;

private:
    SystemSettingService();

    ~SystemSettingService();
};

#endif