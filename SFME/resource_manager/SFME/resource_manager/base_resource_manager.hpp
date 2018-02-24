//
// Created by sztergbaum roman on 2/23/2018.
//

#pragma once

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace sfme::resource
{
    template <template <typename> typename ResourceManagerImpl, typename ResourceIdentifier = std::string>
    class ResourceManager : private ResourceManagerImpl<ResourceIdentifier>
    {
    public:
        using TResourceManager = ResourceManagerImpl<ResourceIdentifier>;
        using TMusic = typename TResourceManager::TMusic;
        using TTexture = typename TResourceManager::TTexture;

    public:
#define noexcept_if(x)  noexcept(noexcept(x))

        TMusic &
        loadMusic(fs::path filename) noexcept_if(TResourceManager::loadMusic(std::declval<fs::path>()))
        {
            return TResourceManager::loadMusic(std::move(filename));
        }

        TTexture &
        loadTexture(fs::path filename) noexcept_if(TResourceManager::loadTexture(std::declval<fs::path>()))
        {
            return TResourceManager::loadTexture(std::move(filename));
        }

        void unloadMusic(const ResourceIdentifier &id) noexcept_if(
            TResourceManager::unloadMusic(std::declval<const ResourceIdentifier>()))
        {
            TResourceManager::unloadMusic(id);
        }

        void unloadTexture(const ResourceIdentifier &id) noexcept_if(
            TResourceManager::unloadTexture(std::declval<const ResourceIdentifier>()))
        {
            TResourceManager::unloadTexture(id);
        }

        TMusic &getMusic(const ResourceIdentifier &id) noexcept_if(
            TResourceManager::getMusic(std::declval<const ResourceIdentifier>()))
        {
            return TResourceManager::getMusic(id);
        }

#undef noexcept_if
    };
}