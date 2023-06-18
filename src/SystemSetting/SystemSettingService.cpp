#include "SystemSettingService.h"
#include "Logger/Logger.h"

char const* SERVICE_NAME = "SystemSettingService";

SystemSettingService::SystemSettingService()
{

}

SystemSettingService::~SystemSettingService()
{

}

void SystemSettingService::connectService()
{
    LOG_INFO("[%s] Connect Service", SERVICE_NAME);

    connectEvent.emit();
}

void SystemSettingService::disconnectService()
{
    LOG_INFO("[%s] Disconnect Service", SERVICE_NAME);

    disconnectEvent.emit();
}