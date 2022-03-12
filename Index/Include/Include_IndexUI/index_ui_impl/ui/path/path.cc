#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct UIPath
    {
    public:
        UIPath(List<string> path) : Path(path) { }

    public:
        static UIPath From(List<string> p) { return { p }; }
        static UIPath From(string s) { return { s.Split("/") }; }

    public:
        List<string> Path;

    public:
        bool GetIsEmpty() const { return Path.Length == 0; }
        INDEX_Property(get = GetIsEmpty) bool IsEmpty;

        string GetTarget() const { return Path.First; }
        INDEX_Property(get = GetTarget) string Target;
        string TargetOr(string other)
        {
            if (IsEmpty)
                return other;
            else
                return Target;
        }

        string GetElement() const { return Path.Last; }
        INDEX_Property(get = GetElement) string Element;
        string ElementOr(string other)
        {
            if (IsEmpty)
                return other;
            else
                return Element;
        }

        bool GetTargetsName() { return IsName(Path.First); }
        INDEX_Property(get = GetTargetsName) bool TargetsName;

        bool GetTargetsId() { return IsId(Path.First); }
        INDEX_Property(get = GetTargetsId) bool TargetsId;

        bool GetTargetsScope() { return Path.Length > 1; }
        INDEX_Property(get = GetTargetsScope) bool TargetsScope;

        bool GetTargetsScopeOut() { return TargetsScope && IsScopeOut(Target); }
        INDEX_Property(get = GetTargetsScopeOut) bool TargetsScopeOut;

        bool GetTargetsScopeStay() { return TargetsScope && IsScopeStay(Target); }
        INDEX_Property(get = GetTargetsScopeStay) bool TargetsScopeStay;

        bool GetTargetsElement() { return Path.Length == 1; }
        INDEX_Property(get = GetTargetsElement) bool TargetsElement;

    public:
        void Next()
        {
            if (Path.Length <= 1) INDEX_THROW("Cannot go further.");
            Path.erase(Path.begin());
        }

    public:
        static bool IsScopeStay(string s) { return s == "."; }
        static bool IsScopeOut(string s) { return s == ".."; }
        static bool IsName(string s) { return !s.StarsWith("#"); }
        static bool IsId(string s) { return s.StarsWith("#"); }
    };
}