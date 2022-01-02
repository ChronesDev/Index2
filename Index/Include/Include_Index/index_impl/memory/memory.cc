#pragma once

#include "../core/include.cc"
#include "../include/include.cc"
#include <utility>

#include "../std/include.cc"
#include "multilevelptr.cc"

#define INDEX_MEM_IsInRange(x, a, b) (x >= a && x <= b)
#define INDEX_MEM_GetBits(x)                                                                                          \
    (INDEX_MEM_IsInRange((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa)                                       \
                                                  : (INDEX_MEM_IsInRange(x, '0', '9') ? x - '0' : 0))
#define INDEX_MEM_GetByte(x) (INDEX_MEM_GetBits(x[0]) << 4 | INDEX_MEM_GetBits(x[1]))

namespace Index
{
    class Memory final
    {
    private:
        explicit Memory(IntPtr minecraftBase) { Base = minecraftBase; }

    public:
        Memory() = delete;

    public:
        IntPtr Base;

    public:
        IntPtr At(int offset) { return Base + offset; }
        IntPtr At(Int64 offset) { return Base + offset; }
        IntPtr At(UInt64 offset) { return Base + offset; }
        void* AtPtr(int offset) { return (void*)(Base + offset); }
        void* AtPtr(Int64 offset) { return (void*)(Base + offset); }
        void* AtPtr(UInt64 offset) { return (void*)(Base + offset); }

    public:
        template <class T> constexpr T& Read(void* at) { return *(T*)(void*)(at); }
        template <class T> constexpr T& Read(IntPtr at) { return *(T*)(void*)(at); }
        template <class T> constexpr T& ReadOr(void* at, T _or) { return at != nullptr ? *(T*)(void*)(at) : _or; }
        template <class T> constexpr T& ReadOr(IntPtr at, T _or) { return at != 0 ? *(T*)(void*)(at) : _or; }
        template <class T> constexpr T& ReadStatic(IntPtr offset) { return Read<T>(Base += offset); }
        template <class T> constexpr T& TryReadOr(void* at, T _or)
        {
            try
            {
                return *(T*)(void*)(at);
            }
            catch (...)
            {
                return _or;
            }
        }
        template <class T> constexpr T& TryReadOr(IntPtr at, T _or)
        {
            try
            {
                return *(T*)(void*)(at);
            }
            catch (...)
            {
                return _or;
            }
        }
        template <class T> constexpr T& TryReadStaticOr(IntPtr offset, T _or)
        {
            try
            {
                return ReadStatic<T>(offset);
            }
            catch (...)
            {
                return _or;
            }
        }

    public:
        template <class T> constexpr void Write(void* at, T value) { *(T*)(void*)(at) = value; }
        template <class T> constexpr void Write(IntPtr at, T value) { *(T*)(void*)(at) = value; }

#ifndef INDEX_NO_WINDOWS_H

        template <class T> constexpr void WriteProtected(void* at, T value)
        {
            uint oldProtection;
            VirtualProtect(at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(void*)(at) = value;
            VirtualProtect(at, sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }
        template <class T> constexpr void WriteProtected(IntPtr at, T value)
        {
            uint oldProtection;
            VirtualProtect((void*)at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(void*)(at) = value;
            VirtualProtect((void*)at, sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }

#endif

        template <class T> constexpr void WriteStatic(IntPtr at, T value) { *(T*)(void*)(Base + at) = value; }

#ifndef INDEX_NO_WINDOWS_H

        template <class T> constexpr void WriteStaticProtected(IntPtr offset, T value)
        {
            uint oldProtection;
            VirtualProtect((void*)(Base + offset), sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(void*)(Base + offset) = value;
            VirtualProtect((void*)(Base + offset), sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }

#endif
    public:
#ifndef INDEX_NO_WINDOWS_H

        void PatchBytes(void* at, List<byte> bytes)
        {
            uint oldProtection;
            VirtualProtect(at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes.First, bytes.Length);
            VirtualProtect(at, bytes.Length, oldProtection, (PDWORD)&oldProtection);
        }
        void PatchBytes(IntPtr at, List<byte> bytes)
        {
            uint oldProtection;
            VirtualProtect((void*)at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes.First, bytes.Length);
            VirtualProtect((void*)at, bytes.Length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(void* at, byte* source, size_t length)
        {
            uint oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, source, length);
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(IntPtr at, byte* source, size_t length)
        {
            uint oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, source, length);
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void Patch(void* at, byte (&bytes)[TSize])
        {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void Patch(IntPtr at, byte (&bytes)[TSize])
        {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void Patch(void* at, byte(&&bytes)[TSize])
        {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void Patch(IntPtr at, byte(&&bytes)[TSize])
        {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void PatchChars(void* at, const char (&chars)[TSize])
        {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &chars, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void PatchChars(IntPtr at, const char (&chars)[TSize])
        {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &chars, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void PatchChars(void* at, const char(&&chars)[TSize])
        {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &chars, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template <size_t TSize> void PatchChars(IntPtr at, const char(&&chars)[TSize])
        {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &chars, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(void* at, const char* source, size_t length)
        {
            uint oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, source, length);
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(IntPtr at, const char* source, size_t length)
        {
            uint oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, source, length);
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection);
        }

    public:
        uint Unprotect(void* at, size_t length)
        {
            DWORD oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            return oldProtection;
        }
        uint Unprotect(IntPtr at, size_t length)
        {
            DWORD oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            return oldProtection;
        }

        void Reprotect(void* at, size_t length, uint oldProtection)
        {
            DWORD oldProtection2;
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection2);
        }
        void Reprotect(IntPtr at, size_t length, uint oldProtection)
        {
            DWORD oldProtection2;
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection2);
        }

        IntPtr FindSignature(IntPtr start, IntPtr end, string pattern)
        {
            const char* pat = pattern.CStr;
            IntPtr firstMatch = 0;
            for (IntPtr pCur = start; pCur < end; pCur++)
            {
                if (!*pat) return firstMatch;
                if (*(char*)pat == '\?' || *(byte*)pCur == INDEX_MEM_GetByte(pat))
                {
                    if (!firstMatch) firstMatch = pCur;
                    if (!pat[2]) { return firstMatch; };
                    if (*(PWORD)pat == *(PWORD) "\?\?" || *(PBYTE)pat != '\?') { pat += 3; }
                    else
                    {
                        pat += 2;
                    }
                }
                else
                {
                    pat = (const char*)pattern;
                    firstMatch = 0;
                }
            }
            return 0;
        }
        IntPtr FindSignature(string pattern)
        {
            if (Base == 0) throw std::exception("Invalid Base.");
            MODULEINFO moduleinfo;
            K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &moduleinfo, sizeof(moduleinfo));
            auto result = FindSignature(Base, Base + moduleinfo.SizeOfImage, std::forward<string>(pattern));
            if (result == 0) throw std::exception("Could not find the Sig.");
            return result;
        }
        IntPtr TryFindSignature(string pattern)
        {
            if (Base == 0) throw std::exception("Invalid Base.");
            MODULEINFO moduleinfo;
            K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &moduleinfo, sizeof(moduleinfo));
            return FindSignature(Base, Base + moduleinfo.SizeOfImage, std::forward<string>(pattern));
        }
        void* FindSignaturePtr(string pattern) { return (void*)FindSignature(pattern); }
        void* TryFindSignaturePtr(string pattern) { return (void*)TryFindSignature(pattern); }

#endif

    public:
        static IntPtr FindMultiLevelPtr(IntPtr base, MultiLevelPtrPath mlptr)
        {
            IntPtr a = base + mlptr.BaseOffset;

            for (int i = 0; i < mlptr.Offsets.Length; i++)
            {
                a = *(IntPtr*)(a);
                if ((IntPtr*)(a) == nullptr) return a;
                a += mlptr.Offsets[i];
            }

            return a;
        }

        IntPtr FindMultiLevelPtr(MultiLevelPtrPath mlptr)
        {
            if (mlptr.Base == "")
                return FindMultiLevelPtr(this->Base, mlptr);
            else
                INDEX_THROW("Not implemented");
        }

    public:
        static Memory New()
        {
#ifndef INDEX_NO_WINDOWS_H
            auto baseAddress = (IntPtr)GetModuleHandleW(nullptr);
            auto mem = Memory(baseAddress);
            return mem;
#elifdef INDEX_LINUX
            INDEX_THROW_NOT_IMPLEMENTED();
#else
            INDEX_THROW_NOT_IMPLEMENTED();
#endif
        }
        static Memory New(IntPtr baseAddress) { return Memory(baseAddress); }
        static Memory New(void* baseAddress) { return Memory((IntPtr)baseAddress); }
    };

#ifndef INDEX_NO_MEMORY
    inline Memory Mem = Memory::New();
#endif
}