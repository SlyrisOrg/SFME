#pragma once

#include <core/utils/Enums.hpp>

namespace sfme::input::keyboard
{
    class Key
    {
    public:
        enum enum_Key
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            Escape,
            LControl,
            LShift,
            LAlt,
            LSystem,
            RControl,
            RShift,
            RAlt,
            RSystem,
            Menu,
            LBracket,
            RBracket,
            SemiColon,
            Comma,
            Period,
            Quote,
            Slash,
            BackSlash,
            Tilde,
            Equal,
            Dash,
            Space,
            Return,
            BackSpace,
            Tab,
            PageUp,
            PageDown,
            End,
            Home,
            Insert,
            Delete,
            Add,
            Subtract,
            Multiply,
            Divide,
            Left,
            Right,
            Up,
            Down,
            Numpad0,
            Numpad1,
            Numpad2,
            Numpad3,
            Numpad4,
            Numpad5,
            Numpad6,
            Numpad7,
            Numpad8,
            Numpad9,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            Pause
        };

        using EnumType = enum_Key;

        constexpr Key() noexcept : _value(A)
        {
        }

        constexpr Key(EnumType value) noexcept : _value(value)
        {
        }

        Key& operator=(EnumType value) noexcept
        {
            _value = value;
            return *this;
        }

        static constexpr const std::array<Key, 101> values() noexcept
        {
            return {
                {
                    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Num0, Num1, Num2,
                    Num3, Num4, Num5, Num6, Num7, Num8, Num9, Escape, LControl, LShift, LAlt, LSystem, RControl, RShift,
                    RAlt, RSystem, Menu, LBracket, RBracket, SemiColon, Comma, Period, Quote, Slash, BackSlash, Tilde,
                    Equal, Dash, Space, Return, BackSpace, Tab, PageUp, PageDown, End, Home, Insert, Delete, Add,
                    Subtract, Multiply, Divide, Left, Right, Up, Down, Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
                    Numpad5, Numpad6, Numpad7, Numpad8, Numpad9, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13,
                    F14, F15, Pause
                }
            };
        }

        static constexpr size_t size() noexcept { return 101; }

        class InvalidConversion : public std::exception
        {
        public:
            const char* what() const noexcept override { return "Unable to convert this string to an enum value"; }
        };

