#ifndef CALLBACKEVENT_H
#define CALLBACKEVENT_H

#include <shared_mutex>
#include <mutex>
#include "EventEmitter.h"

template <typename Func, typename... Args>
class CallbackEvent : public EventEmitter<>
{
public:
    uint32_t regCallbackFunc(Func &&fn)
    {
        return m_cbEvent.connect(std::forward<Func>(fn));
    }

    void unRegCallbackFunc(uint32_t id)
    {
        m_cbEvent.disconnect(id);
    }

    void emit(Args... args)
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_cbEvent.emit(args...);
    }

private:
    std::shared_mutex m_mutex;
    Event<> &m_cbEvent = *event(Events::Callback);
};

#endif