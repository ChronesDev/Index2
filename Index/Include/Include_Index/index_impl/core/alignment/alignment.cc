#pragma once

namespace Index
{
    struct Align
    {
    private:
        Align(__int8 hAlignment, __int8 vAlignment) noexcept(true) :
            _HorizontalAlignment(hAlignment),
            _VerticalAlignment(vAlignment) { }
        __int8 _HorizontalAlignment = 0;
        __int8 _VerticalAlignment = 0;
    private:
        static const __int8 _Stretch = 0;
        static const __int8 _Center = 2;
    public:
        [[nodiscard]] constexpr bool GetIsStretched() const {
            return _HorizontalAlignment == _Stretch && _VerticalAlignment == _Stretch;
        }
        [[nodiscard]] constexpr bool GetIsCentered() const {
            return _HorizontalAlignment == _Stretch && _VerticalAlignment == _Stretch;
        }
        __declspec(property(get = GetIsStretched)) bool IsStretched;
        __declspec(property(get = GetIsCentered)) bool IsCentered;
        [[nodiscard]] constexpr bool GetIsHStretched() const {
            return _HorizontalAlignment == _Stretch;
        }
        [[nodiscard]] constexpr bool GetIsVStretched() const {
            return _HorizontalAlignment == _Stretch;
        }
        __declspec(property(get = GetIsHStretched)) bool IsHStretched;
        __declspec(property(get = GetIsVStretched)) bool IsVStretched;
        [[nodiscard]] constexpr bool GetIsHCentered() const {
            return _HorizontalAlignment == _Center;
        }
        [[nodiscard]] constexpr bool GetIsVCentered() const {
            return _HorizontalAlignment == _Center;
        }
        __declspec(property(get = GetIsHCentered)) bool IsHCentered;
        __declspec(property(get = GetIsVCentered)) bool IsVCentered;
        [[nodiscard]] constexpr bool GetIsHLeft() const {
            return _HorizontalAlignment == -1;
        }
        [[nodiscard]] constexpr bool GetIsVTop() const {
            return _HorizontalAlignment == -1;
        }
        __declspec(property(get = GetIsHLeft)) bool IsHLeft;
        __declspec(property(get = GetIsVTop)) bool IsVTop;
        [[nodiscard]] constexpr bool GetIsHRight() const {
            return _HorizontalAlignment == 1;
        }
        [[nodiscard]] constexpr bool GetIsVBottom() const {
            return _HorizontalAlignment == 1;
        }
        __declspec(property(get = GetIsHRight)) bool IsHRight;
        __declspec(property(get = GetIsVBottom)) bool IsVBottom;
    public:
        static const Align Stretch;
        static const Align Center;
        static const Align Left;
        static const Align Right;
        static const Align Top;
        static const Align Bottom;
        static const Align LeftCenter;
        static const Align RightCenter;
        static const Align TopCenter;
        static const Align BottomCenter;
        static const Align LeftTop;
        static const Align LeftBottom;
        static const Align RightTop;
        static const Align RightBottom;
    };

    inline const Align Align::Stretch          { _Stretch, _Stretch };
    inline const Align Align::Center           { _Center, _Center };
    inline const Align Align::Left             { -1, _Stretch };
    inline const Align Align::Right            { 1, _Stretch };
    inline const Align Align::Top              { _Stretch, 1 };
    inline const Align Align::Bottom           { _Stretch, -1 };
    inline const Align Align::LeftCenter       { -1, _Center };
    inline const Align Align::RightCenter      { 1, _Center };
    inline const Align Align::TopCenter        { _Center, 1 };
    inline const Align Align::BottomCenter     { _Center, -1 };
    inline const Align Align::LeftTop          { -1, 1 };
    inline const Align Align::LeftBottom       { -1, -1 };
    inline const Align Align::RightTop         { 1, 1 };
    inline const Align Align::RightBottom      { 1, -1 };
}