#include "SmartPhoneService.h"
#include "Logger/Logger.h"

SmartPhoneService::SmartPhoneService()
{
    SERVICE_NAME = "SmartPhoneService";
}

SmartPhoneService::~SmartPhoneService()
{
}

SmartPhoneService *SmartPhoneService::instance()
{
    static SmartPhoneService *ins = new SmartPhoneService();
    return ins;
}

void SmartPhoneService::connectService()
{
    LOG_INFO("[%s] Connect Service", SERVICE_NAME);

    connectEvent.emitEvent();
}

void SmartPhoneService::disconnectService()
{
    LOG_INFO("[%s] Disconnect Service", SERVICE_NAME);

    disconnectEvent.emitEvent();
}