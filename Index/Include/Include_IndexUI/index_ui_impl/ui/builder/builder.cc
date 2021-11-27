#pragma once

#include "../../index.cc"

namespace Index::SomeUI
{
    struct Element;
    struct ElementMapper;

    struct Element
    {
        template <class T> struct Map
        {
            Func<void(Element*, IPtr<ElementMapper>)> operator+(Func<void(Element*, const ElementMapper&)> f)
            {
                return [] {

                };
            }
        };
    };

#define sub element.template Sub <
#define map > () += [](auto element, auto mapper)

    struct ElementMapper
    {
    public:
        IPtr<ElementMapper> Content;

        // Content
        template <class TThis, class T> struct PlusAssignMaker
        {
            TThis* That;
            explicit PlusAssignMaker(TThis* that)
                : That(that)
            {
            }
            void operator+=(Func<void(const TThis&, const typename T::Mapper&)> f)
            {
                auto mapper = INew<typename T::Mapper>();
                f(*That, mapper.Value);
                mapper.template DynamicAs<ElementMapper>();
            }
        };

        template <class T> PlusAssignMaker<ElementMapper, T> Sub() { return PlusAssignMaker<ElementMapper, T>(this); }

        IPtr<Element> Build() { }
    };

    struct ButtonMapper;

    struct Button : Element
    {
        using Mapper = ButtonMapper;
    };

    struct ButtonMapper : Element
    {
    };

    void Make()
    {
        ElementMapper element;
        sub Button map
        {
            sub Button map
            {
                sub Button map {

                };
            };
        };
    }
}