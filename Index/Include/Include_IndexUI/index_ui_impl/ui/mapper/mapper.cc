#pragma once

#include "../ui.cc"

#define INDEX_UI_Declare(name)                                                                                        \
    struct name;                                                                                                      \
    struct name##Mapper

#define INDEX_UI_DeclareExplicit(name, mapper_name)                                                                   \
    struct name;                                                                                                      \
    struct mapper_name
#define INDEX_UI_UseMapper(name) using Mapper = name

// UIMapper
namespace Index::UI
{
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
            That->Add(mapper.template DynamicAs<UIMapper>());
        }
    };

    struct UIMapper : IObj<UIMapper>
    {
        UIMapper() = default;

    public:
        List<IPtr<UIMapper>> Children;

        virtual void Add(IPtr<UIMapper> child)
        {
            Children.Add(child);
            OnAdd_(child);
        }
        virtual void Remove(IPtr<UIMapper> child)
        {
            Children.Remove(child);
            OnRemove_(child);
        }

    protected:
        virtual void OnAdd_(const IPtr<UIMapper>& child) { }
        virtual void OnRemove_(const IPtr<UIMapper>& child) { }

    protected:
        template <class T> UIMapper_SubMaker_<UIMapper, T> Sub_() { return UIMapper_SubMaker_<UIMapper, T>(this); }

    public:
        virtual IPtr<UIElement> Make() = 0;

    protected:
        virtual IPtr<UIElement> MakeSelf() { INDEX_THROW("Not implemented."); }
    };

    struct UIElementMapper : virtual UIMapper
    {
        UIElementMapper() = default;

    public:
        string Name = "";
        string Id = "";

        Index::Size Size = AutoS;
        Index::Size MinSize = AutoS;
        Index::Size MaxSize = AutoS;

        Vec4F Margin = { 0 };
        Vec4F Padding = { 0 };

        Align Alignment = Align::Stretch;

#pragma region Other

        float GetWidth() const { return Size.Width; }
        void SetWidth(float value) { Size.Width = value; }
        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        float GetHeight() const { return Size.Height; }
        void SetHeight(float value) { Size.Height = value; }
        INDEX_Property(get = GetHeight, put = SetHeight) float Height;

        bool GetAutoWidth() const { return Size.Width == AutoF; }
        void SetAutoWidth(bool value)
        {
            if (value) Size.Width = AutoF;
        }
        INDEX_Property(get = GetAutoWidth, put = SetAutoWidth) bool AutoWidth;

        bool GetAutoHeight() const { return Size.Height == AutoF; }
        void SetAutoHeight(bool value)
        {
            if (value) Size.Height = AutoF;
        }
        INDEX_Property(get = GetAutoHeight, put = SetAutoHeight) bool AutoHeight;

        float GetMinWidth() const { return MinSize.Width; }
        void SetMinWidth(float value) { MinSize.Width = value; }
        INDEX_Property(get = GetMinWidth, put = SetMinWidth) float MinWidth;

        float GetMinHeight() const { return MinSize.Height; }
        void SetMinHeight(float value) { MinSize.Height = value; }
        INDEX_Property(get = GetMinHeight, put = SetMinHeight) float MinHeight;

        bool GetAutoMinWidth() const { return MinSize.Width == AutoF; }
        void SetAutoMinWidth(bool value)
        {
            if (value) MinSize.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMinWidth, put = SetAutoMinWidth) bool AutoMinWidth;

        bool GetAutoMinHeight() const { return MinSize.Height == AutoF; }
        void SetAutoMinHeight(bool value)
        {
            if (value) MinSize.Height = AutoF;
        }
        INDEX_Property(get = GetAutoMinHeight, put = SetAutoMinHeight) bool AutoMinHeight;

        float GetMaxWidth() const { return MaxSize.Width; }
        void SetMaxWidth(float value) { MaxSize.Width = value; }
        INDEX_Property(get = GetMaxWidth, put = SetMaxWidth) float MaxWidth;

        float GetMaxHeight() const { return MaxSize.Height; }
        void SetMaxHeight(float value) { MaxSize.Height = value; }
        INDEX_Property(get = GetMaxHeight, put = SetMaxHeight) float MaxHeight;

        bool GetAutoMaxWidth() const { return MaxSize.Width == AutoF; }
        void SetAutoMaxWidth(bool value)
        {
            if (value) MaxSize.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMaxWidth, put = SetAutoMaxWidth) bool AutoMaxWidth;

        bool GetAutoMaxHeight() const { return MaxSize.Height == AutoF; }
        void SetAutoMaxHeight(bool value)
        {
            if (value) MaxSize.Height = AutoF;
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
        Index::Size MinSizeOr(float value) { return { MinWidthOr(value), MinHeightOr(value) }; }
        Index::Size MaxSizeOr(float value) { return { MaxWidthOr(value), MaxHeightOr(value) }; }

        float GetMarginLeft() const { return Margin.X; }
        void SetMarginLeft(float value) { Margin.X = value; }
        INDEX_Property(get = GetMarginLeft, put = SetMarginLeft) float MarginLeft;

        bool GetAutoMarginLeft() const { return Margin.X == AutoF; }
        void SetAutoMarginLeft(bool value)
        {
            if (value) Margin.X = AutoF;
        }
        INDEX_Property(get = GetAutoMarginLeft, put = SetAutoMarginLeft) bool AutoMarginLeft;

        float GetMarginTop() const { return Margin.Y; }
        void SetMarginTop(float value) { Margin.Y = value; }
        INDEX_Property(get = GetMarginTop, put = SetMarginTop) float MarginTop;

        bool GetAutoMarginTop() const { return Margin.Y == AutoF; }
        void SetAutoMarginTop(bool value)
        {
            if (value) Margin.Y = AutoF;
        }
        INDEX_Property(get = GetAutoMarginTop, put = SetAutoMarginTop) bool AutoMarginTop;

        float GetMarginRight() const { return Margin.Z; }
        void SetMarginRight(float value) { Margin.Z = value; }
        INDEX_Property(get = GetMarginRight, put = SetMarginRight) float MarginRight;

        bool GetAutoMarginRight() const { return Margin.Z == AutoF; }
        void SetAutoMarginRight(bool value)
        {
            if (value) Margin.Z = AutoF;
        }
        INDEX_Property(get = GetAutoMarginRight, put = SetAutoMarginRight) bool AutoMarginRight;

        float GetMarginBottom() const { return Margin.W; }
        void SetMarginBottom(float value) { Margin.W = value; }
        INDEX_Property(get = GetMarginBottom, put = SetMarginBottom) float MarginBottom;

        bool GetAutoMarginBottom() const { return Margin.W == AutoF; }
        void SetAutoMarginBottom(bool value)
        {
            if (value) Margin.W = AutoF;
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
        Vec4F MarginOr(float value)
        {
            return { MarginLeftOr(value), MarginTopOr(value), MarginRightOr(value), MarginBottomOr(value) };
        }

        float GetPaddingLeft() const { return Padding.X; }
        void SetPaddingLeft(float value) { Padding.X = value; }
        INDEX_Property(get = GetPaddingLeft, put = SetPaddingLeft) float PaddingLeft;

        bool GetAutoPaddingLeft() const { return Padding.X == AutoF; }
        void SetAutoPaddingLeft(bool value)
        {
            if (value) Padding.X = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingLeft, put = SetAutoPaddingLeft) bool AutoPaddingLeft;

        float GetPaddingTop() const { return Padding.Y; }
        void SetPaddingTop(float value) { Padding.Y = value; }
        INDEX_Property(get = GetPaddingTop, put = SetPaddingTop) float PaddingTop;

        bool GetAutoPaddingTop() const { return Padding.Y == AutoF; }
        void SetAutoPaddingTop(bool value)
        {
            if (value) Padding.Y = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingTop, put = SetAutoPaddingTop) bool AutoPaddingTop;

        float GetPaddingRight() const { return Padding.Z; }
        void SetPaddingRight(float value) { Padding.Z = value; }
        INDEX_Property(get = GetPaddingRight, put = SetPaddingRight) float PaddingRight;

        bool GetAutoPaddingRight() const { return Padding.Z == AutoF; }
        void SetAutoPaddingRight(bool value)
        {
            if (value) Padding.Z = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingRight, put = SetAutoPaddingRight) bool AutoPaddingRight;

        float GetPaddingBottom() const { return Padding.W; }
        void SetPaddingBottom(float value) { Padding.W = value; }
        INDEX_Property(get = GetPaddingBottom, put = SetPaddingBottom) float PaddingBottom;

        bool GetAutoPaddingBottom() const { return Padding.W == AutoF; }
        void SetAutoPaddingBottom(bool value)
        {
            if (value) Padding.W = AutoF;
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
        Vec4F PaddingOr(float value)
        {
            return { PaddingLeftOr(value), PaddingTopOr(value), PaddingRightOr(value), PaddingBottomOr(value) };
        }
#pragma endregion

    protected:
        template <class T> void Impl_(T& e)
        {
            e.Name = Name;
            e.Id = Id;

            e.Size = Size;
            e.MinSize = MinSize;
            e.MaxSize = MaxSize;

            e.Margin = Margin;
            e.Padding = Padding;

            e.Alignment = Alignment;
        }
    };
}