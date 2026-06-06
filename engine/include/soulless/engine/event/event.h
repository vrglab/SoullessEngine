#pragma once


namespace SoullessEngine::events
{
    template<typename... Args>
    class SOULLESS_API Event
    {
    public:
        using Callback = std::function<void(Args...)>;
        
        void AddListener(Callback cb)
        {
            m_Listeners.push_back(std::move(cb));
        }
        
        void Broadcast(Args... args)
        {
            for (auto& listener : m_Listeners)
            {
                listener(args...);
            }
        }


    private:
        std::vector<Callback> m_Listeners;
    };
}

#define SOULLESS_EVENT(name, ...) Event<__VA_ARGS__> name;
#define SOULLESS_SIMPLE_EVENT(name, ret, ...)  std::function<ret(__VA_ARGS__)> name;