//
// Created by milerius on 13/02/18.
//

#pragma once

#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;

namespace sfme::ecs::details
{
    static inline bool is_shared_library(const fs::path &p)
    {
        const std::string &s = p.string();
        return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos ||
                s.find(".dylib") != std::string::npos)
               && s.find(".lib") == std::string::npos
               && s.find(".exp") == std::string::npos
               && s.find(".pdb") == std::string::npos
               && s.find(".manifest") == std::string::npos
               && s.find(".rsp") == std::string::npos
               && s.find(".obj") == std::string::npos
               && s.find(".a") == std::string::npos;
    }
}
