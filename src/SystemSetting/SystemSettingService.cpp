#include "SystemSettingService.h"
#include "Logger/Logger.h"

SystemSettingService::SystemSettingService()
{
    SERVICE_NAME = "SystemSettingService";
}

SystemSettingService::~SystemSettingService()
{
}

SystemSettingService *SystemSettingService::instance()
{
    static SystemSettingService *ins = new SystemSettingService();
    return ins;
}

void SystemSettingService::connectService()
{
    LOG_INFO("[%s] Connect Service", SERVICE_NAME);

    connectEvent.emitEvent();
}

void SystemSettingService::disconnectService()
{
    LOG_INFO("[%s] Disconnect Service", SERVICE_NAME);

    disconnectEvent.emitEvent();
}