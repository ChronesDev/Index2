#pragma once

#include "../../std/string/string.cc"

namespace Index
{
    struct Version
    {
        short Major = 0;
        short Minor = 0;
        short Build = 0;
        short Revision = 0;

        bool operator==(Version const&) const = default;
        inline bool operator>(Version const&) const;
        inline bool operator<(Version const&) const;
        inline operator string() const;

        inline static Version Parse(string s);
        inline static Version TryParse(string s);
        inline static bool TryParse(string s, Version& out);
    };

    Version::operator string() const
    {
        std::stringstream ss;
        ss << Major << "." << Minor << "." << Build << "." << Revision;
        return ss.str();
    }

    inline bool Version::operator>(const Version& other) const
    {
        if (Major > other.Major) return true;
        if (Major < other.Major) return false;

        if (Minor > other.Minor) return true;
        if (Minor < other.Minor) return false;

        if (Build > other.Build) return true;
        if (Build < other.Build) return false;

        if (Revision > other.Revision) return true;
        return false;
    }

    inline bool Version::operator<(const Version& other) const
    {
        if (Major < other.Major) return true;
        if (Major > other.Major) return false;

        if (Minor < other.Minor) return true;
        if (Minor > other.Minor) return false;

        if (Build < other.Build) return true;
        if (Build > other.Build) return false;

        if (Revision < other.Revision) return true;
        return false;
    }

    Version Version::Parse(string s)
    {
        auto ss = s.Split(".");
        auto ret = Version();

        if (ss.Length < 1) goto jmp_ret;
        ret.Major = std::stoi(ss[0]);

        if (ss.Length < 2) goto jmp_ret;
        ret.Minor = std::stoi(ss[1]);

        if (ss.Length < 3) goto jmp_ret;
        ret.Build = std::stoi(ss[2]);

        if (ss.Length < 3) goto jmp_ret;
        ret.Revision = std::stoi(ss[3]);

    jmp_ret:
        return ret;
    }

    Version Version::TryParse(string s)
    {
        try
        {
            return Parse(s);
        }
        catch (std::exception ex)
        {
            return { };
        }
    }

    bool Version::TryParse(string s, Version& out)
    {
        try
        {
            out = Parse(s);
            return true;
        }
        catch (std::exception ex)
        {
            return false;
        }
    }
}