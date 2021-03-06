#include <index>
#include <index_mem>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;
    using namespace Index::UI;

    struct TestElementMapper;
    struct TestElement : virtual UIContainer
    {
        INDEX_UI_UseMapper(TestElementMapper);

        TestElement() : UITouchElement(true) { }
        ~TestElement() { }

        void OnUpdate() override {
            Debug.Log("Root: ", this->UIRoot.Ptr);
        }
    };

    struct TestElementMapper : virtual UIElementMapper
    {
        IPtr<UIElement> Make() override {
            IPtr<TestElement> e_ref = INew<TestElement>();
            TestElement& e = e_ref.Value;

            Impl_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };

    IPtr<UIRoot> ui_root = INew<UIRoot>();

    var mapper = ScopedContainerMapper();
    sub VStack mapn
    {
        m Name = "SSSS";
        m Id = "#:DDD";
        sub TestElement mapn {
            m Name = "My cool element";
            m Height = 11;
        };
        sub ScopedContainer mapn {
            m Name = "Mu";
            m Size = { 10, 10 };
            sub TestElement mapn {
                m Name = "Mu";
            };

            sub Switcher mapn {
                m Name = "Switcher";
                sub TestElement, 1 mapn {

                };
                sub TestElement, 2 mapn {
                    m Name = ":)";
                    m Id = "#24235345";
                };
                sub ScopedContainer mapn {
                    m Name = "E";
                    sub ScopedContainer mapn {
                        m Name = "E2";
                    };
                };
            };
        };
    };
    var ui = mapper.Make();

    ui_root->AttachRootElement(ui);
    ui_root->Compute(0, { 0, 0, 200, 100 });

    var target = ui_root->ElementHitTest({ 1, 1 });
    if (!target.IsNull)
    {
        ui_root->Update();
    }

    auto e2 = ui_root->SearchT<TestElement>(UIPath::From("!/Mu/#24235345"));
    auto e3 = e2->Search(UIPath::From("!/Mu/E/E2/../../#24235345"));

    ui_root->DetachRootElement();

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>