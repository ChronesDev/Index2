#pragma once

#include "../index.cc"
#include <SimpleYoga/yoga/YGNode.h>
#include <SimpleYoga/yoga/Yoga.h>

namespace Index::UI2
{
    struct UIElement;
    struct UIElementMapper;

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
        UIElementPropertyAnimation(WPtr<UIElement> element,
            Func<void(TElement*, typename TAnimation::TType)> propertySetter, TAnimation animation)
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
    protected:
        WPtr<UIElement> Parent_;
        List<WPtr<UIElement>> MultiParents_;

    public:
        IPtr<UIElement> GetParent() { return Parent_.Lock; }
        INDEX_Property(get = GetParent) IPtr<UIElement> Parent;

        WPtr<UIElement> GetWeakParent() { return Parent_; }
        INDEX_Property(get = GetWeakParent) WPtr<UIElement> WeakParent;

        virtual bool GetIsMultiParent() { return false; }
        INDEX_Property(get = GetIsMultiParent) bool IsMultiParent;

        virtual bool GetCanAttach() { return true; };
        INDEX_Property(get = GetCanAttach) bool CanAttach;

        virtual bool GetCanAttachYogaNode() { return true; };
        INDEX_Property(get = GetCanAttachYogaNode) bool CanAttachYogaNode;

    protected:
        virtual void ParentAttach(IPtr<UIElement> parent)
        {
            if (parent.IsNull) throw std::exception("parent was null.");
            if (!CanAttach) throw std::exception("CanAttach was false.");
            if (IsMultiParent)
            {
                if (!Parent_.IsNull) throw std::exception("Parent_ was not null while in MultiParent state.");
                for (auto p : MultiParents_)
                {
                    if (p.Lock.Ptr == parent.Ptr) throw std::exception("Duplicate parent found.");
                }
            }
            else
            {
                if (!Parent_.IsNull)
                    throw std::exception("Parent_ was not null. Make sure to detach this element first.");
                Parent_ = parent;
            }
        }

        virtual void ParentTryAttach(IPtr<UIElement> parent)
        {
            if (!CanAttach) return;
            if (parent.IsNull) return;
            ParentAttach(parent);
        }

        virtual void ParentDetach()
        {
            if (Parent_.IsNull) return;
            Parent_ = {};
        }

        virtual void ParentDetach(IPtr<UIElement> parent) { ParentDetach(parent.Ptr); }

        virtual void ParentDetach(UIElement* parent)
        {
            if (parent == nullptr) return;
            if (IsMultiParent)
            {
                for (int i = 0; i < MultiParents_.Length; i++)
                {
                    if (MultiParents_[i].Lock.Ptr == parent)
                    {
                        MultiParents_.Erase(MultiParents_.begin() + i);
                        return;
                    }
                }
            }
            else if (Parent_.Lock.Ptr == parent)
            {
                Parent_ = {};
                return;
            }
        }

        virtual void ParentDetachAll()
        {
            if (IsMultiParent) { MultiParents_ = {}; }
            else
            {
                Parent_ = {};
            }
        }

    protected:
        YGNode YogaNode;

    public:
        const YGNode& GetYogaNode() const { return YogaNode; }

