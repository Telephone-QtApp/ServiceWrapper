#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <atomic>
#include <vector>
#include <shared_mutex>
#include <mutex>

template <typename... Args>
class Event
{
public:
    using Id = uint32_t;
    using Callback = std::function<void(Args...)>;
    using PairIdCb = std::pair<Id, Callback>;
    using Events = std::vector<PairIdCb>;

    Event()
    {
        id.store(0u);
    }

    Event(const Event<Args...> &other)
    {
        id.store(0u);
        callbacks = other.callbacks;
    }

    /**
     * Generate new ID for new callback
     */
    Id createNewId()
    {
        return ++id;
    }

    std::size_t size() const
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return callbacks.size();
    }

    bool isEmpty() const
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return callbacks.empty();
    }

    /**
     * @brief: Disconnect callback with id
     */
    void disconnect(const Id &id)
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        for (std::size_t i = 0u; i < callbacks.size(); ++i)
        {
            if (callbacks.at(i).first == id)
            {
                callbacks.erase(callbacks.begin() + i);
            }
        }
    }

    void disconnectAllCB()
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        callbacks.clear();
    }

    /**
     * @brief: Add new callback to callback list
     */
    template <typename Func>
    Id connect(Func &&callback)
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        const auto id = createNewId();
        callbacks.emplace_back(id, std::forward<Func>(callback));
        return id;
    }

    /**
     * @brief: If callback list is not empty. Call all callbacks with params
     */
    void emitEventList(const Events &events, Args... args)
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        for (auto event : events)
        {
            event.second(args...);
        }
    }

    void emit(Args... args)
    {
        if (!isEmpty())
        {
            emitEventList(callbacks, args...);
        }
    }

private:
    Events callbacks;

    /**
     * @details: atomic - offers thread-safe, avoid data race
     * @brief: unique ID to count;
     */
    std::atomic<Id> id;
    mutable std::shared_mutex m_mutex;
};

#endif