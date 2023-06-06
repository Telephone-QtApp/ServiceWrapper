#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include "event.h"
#include "enums.h"
#include "std/unordered_map.h"

template <typename Key = Events, typename... Args>
class EventEmitter
{
public:
    using EventType = Event<Args...>;
    using EventMap = UMap<Key, EventType>;

    template <typename K>
    EventType *getEvent(K && key)
    {
        auto it = m_eventMap.find(std::forward<K>(key));
        return it != m_eventMap.end() ? &it->second : nullptr;
    }

    template <typename K>
    void insertEventKey(K &&key)
    {
        auto* ptr = getEvent(std::forward<K>(key));
        if (ptr == nullptr)
        {
            m_eventMap.insert(std::make_pair(std::forward<K>(key), EventType()));
        }
    }

    template <typename K, typename CB>
    void on(K && key, CB && callback)
    {
        insertEventKey(std::forward<K>(key));
        getEvent(std::forward<K>(key))->connect(std::forward<CB>(callback));
    }

    template <typename K>
    void emit(K &&key, Args... args)
    {
        EventType *ptr = getEvent(std::forward<K>(key));
        if (ptr != nullptr)
        {
            ptr->emit(args...);
        }
    }

private:
    EventMap m_eventMap;
};

#endif

