//
// Created by milerius on 04/02/18.
//

#ifndef SFME_TYPE_TRAITS_HPP
#define SFME_TYPE_TRAITS_HPP

#include <type_traits>

namespace sfme::mediator::details
{
    template<typename T>
    constexpr bool is_mediator_event = std::is_base_of_v<BaseEvent, T>;
}

#endif //SFME_TYPE_TRAITS_HPP
