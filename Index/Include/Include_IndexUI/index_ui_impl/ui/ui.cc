#pragma once

#include "../index.cc"
#include <SimpleYoga/yoga/YGNode.h>
#include <SimpleYoga/yoga/Yoga.h>

#define INDEX_UI_Declare(name)                                                                                                                                 \
    struct name;                                                                                                                                               \
    struct name##Mapper
#define INDEX_UI_DeclareExplicit(name, mapper_name)                                                                                                            \
    struct name;                                                                                                                                               \
    struct mapper_name
#define INDEX_UI_UseMapper(name) using Mapper = name

namespace Index::UI2
{
    struct UIElement;
    struct UIMapper;

    struct UIElementAnimation;
    template <class T, class TElement> struct UIElementPropertyAnimation;
}

// Variables
namespace Index::UI2
{
    constexpr float AutoF = Limits::FloatMax;
}

// UIUnit
namespace Index::UI2
{
    enum class UIUnit
    {
        Undefined,
        Point,
        Percent,
        Auto
    };

    inline UIUnit UIUnitFromYGUnit(YGUnit unit)
    {
        switch (unit)
        {
        case YGUnitPoint:
            return UIUnit::Point;
        case YGUnitPercent:
            return UIUnit::Percent;
        case YGUnitAuto:
            return UIUnit::Auto;
        default:
            return UIUnit::Undefined;
        }
    }
}

// UIElementAnimation
namespace Index::UI2
{
    struct UIElementAnimation : IObj<UIElementAnimation>
    {
        WPtr<UIElement> Element;

        virtual void Update() = 0;

        virtual bool GetIsDone() = 0;
        INDEX_Property(get = GetIsDone) bool IsDone;
    };

    template <class TAnimation, class TElement = UIElement> struct UIElementPropertyAnimation : UIElementAnimation
    {
    public:
        UIElementPropertyAnimation() = default;
        UIElementPropertyAnimation(WPtr<UIElement> element, Func<void(TElement*, typename TAnimation::TType)> propertySetter, TAnimation animation)
            : Animation_(animation)
            , PropertySetter_(propertySetter)
        {
            Element = Move(element);
        }

    protected:
        Func<void(TElement*, typename TAnimation::TType)> PropertySetter_;
        Nullable<TAnimation> Animation_;

    public:
        void Update() override
        {
            if (IsDone) return;
            if (auto element = Element.Lock) PropertySetter_(element.Ptr, Animation_.Value.Value);
        }

        bool GetIsDone() override { return !Animation_.HasValue || Animation_.Value.HasFinished; }

        TAnimation& GetAnimation() const { return Animation_; }
        INDEX_Property(get = GetAnimation) TAnimation& Animation;
    };
}

// UIElement
namespace Index::UI2
{
    struct UIElement : IObj<UIElement>
    {
    protected:
        string Name_;
        string Id_;

    public:
        string GetName() const { return Name_; }
        void SetName(string value) { Name_ = value; }
        INDEX_Property(get = GetName, put = SetName) string Name;

        string GetId() const { return Id_; }
        void SetId(string value) { Id_ = value; }
        INDEX_Property(get = GetId, put = SetId) string Id;

    protected:
        WPtr<UIElement> Parent_;
        List<IPtr<UIElement>> Children_;

    public:
        WPtr<UIElement> GetParent() const { return Parent_; }
        INDEX_Property(get = GetParent) WPtr<UIElement> Parent;

        const List<IPtr<UIElement>>& GetChildren() const { return Children_; }
        INDEX_Property(get = GetChildren) const List<IPtr<UIElement>>& Children;

    protected:
        void Children_Add_(const IPtr<UIElement>& child) { Children_.Add(child); }
        void Children_Remove_(const IPtr<UIElement>& child) { Children_.Remove(child); }
        bool Children_Contains_(const IPtr<UIElement>& child) { return Children_.Contains(child); }

    protected:
        Index::Size Size_ = { AutoF, AutoF };
        Index::Size MinSize_ = { AutoF, AutoF };
        Index::Size MaxSize_ = { AutoF, AutoF };
        Vec4F Margin_ = { 0 };
        Vec4F Padding_ = { 0 };

