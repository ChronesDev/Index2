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
        INDEX_Property(get = GetCanAttach) bool CanAttachYogaNode;

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
        void YogaNode_MakeStretch_()
        {
            PercentWidth = 100;
            PercentHeight = 100;
        }

        void YogaNode_MakeCenter_()
        {
            PercentWidth = 0;
            PercentHeight = 0;
        }

        void YogaNode_Content_SetDirection_(YGFlexDirection value)
        {
            YGNodeStyleSetFlexDirection(&YogaNode, value);
        }

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
            //if (value.IsS)
        }

    private:
        bool ClipContent_ = false;

    public:
        bool GetClipContent() const { return ClipContent_; }
        void SetClipContent(bool value) { ClipContent_ = value; }
        INDEX_Property(get = GetClipContent, put = SetClipContent) bool ClipContent;
    };

#define ui_ref IPtr<UIElement>

    void f()
    {
        ui_ref e;
        e->AutoHeight = true;
        ui_ref e2 = INew<UIElement>();
        if (e->IsContentless) { e->Add(e2); }
    }
}