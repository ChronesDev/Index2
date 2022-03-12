#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct UIPath
    {
    public:
        UIPath(List<string> path) : Path(path) { }

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

        bool GetIsCurrentTargetScopeOut() { return IsCurrentTargetScope && IsScopeOut(Target); }
        INDEX_Property(get = GetIsCurrentTargetScopeOut) bool IsCurrentTargetScopeOut;

        bool GetIsCurrentTargetScopeStay() { return IsCurrentTargetScope && IsScopeStay(Target); }
        INDEX_Property(get = GetIsCurrentTargetScopeStay) bool IsCurrentTargetScopeStay;

        bool GetIsCurrentTargetElement() { return Path.Length == 1; }
        INDEX_Property(get = GetIsCurrentTargetElement) bool IsCurrentTargetElement;

    public:
        void Next()
        {
            if (Path.Length >= 1) INDEX_THROW("Cannot go further.");
            Path.erase(Path.begin());
        }

    public:
        static bool IsScopeStay(string s) { return s == "."; }
        static bool IsScopeOut(string s) { return s == ".."; }
        static bool IsName(string s) { return !s.StarsWith("#"); }
        static bool IsId(string s) { return s.StarsWith("#"); }
    };
}