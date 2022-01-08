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
            That->Children.Add(mapper.template DynamicAs<UIMapper>());
        }
    };

    struct UIMapper : IObj<UIMapper>
    {
    public:
        string Name = "";
        string Id = "";

        Index::Size Size = AutoS;
        Index::Size MinSize = AutoS;
        Index::Size MaxSize = AutoS;

        Vec4F Margin = { 0 };
        Vec4F Padding = { 0 };

        Align Alignment = Align::Stretch;

    public:
        List<IPtr<UIMapper>> Children;

        virtual void Add(IPtr<UIMapper> child) { Children.Add(child); }
        virtual void Remove(IPtr<UIMapper> child) { Children.Remove(child); }

        template <class T> UIMapper_SubMaker_<UIMapper, T> Sub() { return UIMapper_SubMaker_<UIMapper, T>(this); }

    protected:
        virtual IPtr<UIElement> MakeSelf() { INDEX_THROW("Not implemented."); };

    public:
        virtual IPtr<UIElement> Make() = 0;
    };
}