    private:
        enum_Key _stringToValue(const std::string_view v)
        {
            static constexpr const std::string_view strTab[] = {
                std::string_view("A", (sizeof("A""") - 1)), std::string_view("B", (sizeof("B""") - 1)),
                std::string_view("C", (sizeof("C""") - 1)), std::string_view("D", (sizeof("D""") - 1)),
                std::string_view("E", (sizeof("E""") - 1)), std::string_view("F", (sizeof("F""") - 1)),
                std::string_view("G", (sizeof("G""") - 1)), std::string_view("H", (sizeof("H""") - 1)),
                std::string_view("I", (sizeof("I""") - 1)), std::string_view("J", (sizeof("J""") - 1)),
                std::string_view("K", (sizeof("K""") - 1)), std::string_view("L", (sizeof("L""") - 1)),
                std::string_view("M", (sizeof("M""") - 1)), std::string_view("N", (sizeof("N""") - 1)),
                std::string_view("O", (sizeof("O""") - 1)), std::string_view("P", (sizeof("P""") - 1)),
                std::string_view("Q", (sizeof("Q""") - 1)), std::string_view("R", (sizeof("R""") - 1)),
                std::string_view("S", (sizeof("S""") - 1)), std::string_view("T", (sizeof("T""") - 1)),
                std::string_view("U", (sizeof("U""") - 1)), std::string_view("V", (sizeof("V""") - 1)),
                std::string_view("W", (sizeof("W""") - 1)), std::string_view("X", (sizeof("X""") - 1)),
                std::string_view("Y", (sizeof("Y""") - 1)), std::string_view("Z", (sizeof("Z""") - 1)),
                std::string_view("Num0", (sizeof("Num0""") - 1)), std::string_view("Num1", (sizeof("Num1""") - 1)),
                std::string_view("Num2", (sizeof("Num2""") - 1)), std::string_view("Num3", (sizeof("Num3""") - 1)),
                std::string_view("Num4", (sizeof("Num4""") - 1)), std::string_view("Num5", (sizeof("Num5""") - 1)),
                std::string_view("Num6", (sizeof("Num6""") - 1)), std::string_view("Num7", (sizeof("Num7""") - 1)),
                std::string_view("Num8", (sizeof("Num8""") - 1)), std::string_view("Num9", (sizeof("Num9""") - 1)),
                std::string_view("Escape", (sizeof("Escape""") - 1)),
                std::string_view("LControl", (sizeof("LControl""") - 1)),
                std::string_view("LShift", (sizeof("LShift""") - 1)), std::string_view("LAlt", (sizeof("LAlt""") - 1)),
                std::string_view("LSystem", (sizeof("LSystem""") - 1)),
                std::string_view("RControl", (sizeof("RControl""") - 1)),
                std::string_view("RShift", (sizeof("RShift""") - 1)), std::string_view("RAlt", (sizeof("RAlt""") - 1)),
                std::string_view("RSystem", (sizeof("RSystem""") - 1)),
                std::string_view("Menu", (sizeof("Menu""") - 1)),
                std::string_view("LBracket", (sizeof("LBracket""") - 1)),
                std::string_view("RBracket", (sizeof("RBracket""") - 1)),
                std::string_view("SemiColon", (sizeof("SemiColon""") - 1)),
                std::string_view("Comma", (sizeof("Comma""") - 1)),
                std::string_view("Period", (sizeof("Period""") - 1)),
                std::string_view("Quote", (sizeof("Quote""") - 1)), std::string_view("Slash", (sizeof("Slash""") - 1)),
                std::string_view("BackSlash", (sizeof("BackSlash""") - 1)),
                std::string_view("Tilde", (sizeof("Tilde""") - 1)), std::string_view("Equal", (sizeof("Equal""") - 1)),
                std::string_view("Dash", (sizeof("Dash""") - 1)), std::string_view("Space", (sizeof("Space""") - 1)),
                std::string_view("Return", (sizeof("Return""") - 1)),
                std::string_view("BackSpace", (sizeof("BackSpace""") - 1)),
                std::string_view("Tab", (sizeof("Tab""") - 1)), std::string_view("PageUp", (sizeof("PageUp""") - 1)),
                std::string_view("PageDown", (sizeof("PageDown""") - 1)),
                std::string_view("End", (sizeof("End""") - 1)), std::string_view("Home", (sizeof("Home""") - 1)),
                std::string_view("Insert", (sizeof("Insert""") - 1)),
                std::string_view("Delete", (sizeof("Delete""") - 1)), std::string_view("Add", (sizeof("Add""") - 1)),
                std::string_view("Subtract", (sizeof("Subtract""") - 1)),
                std::string_view("Multiply", (sizeof("Multiply""") - 1)),
                std::string_view("Divide", (sizeof("Divide""") - 1)), std::string_view("Left", (sizeof("Left""") - 1)),
                std::string_view("Right", (sizeof("Right""") - 1)), std::string_view("Up", (sizeof("Up""") - 1)),
                std::string_view("Down", (sizeof("Down""") - 1)),
                std::string_view("Numpad0", (sizeof("Numpad0""") - 1)),
                std::string_view("Numpad1", (sizeof("Numpad1""") - 1)),
                std::string_view("Numpad2", (sizeof("Numpad2""") - 1)),
                std::string_view("Numpad3", (sizeof("Numpad3""") - 1)),
                std::string_view("Numpad4", (sizeof("Numpad4""") - 1)),
                std::string_view("Numpad5", (sizeof("Numpad5""") - 1)),
                std::string_view("Numpad6", (sizeof("Numpad6""") - 1)),
                std::string_view("Numpad7", (sizeof("Numpad7""") - 1)),
                std::string_view("Numpad8", (sizeof("Numpad8""") - 1)),
                std::string_view("Numpad9", (sizeof("Numpad9""") - 1)), std::string_view("F1", (sizeof("F1""") - 1)),
                std::string_view("F2", (sizeof("F2""") - 1)), std::string_view("F3", (sizeof("F3""") - 1)),
                std::string_view("F4", (sizeof("F4""") - 1)), std::string_view("F5", (sizeof("F5""") - 1)),
                std::string_view("F6", (sizeof("F6""") - 1)), std::string_view("F7", (sizeof("F7""") - 1)),
                std::string_view("F8", (sizeof("F8""") - 1)), std::string_view("F9", (sizeof("F9""") - 1)),
                std::string_view("F10", (sizeof("F10""") - 1)), std::string_view("F11", (sizeof("F11""") - 1)),
                std::string_view("F12", (sizeof("F12""") - 1)), std::string_view("F13", (sizeof("F13""") - 1)),
                std::string_view("F14", (sizeof("F14""") - 1)), std::string_view("F15", (sizeof("F15""") - 1)),
                std::string_view("Pause", (sizeof("Pause""") - 1)),
            };
            static constexpr const auto vals = values();
            for (size_t i = 0; i < (sizeof(strTab) / sizeof((strTab)[0])); ++i)
            {
                if (strTab[i] == v) { return vals[i]; }
            }
            throw InvalidConversion();
        }

