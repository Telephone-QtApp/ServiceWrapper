#ifndef SMARTPHONESERVICE_H
#define SMARTPHONESERVICE_H

#include "AbstractService.h"

class SmartPhoneService : public AbstractService
{
public:
    static SmartPhoneService *instance();

    void connectService();

    void disconnectService();

private:
    SmartPhoneService();

    ~SmartPhoneService();
};

#endif
