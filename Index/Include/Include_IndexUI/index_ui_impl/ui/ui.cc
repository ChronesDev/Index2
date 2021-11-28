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
        YGNode YogaNode;

        float GetWidth()
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitPoint ? style.value : 0;
        }
        void SetWidth(float value) { YGNodeStyleSetWidth(&YogaNode, value); }
        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        float GetHeight()
        {
            auto style = YGNodeStyleGetHeight(&YogaNode);
            return style.unit == YGUnitPoint ? style.value : 0;
        }
        void SetHeight(float value) { YGNodeStyleSetWidth(&YogaNode, value); }
        INDEX_Property(get = GetHeight, put = SetHeight) float Height;

        float GetPercentWidth()
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitPercent ? style.value : 0;
        }
        void SetPercentWidth(float value) { YGNodeStyleSetWidthPercent(&YogaNode, value); }
        INDEX_Property(get = GetPercentWidth, put = SetPercentWidth) float PercentWidth;

        float GetPercentHeight()
        {
            auto style = YGNodeStyleGetHeight(&YogaNode);
            return style.unit == YGUnitPercent ? style.value : 0;
        }
        void SetPercentHeight(float value) { YGNodeStyleSetWidthPercent(&YogaNode, value); }
        INDEX_Property(get = GetPercentHeight, put = SetPercentHeight) float PercentHeight;

        bool GetAutoWidth()
        {
            auto style = YGNodeStyleGetWidth(&YogaNode);
            return style.unit == YGUnitAuto;
        }
        void SetAutoWidth(bool value)
        {
            if (value) YGNodeStyleSetWidthAuto(&YogaNode);
        }
        INDEX_Property(get = GetAutoWidth, put = SetAutoWidth) bool AutoWidth;

        bool GetAutoHeight()
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

        UIUnit GetWidthUnit() { return UIUnitFromYGUnit(YGNodeStyleGetWidth(&YogaNode).unit); }
        INDEX_Property(get = GetWidthUnit) UIUnit WidthUnit;

        UIUnit GetHeightUnit() { return UIUnitFromYGUnit(YGNodeStyleGetHeight(&YogaNode).unit); }
        INDEX_Property(get = GetHeightUnit) UIUnit HeightUnit;

        Size GetComputedSize() { return { ComputedWidth, ComputedHeight }; }
        INDEX_Property(get = GetComputedSize) Size ComputedSize;
    };

    void f()
    {
        UIElement e;
        e.AutoHeight = true;
        Vec2F f = e.ComputedSize;
    }
}