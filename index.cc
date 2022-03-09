#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;
    using namespace Index::UI;

    struct TestElement : virtual UIContainer
    {
        TestElement()
        {
            Debug.Log("Creating.");
        }

        ~TestElement()
        {
            Debug.Log("[", Id, "] Deleting.");
        }
    protected:
        void OnAttachedTo_(const IPtr<UIElement>& parent) override
        {
            Debug.Log("[", Id, "] Attaching", parent->Id == "." ? "" : " to (" + parent->Id + ").");
        }
        void OnDetachedFrom_() override
        {
            Debug.Log("[", Id, "] Detaching.");
        }

        void OnAttached_(IPtr<UIElement> child) override
        {
            Debug.Log("[", Id, "] Adding Child", child->Id == "." ? "" : " (" + child->Id + ").");
        }
        void OnDetached_(IPtr<UIElement> child) override
        {
            Debug.Log("[", Id, "] Removing Child", child->Id == "." ? "" : " (" + child->Id + ").");
        }
    };

    {
        IPtr<TestElement> u1 = INew<TestElement>();
        u1->Id = "U1";
        {
            IPtr<TestElement> u2 = INew<TestElement>();
            IPtr<TestElement> u3 = INew<TestElement>();
            u2->Id = "U2";
            u3->Id = "U3";

            u1->Attach(u2);
            u2->Attach(u3);

            u1->Detach(u2);
        }
    }

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>