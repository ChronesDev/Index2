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
                A = 11;
                set Name = "Hello There!";
                sub Element mapn
                {
                    sub Button mapn
                    {
                        set Name = "Test";
                        sub MyClass mapn
                        {
                            set Name = "??";
                            set Name = "...";
                        };
                    };
                    sub Button mapn
                    {
                        set SomeValue = 11;
                        set Name = "Hi?";
                        set Name = "";
                    };
                    sub Button mapn {};
                    sub MyClass mapn
                    {
                        set Name = "?";
                        sub MyClass mapn { string name = get Name; };
                        sub MyClass mapn
                        {
                            set Name = "Hi";
                            set Name = "Hi";
                        };
                        sub Button mapn
                        {
                            set Name = "L";
                            set Name = "Hi";
                        };
                    };
                };
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