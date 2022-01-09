#pragma once

#include <map>

#include "../container/container.cc"
#include "../ui.cc"

namespace Index::UI
{
    INDEX_UI_Declare(Switcher);

    struct Switcher : virtual UIElement
    {
        INDEX_UI_UseMapper(SwitcherMapper);

    public:
        virtual void Attach(const INDEX_UI_Ref& child, int index)
        {
            AttachChild_(child);
            OnAttached_(child, index);
        }
        virtual void Detach(const INDEX_UI_Ref& child) { DetachChild_(child); }

    protected:
        std::multimap<int, INDEX_UI_Ref> Switchables_;

    public:
        const decltype(Switchables_)& GetSwitchables() const { return Switchables_; }
        INDEX_Property(get = GetSwitchables) const decltype(Switchables_)& Switchables;

    protected:
        virtual void OnAttached_(const INDEX_UI_Ref& child, int index) { Switchables_.insert({ index, child }); }

        void OnDetached_(INDEX_UI_Ref child) override
        {
            auto result = std::find_if(
                Switchables_.begin(), Switchables_.end(), [&](auto& p) { return p.second == child; });

            if (result != Switchables_.end()) { Switchables_.erase(result); }
        }

    protected:
        void OnComputeLayoutPosition(Rect i) override
        {
            Rect r = GetSubrect_(i);
            ComputedLayout_ = r;

            float width = 0;
            for (auto& c : Children_)
            {
                Rect r2 = r;
                r2.X += width;
                r2.Width = c->ComputedMinWidthOr(AutoF);
                c->ComputeLayoutPosition(r2);

                width += c->ComputedMinWidth;
            }

            PolishComputedLayoutPosition();
        }

    public:
        void OnComputeLayout() override
        {
            auto minChildren = ApplyPadding_(FitRectToChildren_());
            auto min = ClampSize(minChildren);
            auto max = ActualMaxSize;

            ComputedMinSize_ = ApplyMargin_(min);
            ComputedMaxSize_ = max;

            PolishLayout();
            PolishComputedLayout();
        }
    };

    struct SwitcherMapper : virtual UIMapper
    {
        INDEX_UI_Ref Make()
        {
            IPtr<Switcher> e_ref = INew<Switcher>();
            Switcher& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }

    protected:
        template <class T> void Impl_Children_(T& e)
        {
            for (auto& c : Children)
            {
                e.Attach(c->Make(), 0);
            }
        }
    };
}
