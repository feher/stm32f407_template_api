#pragma once

#include <data_struct/circular_queue.hpp>

namespace Ao
{
    template <typename TEvent>
    class EventReceiver
    {
    public:
        virtual void receive(const TEvent& event) = 0;
    };

    template <typename TEvent>
    class EventSender
    {
    public:
        void registerReceiver(EventReceiver<TEvent>* receiver)
        {
            m_receivers[m_count++] = receiver;
        }

        void send(const TEvent& event)
        {
            for (EventReceiver<TEvent>* receiver : m_receivers)
            {
                if (receiver)
                {
                    receiver->receive(event);
                }
            }
        }

    private:
        std::array<EventReceiver<TEvent>*, 10> m_receivers;
        std::size_t m_count = 0;
    };

    template <typename TEvent, std::size_t TVQueueSize>
    class ActiveObject : public EventSender<TEvent>, public EventReceiver<TEvent>
    {
    public:
        void step()
        {
            auto event = m_queue.take();
            if (event)
            {
                handleEvent(*event);
            }
        }

        void receive(const TEvent& event) override
        {
            // TODO: Make this atomic (may be called from ISRs).
            m_queue.add(event);
        }

    protected:
        virtual void handleEvent(const TEvent& event) = 0;

    private:
        CircularQueueMpMcLf<TEvent, TVQueueSize> m_queue;
    };

} // namespace Ao
