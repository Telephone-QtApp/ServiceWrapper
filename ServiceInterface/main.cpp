#include "common/signal.h"
#include <iostream>

class Service
{
public:
    signal::Signal<void()> onStateChanged;
    void requestChangeState()
    {
        onStateChanged();
    }
};

class Application
{
    signal::Connect m_connectSlot {nullptr};
    Service* m_service {nullptr};
public:
    Application()
    {
        m_service = new Service();
        m_connectSlot = m_service->onStateChanged.connect([&]() {
            std::cout << "State Changed";
        });
    }
    void requestChangeState()
    {
        std::cout << "request Changed State\n";
        m_service->requestChangeState();
    }
};

int main()
{
    Application app;
    app.requestChangeState();
    return 0;
}