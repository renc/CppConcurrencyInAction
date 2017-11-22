#ifndef listing_c_3_h
#define listing_c_3_h

#include "listing_c.1.queue.h"
#include "listing_c.2.sender.h"
#include "listing_c.4.dispatcher.h"

namespace messaging
{
    class receiver
    {
		msgqueue q;
    public:
        operator sender()          // renc: ? what kind of function, convert "receiver" to "sender" ??
        {
            return sender(&q);
        }

        dispatcher wait()
        {
            return dispatcher(&q);
        }
    };
}

#endif //listing_c_3_h