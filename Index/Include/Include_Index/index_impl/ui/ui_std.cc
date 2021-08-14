#pragma once

#include "ui.cc"

#define INDEX_UI_DEFAULT_NEW_MEBERS                             \
Index::Size MinSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size Size { Index::UI::NullF, Index::UI::NullF };        \
Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_SET_DEFAULT_MEMBERS     \
this->MinSize = e.MinSize;               \
this->MaxSize = e.MaxSize;               \
this->Size = e.Size;                     \
this->Alignment = e.Alignment;

#define INDEX_UI_ARGS struct Args

#define INDEX_UI_NEW_CLASS(class_name) template<class T = Index::UI::UIElement>                    \
struct New : public Index::IPtr<T>                                                      \
{                                                                                       \
    explicit New(Args e) {                                                              \
        if constexpr (!std::is_same<Index::UI::UIElement, T>::value) {                                      \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e).As<Index::UI::UIElement>();    \
        }                                                                               \
        if constexpr (std::is_same<class_name, T>::value) {                             \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e);                         \
        }                                                                               \
        else {                                                                          \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e).As<T>();                 \
        }                                                                               \
    }                                                                                   \
};

#define INDEX_UI_NEW_CLASS_ARGS(class_name, args_name) template<class T = Index::UI::UIElement>            \
struct New : public Index::IPtr<T>                                                              \
{                                                                                               \
    explicit New(args_name e) {                                                                 \
        if constexpr (!std::is_same<Index::UI::UIElement, T>::value) {                                     \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e).As<Index::UI::UIElement>();   \
        }                                                                                       \
        if constexpr (std::is_same<class_name, T>::value) {                                     \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e);                   \
        }                                                                                       \
        else {                                                                                  \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>(e).As<T>();           \
        }                                                                                       \
    }                                                                                           \
};

#define INDEX_UI_NEW_CLASS_EMPTY(class_name) template<class T = Index::UI::UIElement>          \
struct New : public Index::IPtr<T>                                                              \
{                                                                                               \
    explicit New() {                                                                            \
        if constexpr (!std::is_same<Index::UI::UIElement, T>::value) {                                     \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>().As<Index::UI::UIElement>();    \
        }                                                                                       \
        if constexpr (std::is_same<class_name, T>::value) {                                     \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>();                    \
        }                                                                                       \
        else {                                                                                  \
            static_cast<Index::IPtr<T>&>(*this) = Index::INew<class_name>().As<T>();            \
        }                                                                                       \
    }                                                                                           \
};

#define INDEX_UI_NEW_CONSTRUCTOR(class_name) explicit class_name(Args e)

#define INDEX_UI_NEW_CONSTRUCTOR_ARGS(class_name, args_name) explicit class_name(args_name e)

#define INDEX_UI_NEW_CONSTRUCTOR_EMPTY(class_name) explicit class_name()

#define INDEX_UI_THISSTATE (+Index::UI::UIContext::CurrentStates)

// Normal Elements
namespace Index::UI
{
    struct Empty : UIElement
    {
        INDEX_UI_NEW_CLASS_EMPTY(Empty);
        INDEX_UI_NEW_CONSTRUCTOR_EMPTY(Empty) { }
        void Build(Layout i) override { }
        void Notify(INotification* e) override { }
    };

    struct Holder : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_NEW_CLASS_ARGS(Holder, List<IPtr<UIElement>>);
        INDEX_UI_NEW_CONSTRUCTOR_ARGS(Holder, List<IPtr<UIElement>>) {
            Content = std::move(e);
        }
        void Build(Layout i) override {
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureMinSize() override {
            return LayoutUtils::CalculateMinSizeFrom(Content);
        }
    };

    struct Wrap : UIElement
    {
        IPtr<UIElement> Content;
        INDEX_UI_ARGS {
            IPtr<UIElement> Content;
        };
        INDEX_UI_NEW_CLASS(Wrap);
        INDEX_UI_NEW_CONSTRUCTOR(Wrap) {
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            if (Content) Content->Build(i);
        }
        void Notify(INotification* e) override {
            if (Content) Content->Notify(e);
        }
        Index::Size MeasureMinSize() override {
            if (Content) return Content->MeasureMinSize();
            return { };
        }
    };

