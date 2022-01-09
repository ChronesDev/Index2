#pragma once

#include "../element/element.cc"

namespace Index::UI
{
    struct UIProvider : IObj<UIProvider>, IUIProvider
    {
        UIProvider() = default;

        ~UIProvider() override { DisconnectAll_(); }

    protected:
        List<WPtr<UIElement>> Connections_;

    public:
        const decltype(Connections_)& GetConnections() const { return Connections_; }
        INDEX_Property(get = GetConnections) const decltype(Connections_)& Connections;

    protected:
        void Connections_Add_(const WPtr<UIElement>& provider) { Connections_.Add(provider); }
        void Connections_Remove_(const WPtr<UIElement>& provider) { Connections_.Remove(provider); }
        bool Connections_Contains_(const WPtr<UIElement>& provider) const
        {
            for (auto& c : Connections_)
            {
                if (c == provider) return true;
            }
            return false;
        }

    public:
        bool IsConnectedTo(const IPtr<UIElement>& e) override
        {
            return Connections_Contains_(e);
        }

        void Connect(IPtr<UIElement> e) override
        {
            if (e.IsNull) INDEX_THROW("element was null.");
            if (Connections_Contains_(e)) INDEX_THROW("Already connected with element.");

            try
            {
                UIElement_ConnectTo_(e);
            }
            catch (std::exception ex)
            {
                INDEX_THROW("Failed at trying to connect element.");
            }

            Connections_.Add(e);
        }
        void Disconnect(IPtr<UIElement> e) override
        {
            if (e.IsNull) INDEX_THROW("element was null.");
            if (!Connections_Contains_(e)) INDEX_THROW("element is not connected.");

            try
            {
                UIElement_ConnectTo_(e);
            }
            catch (std::exception ex)
            {
                INDEX_THROW("Failed at trying to disconnect element.");
            }
            
            Connections_Remove_(e);
        }

    protected:
        void DisconnectAll_()
        {
            auto connections = Connections_;
            for (auto& c : connections)
            {
                Disconnect(c.Lock);
            }
        }

    protected:
        void UIElement_ConnectTo_(IPtr<UIElement>& e) { e->CreateConnectionWith(WSelf().DynamicAs<IUIProvider>()); }
        void UIElement_DisconnectFrom_(IPtr<UIElement>& e)
        {
            e->DestroyConnectionWith(WSelf().DynamicAs<IUIProvider>());
        }
    };
}