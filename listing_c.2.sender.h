#ifndef listing_c_2_h
#define listing_c_2_h

#include "listing_c.1.queue.h"

namespace messaging
{
    class sender
    {
		msgqueue*q;
    public:
        sender():
            q(nullptr)
        {}
        explicit sender(msgqueue*q_):
            q(q_)
        {}
        template<typename Message>
        void send(Message const& msg)
        {
            if(q)
            {
                q->push(msg);
            }
        }
    };
}
#endif //listing_c_2_h