        float GetWidth() const
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitPoint ? style.value : 0;
        }
        void SetWidth(float value) { YGNodeStyleSetWidth(&YogaNode, value); }
        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        float GetHeight() const
        {
            auto style = YGNodeStyleGetHeight(&YogaNode);
            return style.unit == YGUnitPoint ? style.value : 0;
        }
        void SetHeight(float value) { YGNodeStyleSetWidth(&YogaNode, value); }
        INDEX_Property(get = GetHeight, put = SetHeight) float Height;

        float GetPercentWidth() const
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitPercent ? style.value : 0;
        }
        void SetPercentWidth(float value) { YGNodeStyleSetWidthPercent(&YogaNode, value); }
        INDEX_Property(get = GetPercentWidth, put = SetPercentWidth) float PercentWidth;

        float GetPercentHeight() const
        {
            auto style = YGNodeStyleGetHeight(&YogaNode);
            return style.unit == YGUnitPercent ? style.value : 0;
        }
        void SetPercentHeight(float value) { YGNodeStyleSetWidthPercent(&YogaNode, value); }
        INDEX_Property(get = GetPercentHeight, put = SetPercentHeight) float PercentHeight;

        bool GetAutoWidth() const
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitAuto;
        }
        void SetAutoWidth(bool value)
        {
            if (value) YGNodeStyleSetWidthAuto(&YogaNode);
        }
        INDEX_Property(get = GetAutoWidth, put = SetAutoWidth) bool AutoWidth;

        bool GetAutoHeight() const
        {
            auto style = YGNodeStyleGetHeight(&YogaNode);
            return style.unit == YGUnitAuto;
        }
        void SetAutoHeight(bool value)
        {
            if (value) YGNodeStyleSetHeightAuto(&YogaNode);
        }
        INDEX_Property(get = GetAutoHeight, put = SetAutoHeight) bool AutoHeight;

        float ComputedGetWidth() { return YGNodeLayoutGetWidth(&YogaNode); }
        INDEX_Property(get = ComputedGetWidth) float ComputedWidth;

        float ComputedGetHeight() { return YGNodeLayoutGetHeight(&YogaNode); }
        INDEX_Property(get = ComputedGetHeight) float ComputedHeight;

        Size GetComputedSize() { return { ComputedWidth, ComputedHeight }; }
        INDEX_Property(get = GetComputedSize) Size ComputedSize;

        UIUnit GetWidthUnit() const { return UIUnitFromYGUnit(YGNodeStyleGetWidth(&YogaNode).unit); }
        INDEX_Property(get = GetWidthUnit) UIUnit WidthUnit;

        UIUnit GetHeightUnit() const { return UIUnitFromYGUnit(YGNodeStyleGetHeight(&YogaNode).unit); }
        INDEX_Property(get = GetHeightUnit) UIUnit HeightUnit;

        float GetComputedLeftPosition() { return YGNodeLayoutGetLeft(&YogaNode); }
        INDEX_Property(get = GetComputedLeftPosition) float ComputedLeftPosition;

        float GetComputedTopPosition() { return YGNodeLayoutGetTop(&YogaNode); }
        INDEX_Property(get = GetComputedTopPosition) float ComputedTopPosition;

        float GetComputedRightPosition() { return YGNodeLayoutGetRight(&YogaNode); }
        INDEX_Property(get = GetComputedRightPosition) float ComputedRightPosition;

        float GetComputedBottomPosition() { return YGNodeLayoutGetBottom(&YogaNode); }
        INDEX_Property(get = GetComputedBottomPosition) float ComputedBottomPosition;

        Vec2F GetComputedPosition() { return { ComputedTopPosition, ComputedLeftPosition }; }
        INDEX_Property(get = GetComputedPosition) Vec2F ComputedPosition;

        Rect GetComputedRect() { return { ComputedPosition, ComputedSize }; }
        INDEX_Property(get = GetComputedRect) Rect ComputedRect;

    protected:
        void YogaNode_Make_()
        {
            AutoWidth = true;
            AutoHeight = true;

            YogaNode_Stretch_();
            YogaNode_CenterContent_();
        }

        void YogaNode_Stretch_()
        {
            YGNodeStyleSetPositionType(&YogaNode, YGPositionTypeAbsolute);
            YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeAll, 0);
        }

        void YogaNode_Center_()
        {
            YGNodeStyleSetPositionType(&YogaNode, YGPositionTypeAbsolute);
            YGNodeStyleSetPosition(&YogaNode, YGEdgeAll, YGUndefined);
        }

        void YogaNode_CenterContent_()
        {
            YGNodeStyleSetJustifyContent(&YogaNode, YGJustifyCenter);
            YGNodeStyleSetAlignItems(&YogaNode, YGAlignCenter);
        }

        void YogaNode_SetAlignmentFromAlign_(Align align)
        {
            YGNodeStyleSetPositionType(&YogaNode, YGPositionTypeAbsolute);

            if (align.IsHStretched)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeHorizontal, 0);
            }
            else if (align.IsHCentered)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeHorizontal, YGUndefined);
            }
            else if (align.IsHLeft)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeLeft, 0);
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeRight, YGUndefined);
            }
            else if (align.IsHRight)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeLeft, YGUndefined);
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeRight, 0);
            }

            if (align.IsVStretched)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeVertical, 0);
            }
            else if (align.IsVCentered)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeVertical, YGUndefined);
            }
            else if (align.IsVTop)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeTop, 0);
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeBottom, YGUndefined);
            }
            else if (align.IsVBottom)
            {
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeTop, YGUndefined);
                YGNodeStyleSetPositionPercent(&YogaNode, YGEdgeBottom, 0);
            }
        }

        void YogaNode_Content_SetDirection_(YGFlexDirection value) { YGNodeStyleSetFlexDirection(&YogaNode, value); }

    private:
        List<IPtr<UIElement>> Content_;

    public:
        const List<IPtr<UIElement>>& GetContent() { return Content_; }
        INDEX_Property(get = GetContent) const List<IPtr<UIElement>>& Content;

        virtual bool GetIsContentless() { return false; }
        INDEX_Property(get = GetIsContentless) bool IsContentless;

        void Add(IPtr<UIElement> child)
        {
            if (IsContentless) throw std::exception("This element cannot hold content.");
            TryAdd(child);
        }

        void TryAdd(IPtr<UIElement> child)
        {
            if (child.IsNull) return;
            if (IsContentless) return;
            if (child->CanAttachYogaNode) YogaNode.insertChild(&child->YogaNode, YGNodeGetChildCount(&YogaNode));
            child->ParentTryAttach(ISelf());
        }

        void Remove(IPtr<UIElement> child)
        {
            if (IsContentless) throw std::exception("This element doesn't hold content.");
            TryRemove(child);
        }

        void TryRemove(IPtr<UIElement> child)
        {
            if (child.IsNull) return;
            if (Content_.Contains(child))
            {
                Content_.Remove(child);
                if (child->CanAttachYogaNode) YogaNode.removeChild(&child->YogaNode);
                child->ParentDetach(this);
            }
        }

        void SetContentAlign(Align value)
        {
            // if (value.IsS)
        }

    private:
        bool ClipContent_ = false;

    public:
        bool GetClipContent() const { return ClipContent_; }
        void SetClipContent(bool value) { ClipContent_ = value; }
        INDEX_Property(get = GetClipContent, put = SetClipContent) bool ClipContent;

    private:
        std::deque<IPtr<UIElementAnimation>> ElementAnimations_;

    public:
        decltype(ElementAnimations_)& GetElementAnimations() { return ElementAnimations_; }
        INDEX_Property(get = GetElementAnimations) decltype(ElementAnimations_)& ElementAnimations;

        void AddAnimation(IPtr<UIElementAnimation> animation) { ElementAnimations.push_back(animation); }

        template <class TAnimation>
        void Animate(Func<void(UIElement*, typename TAnimation::TType)> propertySetter, TAnimation animation)
        {
            AddAnimation(INew<UIElementPropertyAnimation<TAnimation>>(WSelf(), propertySetter, animation));
        }

        template <class TAnimation>
        void Animate(Func<void(UIElement*, typename TAnimation::TType)> propertySetter,
            typename TAnimation::TType from, typename TAnimation::TType to, TimeSpan duration)
        {
            Animate<TAnimation>(std::forward<decltype(propertySetter)>(propertySetter), { from, to, duration });
        }

    protected:
        void AnimationTick_()
        {
            for (auto& a : ElementAnimations_)
            {
                if (a.IsNull) continue;
                a->Update();
            }

            auto rm = std::remove_if(ElementAnimations_.begin(), ElementAnimations_.end(),
                [&](IPtr<UIElementAnimation>& item) { return item.IsNull || item->IsDone; });
            ElementAnimations_.erase(rm);
        }

    public:
        virtual Span<IPtr<UIElement>> GetTickContent() { return Content_; }
        INDEX_Property(get = GetTickContent) Span<IPtr<UIElement>> TickContent;

        virtual void Tick() { AnimationTick_(); }

        virtual void RecursiveTick()
        {
            Tick();
            for (auto& c : TickContent)
            {
                c->RecursiveTick();
            }
        }

    public:
        virtual Span<IPtr<UIElement>> GetRenderContent() { return Content_; }
        INDEX_Property(get = GetRenderContent) Span<IPtr<UIElement>> RenderContent;
    };

#define ui_ref IPtr<UIElement>

    void f()
    {
        ui_ref e;
        e->AutoHeight = true;
        ui_ref e2 = INew<UIElement>();
        if (e->IsContentless) { e->Add(e2); }
        Func<void(UIElement*, bool)> func = &UIElement::SetWidth;
        e->Add(e2);
        e->Animate<QuartInOutAnimation>(&UIElement::SetWidth, e->Width, 100, TimeSpan::FromSec(10));

        e->RecursiveTick();
    }
}