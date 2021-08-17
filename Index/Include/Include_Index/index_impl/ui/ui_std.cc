#pragma once

#include "ui.cc"

#pragma region Macros

#define INDEX_UI_List \
Index::List<Index::IPtr<Index::UI::UIElement>>

#define INDEX_UI_DefaultMembers                             \
Index::Size MinSize { 0, 0 };                               \
Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF }; \
Index::Size Size { Index::UI::NullF, Index::UI::NullF };    \
Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_SetDefaultMembers       \
this->MinSize = e.MinSize;               \
this->MaxSize = e.MaxSize;               \
this->Size = e.Size;                     \
this->Alignment = e.Alignment;

#define INDEX_UI_HolderMembers                             \
Index::List<Index::IPtr<Index::UI::UIElement>> Content;

#define INDEX_UI_SetHolderMembers \
this->Content = std::move(e.Content);

#define INDEX_UI_Args \
struct Args

#define INDEX_UI_New(class_name)                                                    \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New(Args&& args) {   \
return Index::INew<class_name>(std::forward<Args>(args));                           \
}

#define INDEX_UI_NewArgs(class_name, args_name)                                        \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New(args_name args) {   \
return Index::INew<class_name>(std::forward<args_name>(args));                         \
}

#define INDEX_UI_NewEmpty(class_name)                                                  \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New() {                 \
return Index::INew<class_name>();                                                      \
}

#define INDEX_UI_NewC \
template<class T = Index::UI::UIElement> static Index::IPtr<T> New

#define INDEX_UI_Constructor(class_name) \
explicit class_name(Args e)

#define INDEX_UI_ConstructorArgs(class_name, args_name) \
explicit class_name(args_name e)

#define INDEX_UI_ConstructorEmpty(class_name) \
explicit class_name()

#define INDEX_UI_ConstructorC(class_name, args) \
explicit class_name(args)

#pragma endregion

// ##################################### //
#pragma region Standard Library
// ##################################### //



namespace Index::UI
{
    struct Empty : UIElement
    {
        INDEX_UI_ConstructorEmpty(Empty) { }
    };

