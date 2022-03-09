#include <index>
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

    var mapper = ContainerMapper();
    sub VStack mapn
    {
        m Id = ":DDD";
        sub TestElement mapn {
            m Name = "My cool element";
            m Height = 11;
        };
        sub Container mapn {
            m Size = { 10, 10 };
            sub TestElement mapn {
                m Name = "2";
            };

            sub Switcher mapn {
                m Name = "Switcher";
                sub TestElement, 1 mapn {

                };
            };
        };
    };
    var ui = mapper.Make();
    ui->ComputeLayout(0);
    ui->ComputeLayoutPosition({ 0, 0, 100, 100 });

    var target = ui->PerformElementHitTest({ 1, 1 });
    if (target.IsNull)
    {
        target->Update();
    }

    return 0;
}

#include <index_macros_end>
#include <index_ui_macros_end>