#pragma once

#include "../../helpers/include.cc"
#include "../../std/include.cc"

namespace Index
{
    template <class T> class Event
    {
    public:
        Event() = default;

    protected:
        List<Func<T>> Subscribers_;

    public:
        List<Func<T>>& GetSubscribers() { return Subscribers_; }
        INDEX_Property(get = GetSubscribers) List<Func<T>>& Subscribers;

        size_t GetCount() { return Subscribers_.Length; }
        INDEX_Property(get = GetCount) size_t Count;

        Func<T>& At(size_t index) { return Subscribers_[index]; }
        Func<T>& operator[](size_t index) { return Subscribers_[index]; }
        List<Func<T>>* operator->() { return &Subscribers_; }

        auto begin() { return Subscribers_.begin(); }
        auto end() { return Subscribers_.end(); }

        void Add(const Func<T>& f) { Subscribers_.Add(f); }
        void Remove(const Func<T>& f)
        {
            for (auto it = Subscribers_.begin(); it != Subscribers_.end(); it++)
            {
                if (it->IsIdentical(f))
                {
                    Subscribers_.Erase(it);
                    return;
                }
            }
        }
        void RemoveAll(const Func<T>& f)
        {
            auto end = std::remove_if(Subscribers_.begin(), Subscribers_.end(), [&](Func<T>& e) { return e.IsIdentical(f); });
            Subscribers_.Erase(end, Subscribers_.end());
        }
        bool Contains(const Func<T>& f) { return Subscribers_.Contains(f); }
        void Clear() { Subscribers_.Clear(); }

        template <class... TArgs> void Invoke(TArgs&&... args)
        {
            for (auto& s : Subscribers_)
            {
                if (s) s(std::forward<TArgs>(args)...);
            }
        }

        Event<T>& operator+=(const Func<T>& f)
        {
            Add(f);
            return *this;
        }
        Event<T>& operator-=(const Func<T>& f)
        {
            Remove(f);
            return *this;
        }
    };
}