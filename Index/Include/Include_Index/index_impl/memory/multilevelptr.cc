#pragma once

#include "../std/include.cc"

namespace Index
{
    struct MultiLevelPtrPath
    {
        MultiLevelPtrPath() = default;
        MultiLevelPtrPath(string base)
            : Base(base) {};
        MultiLevelPtrPath(string base, Int64 baseOffset, List<Int64> offsets = {})
            : Base(base)
            , BaseOffset(baseOffset)
            , Offsets(offsets) {};
        MultiLevelPtrPath(Int64 baseOffset, List<Int64> offsets = {})
            : BaseOffset(baseOffset)
            , Offsets(offsets) {};

        string Base = "";
        Int64 BaseOffset;
        List<Int64> Offsets;
    };
}