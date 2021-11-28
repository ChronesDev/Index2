#pragma once

#include "../../index.cc"

namespace Index::SomeUI
{
    struct Element;
    struct ElementMapper;

    struct Element
    {
        using Mapper = Element;
    };

#define sub parent.template Sub <

#define map > () += [this](auto parent, auto mapper)
#define mapn > () += [](auto parent, auto mapper)
#define mapc(capture) > () += [capture](auto parent, auto mapper)

#define mapm > () += [this](auto parent, auto mapper) { }
#define mapmn > () += [](auto parent, auto mapper) { }
#define mapmc(capture) > () += [capture](auto parent, auto mapper) { }

#define set mapper.
#define get mapper.

    struct ElementMapper
    {
    public:
        List<IPtr<ElementMapper>> Content;

        string Name;

        // Content
        template <class TThis, class T> struct PlusAssignMaker
        {
            TThis* That;

            explicit PlusAssignMaker(TThis* that)
                : That(that)
            {
            }

            // Add Child
            void operator+=(Func<void(const TThis&, const typename T::Mapper&)> f)
            {
                auto mapper = INew<typename T::Mapper>();
                f(*That, mapper.Value);
                That->Content.Add(mapper.template DynamicAs<ElementMapper>());
            }
        };

        // Get PlusAssignMaker
        template <class T> PlusAssignMaker<ElementMapper, T> Sub() { return PlusAssignMaker<ElementMapper, T>(this); }

        IPtr<Element> Build() { return {}; }
    };

    struct ButtonMapper : ElementMapper
    {
        int SomeValue = 0;
        Color Fill = Colors::Green;
        string Text = "";
    };

    struct Button : Element
    {
        using Mapper = ButtonMapper;
    };

#define n void

    struct MyClassMapper : ElementMapper
    {
    };

    struct MyClass : Element
    {
        using Mapper = MyClassMapper;

        int A = 0;

        void Make()
        {
            ElementMapper parent;
            sub Button map
            {
                set Fill = Colors::Red;
                set Text = "Hello";
                set Content.Add(INew<ButtonMapper>());
                sub Button mapm;
            };

            sub Button map {
                set Text = "Hello world";
            };

            /*
             * Button
             * -- Element
             * -- -- Button
             * -- -- -- MyClass
             * -- -- Button
             * -- -- Button
             * -- -- MyClass
             * -- -- -- MyClass
             * -- -- -- MyClass
             * -- -- -- Button
             */
            auto ui = parent.Build();
        }
    };
}