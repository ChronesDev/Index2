#pragma once

#include "../index.cc"
#include <SimpleYoga/yoga/YGNode.h>
#include <SimpleYoga/yoga/Yoga.h>

/**
 * @param field: The internal field
 * @param value: The current value
 */
#define INDEX_UI_LayoutDirtyChecker_(field, value)                                                                    \
    if (this->field != value) this->MakeLayoutDirty();

#define INDEX_UI_Declare(name)                                                                                        \
    struct name;                                                                                                      \
    struct name##Mapper
#define INDEX_UI_DeclareExplicit(name, mapper_name)                                                                   \
    struct name;                                                                                                      \
    struct mapper_name
#define INDEX_UI_UseMapper(name) using Mapper = name

namespace Index::UI
{
    struct UIElement;
    //struct UIMapper;
}

// Variables
namespace Index::UI
{
    constexpr float AutoF = Limits::FloatMax;
}

// UIElement
namespace Index::UI
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
        void SetSize(Index::Size value) { INDEX_UI_LayoutDirtyChecker_(Size_, value) Size_ = value; }
        INDEX_Property(get = GetSize, put = SetSize) Index::Size& Size;

        Index::Size& GetMinSize() { return MinSize_; }
        const Index::Size& GetMinSize() const { return MinSize_; }
        void SetMinSize(Index::Size value) { INDEX_UI_LayoutDirtyChecker_(MinSize_, value) MinSize_ = value; }
        INDEX_Property(get = GetMinSize, put = SetMinSize) Index::Size& MinSize;

        Index::Size& GetMaxSize() { return MaxSize_; }
        const Index::Size& GetMaxSize() const { return MaxSize_; }
        void SetMaxSize(Index::Size value) { INDEX_UI_LayoutDirtyChecker_(MaxSize_, value) MaxSize_ = value; }
        INDEX_Property(get = GetMaxSize, put = SetMaxSize) Index::Size& MaxSize;

        float GetWidth() const { return Size_.Width; }
        void SetWidth(float value) { INDEX_UI_LayoutDirtyChecker_(Size_.Width, value) Size_.Width = value; }
        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        float GetHeight() const { return Size_.Height; }
        void SetHeight(float value) { INDEX_UI_LayoutDirtyChecker_(Size_.Height, value) Size_.Height = value; }
        INDEX_Property(get = GetHeight, put = SetHeight) float Height;

        bool GetAutoWidth() const { return Size_.Width == AutoF; }
        void SetAutoWidth(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Size_.Width, AutoF) if (value) Size_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoWidth, put = SetAutoWidth) bool AutoWidth;

        bool GetAutoHeight() const { return Size_.Height == AutoF; }
        void SetAutoHeight(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Size_.Height, AutoF) if (value) Size_.Height = AutoF;
        }
        INDEX_Property(get = GetAutoHeight, put = SetAutoHeight) bool AutoHeight;

        float GetMinWidth() const { return MinSize_.Width; }
        void SetMinWidth(float value) { INDEX_UI_LayoutDirtyChecker_(MinSize_.Width, value) MinSize_.Width = value; }
        INDEX_Property(get = GetMinWidth, put = SetMinWidth) float MinWidth;

        float GetMinHeight() const { return MinSize_.Height; }
        void SetMinHeight(float value)
        {
            INDEX_UI_LayoutDirtyChecker_(MinSize_.Height, value) MinSize_.Height = value;
        }
        INDEX_Property(get = GetMinHeight, put = SetMinHeight) float MinHeight;

        bool GetAutoMinWidth() const { return MinSize_.Width == AutoF; }
        void SetAutoMinWidth(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(MinSize_.Width, AutoF) if (value) MinSize_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMinWidth, put = SetAutoMinWidth) bool AutoMinWidth;

        bool GetAutoMinHeight() const { return MinSize_.Height == AutoF; }
        void SetAutoMinHeight(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(MinSize_.Height, AutoF) if (value) MinSize_.Height = AutoF;
        }
        INDEX_Property(get = GetAutoMinHeight, put = SetAutoMinHeight) bool AutoMinHeight;

        float GetMaxWidth() const { return MaxSize_.Width; }
        void SetMaxWidth(float value) { MaxSize_.Width = value; }
        INDEX_Property(get = GetMaxWidth, put = SetMaxWidth) float MaxWidth;

        float GetMaxHeight() const { return MaxSize_.Height; }
        void SetMaxHeight(float value)
        {
            INDEX_UI_LayoutDirtyChecker_(MaxSize_.Height, value) MaxSize_.Height = value;
        }
        INDEX_Property(get = GetMaxHeight, put = SetMaxHeight) float MaxHeight;

        bool GetAutoMaxWidth() const { return MaxSize_.Width == AutoF; }
        void SetAutoMaxWidth(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(MaxSize_.Width, AutoF) if (value) MaxSize_.Width = AutoF;
        }
        INDEX_Property(get = GetAutoMaxWidth, put = SetAutoMaxWidth) bool AutoMaxWidth;

        bool GetAutoMaxHeight() const { return MaxSize_.Height == AutoF; }
        void SetAutoMaxHeight(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(MaxSize_.Height, AutoF) if (value) MaxSize_.Height = AutoF;
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
        void SetMargin(Vec4F value) { INDEX_UI_LayoutDirtyChecker_(Margin_, value) Margin_ = value; }
        INDEX_Property(get = GetMargin, put = SetMargin) Vec4F& Margin;

        float GetMarginLeft() const { return Margin_.X; }
        void SetMarginLeft(float value) { INDEX_UI_LayoutDirtyChecker_(Margin_.X, value) Margin_.X = value; }
        INDEX_Property(get = GetMarginLeft, put = SetMarginLeft) float MarginLeft;

        bool GetAutoMarginLeft() const { return Margin_.X == AutoF; }
        void SetAutoMarginLeft(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Margin_.X, AutoF) if (value) Margin_.X = AutoF;
        }
        INDEX_Property(get = GetAutoMarginLeft, put = SetAutoMarginLeft) bool AutoMarginLeft;

        float GetMarginTop() const { return Margin_.Y; }
        void SetMarginTop(float value) { INDEX_UI_LayoutDirtyChecker_(Margin_.Y, value) Margin_.Y = value; }
        INDEX_Property(get = GetMarginTop, put = SetMarginTop) float MarginTop;

        bool GetAutoMarginTop() const { return Margin_.Y == AutoF; }
        void SetAutoMarginTop(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Margin_.Y, AutoF) if (value) Margin_.Y = AutoF;
        }
        INDEX_Property(get = GetAutoMarginTop, put = SetAutoMarginTop) bool AutoMarginTop;

        float GetMarginRight() const { return Margin_.Z; }
        void SetMarginRight(float value) { INDEX_UI_LayoutDirtyChecker_(Margin_.Z, value) Margin_.Z = value; }
        INDEX_Property(get = GetMarginRight, put = SetMarginRight) float MarginRight;

        bool GetAutoMarginRight() const { return Margin_.Z == AutoF; }
        void SetAutoMarginRight(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Margin_.Z, AutoF) if (value) Margin_.Z = AutoF;
        }
        INDEX_Property(get = GetAutoMarginRight, put = SetAutoMarginRight) bool AutoMarginRight;

        float GetMarginBottom() const { return Margin_.W; }
        void SetMarginBottom(float value) { INDEX_UI_LayoutDirtyChecker_(Margin_.W, value) Margin_.W = value; }
        INDEX_Property(get = GetMarginBottom, put = SetMarginBottom) float MarginBottom;

        bool GetAutoMarginBottom() const { return Margin_.W == AutoF; }
        void SetAutoMarginBottom(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Margin_.W, AutoF) if (value) Margin_.W = AutoF;
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

        Vec4F& GetPadding() { return Padding_; }
        const Vec4F& GetPadding() const { return Padding_; }
        void SetPadding(Vec4F value) { INDEX_UI_LayoutDirtyChecker_(Padding_, value) Padding_ = value; }
        INDEX_Property(get = GetPadding, put = SetPadding) Vec4F& Padding;

        float GetPaddingLeft() const { return Padding_.X; }
        void SetPaddingLeft(float value) { INDEX_UI_LayoutDirtyChecker_(Padding_.X, value) Padding_.X = value; }
        INDEX_Property(get = GetPaddingLeft, put = SetPaddingLeft) float PaddingLeft;

        bool GetAutoPaddingLeft() const { return Padding_.X == AutoF; }
        void SetAutoPaddingLeft(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Padding_.X, AutoF) if (value) Padding_.X = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingLeft, put = SetAutoPaddingLeft) bool AutoPaddingLeft;

        float GetPaddingTop() const { return Padding_.Y; }
        void SetPaddingTop(float value) { INDEX_UI_LayoutDirtyChecker_(Padding_.Y, value) Padding_.Y = value; }
        INDEX_Property(get = GetPaddingTop, put = SetPaddingTop) float PaddingTop;

        bool GetAutoPaddingTop() const { return Padding_.Y == AutoF; }
        void SetAutoPaddingTop(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Padding_.Y, AutoF) if (value) Padding_.Y = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingTop, put = SetAutoPaddingTop) bool AutoPaddingTop;

        float GetPaddingRight() const { return Padding_.Z; }
        void SetPaddingRight(float value) { INDEX_UI_LayoutDirtyChecker_(Padding_.Z, value) Padding_.Z = value; }
        INDEX_Property(get = GetPaddingRight, put = SetPaddingRight) float PaddingRight;

        bool GetAutoPaddingRight() const { return Padding_.Z == AutoF; }
        void SetAutoPaddingRight(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Padding_.Z, AutoF) if (value) Padding_.Z = AutoF;
        }
        INDEX_Property(get = GetAutoPaddingRight, put = SetAutoPaddingRight) bool AutoPaddingRight;

        float GetPaddingBottom() const { return Padding_.W; }
        void SetPaddingBottom(float value) { INDEX_UI_LayoutDirtyChecker_(Padding_.W, value) Padding_.W = value; }
        INDEX_Property(get = GetPaddingBottom, put = SetPaddingBottom) float PaddingBottom;

        bool GetAutoPaddingBottom() const { return Padding_.W == AutoF; }
        void SetAutoPaddingBottom(bool value)
        {
            INDEX_UI_LayoutDirtyChecker_(Padding_.W, AutoF) if (value) Padding_.W = AutoF;
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

    protected:
        Align Alignment_ = Align::Stretch;

    public:
        Align GetAlignment() const { return Alignment_; }
        void SetAlignment(Align value) { INDEX_UI_LayoutDirtyChecker_(Alignment_, value) Alignment_ = value; }
        INDEX_Property(get = GetAlignment, put = SetAlignment) Align Alignment;

    protected:
        bool LayoutDirty_ = false;
        bool ComputedLayoutDirty_ = false;
        bool ComputedLayoutPositionDirty_ = false;

    public:
        bool GetIsLayoutDirty() const { return LayoutDirty_; }
        void MakeLayoutDirty() { LayoutDirty_ = true; }
        constexpr void MakeLayoutDirtyIf(bool condition)
        {
            if (condition) MakeLayoutDirty();
        }
        void PolishLayout() { LayoutDirty_ = false; }
        INDEX_Property(get = GetIsLayoutDirty) bool IsLayoutDirty;

        bool GetIsComputedLayoutDirty() const { return ComputedLayoutDirty_; }
        void MakeComputedLayoutDirty() { ComputedLayoutDirty_ = true; }
        constexpr void MakeComputedLayoutDirtyIf(bool condition)
        {
            if (condition) MakeComputedLayoutDirty();
        }
        void PolishComputedLayout() { ComputedLayoutDirty_ = false; }
        INDEX_Property(get = GetIsComputedLayoutDirty) bool IsComputedLayoutDirty;

        bool GetIsComputedLayoutPositionDirty() const { return ComputedLayoutPositionDirty_; }
        void MakeComputedLayoutPositionDirty() { ComputedLayoutPositionDirty_ = true; }
        constexpr void MakeComputedLayoutPositionDirtyIf(bool condition)
        {
            if (condition) MakeComputedLayoutPositionDirty();
        }
        void PolishComputedLayoutPosition() { ComputedLayoutPositionDirty_ = false; }
        INDEX_Property(get = GetIsComputedLayoutPositionDirty) bool IsComputedLayoutPositionDirty;

    protected:
        UInt64 ComputeFrame_ = 0;
        Index::Size ComputedMinSize_;
        Index::Size ComputedMaxSize_;
        Rect ComputedLayout_;

    public:
        UInt64 GetComputeFrame() const { return ComputeFrame_; }
        INDEX_Property(get = GetComputeFrame) UInt64 ComputeFrame;

        Index::Size GetComputedMinSize() const { return ComputedMinSize_; }
        INDEX_Property(get = GetComputedMinSize) Index::Size ComputedMinSize;

        float GetComputedMinWidth() const { return ComputedMinSize_.Width; }
        INDEX_Property(get = GetComputedMinWidth) float ComputedMinWidth;

        float GetComputedMinHeight() const { return ComputedMinSize_.Height; }
        INDEX_Property(get = GetComputedMinHeight) float ComputedMinHeight;

        Index::Size GetComputedMaxSize() const { return ComputedMaxSize_; }
        INDEX_Property(get = GetComputedMaxSize) Index::Size ComputedMaxSize;

        float GetComputedMaxWidth() const { return ComputedMaxSize_.Width; }
        INDEX_Property(get = GetComputedMaxWidth) float ComputedMaxWidth;

        float GetComputedMaxHeight() const { return ComputedMaxSize_.Height; }
        INDEX_Property(get = GetComputedMaxHeight) float ComputedMaxHeight;

        Rect GetComputedLayout() const { return ComputedLayout_; }
        INDEX_Property(get = GetComputedLayout) Rect ComputedLayout;

    protected:
        virtual bool ShouldComputeSelf_() { return IsLayoutDirty; }

        virtual bool AreChildrenLayoutDirty_()
        {
            for (auto& c : Children_)
            {
                if (c->IsLayoutDirty) return true;
            }
            return false;
        }
        virtual bool AreAllChildrenLayoutDirty_()
        {
            for (auto& c : Children_)
            {
                if (!c->IsLayoutDirty) return false;
            }
            return true;
        }

        virtual bool AreChildrenComputedLayoutDirty_()
        {
            for (auto& c : Children_)
            {
                if (c->IsComputedLayoutDirty) return true;
            }
            return false;
        }
        virtual bool AreAllChildrenComputedLayoutDirty_()
        {
            for (auto& c : Children_)
            {
                if (!c->IsComputedLayoutDirty) return false;
            }
            return true;
        }

    public:
        /**
         * @brief Determines whether it should compute the layout
         */
        INDEX_Property(get = GetShouldCompute) bool ShouldCompute;
        virtual bool GetShouldCompute() { return ShouldComputeSelf_() || AreChildrenLayoutDirty_(); }

    public:
        /**
         * @brief Computes the layout of itself and its children
         */
        virtual void ComputeLayout(UInt64 frame)
        {
            if (frame == 0) ForceComputeLayout();
            ComputeFrame_ = frame;

            ComputeChildrenLayout_(frame);
            if (ShouldCompute)
            {
                OnComputeLayout();
                MakeComputedLayoutPositionDirty();
            }
        }

        /**
         * @brief Computes the layout of itself and its children. Ignores IsDirty and FrameIndex
         */
        virtual void ForceComputeLayout()
        {
            ForceComputeChildrenLayout_();
            OnComputeLayout();
        }

        /**
         * @brief Computes the layout of itself and its children.
         * @note RECURSIVE
         */
        virtual void SubComputeLayout(UInt64 frame)
        {
            if (frame == ComputeFrame_) return;
            ComputeFrame_ = frame;

            ComputeChildrenLayout_(frame);
            if (ShouldCompute)
            {
                OnComputeLayout();
                MakeComputedLayoutPositionDirty();
            }
        }

        /**
         * @brief Forces the computing the layout of itself and its children. Ignores IsDirty and FrameIndex
         * @note RECURSIVE
         */
        virtual void SubForceComputeLayout()
        {
            ForceComputeChildrenLayout_();
            OnComputeLayout();
            MakeComputedLayoutPositionDirty();
        }

        virtual void ComputeLayoutPosition(Rect i)
        {
            OnComputeLayoutPosition(i);
            PolishComputedLayoutPosition();
        }

    protected:
        virtual void ComputeChildrenLayout_(UInt64 frame)
        {
            for (auto& c : Children_)
            {
                c->SubComputeLayout(frame);
                MakeComputedLayoutPositionDirtyIf(c->IsComputedLayoutPositionDirty);
            }
        }

        virtual void ForceComputeChildrenLayout_()
        {
            for (auto& c : Children_)
            {
                c->SubForceComputeLayout();
            }
        }

    public:
        /**
         * @brief Computes its own layout
         */
        virtual void OnComputeLayout()
        {
            Index::Size min = ApplyPadding_(FitRectToChildren_());
            Index::Size max = { AutoF };
            ComputedMinSize_ = ApplyMargin_(min);
            ComputedMaxSize_ = ApplyMargin_(max);

            PolishLayout();
            PolishComputedLayout();
        }

        /**
         * @brief Computes its own layout position
         * @param i: The layout
         */
        virtual void OnComputeLayoutPosition(Rect i)
        {
            Rect r = AlignToComputedLayout_(i);
            Rect rp = Rect_ResizeShrinkOr_Padding_(r, 0);

            ComputedLayout_ = rp;

            for (auto& c : Children_)
            {
                if (c->IsComputedLayoutPositionDirty) c->ComputeLayoutPosition(rp);
            }

            PolishComputedLayoutPosition();
        }

    public:
        /**
         * @brief Renders the element
         */
        virtual void Render()
        {
            OnPreRender();

            for (auto& c : Children_)
            {
                c->Render();
            }

            OnRender();
        }

        /**
         * @brief OnPreRender
         */
        virtual void OnPreRender() { }

        /**
         * @brief OnRender
         */
        virtual void OnRender() { }

    protected:
        Index::Size ApplyMargin_(Index::Size s) { return Rect_ResizeExpand_Margin_({ 0, 0, s.Width, s.Height }).Size; }
        Index::Size ApplyPadding_(Index::Size s)
        {
            return Rect_ResizeExpand_Padding_({ 0, 0, s.Width, s.Height }).Size;
        }
        Index::Size ApplyMarginAndPadding_(Index::Size s) { return ApplyMargin_(ApplyPadding_(s)); }

        Index::Size FitRectToChildren_()
        {
            Index::Size s;
            for (auto& c : Children_)
            {
                float width = c->ComputedMinWidth;
                if (s.Width < width) s.Width = width;

                float height = c->ComputedMinHeight;
                if (s.Height < height) s.Height = height;
            }
            return s;
        }

    protected:
        Rect Rect_Expand_Margin_(Rect r)
        {
            return { r.X - MarginLeft, r.Y - MarginTop, r.Width + MarginRight, r.Height + MarginBottom };
        }
        Rect Rect_ResizeExpand_Margin_(Rect r)
        {
            return { r.X, r.Y, r.Width + MarginLeft + MarginRight, r.Height + MarginTop + MarginBottom };
        }
        Rect Rect_ExpandOr_Margin_(Rect r, float value)
        {
            return { r.X - MarginLeftOr(value), r.Y - MarginTopOr(value), r.Width + MarginRightOr(value),
                r.Height + MarginBottomOr(value) };
        }
        Rect Rect_ResizeExpandOr_Margin_(Rect r, float value)
        {
            return { r.X, r.Y, r.Width + MarginLeftOr(value) + MarginRightOr(value),
                r.Height + MarginTopOr(value) + MarginBottomOr(value) };
        }

        Rect Rect_Expand_Padding_(Rect r)
        {
            return { r.X - PaddingLeft, r.Y - PaddingTop, r.Width + PaddingRight, r.Height + PaddingBottom };
        }
        Rect Rect_ResizeExpand_Padding_(Rect r)
        {
            return { r.X, r.Y, r.Width + PaddingLeft + PaddingRight, r.Height + PaddingTop + PaddingBottom };
        }
        Rect Rect_ExpandOr_Padding_(Rect r, float value)
        {
            return { r.X - PaddingLeftOr(value), r.Y - PaddingTopOr(value), r.Width + PaddingRightOr(value),
                r.Height + PaddingBottomOr(value) };
        }
        Rect Rect_ResizeExpandOr_Padding_(Rect r, float value)
        {
            return { r.X, r.Y, r.Width + PaddingLeftOr(value) + PaddingRightOr(value),
                r.Height + PaddingTopOr(value) + PaddingBottomOr(value) };
        }

        Rect Rect_Shrink_Margin_(Rect r)
        {
            return { r.X + MarginLeft, r.Y + MarginTop, r.Width - MarginRight, r.Height - MarginBottom };
        }
        Rect Rect_ResizeShrink_Margin_(Rect r)
        {
            return { r.X, r.Y, r.Width - MarginLeft - MarginRight, r.Height - MarginTop - MarginBottom };
        }
        Rect Rect_ShrinkOr_Margin_(Rect r, float value)
        {
            return { r.X + MarginLeftOr(value), r.Y + MarginTopOr(value), r.Width - MarginRightOr(value),
                r.Height - MarginBottomOr(value) };
        }
        Rect Rect_ResizeShrinkOr_Margin_(Rect r, float value)
        {
            return { r.X, r.Y, r.Width - MarginLeftOr(value) - MarginRightOr(value),
                r.Height - MarginTopOr(value) - MarginBottomOr(value) };
        }

        Rect Rect_Shrink_Padding_(Rect r)
        {
            return { r.X + PaddingLeft, r.Y + PaddingTop, r.Width - PaddingRight, r.Height - PaddingBottom };
        }
        Rect Rect_ResizeShrink_Padding_(Rect r)
        {
            return { r.X, r.Y, r.Width - PaddingLeft - PaddingRight, r.Height - PaddingTop - PaddingBottom };
        }
        Rect Rect_ShrinkOr_Padding_(Rect r, float value)
        {
            return { r.X + PaddingLeftOr(value), r.Y + PaddingTopOr(value), r.Width - PaddingRightOr(value),
                r.Height - PaddingBottomOr(value) };
        }
        Rect Rect_ResizeShrinkOr_Padding_(Rect r, float value)
        {
            return { r.X, r.Y, r.Width - PaddingLeftOr(value) - PaddingRightOr(value),
                r.Height - PaddingTopOr(value) - PaddingBottomOr(value) };
        }

        static Rect Rect_AlignCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - (r.Width / 2), parent.Center.Y - (r.Height / 2), r.Width, r.Height };
        }
        static Rect Rect_LimitAlignCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - Min(r.Width / 2, parent.Width / 2),
                parent.Center.Y - Min(r.Height / 2, parent.Height / 2), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }

        static Rect Rect_AlignTopCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - (r.Width / 2), parent.Y, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignTopCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - Min(r.Width / 2, parent.Width / 2), parent.Y, Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignTopLeft_(Rect parent, Rect r) { return { parent.X, parent.Y, r.Width, r.Height }; }
        static Rect Rect_LimitAlignTopLeft_(Rect parent, Rect r)
        {
            return { parent.X, parent.Y, Min(r.Width, parent.Width), Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignTopRight_(Rect parent, Rect r)
        {
            return { parent.Second.X - r.Width, parent.Y, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignTopRight_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width), parent.Y, Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }

        static Rect Rect_AlignBottomCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - (r.Width / 2), parent.Second.Y - r.Height, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignBottomCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - Min(r.Width / 2, parent.Width / 2),
                parent.Second.Y - Min(r.Height, parent.Height), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignBottomLeft_(Rect parent, Rect r)
        {
            return { parent.X, parent.Second.Y - r.Height, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignBottomLeft_(Rect parent, Rect r)
        {
            return { parent.X, parent.Second.Y - Min(r.Height, parent.Height), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignBottomRight_(Rect parent, Rect r)
        {
            return { parent.Second.X - r.Width, parent.Second.Y - r.Height, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignBottomRight_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width), parent.Second.Y - Min(r.Height, parent.Height),
                Min(r.Width, parent.Width), Min(r.Height, parent.Height) };
        }

        static Rect Rect_AlignLeftCenter_(Rect parent, Rect r)
        {
            return { parent.X, parent.Center.Y - (r.Width / 2), r.Width, r.Height };
        }
        static Rect Rect_LimitAlignLeftCenter_(Rect parent, Rect r)
        {
            return { parent.X, parent.Center.Y - Min(r.Width / 2, parent.Width / 2), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignLeftTop_(Rect parent, Rect r) { return { parent.X, parent.Y, r.Width, r.Height }; }
        static Rect Rect_LimitAlignLeftTop_(Rect parent, Rect r)
        {
            return { parent.X, parent.Y, Min(r.Width, parent.Width), Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignLeftBottom_(Rect parent, Rect r)
        {
            return { parent.X, parent.Second.Y - r.Height, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignLeftBottom_(Rect parent, Rect r)
        {
            return { parent.X, parent.Second.Y - Min(r.Height, parent.Height), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }

        static Rect Rect_AlignRightCenter_(Rect parent, Rect r)
        {
            return { parent.Second.X - r.Width, parent.Center.Y - (r.Height / 2), r.Width, r.Height };
        }
        static Rect Rect_LimitAlignRightCenter_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width),
                parent.Center.Y - Min(r.Height / 2, parent.Height / 2), Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignRightTop_(Rect parent, Rect r)
        {
            return { parent.Second.X - r.Width, parent.Y, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignRightTop_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width), parent.Y, Min(r.Width, parent.Width),
                Min(r.Height, parent.Height) };
        }
        static Rect Rect_AlignRightBottom_(Rect parent, Rect r)
        {
            return { parent.Second.X - r.Width, parent.Second.Y - r.Height, r.Width, r.Height };
        }
        static Rect Rect_LimitAlignRightBottom_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width), parent.Second.Y - Min(r.Height, parent.Height),
                Min(r.Width, parent.Width), Min(r.Height, parent.Height) };
        }

        static Rect Rect_LimitVAlignLeftBottom_(Rect parent, Rect r)
        {
            return { parent.X, parent.Second.Y - Min(r.Height, parent.Height), r.Width, Min(r.Height, parent.Height) };
        }
        static Rect Rect_LimitVAlignRightBottom_(Rect parent, Rect r)
        {
            return { parent.Second.X - Min(r.Width, parent.Width), parent.Second.Y - r.Height,
                Min(r.Width, parent.Width), r.Height };
        }
        static Rect Rect_LimitHAlignTopCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - Min(r.Width / 2, parent.Width / 2), parent.Y, Min(r.Width, parent.Width),
                r.Height };
        }
        static Rect Rect_LimitHAlignBottomCenter_(Rect parent, Rect r)
        {
            return { parent.Center.X - Min(r.Width / 2, parent.Width / 2), parent.Second.Y - r.Height,
                Min(r.Width, parent.Width), r.Height };
        }

        static Rect Rect_Align_(Rect parent, Rect r, Align a)
        {
            if (a.IsCentered) return Rect_AlignCenter_(parent, r);
            if (a.IsStretched) return parent;

            if (a.IsHLeft && a.IsVStretched)
                return Rect_LimitVAlignLeftBottom_(parent, { r.X, r.Y, r.Width, Limits::FloatMax });
            if (a.IsHLeft && a.IsVCentered) return Rect_AlignLeftBottom_(parent, r);
            if (a.IsHLeft && a.IsVTop) return Rect_AlignLeftTop_(parent, r);
            if (a.IsHLeft && a.IsVBottom) return Rect_AlignLeftBottom_(parent, r);

            if (a.IsHRight && a.IsVStretched)
                return Rect_LimitVAlignRightBottom_(parent, { r.X, r.Y, r.Width, Limits::FloatMax });
            if (a.IsHRight && a.IsVCentered) return Rect_AlignRightBottom_(parent, r);
            if (a.IsHRight && a.IsVTop) return Rect_AlignRightTop_(parent, r);
            if (a.IsHRight && a.IsVBottom) return Rect_AlignRightBottom_(parent, r);

            if (a.IsVTop && a.IsHStretched)
                return Rect_LimitHAlignTopCenter_(parent, { r.X, r.Y, Limits::FloatMax, r.Height });
            if (a.IsVTop && a.IsHCentered) return Rect_AlignTopCenter_(parent, r);

            if (a.IsVBottom && a.IsHStretched)
                return Rect_LimitHAlignBottomCenter_(parent, { r.X, r.Y, Limits::FloatMax, r.Height });
            if (a.IsVBottom && a.IsHCentered) return Rect_AlignBottomCenter_(parent, r);

            return parent;
        }
        static Rect Rect_LimitAlign_(Rect parent, Rect r, Align a)
        {
            if (a.IsCentered) return Rect_LimitAlignCenter_(parent, r);
            if (a.IsStretched) return parent;

            if (a.IsHLeft && a.IsVStretched)
                return Rect_LimitAlignLeftBottom_(parent, { r.X, r.Y, r.Width, Limits::FloatMax });
            if (a.IsHLeft && a.IsVCentered) return Rect_LimitAlignLeftBottom_(parent, r);
            if (a.IsHLeft && a.IsVTop) return Rect_LimitAlignLeftTop_(parent, r);
            if (a.IsHLeft && a.IsVBottom) return Rect_LimitAlignLeftBottom_(parent, r);

            if (a.IsHRight && a.IsVStretched)
                return Rect_LimitAlignRightBottom_(parent, { r.X, r.Y, r.Width, Limits::FloatMax });
            if (a.IsHRight && a.IsVCentered) return Rect_LimitAlignRightBottom_(parent, r);
            if (a.IsHRight && a.IsVTop) return Rect_LimitAlignRightTop_(parent, r);
            if (a.IsHRight && a.IsVBottom) return Rect_LimitAlignRightBottom_(parent, r);

            if (a.IsVTop && a.IsHStretched)
                return Rect_LimitAlignTopCenter_(parent, { r.X, r.Y, Limits::FloatMax, r.Height });
            if (a.IsVTop && a.IsHCentered) return Rect_LimitAlignTopCenter_(parent, r);

            if (a.IsVBottom && a.IsHStretched)
                return Rect_LimitAlignBottomCenter_(parent, { r.X, r.Y, Limits::FloatMax, r.Height });
            if (a.IsVBottom && a.IsHCentered) return Rect_LimitAlignBottomCenter_(parent, r);

            return parent;
        }

        Rect AlignToComputedLayout_(Rect i)
        {
            Rect im = Rect_ShrinkOr_Margin_(i, 0);
            Rect r1 = Rect_Align_(im, { 0, 0, ComputedMinWidth, ComputedMinHeight }, Alignment_);
            Rect r2 = Rect_LimitAlign_(r1, { 0, 0, ComputedMaxWidth, ComputedMaxHeight }, Alignment_);
            return r2;
        }
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