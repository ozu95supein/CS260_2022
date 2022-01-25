#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <chrono>
#include <fmt/core.h>
#include <fmt/ostream.h>

namespace CS260 {

    // Time utils
    using clock_t = std::chrono::high_resolution_clock;

    inline auto now()
    {
        return clock_t::now();
    }

    inline uint32_t now_ns()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(clock_t::now().time_since_epoch()).count();
    }

    inline uint32_t ms_since(clock_t::time_point const& moment)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(now() - moment).count();
    }

}

#endif // __UTILS_HPP__