#pragma once

#include "../index.cc"
#include <SimpleYoga/yoga/YGNode.h>
#include <SimpleYoga/yoga/Yoga.h>

#define INDEX_UI_Declare(name)                                                                                        \
    struct name;                                                                                                      \
    struct name##Mapper
#define INDEX_UI_DeclareExplicit(name, mapper_name)                                                                   \
    struct name;                                                                                                      \
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
        UInt64 ComputeFrame_ = 0;
        Size ComputedSize_;

    public:
        UInt64 GetComputeFrame() const { return ComputeFrame_; }
        INDEX_Property(get = GetComputeFrame) UInt64 ComputeFrame;

        Size GetComputedSize() const { return ComputedSize_; }
        INDEX_Property(get = GetComputedSize) Size ComputedSize;
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