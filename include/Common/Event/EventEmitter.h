#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include "Event.h"
#include "Enums.h"
#include "Std/UnorderedMap.h"

template <typename Key = Events, typename... Args>
class EventEmitter
{
public:
    using EventType = Event<Args...>;
    using EventMap = UMap<Key, EventType>;

    template <typename K>
    EventType* event(K &&key)
    {
        auto* ptr = getEvent(std::forward<K>(key));
        if (ptr == nullptr)
        {
            ptr = new EventType();
        }
        return ptr;
    }

    template <typename K>
    EventType *getEvent(K &&key)
    {
        auto it = m_eventMap.find(std::forward<K>(key));
        return it != m_eventMap.end() ? &it->second : nullptr;
    }

    template <typename K, typename CB>
    void on(K &&key, CB &&callback)
    {
        auto *ptr = getEvent(std::forward<K>(key));
        if (ptr == nullptr)
        {
            m_eventMap.insert(std::make_pair(std::forward<K>(key), EventType()));
        }
        ptr->connect(std::forward<CB>(callback));
    }

    template <typename K>
    void emitEvent(K &&key, Args... args)
    {
        EventType *ptr = getEvent(std::forward<K>(key));
        if (ptr != nullptr)
        {
            ptr->emitEvent(args...);
        }
    }

private:
    EventMap m_eventMap;
};

#endif
