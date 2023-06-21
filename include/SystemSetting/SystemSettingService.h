#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include "AbstractService.h"

extern char const* SERVICE_NAME;

class SystemSettingService : public AbstractService
{
public:
    static SystemSettingService* instance();

    void connectService();

    void disconnectService();

private:
    SystemSettingService();

    ~SystemSettingService();
};

#endif