    public:
        Index::Size& GetSize() { return Size_; }
        const Index::Size& GetSize() const { return Size_; }
        void SetSize(Index::Size value) { Size_ = value; }
        INDEX_Property(get = GetSize, put = SetSize) Index::Size& Size;

        Index::Size& GetMinSize() { return MinSize_; }
        const Index::Size& GetMinSize() const { return MinSize_; }
        void SetMinSize(Index::Size value) { MinSize_ = value; }
        INDEX_Property(get = GetMinSize, put = SetMinSize) Index::Size& MinSize;

        Index::Size& GetMaxSize() { return MaxSize_; }
        const Index::Size& GetMaxSize() const { return MaxSize_; }
        void SetMaxSize(Index::Size value) { MaxSize_ = value; }
        INDEX_Property(get = GetMaxSize, put = SetMaxSize) Index::Size& MaxSize;

        float GetWidth() const { return Size_.Width; }
        void SetWidth(float value) { Size_.Width = value; }
        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        float GetHeight() const { return Size_.Height; }
        void SetHeight(float value) { Size_.Height = value; }
        INDEX_Property(get = GetHeight, put = SetHeight) float Height;

        bool GetAutoWidth() const { return Size_.Width == AutoF; }
        void SetAutoWidth(bool value)
        {
            if (value) Size_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoWidth, put = SetAutoWidth) bool AutoWidth;

        bool GetAutoHeight() const { return Size_.Height == AutoF; }
        void SetAutoHeight(bool value)
        {
            if (value) Size_.Height = AutoF;
        }
        INDEX_Property(get = GetAutoHeight, put = SetAutoHeight) bool AutoHeight;

        float GetMinWidth() const { return MinSize_.Width; }
        void SetMinWidth(float value) { MinSize_.Width = value; }
        INDEX_Property(get = GetMinWidth, put = SetMinWidth) float MinWidth;

        float GetMinHeight() const { return MinSize_.Height; }
        void SetMinHeight(float value) { MinSize_.Height = value; }
        INDEX_Property(get = GetMinHeight, put = SetMinHeight) float MinHeight;

        bool GetAutoMinWidth() const { return MinSize_.Width == AutoF; }
        void SetAutoMinWidth(bool value)
        {
            if (value) MinSize_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMinWidth, put = SetAutoMinWidth) bool AutoMinWidth;

        bool GetAutoMinHeight() const { return MinSize_.Height == AutoF; }
        void SetAutoMinHeight(bool value)
        {
            if (value) MinSize_.Height = AutoF;
        }
        INDEX_Property(get = GetAutoMinHeight, put = SetAutoMinHeight) bool AutoMinHeight;

        float GetMaxWidth() const { return MaxSize_.Width; }
        void SetMaxWidth(float value) { MaxSize_.Width = value; }
        INDEX_Property(get = GetMaxWidth, put = SetMaxWidth) float MaxWidth;

        float GetMaxHeight() const { return MaxSize_.Height; }
        void SetMaxHeight(float value) { MaxSize_.Height = value; }
        INDEX_Property(get = GetMaxHeight, put = SetMaxHeight) float MaxHeight;

        bool GetAutoMaxWidth() const { return MaxSize_.Width == AutoF; }
        void SetAutoMaxWidth(bool value)
        {
            if (value) MaxSize_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMaxWidth, put = SetAutoMaxWidth) bool AutoMaxWidth;

        bool GetAutoMaxHeight() const { return MaxSize_.Height == AutoF; }
        void SetAutoMaxHeight(bool value)
        {
            if (value) MaxSize_.Height = AutoF;
        }
        INDEX_Property(get = GetAutoMaxHeight, put = SetAutoMaxHeight) bool AutoMaxHeight;

        float WidthOr(float value)
        {
            if (AutoWidth)
                return value;
            else
                return Width;
        }
        float HeightOr(float value)
        {
            if (AutoHeight)
                return value;
            else
                return Height;
        }
        float MinWidthOr(float value)
        {
            if (AutoMinWidth)
                return value;
            else
                return MinWidth;
        }
        float MinHeightOr(float value)
        {
            if (AutoMinHeight)
                return value;
            else
                return MinHeight;
        }
        float MaxWidthOr(float value)
        {
            if (AutoMaxWidth)
                return value;
            else
                return MaxWidth;
        }
        float MaxHeightOr(float value)
        {
            if (AutoMaxHeight)
                return value;
            else
                return MaxHeight;
        }
        Index::Size SizeOr(float value) { return { WidthOr(value), HeightOr(value) }; }

