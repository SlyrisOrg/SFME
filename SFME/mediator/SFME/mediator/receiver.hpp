//
// Created by milerius on 03/02/18.
//

#ifndef SFME_MEDIATOR_RECEIVER_HPP
#define SFME_MEDIATOR_RECEIVER_HPP

#include <core/utils/NonCopyable.hpp>

namespace sfme::mediator
{
    struct BaseReceiver : private utils::NonCopyable
    {
    };

    template <typename Derived>
    struct Receiver : public BaseReceiver
    {
    };
}

#endif //SFME_MEDIATOR_RECEIVER_HPP
