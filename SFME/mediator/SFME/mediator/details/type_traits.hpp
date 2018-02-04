//
// Created by milerius on 04/02/18.
//

#ifndef SFME_TYPE_TRAITS_HPP
#define SFME_TYPE_TRAITS_HPP

#include <type_traits>

namespace sfme::mediator::details
{
    template<typename T>
    using is_mediator_event = std::enable_if_t<std::is_base_of_v<InsideEvents, T>>;
}

#endif //SFME_TYPE_TRAITS_HPP