        Vec4F& GetMargin() { return Margin_; }
        const Vec4F& GetMargin() const { return Margin_; }
        void SetMargin(Vec4F value) { Margin_ = value; }
        INDEX_Property(get = GetMargin, put = SetMargin) Vec4F& Margin;

        float GetMarginLeft() const { return Margin_.X; }
        void SetMarginLeft(float value) { Margin_.X = value; }
        INDEX_Property(get = GetMarginLeft, put = SetMarginLeft) float MarginLeft;

        bool GetAutoMarginLeft() const { return Margin_.X == AutoF; }
        void SetAutoMarginLeft(bool value)
        {
            if (value) Margin_.X = AutoF;
        }
        INDEX_Property(get = GetAutoMarginLeft, put = SetAutoMarginLeft) bool AutoMarginLeft;

        float GetMarginTop() const { return Margin_.Y; }
        void SetMarginTop(float value) { Margin_.Y = value; }
        INDEX_Property(get = GetMarginTop, put = SetMarginTop) float MarginTop;

        bool GetAutoMarginTop() const { return Margin_.Y == AutoF; }
        void SetAutoMarginTop(bool value)
        {
            if (value) Margin_.Y = AutoF;
        }
        INDEX_Property(get = GetAutoMarginTop, put = SetAutoMarginTop) bool AutoMarginTop;

        float GetMarginRight() const { return Margin_.Z; }
        void SetMarginRight(float value) { Margin_.Z = value; }
        INDEX_Property(get = GetMarginRight, put = SetMarginRight) float MarginRight;

        bool GetAutoMarginRight() const { return Margin_.Z == AutoF; }
        void SetAutoMarginRight(bool value)
        {
            if (value) Margin_.Z = AutoF;
        }
        INDEX_Property(get = GetAutoMarginRight, put = SetAutoMarginRight) bool AutoMarginRight;

        float GetMarginBottom() const { return Margin_.W; }
        void SetMarginBottom(float value) { Margin_.W = value; }
        INDEX_Property(get = GetMarginBottom, put = SetMarginBottom) float MarginBottom;

        bool GetAutoMarginBottom() const { return Margin_.W == AutoF; }
        void SetAutoMarginBottom(bool value)
        {
            if (value) Margin_.W = AutoF;
        }
        INDEX_Property(get = GetAutoMarginBottom, put = SetAutoMarginBottom) bool AutoMarginBottom;

        float MarginLeftOr(float value)
        {
            if (AutoMarginLeft)
                return value;
            else
                return MarginLeft;
        }
        float MarginTopOr(float value)
        {
            if (AutoMarginTop)
                return value;
            else
                return MarginTop;
        }
        float MarginRightOr(float value)
        {
            if (AutoMarginRight)
                return value;
            else
                return MarginRight;
        }
        float MarginBottomOr(float value)
        {
            if (AutoMarginBottom)
                return value;
            else
                return MarginBottom;
        }
        Vec4F MarginOr(float value) { return { MarginLeftOr(value), MarginTopOr(value), MarginRightOr(value), MarginBottomOr(value) }; }

        Vec4F& GetPadding() { return Padding_; }
        const Vec4F& GetPadding() const { return Padding_; }
        void SetPadding(Vec4F value) { Padding_ = value; }
        INDEX_Property(get = GetPadding, put = SetPadding) Vec4F& Padding;

        float GetPaddingLeft() const { return Padding_.X; }
        void SetPaddingLeft(float value) { Padding_.X = value; }
        INDEX_Property(get = GetPaddingLeft, put = SetPaddingLeft) float PaddingLeft;

        bool GetAutoPaddingLeft() const { return Padding_.X == AutoF; }
        void SetAutoPaddingLeft(bool value)
        {
            if (value) Padding_.X = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingLeft, put = SetAutoPaddingLeft) bool AutoPaddingLeft;

