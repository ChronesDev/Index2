#pragma once

#include "../../helpers/include.cc"

namespace Index
{
    struct Align
    {
    private:
        constexpr Align(short hAlignment, short vAlignment) noexcept(true)
            : HorizontalAlignment_(hAlignment)
            , VerticalAlignment_(vAlignment)
        {
        }

        short HorizontalAlignment_ = 0;
        short VerticalAlignment_ = 0;

    private:
        static constexpr short Stretch_ = 0;
        static constexpr short Center_ = 2;

    public:
        [[nodiscard]] constexpr bool GetIsStretched() const
        {
            return HorizontalAlignment_ == Stretch_ && VerticalAlignment_ == Stretch_;
        }
        [[nodiscard]] constexpr bool GetIsCentered() const
        {
            return HorizontalAlignment_ == Center_ && VerticalAlignment_ == Center_;
        }

        INDEX_Property(get = GetIsStretched) bool IsStretched;
        INDEX_Property(get = GetIsCentered) bool IsCentered;

        [[nodiscard]] constexpr bool GetIsHStretched() const { return HorizontalAlignment_ == Stretch_; }
        [[nodiscard]] constexpr bool GetIsVStretched() const { return VerticalAlignment_ == Stretch_; }

        INDEX_Property(get = GetIsHStretched) bool IsHStretched;
        INDEX_Property(get = GetIsVStretched) bool IsVStretched;

        [[nodiscard]] constexpr bool GetIsHCentered() const { return HorizontalAlignment_ == Center_; }
        [[nodiscard]] constexpr bool GetIsVCentered() const { return VerticalAlignment_ == Center_; }

        INDEX_Property(get = GetIsHCentered) bool IsHCentered;
        INDEX_Property(get = GetIsVCentered) bool IsVCentered;

        [[nodiscard]] constexpr bool GetIsHLeft() const { return HorizontalAlignment_ == -1; }
        [[nodiscard]] constexpr bool GetIsVTop() const { return VerticalAlignment_ == -1; }

        INDEX_Property(get = GetIsHLeft) bool IsHLeft;
        INDEX_Property(get = GetIsVTop) bool IsVTop;

        [[nodiscard]] constexpr bool GetIsHRight() const { return HorizontalAlignment_ == 1; }
        [[nodiscard]] constexpr bool GetIsVBottom() const { return VerticalAlignment_ == 1; }

        INDEX_Property(get = GetIsHRight) bool IsHRight;
        INDEX_Property(get = GetIsVBottom) bool IsVBottom;

    public:
        bool operator==(const Align& other) const
        {
            return (HorizontalAlignment_ == other.HorizontalAlignment_)
                && (VerticalAlignment_ == other.VerticalAlignment_);
        }
        bool operator!=(const Align& other) const
        {
            return (HorizontalAlignment_ != other.HorizontalAlignment_)
                && (VerticalAlignment_ != other.VerticalAlignment_);
        }

    public:
        static const Align Stretch;
        static const Align Center;
        static const Align StretchCenter;
        static const Align CenterStretch;
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

    inline const Align Align::Stretch { Stretch_, Stretch_ };
    inline const Align Align::Center { Center_, Center_ };
    inline const Align Align::StretchCenter { Stretch_, Center_ };
    inline const Align Align::CenterStretch { Center_, Stretch_ };
    inline const Align Align::Left { -1, Stretch_ };
    inline const Align Align::Right { 1, Stretch_ };
    inline const Align Align::Top { Stretch_, -1 };
    inline const Align Align::Bottom { Stretch_, 1 };
    inline const Align Align::LeftCenter { -1, Center_ };
    inline const Align Align::RightCenter { 1, Center_ };
    inline const Align Align::TopCenter { Center_, -1 };
    inline const Align Align::BottomCenter { Center_, 1 };
    inline const Align Align::LeftTop { -1, -1 };
    inline const Align Align::LeftBottom { -1, 1 };
    inline const Align Align::RightTop { 1, -1 };
    inline const Align Align::RightBottom { 1, 1 };
}