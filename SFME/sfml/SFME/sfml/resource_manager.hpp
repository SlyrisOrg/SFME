//
// Created by sztergbaum roman on 2/23/2018.
//

#pragma once

#include <optional>
#include <functional>
#include <string>
#include <unordered_map>
#include <memory>
#include <experimental/filesystem>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>

namespace fs = std::experimental::filesystem;

namespace sfme::sfml::details
{
    template <typename Resource, typename Identifier>
    class ResourceHolder
    {
    public:
        ResourceHolder(const ResourceHolder &) = delete;
        ResourceHolder &operator=(const ResourceHolder &) = delete;

        ResourceHolder() noexcept
        {
        }

        template <typename ...Args>
        Resource &load(const Identifier &id, Args &&...args)
        {
            Resource res;

            if (!res.loadFromFile(std::forward<Args>(args)...)) {
                throw std::runtime_error("Impossible to load file");
            }

            if (!_resourcesRegistry.emplace(id, std::move(res)).second) {
                throw std::runtime_error("Impossible to emplace in map. Object already exists?");
            }

            return _resourcesRegistry[id];
        }

        void remove(const Identifier &id) noexcept
        {
            if (_resourcesRegistry.count(id) == 1) {
                _resourcesRegistry.erase(id);
            }
        }

        const Resource &get(const Identifier &id) const
        {
            return _resourcesRegistry.at(id);
        }

        Resource &get(const Identifier &id)
        {
            return _resourcesRegistry.at(id);
        }

        template <typename ...Args>
        Resource &getOrLoad(const Identifier &id, Args &&...args)
        {
            if (_resourcesRegistry.count(id) == 0) {
                return load(id, std::forward<Args>(args)...);
            }
            return get(id);
        }

        void clear() noexcept
        {
            _resourcesRegistry.clear();
        }

    private:
        std::unordered_map<Identifier, Resource> _resourcesRegistry;
    };

    template <typename Identifier>
    class ResourceHolder<sf::Music, Identifier>
    {
    public:
        ResourceHolder(const ResourceHolder &) = delete;
        ResourceHolder &operator=(const ResourceHolder &) = delete;

        ResourceHolder() = default;

        template <typename ...Args>
        sf::Music &load(const Identifier &id, Args &&...args)
        {
            auto ptr = std::make_unique<sf::Music>();

            if (!ptr->openFromFile(std::forward<Args>(args)...)) {
                throw std::runtime_error("Impossible to load file");
            }

            if (!_resourcesRegistry.emplace(id, std::move(ptr)).second) {
                throw std::runtime_error("Impossible to emplace in map. Object aleardy exists?");
            }
            return *_resourcesRegistry[id];
        }

        sf::Music &get(const Identifier &id) const
        {
            return *_resourcesRegistry.at(id);
        }

        template <typename ...Args>
        sf::Music &getOrLoad(const Identifier &id, Args &&... args)
        {
            if (_resourcesRegistry.count(id) == 0) {
                return load(id, std::forward<Args>(args)...);
            }
            return get(id);
        }

        void remove(const Identifier &id) noexcept
        {
            if (_resourcesRegistry.count(id) == 1) {
                _resourcesRegistry.erase(id);
            }
        }

        void clear() noexcept
        {
            _resourcesRegistry.clear();
        }

    private:
        std::unordered_map<Identifier, std::unique_ptr<sf::Music>> _resourcesRegistry;
    };
}

namespace sfme::sfml
{
    template <typename ResourceIdentifier>
    class ResourceManager
    {
    public:
        using TMusic = sf::Music;
        using TTexture = sf::Texture;

    private:
        using TexturesRegistry = details::ResourceHolder<sf::Texture, ResourceIdentifier>;
        using MusicsRegistry = details::ResourceHolder<sf::Music, ResourceIdentifier>;

    public:
        ResourceManager(fs::path resourceDirectoryPath = fs::current_path() / "assets") noexcept :
            _resourceDirectoryPath(std::move(resourceDirectoryPath))
        {
        }

    private:
        template <typename Resource, typename Registry>
        Resource &_load(Registry &registry, const std::string &resourceTypePath, const fs::path &&filename) noexcept
        {
            ResourceIdentifier id = fs::path(filename).replace_extension("").string();
            return registry.load(id, fs::path(_resourceDirectoryPath / resourceTypePath / filename).string());
        }

        template <typename Registry>
        void _remove(const ResourceIdentifier &id, Registry &registry) noexcept
        {
            registry.remove(id);
        }

    protected:
        TMusic &loadMusic(fs::path &&filename)
        {
            if (filename.has_extension() == false) {
                filename.replace_extension(".ogg");
            }
            return _load<TMusic>(_musicRegistry, "musics", std::move(filename));
        }

        void unloadMusic(const ResourceIdentifier &id) noexcept
        {
            _remove(id, _musicRegistry);
        }

        TTexture &loadTexture(fs::path &&filename)
        {
            if (filename.has_extension() == false) {
                filename.replace_extension(".png");
            }
            return _load<TTexture>(_texturesRegistry, "textures", std::move(filename));
        }

        void unloadTexture(const ResourceIdentifier &id) noexcept
        {
            _remove(id, _texturesRegistry);
        }

        TMusic &getMusic(const ResourceIdentifier &id)
        {
            return _musicRegistry.get(id);
        }

        TTexture &getTexture(const ResourceIdentifier &id)
        {
            return _texturesRegistry.get(id);
        }

    private:
        fs::path _resourceDirectoryPath;
        TexturesRegistry _texturesRegistry;
        MusicsRegistry _musicRegistry;
    };
}