        float GetPaddingTop() const { return Padding_.Y; }
        void SetPaddingTop(float value) { Padding_.Y = value; }
        INDEX_Property(get = GetPaddingTop, put = SetPaddingTop) float PaddingTop;

        bool GetAutoPaddingTop() const { return Padding_.Y == AutoF; }
        void SetAutoPaddingTop(bool value)
        {
            if (value) Padding_.Y = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingTop, put = SetAutoPaddingTop) bool AutoPaddingTop;

        float GetPaddingRight() const { return Padding_.Z; }
        void SetPaddingRight(float value) { Padding_.Z = value; }
        INDEX_Property(get = GetPaddingRight, put = SetPaddingRight) float PaddingRight;

        bool GetAutoPaddingRight() const { return Padding_.Z == AutoF; }
        void SetAutoPaddingRight(bool value)
        {
            if (value) Padding_.Z = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingRight, put = SetAutoPaddingRight) bool AutoPaddingRight;

        float GetPaddingBottom() const { return Padding_.W; }
        void SetPaddingBottom(float value) { Padding_.W = value; }
        INDEX_Property(get = GetPaddingBottom, put = SetPaddingBottom) float PaddingBottom;

        bool GetAutoPaddingBottom() const { return Padding_.W == AutoF; }
        void SetAutoPaddingBottom(bool value)
        {
            if (value) Padding_.W = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingBottom, put = SetAutoPaddingBottom) bool AutoPaddingBottom;

        float PaddingLeftOr(float value)
        {
            if (AutoPaddingLeft)
                return value;
            else
                return PaddingLeft;
        }
        float PaddingTopOr(float value)
        {
            if (AutoPaddingTop)
                return value;
            else
                return PaddingTop;
        }
        float PaddingRightOr(float value)
        {
            if (AutoPaddingRight)
                return value;
            else
                return PaddingRight;
        }
        float PaddingBottomOr(float value)
        {
            if (AutoPaddingBottom)
                return value;
            else
                return PaddingBottom;
        }
        Vec4F PaddingOr(float value) { return { PaddingLeftOr(value), PaddingTopOr(value), PaddingRightOr(value), PaddingBottomOr(value) }; }

    protected:
        UInt64 ComputeFrame_ = 0;
        Index::Size ComputedSize_;

    public:
        UInt64 GetComputeFrame() const { return ComputeFrame_; }
        INDEX_Property(get = GetComputeFrame) UInt64 ComputeFrame;

        Index::Size GetComputedSize() const { return ComputedSize_; }
        INDEX_Property(get = GetComputedSize) Index::Size ComputedSize;

        float GetComputedWidth() const { return ComputedSize_.Width; }
        INDEX_Property(get = GetComputedWidth, put = SetComputedWidth) float ComputedWidth;

        float GetComputedHeight() const { return ComputedSize_.Height; }
        INDEX_Property(get = GetComputedHeight, put = SetComputedHeight) float ComputedHeight;
    };

    /*
        template <class TThis, class T> struct UIMapper_SubMaker_
        {
        protected:
            TThis* That;

        public:
            explicit UIMapper_SubMaker_(TThis* that)
                : That(that)
            {
            }

            void operator+=(Func<void(TThis&, typename T::Mapper&)> f)
            {
                auto mapper = INew<typename T::Mapper>();
                f(*That, mapper.Value);
                That->Content.Add(mapper.template DynamicAs<UIMapper>());
            }
        };

        struct UIMapper : IObj<UIMapper>
        {
        public:
            string Name;

        public:
            List<IPtr<UIMapper>> Content;

            virtual void Add(IPtr<UIMapper> child) { Content.Add(child); }
            virtual void Remove(IPtr<UIMapper> child) { Content.Remove(child); }

            template <class T> UIMapper_SubMaker_<UIMapper, T> Sub() { return UIMapper_SubMaker_<UIMapper, T>(this); }

        protected:
            virtual IPtr<UIElement> MakeSelf() { INDEX_THROW("Not implemented."); };

        public:
            virtual IPtr<UIElement> Make() = 0;
        };
        */
}