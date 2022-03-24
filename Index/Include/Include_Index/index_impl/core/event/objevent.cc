#pragma once

#include "../../helpers/include.cc"
#include "../../std/include.cc"

namespace Index
{
    template <class TObj, class T> class ObjEvent
    {
    public:
        ObjEvent() = default;

    protected:
        List<Pair<TObj, Func<T>>> Subscribers_;

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

        void Add(const Pair<TObj, Func<T>>& p) { Subscribers_.Add(p); }
        void Remove(const Pair<TObj, Func<T>>& p)
        {
            for (auto it = Subscribers_.begin(); it != Subscribers_.end(); it++)
            {
                if (it->First == p.First && it->Second.IsIdentical(p.Second))
                {
                    Subscribers_.Erase(it);
                    return;
                }
            }
        }
        void RemoveAll(const Pair<TObj, Func<T>>& p)
        {
            auto end = std::remove_if(Subscribers_.begin(), Subscribers_.end(),
                [&](Pair<TObj, Func<T>>& e) { return e.First == p.First && e.Second.IsIdentical(p.Second); });
            Subscribers_.Erase(end, Subscribers_.end());
        }
        bool Contains(const Pair<TObj, Func<T>>& p)
        {
            for (auto it = Subscribers_.begin(); it != Subscribers_.end(); it++)
            {
                if (it->First == p.First && it->Second.IsIdentical(p.Second)) { return true; }
            }
            return false;
        }
        void Clear() { Subscribers_.Clear(); }

        template <class... TArgs> void Invoke(TArgs&&... args)
        {
            for (auto& s : Subscribers_)
            {
                if (s.Second) s.Second(std::forward<TArgs>(args)...);
            }
        }

        ObjEvent<TObj, T>& operator+=(const Pair<TObj, Func<T>>& p)
        {
            Add(p);
            return *this;
        }
        ObjEvent<TObj, T>& operator-=(const Pair<TObj, Func<T>>& p)
        {
            Remove(p);
            return *this;
        }
    };
}