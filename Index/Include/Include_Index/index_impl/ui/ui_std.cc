#pragma once

#include "ui.cc"

#pragma region Macros

#define INDEX_UI_List Index::List<Index::IPtr<Index::UI::UIElement>>

#define INDEX_UI_DefaultMembers                                                                                       \
    Index::String Name;                                                                                               \
    Index::Size MinSize { 0, 0 };                                                                                     \
    Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF };                                                       \
    Index::Size Size { Index::UI::NullF, Index::UI::NullF };                                                          \
    Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_DefaultDynamicMembers                                                                                \
    Index::String Name;                                                                                               \
    Index::UI::DynSize DynMinSize { 0.0f, 0.0f };                                                                     \
    Index::UI::DynSize DynMaxSize { Index::UI::NullF, Index::UI::NullF };                                             \
    Index::UI::DynSize DynSize { Index::UI::NullF, Index::UI::NullF };                                                \
    Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_SetDefaultMembers                                                                                    \
    this->Name = e.Name;                                                                                              \
    this->MinSize = e.MinSize;                                                                                        \
    this->MaxSize = e.MaxSize;                                                                                        \
    this->Size = e.Size;                                                                                              \
    this->Alignment = e.Alignment;

#define INDEX_UI_SetDefaultDynamicMembers                                                                             \
    this->Name = e.Name;                                                                                              \
    this->DynMinSize = e.DynMinSize;                                                                                  \
    this->DynMaxSize = e.DynMaxSize;                                                                                  \
    this->DynSize = e.DynSize;                                                                                        \
    this->Alignment = e.Alignment;

#define INDEX_UI_HolderMembers Index::List<Index::IPtr<Index::UI::UIElement>> Content;

#define INDEX_UI_SetHolderMembers this->Content = std::move(e.Content);

#define INDEX_UI_Args struct Args

#define INDEX_UI_New(class_name)                                                                                      \
    template <class T = Index::UI::UIElement> static Index::IPtr<T> New(Args&& args)                                  \
    {                                                                                                                 \
        return Index::INew<class_name>(std::forward<Args>(args));                                                     \
    }

#define INDEX_UI_NewArgs(class_name, args_name)                                                                       \
    template <class T = Index::UI::UIElement> static Index::IPtr<T> New(args_name args)                               \
    {                                                                                                                 \
        return Index::INew<class_name>(std::forward<args_name>(args));                                                \
    }

#define INDEX_UI_NewEmpty(class_name)                                                                                 \
    template <class T = Index::UI::UIElement> static Index::IPtr<T> New() { return Index::INew<class_name>(); }

#define INDEX_UI_NewC template <class T = Index::UI::UIElement> static Index::IPtr<T> New

#define INDEX_UI_DefaultConstructor(class_name) class_name() = default;

#define INDEX_UI_Constructor(class_name) explicit class_name(Args e)

#define INDEX_UI_ConstructorArgs(class_name, args_name) explicit class_name(args_name e)

#define INDEX_UI_ConstructorEmpty(class_name) explicit class_name()

#define INDEX_UI_ConstructorC(class_name, args) explicit class_name(args)

#pragma endregion

// ##################################### //
#pragma region Standard Library
// ##################################### //

// ##################################### //
#pragma region Standard Library
// ##################################### //

namespace Index::UI
{
    struct UIElementRenderAreaCache
    {
        Nullable<Rect> LastArea;
    };
}

// ##################################### //
#pragma endregion
// ##################################### //

// ##################################### //
#pragma region Standard Controls
// ##################################### //

namespace Index::UI
{
    struct Empty : virtual UIElement
    {
        INDEX_UI_NewEmpty(Empty)

            INDEX_UI_ConstructorEmpty(Empty)
        {
        }

        void Render(UIContext* u, Layout i) override { }

        void OnNotify(UINotification* e) override { }

        Index::Size MeasureIntentSize(Layout i) override { return {}; }
    };

    struct Stack : virtual UIElementHolder
    {
        INDEX_UI_NewArgs(Stack, INDEX_UI_List)

            INDEX_UI_DefaultConstructor(Stack)

                INDEX_UI_ConstructorArgs(Stack, INDEX_UI_List)
        {
            Content = std::move(e);
        }

        void Render(UIContext* u, Layout i) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override { return GetIntentSizeFrom(i, Content); }
    };

    struct ScopedStack : virtual UIElementHolder, virtual UIScope
    {
        INDEX_UI_NewArgs(ScopedStack, INDEX_UI_List)

            INDEX_UI_DefaultConstructor(ScopedStack)

