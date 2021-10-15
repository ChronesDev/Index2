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

        void Add(const Func<T>& f) { Subscribers_.template Add(f); }
        void Remove(const Func<T>& f) { Subscribers_.template Remove(f); }
        void RemoveAll(const Func<T>& f) { Subscribers_.template RemoveAll(f); }
        bool Contains(const Func<T>& f) { return Subscribers_.template Contains(f); }
        void Clear() { Subscribers_.template Clear(); }

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