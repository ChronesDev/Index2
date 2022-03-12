#pragma once

#include "../element/element.cc"

namespace Index::UI
{
    struct UIScope : virtual UIElement, virtual IUIScope
    {
    public:
        ~UIScope() override = default;

    public:
        IPtr<UIElement> Search(UIPath path) override
        {
            return Scope_Search(path);
        }
        IPtr<UIElement> TrySearch(UIPath path) override
        {
            return Scope_TrySearch(path);
        }

        IPtr<UIElement> Scope_Search(UIPath path) override
        {
            auto result = Search_(&path);
            if (result == nullptr) INDEX_THROW("Could not find this element.");
            return result->ISelf();
        }
        IPtr<UIElement> Scope_TrySearch(UIPath path) override
        {
            auto result = Search_(&path);
            if (result == nullptr) return IPtr<UIElement>(nullptr);
            return result->ISelf();
        }

    protected:
        virtual UIElement* Search_(UIPath* path)
        {
            if (path == nullptr) INDEX_THROW("path was null.");

            Func<UIElement*(UIScope*)> Search_ = [&path, &Search_](UIScope* s) -> UIElement*
            {
                jmp_begin:
                    if (path->TargetsRoot)
                    {
                        auto root = s->UIRoot.Ptr;
                        auto keep_ = root->RootElement;

                        if (path->TargetsElement) return root->RootElement.Ptr;

                        auto result = dynamic_cast<UIScope*>(keep_.Ptr);
                        if (result == nullptr) goto jmp_ret;
                        path->Next();
                        return Search_(result);
                    }

                    if (path->TargetsElement) { return s->SearchElement_(path); }

                    if (path->TargetsScopeStay)
                    {
                        path->Next();
                        goto jmp_begin;
                    }

                    if (path->TargetsScopeOut)
                    {
                        auto result = s->SearchParentScope_();
                        if (result == nullptr) goto jmp_ret;
                        path->Next();
                        return Search_(result);
                    }

                    if (path->TargetsScope)
                    {
                        auto result = s->SearchScope_(path);
                        if (result == nullptr) goto jmp_ret;
                        path->Next();
                        return Search_(result);
                    }

                jmp_ret:
                    return nullptr;
            };
            return Search_(this);
        }

        UIElement* SearchElement_(UIPath* path)
        {
            if (path->TargetsName)
                return SearchElementByName_(path->Target);
            else if (path->TargetsId)
                return SearchElementById_(path->Target);
            return nullptr;
        }
        UIElement* SearchElementByName_(string name)
        {
            Func<UIElement*(UIElement*)> Search_ = [&Search_, &name](UIElement* p) -> UIElement*
            {
                auto cs = dynamic_cast<UIScope*>(p);
                if (p->Name == name) return p;
                if (cs == nullptr)
                {
                    for (auto& c : p->Children)
                    {
                        auto result = Search_(c.Ptr);
                        if (result) return result;
                    }
                }
                return nullptr;
            };

            for (auto& c : Children)
            {
                auto result = Search_(static_cast<UIElement*>(c.Ptr));
                if (result) return result;
            }
            return nullptr;
        }
        UIElement* SearchElementById_(string id)
        {
            Func<UIElement*(UIElement*)> Search_ = [&Search_, &id](UIElement* p) -> UIElement*
            {
                auto cs = dynamic_cast<UIScope*>(p);
                if (p->Id == id) return p;
                if (cs == nullptr)
                {
                    for (auto& c : p->Children)
                    {
                        auto result = Search_(c.Ptr);
                        if (result) return result;
                    }
                }
                return nullptr;
            };

            for (auto& c : Children)
            {
                auto result = Search_(static_cast<UIElement*>(c.Ptr));
                if (result) return result;
            }
            return nullptr;
        }
        UIScope* SearchScope_(UIPath* path)
        {
            if (path->TargetsName)
                return SearchScopeByName_(path->Target);
            else if (path->TargetsId)
                return SearchScopeById_(path->Target);
            return nullptr;
        }
        UIScope* SearchScopeByName_(string name)
        {
            Func<UIScope*(UIElement*)> Search_ = [&Search_, &name](UIElement* p) -> UIScope*
            {
                auto cs = dynamic_cast<UIScope*>(p);
                if (cs)
                {
                    if (cs->Name == name) return cs;
                    goto jmp_ret;
                }
                for (auto& c : p->Children)
                {
                    auto result = Search_(c.Ptr);
                    if (result) return result;
                }
            jmp_ret:
                return nullptr;
            };

            for (auto& c : Children)
            {
                auto result = Search_(static_cast<UIElement*>(c.Ptr));
                if (result) return result;
            }
            return nullptr;
        }
        UIScope* SearchScopeById_(string id)
        {
            Func<UIScope*(UIElement*)> Search_ = [&Search_, &id](UIElement* p) -> UIScope*
            {
                auto cs = dynamic_cast<UIScope*>(p);
                if (cs)
                {
                    if (cs->Id == id) return cs;
                    goto jmp_ret;
                }
                for (auto& c : p->Children)
                {
                    auto result = Search_(c.Ptr);
                    if (result) return result;
                }
            jmp_ret:
                return nullptr;
            };

            for (auto& c : Children)
            {
                auto result = Search_(static_cast<UIElement*>(c.Ptr));
                if (result) return result;
            }
            return nullptr;
        }
        UIScope* SearchParentScope_()
        {
            Func<UIScope*(UIElement*)> Search_ = [&Search_](UIElement* p) -> UIScope*
            {
                auto p2 = p->Parent;
                if (p2.Expired) return nullptr;
                auto p3 = p2.Lock;
                auto ptr = p3.Ptr;

                auto cs = dynamic_cast<UIScope*>(ptr);
                if (cs) return cs;

                return Search_(ptr);
            };
            return Search_(this);
        }
    };
}