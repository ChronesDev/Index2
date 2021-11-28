#pragma once

#include "../index.cc"
#include <SimpleYoga/yoga/YGNode.h>
#include <SimpleYoga/yoga/Yoga.h>

namespace Index::UI2
{
    struct UIElement;
    struct UIElementMapper;
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

// UIElement
namespace Index::UI2
{
    struct UIElement : IObj<UIElement>
    {
    protected:
        WPtr<UIElement> Parent_;

    public:
        IPtr<UIElement> GetParent() { return Parent_.Lock; }
        INDEX_Property(get = GetParent) IPtr<UIElement> Parent;

        WPtr<UIElement> GetWeakParent() { return Parent_; }
        INDEX_Property(get = GetParent) WPtr<UIElement> WeakParent;

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
        INDEX_Property(get = GetComputedPosition) float ComputedPosition;

        Rect GetComputedRect() { return { ComputedPosition, ComputedSize }; }
        INDEX_Property(get = GetComputedRect) Rect ComputedRect;

    private:
        List<IPtr<UIElement>> Content_;

    public:
        const List<IPtr<UIElement>>& GetContent() { return Content_; }
        INDEX_Property(get = GetContent) const List<IPtr<UIElement>>& Content;

        void Add(IPtr<UIElement> child)
        {
            if (child.IsNull) return;
            YogaNode.insertChild(&child->YogaNode, YGNodeGetChildCount(&YogaNode));
        }

        void Remove(IPtr<UIElement> child)
        {
            Content_.Remove(child);
            YogaNode.removeChild(&child->YogaNode);
        }

        void ComputeLayout()
        {

        }
    };

    void f()
    {
        UIElement e;
        e.AutoHeight = true;
        Vec2F f = e.ComputedSize;
    }
}