    public:
        Key(const std::string_view v) : _value(_stringToValue(v))
        {
        }

        Key& operator=(const std::string_view v)
        {
            _value = _stringToValue(v);
            return *this;
        }

        operator EnumType() const noexcept { return _value; }

        std::string toString() const noexcept
        {
            switch (_value)
            {
            case A: return "A";
            case B: return "B";
            case C: return "C";
            case D: return "D";
            case E: return "E";
            case F: return "F";
            case G: return "G";
            case H: return "H";
            case I: return "I";
            case J: return "J";
            case K: return "K";
            case L: return "L";
            case M: return "M";
            case N: return "N";
            case O: return "O";
            case P: return "P";
            case Q: return "Q";
            case R: return "R";
            case S: return "S";
            case T: return "T";
            case U: return "U";
            case V: return "V";
            case W: return "W";
            case X: return "X";
            case Y: return "Y";
            case Z: return "Z";
            case Num0: return "Num0";
            case Num1: return "Num1";
            case Num2: return "Num2";
            case Num3: return "Num3";
            case Num4: return "Num4";
            case Num5: return "Num5";
            case Num6: return "Num6";
            case Num7: return "Num7";
            case Num8: return "Num8";
            case Num9: return "Num9";
            case Escape: return "Escape";
            case LControl: return "LControl";
            case LShift: return "LShift";
            case LAlt: return "LAlt";
            case LSystem: return "LSystem";
            case RControl: return "RControl";
            case RShift: return "RShift";
            case RAlt: return "RAlt";
            case RSystem: return "RSystem";
            case Menu: return "Menu";
            case LBracket: return "LBracket";
            case RBracket: return "RBracket";
            case SemiColon: return "SemiColon";
            case Comma: return "Comma";
            case Period: return "Period";
            case Quote: return "Quote";
            case Slash: return "Slash";
            case BackSlash: return "BackSlash";
            case Tilde: return "Tilde";
            case Equal: return "Equal";
            case Dash: return "Dash";
            case Space: return "Space";
            case Return: return "Return";
            case BackSpace: return "BackSpace";
            case Tab: return "Tab";
            case PageUp: return "PageUp";
            case PageDown: return "PageDown";
            case End: return "End";
            case Home: return "Home";
            case Insert: return "Insert";
            case Delete: return "Delete";
            case Add: return "Add";
            case Subtract: return "Subtract";
            case Multiply: return "Multiply";
            case Divide: return "Divide";
            case Left: return "Left";
            case Right: return "Right";
            case Up: return "Up";
            case Down: return "Down";
            case Numpad0: return "Numpad0";
            case Numpad1: return "Numpad1";
            case Numpad2: return "Numpad2";
            case Numpad3: return "Numpad3";
            case Numpad4: return "Numpad4";
            case Numpad5: return "Numpad5";
            case Numpad6: return "Numpad6";
            case Numpad7: return "Numpad7";
            case Numpad8: return "Numpad8";
            case Numpad9: return "Numpad9";
            case F1: return "F1";
            case F2: return "F2";
            case F3: return "F3";
            case F4: return "F4";
            case F5: return "F5";
            case F6: return "F6";
            case F7: return "F7";
            case F8: return "F8";
            case F9: return "F9";
            case F10: return "F10";
            case F11: return "F11";
            case F12: return "F12";
            case F13: return "F13";
            case F14: return "F14";
            case F15: return "F15";
            case Pause: return "Pause";
            default: return "";
            }
        }

        static std::string toString(Key v) { return v.toString(); }
    private:
        EnumType _value;
    };;

    using TKey = Key::EnumType;
}
