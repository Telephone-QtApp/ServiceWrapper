#include "ServiceEngine.h"

using time_clock = std::chrono::system_clock;

ServiceEngine::ServiceEngine()
    : m_thread(std::bind(&ServiceEngine::processLoop, this))
{
    m_thread.detach();
}

ServiceEngine::~ServiceEngine()
{
    m_isFirstProcess = false;
    m_isThreadRunning = false;
}

ServiceEngine *ServiceEngine::instance()
{
    static ServiceEngine *ins = new ServiceEngine();
    return ins;
}

void ServiceEngine::addObjToLoopEngine(LoopEngine *obj)
{
    if (obj == nullptr)
        return;

    std::unique_lock<std::shared_mutex> lock(m_mutexLoop);
    auto it = m_loopEngineList.begin();
    while (it != m_loopEngineList.end())
    {
        if ((*it++) == obj)
        {
            return;
        }
    }
    m_loopEngineList.push_back(obj);
}

void ServiceEngine::removeObjFrLoopEngine(LoopEngine *obj)
{
    if (obj == nullptr)
        return;

    std::unique_lock<std::shared_mutex> lock(m_mutexLoop);
    m_loopEngineList.erase(std::remove(m_loopEngineList.begin(), m_loopEngineList.end(), obj), m_loopEngineList.end());
}

void ServiceEngine::sendMessage(std::string receiver, std::string message)
{
}

std::string ServiceEngine::getMessage(std::string receiver)
{
    return receiver;
}

bool ServiceEngine::isNotResponseMode()
{
    return m_mode == RunningMode::NotResponseMode;
}

void ServiceEngine::processLoop()
{
    m_isThreadRunning = true;
    static time_clock::time_point lastUpdate = time_clock::now();
    while (m_isThreadRunning)
    {
        std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(time_clock::now() - lastUpdate);
        lastUpdate = time_clock::now();

        m_mutexProcess.lock_shared();
        auto it = m_loopEngineList.begin();
        while (it != m_loopEngineList.end())
        {
            (*it)->processLoop(delta);
            it++;
        }
        m_mutexProcess.unlock_shared();

        usleep(m_delayMicroSecond);
        
        if (!m_isFirstProcess)
        {
            m_isFirstProcess = true;
        }
    }
}