                INDEX_UI_ConstructorArgs(ScopedStack, INDEX_UI_List)
        {
            Content = std::move(e);
        }

        void Render(UIContext* u, Layout i) override
        {
            EnterScope(u);
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
            LeaveScope();
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override { return GetIntentSizeFrom(i, Content); }
    };

    struct StackH : virtual UIElementHolder
    {
        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(StackH)

            INDEX_UI_DefaultConstructor(StackH)

                INDEX_UI_Constructor(StackH)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            Rect r = GetSubrect(this, i);
            float x = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto mins = c->MeasureIntentSize(i);
                c->Render(u, { .Area = Rect { r.X + x, r.Y, { mins.Width, r.Height } } });
                x += mins.Width;
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            float width = 0;
            for (auto& c : Content)
            {
                auto size = c->MeasureIntentSize(i);
                width += Validate(size.Width);
                minSize.Height = Index::Max(size.Height, minSize.Height);
            }
            return { Index::Max(minSize.Width, width), minSize.Height };
        }
    };

    struct StackV : virtual UIElementHolder
    {
        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(StackV)

            INDEX_UI_DefaultConstructor(StackV)

                INDEX_UI_Constructor(StackV)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            Rect r = GetSubrect(this, i);
            float y = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto mins = c->MeasureIntentSize(i);
                c->Render(u, { .Area = Rect { r.X, r.Y + y, { r.Width, mins.Height } } });
                y += mins.Height;
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            float height = 0;
            for (auto& c : Content)
            {
                auto size = c->MeasureIntentSize(i);
                height += Validate(size.Height);
                minSize.Width = Index::Max(size.Width, minSize.Width);
            }
            return { minSize.Width, Index::Max(minSize.Height, height) };
        }
    };

    struct Container : virtual UIElementHolder
    {
        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(Container)

            INDEX_UI_DefaultConstructor(Container)

                INDEX_UI_Constructor(Container)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            Rect r = GetSubrect(this, i);
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, { .Area = r });
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            return Max(GetMinSize(this), GetIntentSizeFrom(i, Content));
        }
    };

    struct ScopedContainer : virtual UIScope, virtual Container
    {
        INDEX_UI_Args
        {
            INDEX_UI_DefaultMembers;
            INDEX_UI_HolderMembers;
        };

        INDEX_UI_New(ScopedContainer)

            INDEX_UI_DefaultConstructor(ScopedContainer)

                INDEX_UI_Constructor(ScopedContainer)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            EnterScope(u);
            Rect r = GetSubrect(this, i);
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, { .Area = r });
            }
            LeaveScope();
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            return Max(GetMinSize(this), GetIntentSizeFrom(i, Content));
        }
    };

    struct DynContainer : virtual UIDynamic, virtual UIElementHolder
    {
        INDEX_UI_Args { INDEX_UI_DefaultDynamicMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(DynContainer)

            INDEX_UI_DefaultConstructor(DynContainer)

                INDEX_UI_Constructor(DynContainer)
        {
            INDEX_UI_SetDefaultDynamicMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            DynCache(u);
            Rect r = GetSubrect(this, i);
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, { .Area = r });
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            return Max(GetMinSize(this), GetIntentSizeFrom(i, Content));
        }
    };

    struct SpacingH : virtual UIElement
    {
        INDEX_UI_NewArgs(SpacingH, float)

            INDEX_UI_DefaultConstructor(SpacingH)

                INDEX_UI_ConstructorArgs(SpacingH, float)
        {
            Size.Width = e;
        }

        void Render(UIContext* u, Layout i) override { }

        void OnNotify(UINotification* e) override { }
    };

    struct SpacingV : virtual UIElement
    {
        INDEX_UI_NewArgs(SpacingV, float)

            INDEX_UI_DefaultConstructor(SpacingV)

                INDEX_UI_ConstructorArgs(SpacingV, float)
        {
            Size.Height = e;
        }

        void Render(UIContext* u, Layout i) override { }

        void OnNotify(UINotification* e) override { }
    };

    struct Wrap : virtual UIElement
    {
        IPtr<UIElement> Content;
        INDEX_UI_Args { IPtr<UIElement> Content; };

        INDEX_UI_New(Wrap)

            INDEX_UI_DefaultConstructor(Wrap)

                INDEX_UI_Constructor(Wrap)
        {
            Content = std::move(e.Content);
        }

        void Render(UIContext* u, Layout i) override
        {
            if (Content.IsNull) return;
            Content->Render(u, i);
        }

        void OnNotify(UINotification* e) override
        {
            if (Content.IsNull) return;
            Content->Notify(e);
        }
    };

    struct FixedGridElement
    {
        int Column = 0, Row = 0;
        int ColumnSpan = 1, RowSpan = 1;
        INDEX_UI_List Content;
        INDEX_UI_Args
        {
            int Column = 0, Row = 0;
            int ColumnSpan = 1, RowSpan = 1;
            INDEX_UI_List Content;
        };

        template <class T = FixedGridElement> static Index::IPtr<T> New(Args&& args)
        {
            return Index::INew<FixedGridElement>(std::forward<Args>(args));
        }
        INDEX_UI_DefaultConstructor(FixedGridElement)

            INDEX_UI_Constructor(FixedGridElement)
        {
            Column = e.Column;
            Row = e.Row;
            ColumnSpan = e.ColumnSpan;
            RowSpan = e.RowSpan;
            Content = std::move(e.Content);
        }

        __forceinline void Render(UIContext* u, Layout i)
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }

        __forceinline void Notify(UINotification* e)
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->OnNotify(e);
                if (e->Handled) return;
            }
        }

        __forceinline Index::Size MeasureIntentSize(Layout i) { return GetIntentSizeFrom(i, Content); }
    };

    struct FixedGrid : virtual UIElement
    {
        int Columns = 0, Rows = 0;
        List<IPtr<FixedGridElement>> Content;
        INDEX_UI_Args
        {
            INDEX_UI_DefaultMembers int Columns = 0, Rows = 0;
            List<IPtr<FixedGridElement>> Content;
        };

        INDEX_UI_New(FixedGrid)

            INDEX_UI_DefaultConstructor(FixedGrid)

                INDEX_UI_Constructor(FixedGrid)
        {
            INDEX_UI_SetDefaultMembers Columns = e.Columns;
            Rows = e.Rows;
            Content = std::move(e.Content);
        }

        void Render(UIContext* u, Layout i) override
        {
            Rect r = GetSubrect(this, i);
            float columns = Columns == 0 ? 1 : Columns;
            float rows = Rows == 0 ? 1 : Rows;
            float columnSize = r.Width / columns;
            float rowSize = r.Height / rows;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                int column = c->Column, row = c->Row;
                column = Clamp<int>(column, 0, columns - 1);
                row = Clamp<int>(row, 0, rows - 1);
                int columnSpan = c->ColumnSpan, rowSpan = c->RowSpan;
                Index::Size size {
                    (float)columnSpan * columnSize,
                    (float)rowSpan * rowSize,
                };
                c->Render(u, { .Area { r.X + (columnSize * (float)column), r.Y + (rowSize * (float)row), size } });
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override { return GetMinSize(this); }
    };

    struct Dock : virtual UIElement
    {
        enum class DockSide
        {
            Left,
            Top,
            Right,
            Bottom,
            Fill
        };

        struct DockHolder
        {
            DockSide Side;
            INDEX_UI_List Content;
            INDEX_UI_Args
            {
                DockSide Side;
                INDEX_UI_List Content;
            };
            INDEX_UI_DefaultConstructor(DockHolder)

                INDEX_UI_Constructor(DockHolder)
            {
                Side = e.Side;
                Content = std::move(e.Content);
            }

            __forceinline void Render(UIContext* u, Layout i)
            {
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    c->Render(u, i);
                }
            }

            __forceinline void Notify(UINotification* e)
            {
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    c->Notify(e);
                    if (e->Handled) return;
                }
            }

            __forceinline Index::Size MeasureIntentSize(Layout i) { return GetIntentSizeFrom(i, Content); }
        };

        static Align DockSideToAlign(DockSide side)
        {
            switch (side)
            {
            case DockSide::Left:
                return Align::Left;
            case DockSide::Top:
                return Align::Top;
            case DockSide::Right:
                return Align::Right;
            case DockSide::Bottom:
                return Align::Bottom;
            default:
                return Align::Stretch;
            }
        }

        static IPtr<DockHolder> Left(INDEX_UI_List content)
        {
            return INew<DockHolder>(DockHolder::Args { DockSide::Left, std::forward<INDEX_UI_List>(content) });
        }

        static IPtr<DockHolder> Top(INDEX_UI_List content)
        {
            return INew<DockHolder>(DockHolder::Args { DockSide::Top, std::forward<INDEX_UI_List>(content) });
        }

        static IPtr<DockHolder> Right(INDEX_UI_List content)
        {
            return INew<DockHolder>(DockHolder::Args { DockSide::Right, std::forward<INDEX_UI_List>(content) });
        }

        static IPtr<DockHolder> Bottom(INDEX_UI_List content)
        {
            return INew<DockHolder>(DockHolder::Args { DockSide::Bottom, std::forward<INDEX_UI_List>(content) });
        }

        static IPtr<DockHolder> Fill(INDEX_UI_List content)
        {
            return INew<DockHolder>(DockHolder::Args { DockSide::Fill, std::forward<INDEX_UI_List>(content) });
        }

        bool FillLast = true;
        List<IPtr<DockHolder>> Content;
        INDEX_UI_Args
        {
            INDEX_UI_DefaultMembers bool FillLast = true;
            List<IPtr<DockHolder>> Content;
        };

        INDEX_UI_New(Dock)

            INDEX_UI_DefaultConstructor(Dock)

                INDEX_UI_Constructor(Dock)
        {
            INDEX_UI_SetDefaultMembers FillLast = e.FillLast;
            Content = std::move(e.Content);
        }

        void Render(UIContext* u, Layout i) override
        {
            Rect r = GetSubrect(this, i);
            Rect leftPlace = r;
            auto length = Content.Length;
            for (int i2 = 0; i2 < length; i2++)
            {
                auto& c = Content[i2];
                if (c.IsNull) continue;
                if (((i2 == (length - 1)) && FillLast) || c->Side == DockSide::Fill)
                {
                    c->Render(u, { .Area = leftPlace });
                    return;
                }
                auto contentSize = c->MeasureIntentSize(i);
                auto contentAlign = DockSideToAlign(c->Side);
                Rect area = leftPlace;
                switch (c->Side)
                {
                case DockSide::Left:
                {
                    area.Width = Index::Min(area.Width, contentSize.Width);
                    leftPlace.X += area.Width;
                    leftPlace.Width -= area.Width;
                    break;
                }
                case DockSide::Top:
                {
                    area.Height = Index::Min(area.Height, contentSize.Height);
                    leftPlace.Y += area.Height;
                    leftPlace.Height -= area.Height;
                    break;
                }
                case DockSide::Right:
                {
                    area.Width = Index::Min(area.Width, contentSize.Width);
                    area.X = leftPlace.Second.X - area.Width;
                    leftPlace.Width -= area.Width;
                    break;
                }
                case DockSide::Bottom:
                {
                    area.Height = Index::Min(area.Height, contentSize.Height);
                    area.Y = leftPlace.Second.Y - area.Height;
                    leftPlace.Height -= area.Height;
                    break;
                }
                case DockSide::Fill:
                    break;
                }
                c->Render(u, { .Area = area });
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override { return GetMinSize(this); }
    };

    struct Padding : virtual UIElementHolder
    {
        Vec4F Edges;
        INDEX_UI_Args
        {
            Vec4F Edges;
            INDEX_UI_HolderMembers
        };

        INDEX_UI_New(Padding)

            INDEX_UI_DefaultConstructor(Padding)

                INDEX_UI_Constructor(Padding)
        {
            Edges = e.Edges;
            Content = std::move(e.Content);
        }

        void Render(UIContext* u, Layout i) override
        {
            auto& r = i.Area;
            r.X += Edges.X;
            r.Width -= Edges.X;
            r.Y += Edges.Y;
            r.Height -= Edges.Y;
            r.Width -= Edges.Z;
            r.Height -= Edges.W;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            auto size = GetIntentSizeFrom(i, Content);
            size.Width += Edges.X + Edges.Z;
            size.Height += Edges.Y + Edges.W;
            return size;
        }
    };

    struct Expanded : virtual UIElementHolder
    {
        int Flex = 1;
        INDEX_UI_Args
        {
            int Flex = 1;
            INDEX_UI_HolderMembers
        };

        INDEX_UI_New(Expanded)

            INDEX_UI_DefaultConstructor(Expanded)

                INDEX_UI_Constructor(Expanded)
        {
            Flex = e.Flex;
            INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override { return GetIntentSizeFrom(i, Content); }
    };

    template <int TFlex = 1> struct Expand : Expanded
    {
        INDEX_UI_NewArgs(Expand, INDEX_UI_List)

            INDEX_UI_DefaultConstructor(Expand)

                INDEX_UI_ConstructorArgs(Expand, INDEX_UI_List)
        {
            Flex = TFlex;
            Content = std::move(e);
        }
    };

    struct Column : virtual UIElementHolder
    {
        struct ExpandedContentInfoResult
        {
            int All = 0;
            int AllFlex = 0;
            float UnitWidth = 0;
        };

        __forceinline ExpandedContentInfoResult GetExpandedContentInfoH(Layout i)
        {
            ExpandedContentInfoResult ret {};
            for (auto& c : Content)
            {
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                if (!ptr) continue;
                auto flex = ptr->Flex;
                ret.All += 1;
                ret.AllFlex += flex;
                if (flex > 0)
                    ret.UnitWidth
                        = Max(ret.UnitWidth, ptr->MeasureIntentSize(std::forward<Layout>(i)).Width / (float)flex);
            }
            return ret;
        }

        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(Column)

            INDEX_UI_DefaultConstructor(Column)

                INDEX_UI_Constructor(Column)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            auto result = MeasureIntentSizeCustom(i);
            if (result.ExpandedInfo.All > 0)
            {
                auto intentSize = result.OtherSize;
                intentSize.Width += result.AllExpandedWidth;
                auto& expandedInfo = result.ExpandedInfo;
                Rect r = GetSubrectWithCustomIntentSize(this, i, intentSize);
                float x = 0;
                float unitwidth = (r.Width - result.OtherSize.Width) / (float)expandedInfo.AllFlex;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                    if (!ptr)
                    {
                        auto mins = c->MeasureIntentSize(i);
                        c->Render(u, { .Area = Rect { r.X + x, r.Y, { mins.Width, r.Height } } });
                        x += mins.Width;
                    }
                    else
                    {
                        auto flex = ptr->Flex;
                        float width = unitwidth * flex;
                        ptr->Render(u, { .Area = Rect { r.X + x, r.Y, { width, r.Height } } });
                        x += width;
                    }
                }
            }
            else
            {
                Rect r = GetSubrectWithCustomIntentSize(this, i, result.OtherSize);
                float additionalWidth = Max(0.f, r.Width - result.OtherSize.Width) / (float)Content.Length;
                float x = 0;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    auto mins = c->MeasureIntentSize(i);
                    mins.Width += additionalWidth;
                    c->Render(u, { .Area = Rect { r.X + x, r.Y, { mins.Width, r.Height } } });
                    x += mins.Width;
                }
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoH(i);
            float width = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Height = Index::Max(size.Height, minSize.Height);
                if (!ptr) { width += Validate(size.Width); }
                else
                {
                    auto flex = ptr->Flex;
                    width += expandedInfo.UnitWidth * (float)flex;
                }
            }
            return { Index::Max(minSize.Width, width), minSize.Height };
        }

        struct MeasureIntentSizeCustomResult
        {
            Index::Size OtherSize {};
            int OtherCount = 0;
            ExpandedContentInfoResult ExpandedInfo;
            float AllExpandedWidth = 0;
        };

        MeasureIntentSizeCustomResult MeasureIntentSizeCustom(Layout i)
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoH(i);
            float width = 0;
            float allExpandedWidth = 0;
            int otherCount = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Height = Index::Max(size.Height, minSize.Height);
                if (!ptr)
                {
                    otherCount += 1;
                    width += Validate(size.Width);
                }
                else
                {
                    auto flex = ptr->Flex;
                    allExpandedWidth += expandedInfo.UnitWidth * (float)flex;
                }
            }
            return { .OtherSize { Index::Max(minSize.Width, width), minSize.Height },
                .OtherCount = otherCount,
                .ExpandedInfo = expandedInfo,
                .AllExpandedWidth = allExpandedWidth };
        }
    };

    struct ColumnC : virtual UIElementHolder
    {
        struct ExpandedContentInfoResult
        {
            int All = 0;
            int AllFlex = 0;
            float UnitWidth = 0;
        };

        __forceinline ExpandedContentInfoResult GetExpandedContentInfoH(Layout i)
        {
            ExpandedContentInfoResult ret {};
            for (auto& c : Content)
            {
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                if (!ptr) continue;
                auto flex = ptr->Flex;
                ret.All += 1;
                ret.AllFlex += flex;
                if (flex > 0)
                    ret.UnitWidth
                        = Max(ret.UnitWidth, ptr->MeasureIntentSize(std::forward<Layout>(i)).Width / (float)flex);
            }
            return ret;
        }

        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(ColumnC)

            INDEX_UI_DefaultConstructor(ColumnC)

                INDEX_UI_Constructor(ColumnC)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            auto result = MeasureIntentSizeCustom(i);
            if (result.ExpandedInfo.All > 0)
            {
                auto intentSize = result.OtherSize;
                intentSize.Width += result.AllExpandedWidth;
                auto& expandedInfo = result.ExpandedInfo;
                Rect r = GetSubrectWithCustomIntentSize(this, i, intentSize);
                float x = 0;
                float unitwidth = (r.Width - result.OtherSize.Width) / (float)expandedInfo.AllFlex;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                    if (!ptr)
                    {
                        auto mins = c->MeasureIntentSize(i);
                        c->Render(u, { .Area = Rect { r.X + x, r.Y, { mins.Width, r.Height } } });
                        x += mins.Width;
                    }
                    else
                    {
                        auto flex = ptr->Flex;
                        float width = unitwidth * flex;
                        ptr->Render(u, { .Area = Rect { r.X + x, r.Y, { width, r.Height } } });
                        x += width;
                    }
                }
            }
            else
            {
                Rect r = GetSubrectWithCustomIntentSize(this, i, result.OtherSize);
                float widthBetween = (r.Width - result.OtherSize.Width) / (result.OtherCount + 1);
                float x = 0;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    x += widthBetween;
                    auto mins = c->MeasureIntentSize(i);
                    c->Render(u, { .Area = Rect { r.X + x, r.Y, { mins.Width, r.Height } } });
                    x += mins.Width;
                }
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoH(i);
            float width = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Height = Index::Max(size.Height, minSize.Height);
                if (!ptr) { width += Validate(size.Width); }
                else
                {
                    auto flex = ptr->Flex;
                    width += expandedInfo.UnitWidth * (float)flex;
                }
            }
            return { Index::Max(minSize.Width, width), minSize.Height };
        }

        struct MeasureIntentSizeCustomResult
        {
            Index::Size OtherSize {};
            int OtherCount = 0;
            ExpandedContentInfoResult ExpandedInfo;
            float AllExpandedWidth = 0;
        };

        MeasureIntentSizeCustomResult MeasureIntentSizeCustom(Layout i)
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoH(i);
            float width = 0;
            float allExpandedWidth = 0;
            int otherCount = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Height = Index::Max(size.Height, minSize.Height);
                if (!ptr)
                {
                    otherCount += 1;
                    width += Validate(size.Width);
                }
                else
                {
                    auto flex = ptr->Flex;
                    allExpandedWidth += expandedInfo.UnitWidth * (float)flex;
                }
            }
            return { .OtherSize { Index::Max(minSize.Width, width), minSize.Height },
                .OtherCount = otherCount,
                .ExpandedInfo = expandedInfo,
                .AllExpandedWidth = allExpandedWidth };
        }
    };

    struct Row : virtual UIElementHolder
    {
        struct ExpandedContentInfoResult
        {
            int All = 0;
            int AllFlex = 0;
            float UnitHeight = 0;
        };

        __forceinline ExpandedContentInfoResult GetExpandedContentInfoV(Layout i)
        {
            ExpandedContentInfoResult ret {};
            for (auto& c : Content)
            {
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                if (!ptr) continue;
                auto flex = ptr->Flex;
                ret.All += 1;
                ret.AllFlex += flex;
                if (flex > 0)
                    ret.UnitHeight
                        = Max(ret.UnitHeight, ptr->MeasureIntentSize(std::forward<Layout>(i)).Height / (float)flex);
            }
            return ret;
        }

        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(Row)

            INDEX_UI_DefaultConstructor(Row)

                INDEX_UI_Constructor(Row)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            auto result = MeasureIntentSizeCustom(i);
            if (result.ExpandedInfo.All > 0)
            {
                auto intentSize = result.OtherSize;
                intentSize.Height += result.AllExpandedHeight;
                auto& expandedInfo = result.ExpandedInfo;
                Rect r = GetSubrectWithCustomIntentSize(this, i, intentSize);
                float y = 0;
                float unitheight = (r.Height - result.OtherSize.Height) / (float)expandedInfo.AllFlex;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                    if (!ptr)
                    {
                        auto mins = c->MeasureIntentSize(i);
                        c->Render(u, { .Area = Rect { r.X, r.Y + y, { mins.Width, r.Height } } });
                        y += mins.Height;
                    }
                    else
                    {
                        auto flex = ptr->Flex;
                        float height = unitheight * flex;
                        ptr->Render(u, { .Area = Rect { r.X, r.Y + y, { r.Width, height } } });
                        y += height;
                    }
                }
            }
            else
            {
                Rect r = GetSubrectWithCustomIntentSize(this, i, result.OtherSize);
                float additionalHeight = Max(0.f, r.Height - result.OtherSize.Height) / (float)Content.Length;
                float y = 0;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    auto mins = c->MeasureIntentSize(i);
                    mins.Height += additionalHeight;
                    c->Render(u, { .Area = Rect { r.X, r.Y + y, { mins.Width, r.Height } } });
                    y += mins.Height;
                }
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoV(i);
            float height = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Width = Index::Max(size.Width, minSize.Width);
                if (!ptr) { height += Validate(size.Height); }
                else
                {
                    auto flex = ptr->Flex;
                    height += expandedInfo.UnitHeight * (float)flex;
                }
            }
            return { minSize.Width, Index::Max(minSize.Height, height) };
        }

        struct MeasureIntentSizeCustomResult
        {
            Index::Size OtherSize {};
            int OtherCount = 0;
            ExpandedContentInfoResult ExpandedInfo;
            float AllExpandedHeight = 0;
        };

        MeasureIntentSizeCustomResult MeasureIntentSizeCustom(Layout i)
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoV(i);
            float height = 0;
            float allExpandedHeight = 0;
            int otherCount = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Height = Index::Max(size.Height, minSize.Height);
                if (!ptr)
                {
                    otherCount += 1;
                    height += Validate(size.Height);
                }
                else
                {
                    auto flex = ptr->Flex;
                    allExpandedHeight += expandedInfo.UnitHeight * (float)flex;
                }
            }
            return { .OtherSize { minSize.Width, Index::Max(minSize.Height, height) },
                .OtherCount = otherCount,
                .ExpandedInfo = expandedInfo,
                .AllExpandedHeight = allExpandedHeight };
        }
    };

    struct RowC : virtual UIElementHolder
    {
        struct ExpandedContentInfoResult
        {
            int All = 0;
            int AllFlex = 0;
            float UnitHeight = 0;
        };

        __forceinline ExpandedContentInfoResult GetExpandedContentInfoV(Layout i)
        {
            ExpandedContentInfoResult ret {};
            for (auto& c : Content)
            {
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                if (!ptr) continue;
                auto flex = ptr->Flex;
                ret.All += 1;
                ret.AllFlex += flex;
                if (flex > 0)
                    ret.UnitHeight
                        = Max(ret.UnitHeight, ptr->MeasureIntentSize(std::forward<Layout>(i)).Height / (float)flex);
            }
            return ret;
        }

        INDEX_UI_Args { INDEX_UI_DefaultMembers INDEX_UI_HolderMembers };

        INDEX_UI_New(RowC)

            INDEX_UI_DefaultConstructor(RowC)

                INDEX_UI_Constructor(RowC)
        {
            INDEX_UI_SetDefaultMembers INDEX_UI_SetHolderMembers
        }

        void Render(UIContext* u, Layout i) override
        {
            auto result = MeasureIntentSizeCustom(i);
            if (result.ExpandedInfo.All > 0)
            {
                auto intentSize = result.OtherSize;
                intentSize.Height += result.AllExpandedHeight;
                auto& expandedInfo = result.ExpandedInfo;
                Rect r = GetSubrectWithCustomIntentSize(this, i, intentSize);
                float y = 0;
                float unitheight = (r.Height - result.OtherSize.Height) / (float)expandedInfo.AllFlex;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                    if (!ptr)
                    {
                        auto mins = c->MeasureIntentSize(i);
                        c->Render(u, { .Area = Rect { r.X, r.Y + y, { mins.Width, r.Height } } });
                        y += mins.Height;
                    }
                    else
                    {
                        auto flex = ptr->Flex;
                        float height = unitheight * flex;
                        ptr->Render(u, { .Area = Rect { r.X, r.Y + y, { r.Width, height } } });
                        y += height;
                    }
                }
            }
            else
            {
                Rect r = GetSubrectWithCustomIntentSize(this, i, result.OtherSize);
                float heightBetween = (r.Height - result.OtherSize.Height) / (result.OtherCount + 1);
                float y = 0;
                for (auto& c : Content)
                {
                    if (c.IsNull) continue;
                    y += heightBetween;
                    auto mins = c->MeasureIntentSize(i);
                    c->Render(u, { .Area = Rect { r.X, r.Y + y, { mins.Width, r.Height } } });
                    y += mins.Height;
                }
            }
        }

        void OnNotify(UINotification* e) override
        {
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoV(i);
            float height = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Width = Index::Max(size.Width, minSize.Width);
                if (!ptr) { height += Validate(size.Height); }
                else
                {
                    auto flex = ptr->Flex;
                    height += expandedInfo.UnitHeight * (float)flex;
                }
            }
            return { minSize.Width, Index::Max(minSize.Height, height) };
        }

        struct MeasureIntentSizeCustomResult
        {
            Index::Size OtherSize {};
            int OtherCount = 0;
            ExpandedContentInfoResult ExpandedInfo;
            float AllExpandedHeight = 0;
        };

        MeasureIntentSizeCustomResult MeasureIntentSizeCustom(Layout i)
        {
            Index::Size minSize = GetMinSize(this);
            auto expandedInfo = GetExpandedContentInfoV(i);
            float height = 0;
            float allExpandedHeight = 0;
            int otherCount = 0;
            for (auto& c : Content)
            {
                if (c.IsNull) continue;
                auto size = c->MeasureIntentSize(i);
                Expanded* ptr = dynamic_cast<Expanded*>(c.Get);
                minSize.Width = Index::Max(size.Width, minSize.Width);
                if (!ptr)
                {
                    otherCount += 1;
                    height += Validate(size.Height);
                }
                else
                {
                    auto flex = ptr->Flex;
                    allExpandedHeight += expandedInfo.UnitHeight * (float)flex;
                }
            }
            return { .OtherSize { minSize.Width, Index::Max(minSize.Height, height) },
                .OtherCount = otherCount,
                .ExpandedInfo = expandedInfo,
                .AllExpandedHeight = allExpandedHeight };
        }
    };

    struct Builder : virtual UIElement
    {
        using BuildFunc = Func<IPtr<UIElement>(UIContext* u, Layout i)>;
        IPtr<UIElement> CachedElement;
        BuildFunc Build;
        INDEX_UI_Args { BuildFunc Build; };

        INDEX_UI_New(Builder)

            INDEX_UI_DefaultConstructor(Builder)

                INDEX_UI_Constructor(Builder)
        {
            Build = e.Build;
        }

        void Render(UIContext* u, Layout i) override
        {
            if (!Build) return;
            auto c = Build(u, i);
            if (c) c->Render(u, i);
            CachedElement = std::move(c);
        }

        void OnNotify(UINotification* e) override
        {
            if (CachedElement.IsNull) return;
            CachedElement->Notify(e);
        }

        Index::Size MeasureIntentSize(Layout i) override
        {
            if (CachedElement.IsNull) return { 0, 0 };
            return CachedElement->MeasureIntentSize(i);
        }
    };

    struct Executor : virtual UIElement
    {
        using ExecutorFunc = Func<void(UIContext* u, Layout i)>;
        ExecutorFunc Execute;
        INDEX_UI_Args { ExecutorFunc Execute; };

        INDEX_UI_New(Executor)

            INDEX_UI_DefaultConstructor(Executor)

                INDEX_UI_Constructor(Executor)
        {
            Execute = e.Execute;
        }

        void Render(UIContext* u, Layout i) override
        {
            if (!Execute) return;
            Execute(u, i);
        }

        void OnNotify(UINotification* e) override { }
    };

    template <class T> struct Element : virtual UIElement
    {
    private:
        IPtr<UIElement> CachedElement;

    protected:
        UIContext* Context;

    public:
        void Reconstruct() { CachedElement.Reset(); }

        virtual IPtr<UIElement> Construct() = 0;

    private:
        void Render(UIContext* u, Layout i) final override
        {
            if (CachedElement.IsNull)
            {
                Context = u;
                CachedElement = Construct();
            }
            if (CachedElement.IsNull) return;
            CachedElement->Render(u, i);
        }

        void OnNotify(UINotification* e) final override
        {
            if (CachedElement.IsNull) return;
            CachedElement->Notify(e);
        }

        Index::Size MeasureIntentSize(Layout i) final override
        {
            if (CachedElement.IsNull) return { 0, 0 };
            return CachedElement->MeasureIntentSize(i);
        }

    public:
        template <class TRet = Index::UI::UIElement> static Index::IPtr<TRet> New()
        {
            return Index::INew<T>().template As<TRet>();
        }
    };

    template <class T> struct ScopedElement : virtual UIScope
    {
    private:
        IPtr<UIElement> CachedElement;

    protected:
        UIContext* Context;

    public:
        void Reconstruct() { CachedElement.Reset(); }

        virtual IPtr<UIElement> Construct() = 0;

    private:
        void Render(UIContext* u, Layout i) final override
        {
            EnterScope(u);
            if (CachedElement.IsNull)
            {
                Context = u;
                CachedElement = Construct();
            }
            if (CachedElement.IsNull) return;
            CachedElement->Render(u, i);
            LeaveScope();
        }

        void OnNotify(UINotification* e) final override
        {
            if (CachedElement.IsNull) return;
            CachedElement->Notify(e);
        }

        Index::Size MeasureIntentSize(Layout i) final override
        {
            if (CachedElement.IsNull) return { 0, 0 };
            return CachedElement->MeasureIntentSize(i);
        }

    public:
        template <class TRet = Index::UI::UIElement> static Index::IPtr<TRet> New()
        {
            return Index::INew<T>().template As<TRet>();
        }
    };
}

// ##################################### //
#pragma endregion
// ##################################### //

// ##################################### //
#pragma endregion
// ##################################### //