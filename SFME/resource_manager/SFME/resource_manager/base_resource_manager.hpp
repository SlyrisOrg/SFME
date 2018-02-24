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
        TMusic &loadMusic(fs::path filename)
        {
            return TResourceManager::loadMusic(std::move(filename));
        }

        TTexture &loadTexture(fs::path filename)
        {
            return TResourceManager::loadTexture(std::move(filename));
        }

        void unloadMusic(const ResourceIdentifier &id)
        {
            TResourceManager::unloadMusic(id);
        }

        void unloadTexture(const ResourceIdentifier &id)
        {
            TResourceManager::unloadTexture(id);
        }

        TMusic &getMusic(const ResourceIdentifier &id)
        {
            return TResourceManager::getMusic(id);
        }
    };
}