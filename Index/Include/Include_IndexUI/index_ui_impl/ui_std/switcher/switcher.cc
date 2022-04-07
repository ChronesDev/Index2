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
            auto result = std::ranges::find_if(Switchables_, [&](auto& p) { return p.second == child; });
            if (result != Switchables_.end()) { Switchables_.erase(result); }
        }

    public:
        int Index;

    protected:
        void OnComputeLayoutPosition(Rect i) override
        {
            ComputeComputedLayoutAndContentLayout_(i);
            
            for (auto& p : Switchables_)
            {
                if (p.first != Index) continue;
                auto& c = p.second;

                if (c->IsComputedLayoutPositionDirty) c->ComputeLayoutPosition(i);
            }

            PolishComputedLayoutPosition();
        }
        
        void OnComputeLayout() override
        {
            ComputeComputedSizes_(FitRectToTargetChildren_());

            PolishLayout();
            PolishComputedLayout();
        }

    public:
        void SubRender() override
        {
            for (auto& p : Switchables_)
            {
                if (p.first != Index) continue;
                auto& c = p.second;
                c->Render();
            }
        }

    protected:
        Index::Size FitRectToTargetChildren_()
        {
            Index::Size s;
            for (auto& p : Switchables_)
            {
                if (p.first != Index) continue;
                auto& c = p.second;

                float width = c->ComputedMinWidth;
                if (s.Width < width) s.Width = width;

                float height = c->ComputedMinHeight;
                if (s.Height < height) s.Height = height;
            }
            return s;
        }

        bool SubHitTestRecursive(HitTestResult& e, Vec2F& p) override
        {
            for (auto& p2 : Switchables_)
            {
                if (p2.first != Index) continue;
                auto& c = p2.second;
                c->HitTestRecursive(e, p);
                if (e.HasSucceeded) return true;
            }
            return false;
        }
    };

    struct SwitcherMapper : virtual UIElementMapper
    {
        SwitcherMapper() = default;

    public:
        int Index = 0;
        int NextIndex = 0;

    protected:
        std::multimap<int, IPtr<UIMapper>> Children_Map_;

    public:
        INDEX_UI_Ref Make() override
        {
            IPtr<Switcher> e_ref = INew<Switcher>();
            Switcher& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            e.Index = Index;

            return e_ref.DynamicAs<UIElement>();
        }

    protected:
        void OnAdd_(const IPtr<UIMapper>& child) override
        {
            Children_Map_.insert({ NextIndex, child });
        }

        void OnRemove_(const IPtr<UIMapper>& child) override
        {
            auto result = std::ranges::find_if(Children_Map_, [&](auto& p) { return p.second == child; });
            if (result != Children_Map_.end()) { Children_Map_.erase(result); }
        }

    public:
        template <class T> auto Sub() { return Sub_<T>(); }
        template <class T, int TNextIndex> auto Sub()
        {
            NextIndex = TNextIndex;
            return Sub_<T>();
        }

    protected:
        template <class T> void Impl_Children_(T& e)
        {
            for (auto& c : Children_Map_)
            {
                e.Attach(c.second->Make(), c.first);
            }
        }
    };
}
