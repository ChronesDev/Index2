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

#define sub element.template Sub <
#define map > () += [this](auto parent, auto mapper)
#define mapc(capture) > () += [capture](auto parent, auto mapper)
#define set mapper.
#define get mapper.

	struct ElementMapper
	{
	public:
		IPtr <ElementMapper> Content;

		string Name;

		// Content
		template<class TThis, class T>
		struct PlusAssignMaker
		{
			TThis *That;

			explicit PlusAssignMaker(TThis *that) : That(that)
			{
			}

			void operator+=(Func<void(const TThis &, const typename T::Mapper &)> f)
			{
				auto mapper = INew<typename T::Mapper>();
				f(*That, mapper.Value);
				mapper.template DynamicAs<ElementMapper>();
			}
		};

		template<class T>
		PlusAssignMaker<ElementMapper, T> Sub()
		{ return PlusAssignMaker<ElementMapper, T>(this); }

		IPtr <Element> Build()
		{ return { }; }
	};

	struct ButtonMapper;

	struct Button : Element
	{
		using Mapper = ButtonMapper;
	};

	struct ButtonMapper : ElementMapper
	{
		int SomeValue = 0;
	};

#define n void

	class MyClass
	{
		int A = 0;

		void Make()
		{
			ElementMapper element;
			sub Button map -> n
			{
				set Name = "Hello There!";
				sub Element map -> n
				{
					sub Button map -> n
					{
						set SomeValue = 11;
						set Name = "Hi?";
						set Name = "";
					};
					sub Button map -> n
					{
						set Name = "Test";
					};
					sub Button map -> n
					{
						set Name = "Hi?";
					};
				};
			};
			auto ui = element.Build();
		}
	};
}