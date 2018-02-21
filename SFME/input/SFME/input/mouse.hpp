#pragma once

#include <core/utils/Enums.hpp>

namespace sfme::input::mouse
{
    class Button
    {
    public:
        enum enum_Button
        {
            Left, Right, Middle, XButton1, XButton2, ButtonCount
        };

        using EnumType = enum_Button;

        constexpr Button() noexcept : _value(Left)
        {
        }

        constexpr Button(EnumType value) noexcept : _value(value)
        {
        }

        Button &operator=(EnumType value) noexcept
        {
            _value = value;
            return *this;
        }

        static constexpr const std::array<Button, 6> values() noexcept
        {
            return {{Left, Right, Middle, XButton1, XButton2, ButtonCount}};
        }

        static constexpr size_t size() noexcept
        {
            return 6;
        }

        class InvalidConversion : public std::exception
        {
        public:
            const char *what() const noexcept override
            {
                return "Unable to convert this string to an enum value";
            }
        };

    private:
        enum_Button _stringToValue(const std::string_view v)
        {
            static constexpr const std::string_view strTab[] = {
                std::string_view("Left", (sizeof("Left""") - 1)),
                std::string_view("Right", (sizeof("Right""") - 1)),
                std::string_view("Middle", (sizeof("Middle""") - 1)),
                std::string_view("XButton1", (sizeof("XButton1""") - 1)),
                std::string_view("XButton2", (sizeof("XButton2""") - 1)),
                std::string_view("ButtonCount", (sizeof("ButtonCount""") - 1)),
            };
            static constexpr const auto vals = values();
            for (size_t i = 0; i < (sizeof(strTab) / sizeof((strTab)[0])); ++i) {
                if (strTab[i] == v) { return vals[i]; }
            }
            throw InvalidConversion();
        }

    public:
        Button(const std::string_view v) : _value(_stringToValue(v))
        {
        }

        Button &operator=(const std::string_view v)
        {
            _value = _stringToValue(v);
            return *this;
        }

        operator EnumType() const noexcept
        { return _value; }

        std::string toString() const noexcept
        {
            switch (_value) {
                case Left:
                    return "Left";
                case Right:
                    return "Right";
                case Middle:
                    return "Middle";
                case XButton1:
                    return "XButton1";
                case XButton2:
                    return "XButton2";
                case ButtonCount:
                    return "ButtonCount";
                default:
                    return "";
            }
        }

        static std::string toString(Button v)
        { return v.toString(); }

    private:
        EnumType _value;
    };

    class Wheel
    {
    public:
        enum enum_Wheel
        {
            VerticalWheel, HorizontalWheel
        }; using EnumType = enum_Wheel;

        constexpr Wheel() noexcept : _value(VerticalWheel)
        {}

        constexpr Wheel(EnumType value) noexcept : _value(value)
        {}

        Wheel &operator=(EnumType value) noexcept
        {
            _value = value;
            return *this;
        }

        static constexpr const std::array<Wheel, 2> values() noexcept
        { return {{VerticalWheel, HorizontalWheel}}; }

        static constexpr size_t size() noexcept
        { return 2; }

        class InvalidConversion : public std::exception
        {
        public:
            const char *what() const noexcept override
            { return "Unable to convert this string to an enum value"; }
        };

    private:
        enum_Wheel _stringToValue(const std::string_view v)
        {
            static constexpr const std::string_view strTab[] = {
                std::string_view("VerticalWheel", (sizeof("VerticalWheel""") - 1)),
                std::string_view("HorizontalWheel", (sizeof("HorizontalWheel""") - 1)),};
            static constexpr const auto vals = values();
            for (size_t i = 0; i < (sizeof(strTab) / sizeof((strTab)[0])); ++i) {
                if (strTab[i] == v) { return vals[i]; }
            }
            throw InvalidConversion();
        }

    public:
        Wheel(const std::string_view v) : _value(_stringToValue(v))
        {}

        Wheel &operator=(const std::string_view v)
        {
            _value = _stringToValue(v);
            return *this;
        }

        operator EnumType() const noexcept
        { return _value; }

        std::string toString() const noexcept
        {
            switch (_value) {
                case VerticalWheel:
                    return "VerticalWheel";
                case HorizontalWheel:
                    return "HorizontalWheel";
                default:
                    return "";
            }
        }

        static std::string toString(Wheel v)
        { return v.toString(); }

    private:
        EnumType _value;
    };
}