    struct Stack : UIElementHolder
    {
        INDEX_UI_NewArgs(Stack, INDEX_UI_List)
        INDEX_UI_ConstructorArgs(Stack, INDEX_UI_List) {
            Content = std::move(e);
        }
        void Render(UIContext* u, Layout i) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }
        void Notify(UINotification* e) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureIntentSize(Layout i) override {
            return GetIntentSizeFrom(i, Content);
        }
    };

    struct StackH : UIElementHolder
    {
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            INDEX_UI_HolderMembers
        };
        INDEX_UI_New(StackH)
        INDEX_UI_Constructor(StackH) {
            INDEX_UI_SetDefaultMembers
            INDEX_UI_SetHolderMembers
        }
        void Render(UIContext* u, Layout i) override {
            Rect r = GetSubrect(this, i);
            float x = 0;
            for (auto& c : Content) {
                if (c.IsNull) continue;
                auto mins = c->MeasureIntentSize(i);
                c->Render(u, {
                    .Area = Rect {
                        r.X + x,
                        r.Y,
                        { mins.Width, r.Height }
                    }
                });
                x += mins.Width;
            }
        }
        void Notify(UINotification* e) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureIntentSize(Layout i) override {
            Index::Size minSize = GetMinSize(this);
            float width = 0;
            for (auto& c : Content) {
                auto size = c->MeasureIntentSize(i);
                width += Validate(size.Width);
                minSize.Height = Index::Max(size.Height, minSize.Height);
            }
            return {
                Index::Max(minSize.Width, width), minSize.Height
            };
        }
    };

    struct StackV : UIElementHolder
    {
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            INDEX_UI_HolderMembers
        };
        INDEX_UI_New(StackV)
        INDEX_UI_Constructor(StackV) {
            INDEX_UI_SetDefaultMembers
            INDEX_UI_SetHolderMembers
        }
        void Render(UIContext* u, Layout i) override {
            Rect r = GetSubrect(this, i);
            float y = 0;
            for (auto& c : Content) {
                if (c.IsNull) continue;
                auto mins = c->MeasureIntentSize(i);
                c->Render(u, {
                    .Area = Rect {
                        r.X,
                        r.Y + y,
                        { r.Width, mins.Height }
                    }
                });
                y += mins.Height;
            }
        }
        void Notify(UINotification* e) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureIntentSize(Layout i) override {
            Index::Size minSize = GetMinSize(this);
            float height = 0;
            for (auto& c : Content) {
                auto size = c->MeasureIntentSize(i);
                height += Validate(size.Height);
                minSize.Width = Index::Max(size.Width, minSize.Width);
            }
            return {
                minSize.Width, Index::Max(minSize.Height, height)
            };
        }
    };

    struct SpacingH : UIElement
    {
        INDEX_UI_NewArgs(SpacingH, float)
        INDEX_UI_ConstructorArgs(SpacingH, float) {
            Size.Width = e;
        }
        void Render(UIContext* u, Layout i) override { }
        void Notify(UINotification* e) override { }
    };

    struct SpacingV : UIElement
    {
        INDEX_UI_NewArgs(SpacingV, float)
        INDEX_UI_ConstructorArgs(SpacingV, float) {
            Size.Height = e;
        }
        void Render(UIContext* u, Layout i) override { }
        void Notify(UINotification* e) override { }
    };

    struct Wrap : UIElement
    {
        IPtr<UIElement> Content;
        INDEX_UI_Args {
            IPtr<UIElement> Content;
        };
        INDEX_UI_New(Wrap)
        INDEX_UI_Constructor(Wrap) {
            Content = std::move(e.Content);
        }
        void Render(UIContext* u, Layout i) override {
            if (Content.IsNull) return;
            Content->Render(u, i);
        }
        void Notify(UINotification* e) override {
            if (Content.IsNull) return;
            Content->Notify(e);
        }
    };

    struct FixedGridElement : UIElementHolder
    {
        int Column = 0, Row = 0;
        int ColumnSpan = 1, RowSpan = 1;
        INDEX_UI_Args {
            int Column = 0, Row = 0;
            int ColumnSpan = 1, RowSpan = 1;
            INDEX_UI_HolderMembers
        };
        template<class T = FixedGridElement>
        static Index::IPtr<T> New(Args &&args) { return Index::INew<FixedGridElement>(std::forward<Args>(args)); }
        INDEX_UI_Constructor(FixedGridElement) {
            Column = e.Column;
            Row = e.Row;
            ColumnSpan = e.ColumnSpan;
            RowSpan = e.RowSpan;
            INDEX_UI_SetHolderMembers
        }
        void Render(UIContext* u, Layout i) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Render(u, i);
            }
        }
        void Notify(UINotification* e) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureIntentSize(Layout i) override {
            return GetIntentSizeFrom(i, Content);
        }
    };

    struct FixedGrid : UIElement
    {
        int Columns = 0, Rows = 0;
        List<IPtr<FixedGridElement>> Content;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            int Columns = 0, Rows = 0;
            List<IPtr<FixedGridElement>> Content;
        };
        INDEX_UI_New(FixedGrid)
        INDEX_UI_Constructor(FixedGrid) {
            INDEX_UI_SetDefaultMembers
            Columns = e.Columns;
            Rows = e.Rows;
            Content = std::move(e.Content);
        }
        void Render(UIContext* u, Layout i) override {
            Rect r = GetSubrect(this, i);
            float columns = Columns == 0 ? 1 : Columns;
            float rows = Rows == 0 ? 1 : Rows;
            float columnSize = r.Width / columns;
            float rowSize = r.Height / rows;
            for (auto& c : Content) {
                if (c.IsNull) continue;
                int column = c->Column, row = c->Row;
                column = Clamp<int>(column, 0, columns - 1);
                row = Clamp<int>(row, 0, rows - 1);
                int columnSpan = c->ColumnSpan, rowSpan = c->RowSpan;
                Index::Size size {
                    (float)columnSpan * columnSize,
                    (float)rowSpan * rowSize,
                };
                c->Render(u, {
                    .Area {
                        r.X + (columnSize * (float)column),
                        r.Y + (rowSize * (float)row),
                        size
                    }
                });
            }
        }
        void Notify(UINotification* e) override {
            for (auto& c : Content) {
                if (c.IsNull) continue;
                c->Notify(e);
                if (e->Handled) return;
            }
        }
        Index::Size MeasureIntentSize(Layout i) override {
            return GetMinSize(this);
        }
    };
}




// ##################################### //
#pragma endregion
// ##################################### //