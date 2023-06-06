#ifndef CALLBACK_H
#define CALLBACK_H

#include <shared_mutex>
#include <mutex>
#include "event/eventemitter.h"

class Callback : public EventEmitter<>
{
public:
    template <typename CB>
    uint32_t regCallbackFunc(CB &&cb)
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return m_cbEvent.connect(std::forward<CB>(cb));
    }

    void unRegCallbackFunc(uint32_t id)
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        m_cbEvent.disconnect(id);
    }

    void emit()
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        m_cbEvent.emit();
    }
private:
    std::shared_mutex m_mutex;
    Event<>& m_cbEvent = *event(Events::Callback);
};

#endif