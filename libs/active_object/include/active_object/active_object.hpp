#pragma once

#include <data_struct/circular_queue_3.hpp>

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
        EventSender()
        {
            std::ranges::fill(m_receivers, nullptr);
        }

        bool connect(EventReceiver<TEvent>* receiver)
        {
            if (m_receiverCount == k_maxReceiverCount)
            {
                return false;
            }
            m_receivers[m_receiverCount] = receiver;
            ++m_receiverCount;
            return true;
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
        static constexpr auto k_maxReceiverCount = 10;
        std::array<EventReceiver<TEvent>*, k_maxReceiverCount> m_receivers;
        std::size_t m_receiverCount = 0;
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
        Ds::CircularQueueMpMcLf3<TEvent, TVQueueSize> m_queue;
    };

} // namespace Ao