    // TODO: Add _Content member
    struct Builder : UIElement
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        INDEX_UI_ARGS {
            Func<Index::UI::UIElement*()> BuildFunc;
        };
        INDEX_UI_NEW_CLASS(Builder);
        INDEX_UI_NEW_CONSTRUCTOR(Builder) {
            BuildFunc = std::move(e.BuildFunc);
        }
        void Build(Layout i) override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Notify(e);
            }
        }
    };

    // TODO: Add _Content member
    struct StatefulBuilder : UIElement, IRenderState
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        INDEX_UI_ARGS {
            Func<Index::UI::UIElement*()> BuildFunc;
        };
        INDEX_UI_NEW_CLASS(StatefulBuilder);
        INDEX_UI_NEW_CONSTRUCTOR(StatefulBuilder) {
            BuildFunc = std::move(e.BuildFunc);
        }
        void Build(Layout i) override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Build(i);
            }
        }
        void Rebuild(Layout i) {
            bool isRebuilding = Index::UI::UIContext::RebuildTree;
            Index::UI::UIContext::RebuildTree = true;
            Build(i);
            Index::UI::UIContext::RebuildTree = isRebuilding;
        }
        void Notify(INotification* e) override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Notify(e);
            }
        }
    };

    struct NextElement : UIElement {
        List<IPtr<UIElement>> Content;
        explicit NextElement(List<IPtr<UIElement>> content) {
            Content = std::move(content);
        }
        NextElement() = default;
        void Build(Layout i) override {
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureMinSize() override {
            return LayoutUtils::CalculateMinSizeFrom(Content);
        }
    };

    struct Element : UIElement
    {
    private:
        IPtr<NextElement> _Next;
        List<IPtr<UIElement>> _Content;
    public:
        IPtr<UIElement> GetNewNext() {
            _Next = INew<NextElement>();
            return _Next;
        }
        void SetNextContent(IPtr<UIElement> c) {
            if (c.IsNull) return;
            if (_Next) {
                _Next->Content.Add(std::move(c));
            }
        }
        __declspec(property(get = GetNewNext, put = SetNextContent)) IPtr<UIElement> next;
        void AddContent(IPtr<UIElement> c) {
            _Content.Add(std::move(c));
        }
        __declspec(property(put = AddContent)) IPtr<UIElement> add;
        List<IPtr<UIElement>>& GetContent() {
            return _Content;
        }
        __declspec(property(get = GetContent)) List<IPtr<UIElement>>& Content;
    public:
        virtual void Construct() = 0;
        void Build(Layout i) override {
            GetNewNext();
            _Content.Clear();
            Construct();
            for (auto& c : _Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : _Content) {
                if (c) c->Notify(e);
                if (e->Handled) return;
            }
        }
    };

    struct StatefulElement : UIElement, IRenderState
    {
    private:
        IPtr<NextElement> _Next;
        List<IPtr<UIElement>> _Content;
    public:
        IPtr<UIElement> GetNewNext() {
            _Next = INew<NextElement>();
            return _Next;
        }
        void SetNextContent(IPtr<UIElement> c) {
            if (c.IsNull) return;
            if (_Next) {
                _Next->Content.Add(std::move(c));
            }
        }
        __declspec(property(get = GetNewNext, put = SetNextContent)) IPtr<UIElement> next;
        void AddContent(IPtr<UIElement> c) {
            _Content.Add(std::move(c));
        }
        __declspec(property(put = AddContent)) IPtr<UIElement> add;
        List<IPtr<UIElement>>& GetContent() {
            return _Content;
        }
        __declspec(property(get = GetContent)) List<IPtr<UIElement>>& Content;
    public:
        virtual void Construct() = 0;
        void Build(Layout i) override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            GetNewNext();
            _Content.Clear();
            Construct();
            for (auto& c : _Content) {
                if (c) c->Build(i);
            }
        }
        void Rebuild(Layout i) {
            bool isRebuilding = Index::UI::UIContext::RebuildTree;
            Index::UI::UIContext::RebuildTree = true;
            Build(i);
            Index::UI::UIContext::RebuildTree = isRebuilding;
        }
        void Notify(INotification* e) override {
            for (auto& c : _Content) {
                if (c) c->Notify(e);
                if (e->Handled) return;
            }
        }
    };
}

// Layout Elements
namespace Index::UI
{
    struct Container : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_ARGS {
            INDEX_UI_DEFAULT_NEW_MEBERS;
            List<IPtr<UIElement>> Content;
        };
        INDEX_UI_NEW_CLASS(Container);
        INDEX_UI_NEW_CONSTRUCTOR(Container) {
            INDEX_UI_SET_DEFAULT_MEMBERS;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            Rect r = LayoutUtils::CalculateUIElementSubrect(this, i);
            for (auto& c : Content) {
                c->Build({
                    .Area = r
                });
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureMinSize() override {
            return {
                LayoutUtils::CalculateMinSizeFrom(Content)
            };
        }
    };

    struct StackH : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_ARGS {
            INDEX_UI_DEFAULT_NEW_MEBERS;
            List<IPtr<UIElement>> Content;
        };
        INDEX_UI_NEW_CLASS(StackH);
        INDEX_UI_NEW_CONSTRUCTOR(StackH) {
            INDEX_UI_SET_DEFAULT_MEMBERS;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            Rect r = LayoutUtils::CalculateUIElementSubrect(this, i);
            float x = 0;
            for (auto& c : Content) {
                auto mins = c->MeasureMinSize();
                c->Build({
                    .Area = Rect {
                        r.X + x,
                        r.Y,
                        r.Size
                    }
                });
                x += mins.Width;
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureMinSize() override {
            float minWidth = LayoutUtils::CalculateMinWidth(this);
            float minHeight = LayoutUtils::CalculateMinHeight(this);
            float width = 0;
            for (auto& c : Content) {
                auto size = c->MeasureMinSize();
                width += FloatValueOr(size.Width, 0);
                minHeight = Max(size.Height, minHeight);
            }
            return {
                Max(minWidth, width), minHeight
            };
        }
    };

    struct StackV : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_ARGS {
            INDEX_UI_DEFAULT_NEW_MEBERS;
            List<IPtr<UIElement>> Content;
        };
        INDEX_UI_NEW_CLASS(StackV);
        INDEX_UI_NEW_CONSTRUCTOR(StackV) {
            INDEX_UI_SET_DEFAULT_MEMBERS;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            Rect r = LayoutUtils::CalculateUIElementSubrect(this, i);
            float y = 0;
            for (auto& c : Content) {
                auto mins = c->MeasureMinSize();
                c->Build({
                             .Area = Rect {
                                 r.X,
                                 r.Y + y,
                                 r.Size
                             }
                         });
                y += mins.Height;
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureMinSize() override {
            float minWidth = LayoutUtils::CalculateMinWidth(this);
            float minHeight = LayoutUtils::CalculateMinHeight(this);
            float height = 0;
            for (auto& c : Content) {
                auto size = c->MeasureMinSize();
                height += FloatValueOr(size.Height, 0);
                minWidth = Max(size.Width, minWidth);
            }
            return {
                minWidth, Max(minHeight, height)
            };
        }
    };
}