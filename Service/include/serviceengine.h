#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <vector>
#include <thread>
#include <shared_mutex>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include "common/loopengine.h"

static constexpr int16_t delayMicroSeconds = 10000; // 0.01s

class ServiceEngine
{
public:
    enum class RunningMode
    {
        NormalMode = 0,
        NotResponseMode
    };

    static ServiceEngine *instance();

    void addObjToLoopEngine(LoopEngine *obj);
    void removeObjFrLoopEngine(LoopEngine *obj);

    void sendMessage(std::string receiver, std::string message);
    std::string getMessage(std::string receiver);

    bool isNotResponseMode();
    void processLoop();

private:
    ServiceEngine();
    ~ServiceEngine();

    std::vector<LoopEngine *> m_loopEngineList;
    useconds_t m_delayMicroSecond = delayMicroSeconds;
    std::shared_mutex m_mutexLoop;
    std::shared_mutex m_mutexProcess;

    std::thread m_thread;
    bool m_isThreadRunning{false};

    RunningMode m_mode{RunningMode::NormalMode};
    bool m_isFirstProcess{false};
};

#endif
