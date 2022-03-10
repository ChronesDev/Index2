#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct UIPath
    {
    public:
        List<string> Path;

    public:
        bool GetIsEmpty() const { return Path.Length == 0; }
        INDEX_Property(get = GetIsEmpty) bool IsEmpty;

        string GetTarget() const { return Path.Last; }
        INDEX_Property(get = GetTarget) string Target;
        string TargetOr(string other)
        {
            if (IsEmpty)
                return other;
            else
                return Target;
        }

        bool GetCurrentTargetsName() { return IsName(Path.First); }
        INDEX_Property(get = GetCurrentTargetsName) bool CurrentTargetsName;

        bool GetCurrentTargetsId() { return IsId(Path.First); }
        INDEX_Property(get = GetCurrentTargetsId) bool CurrentTargetsId;

        bool GetIsCurrentTargetScope() { return Path.Length > 1; }
        INDEX_Property(get = GetIsCurrentTargetScope) bool IsCurrentTargetScope;

        bool GetIsCurrentTargetElement() { return Path.Length == 1; }
        INDEX_Property(get = GetIsCurrentTargetElement) bool IsCurrentTargetElement;

    public:
        static bool IsName(string s) { return !s.StarsWith("#"); }
        static bool IsId(string s) { return s.StarsWith("#"); }
    };
}