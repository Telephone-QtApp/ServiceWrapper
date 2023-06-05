#ifndef __SIGNAL_H
#define __SIGNAL_H

#include "../common/enums.h"
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <shared_mutex>

namespace signal
{
    /**
     * @brief _Signature is a type parameter that represent a function signature or
     * operator signature.
     */
    template <typename _Signature>
    class Signal;
    class Connect;

    struct ConnectState
    {
        ConnectState() : m_state(SignalState::State_Connect){};

        std::shared_mutex m_mutex;
        SignalState m_state;
    };

    /**
     * @brief Func(Args...) represents a function signalture.
     * By using _Signature as the type parameter in template<typename _Signature>.
     * we can define a class template Signal that can accept and work with different
     * typoes of functions with different signatures.
     * @param Func is the return type of the function.
     * @param Args is the list of function parameters.
     */
    template <typename Func, typename... Args>
    class Signal<Func(Args...)>
    {
    public:
        Connect connect(const std::function<Func(Args...)> &slot);

        Func operator()(Args... args);

        void disconnectAllConnection();

        bool isEmpty() const;

    private:
        std::shared_mutex m_mutex;

        /**
         * @brief Use std::weak_ptr track ConnectState objects in the list without
         * creating additional strong references. Access the ConnectState through
         * the std::weak_ptr by converting it to a std::shared_ptr using the lock()
         * method.
         */
        std::list<
            std::pair<std::weak_ptr<ConnectState>, std::function<Func(Args...)>>>
            m_slotList;
    };

    class Connect
    {
    public:
        Connect(){};

        Connect(const std::shared_ptr<ConnectState> &conStsPtr)
        {
            m_conStsPtr = conStsPtr;
        }

        // Copy constructor
        Connect(const Connect &other) { m_conStsPtr = other.m_conStsPtr; }

        // Copy assignment operator
        Connect &operator=(const Connect &other)
        {
            m_conStsPtr = other.m_conStsPtr;
            return *this;
        }

        void disconnect()
        {
            std::unique_lock<std::shared_mutex> lock(m_conStsPtr->m_mutex);
            m_conStsPtr->m_state = SignalState::State_Disconnect;
        }

    protected:
        std::shared_ptr<ConnectState> m_conStsPtr;
    };

    template <typename Func, typename... Args>
    inline Connect
    Signal<Func(Args...)>::connect(const std::function<Func(Args...)> &slot)
    {
        std::shared_ptr<ConnectState> conSts = std::make_shared<ConnectState>();
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_slotList.emplace_back(
            std::make_pair(std::weak_ptr<ConnectState>(conSts), slot));
        return Connect(conSts);
    }

    template <typename Func, typename... Args>
    Func
    Signal<Func(Args...)>::operator()(Args... args)
    {
        bool removeFlg = false;
        {
            std::shared_lock<std::shared_mutex> lock(m_mutex);

            /**
             * @brief typename inform the compiler that
             * td::list<std::pair<std::weak_ptr<ConnectState>,std::function<_Res(_Args...)>>>
             * is a type and not a variable or function.
             */
            for (typename std::list<
                     std::pair<std::weak_ptr<ConnectState>,
                               std::function<Func(Args...)>>>::iterator it =
                     m_slotList.begin();
                 it != m_slotList.end(); ++it)
            {
                std::shared_ptr<ConnectState> conSts =
                    std::get<0>(*it).lock(); // lock(): convert to weak_ptr
                if (conSts == nullptr)
                    removeFlg = true;
                else
                {
                    std::shared_lock<std::shared_mutex> lock(conSts->m_mutex);
                    if (conSts->m_state == SignalState::State_Connect)
                    {
                        std::get<1> (*it)(args...);
                    }
                    else
                    {
                        removeFlg = true;
                    }
                }
            }
            if (removeFlg)
            {
                std::unique_lock<std::shared_mutex> lock(m_mutex);
                typename std::list<
                    std::pair<std::weak_ptr<ConnectState>,
                              std::function<Func(Args...)>>>::iterator it =
                    m_slotList.begin();
                while (it != m_slotList.end())
                {
                    std::shared_ptr<ConnectState> conSts = std::get<0>(*it).lock();
                    if (conSts == nullptr)
                    {
                        m_slotList.erase(it++);
                    }
                    else
                    {
                        std::shared_lock<std::shared_mutex> lock(conSts->m_mutex);
                        if (conSts->m_state == SignalState::State_Connect)
                        {
                            ++it;
                        }
                        else
                        {
                            m_slotList.erase(it++);
                        }
                    }
                }
            }
        }
    }

    template <typename Func, typename... Args>
    void
    Signal<Func(Args...)>::disconnectAllConnection()
    {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        if (!isEmpty())
        {
            m_slotList.clear();
        }
    }

    template <typename Func, typename... Args>
    bool
    Signal<Func(Args...)>::isEmpty() const
    {
        std::shared_lock<std::shared_mutex> lock(m_mutex);
        return m_slotList.empty();
    }
} // namespace signal

#endif