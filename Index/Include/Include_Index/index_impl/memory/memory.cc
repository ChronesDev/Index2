#pragma once

#include "../include/include.cc"
#include "../core/include.cc"
#include <utility>

#include "../std/include.cc"

namespace Index
{
    class Memory final
    {
    private:
        explicit Memory(IntPtr minecraftBase) {
            MinecraftBase = minecraftBase;
        }
    public:
        Memory() = delete;
    public:
        IntPtr MinecraftBase;
    public:
        template<class T> constexpr T& Read(void* at)
        {
            return *(T*)(at);
        }
        template<class T> constexpr T& Read(IntPtr at)
        {
            return *(T*)(at);
        }
        template<class T> constexpr T& ReadOr(void* at, T _or)
        {
            return at != nullptr ? *(T*)(at) : _or;
        }
        template<class T> constexpr T& ReadOr(IntPtr at, T _or)
        {
            return at != 0 ? *(T*)(at) : _or;
        }
        template<class T> constexpr T& ReadStatic(IntPtr offset)
        {
            return Read<T>(MinecraftBase += offset);
        }
        template<class T> constexpr T& TryReadOr(void* at, T _or)
        {
            try
            {
                return *(T*)(at);
            }
            catch (...)
            {
                return _or;
            }
        }
        template<class T> constexpr T& TryReadOr(IntPtr at, T _or)
        {
            try
            {
                return *(T*)(at);
            }
            catch (...)
            {
                return _or;
            }
        }
        template<class T> constexpr T& TryReadStaticOr(IntPtr offset, T _or)
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
        template<class T> constexpr void Write(void* at, T value) {
            *(T*)(at) = value;
        }
        template<class T> constexpr void Write(IntPtr at, T value) {
            *(T*)(at) = value;
        }
        template<class T> constexpr void WriteProtected(void* at, T value) {
            uint oldProtection;
            VirtualProtect(at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(at) = value;
            VirtualProtect(at, sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }
        template<class T> constexpr void WriteProtected(IntPtr at, T value) {
            uint oldProtection;
            VirtualProtect((void*)at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(at) = value;
            VirtualProtect((void*)at, sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }
        template<class T> constexpr void WriteStatic(IntPtr at, T value) {
            *(T*)(MinecraftBase + at) = value;
        }
        template<class T> constexpr void WriteStaticProtected(IntPtr offset, T value) {
            uint oldProtection;
            VirtualProtect((void*)(MinecraftBase + offset), sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            *(T*)(MinecraftBase + offset) = value;
            VirtualProtect((void*)(MinecraftBase + offset), sizeof(T), oldProtection, (PDWORD)&oldProtection);
        }
    public:
        void PatchBytes(void* at, List<byte> bytes) {
            uint oldProtection;
            VirtualProtect(at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes.First, bytes.Length);
            VirtualProtect(at, bytes.Length, oldProtection, (PDWORD)&oldProtection);
        }
        void PatchBytes(IntPtr at, List<byte> bytes) {
            uint oldProtection;
            VirtualProtect((void*)at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes.First, bytes.Length);
            VirtualProtect((void*)at, bytes.Length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(void* at, byte* source, size_t length) {
            uint oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, source, length);
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(IntPtr at, byte* source, size_t length) {
            uint oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, source, length);
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void Patch(void* at, byte(&bytes)[TSize]) {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void Patch(IntPtr at, byte(&bytes)[TSize]) {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void Patch(void* at, byte(&&bytes)[TSize]) {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &bytes, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void Patch(IntPtr at, byte(&&bytes)[TSize]) {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &bytes, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void PatchChars(void* at, const char(&chars)[TSize]) {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &chars, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void PatchChars(IntPtr at, const char(&chars)[TSize]) {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &chars, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void PatchChars(void* at, const char(&&chars)[TSize]) {
            uint oldProtection;
            VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, &chars, TSize);
            VirtualProtect(at, TSize, oldProtection, (PDWORD)&oldProtection);
        }
        template<size_t TSize> void PatchChars(IntPtr at, const char(&&chars)[TSize]) {
            uint oldProtection;
            VirtualProtect((void*)at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, &chars, TSize);
            VirtualProtect((void*)at, TSize, oldProtection, (PDWORD)&oldProtection);
        }

        void Patch(void* at, const char* source, size_t length) {
            uint oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy(at, source, length);
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection);
        }
        void Patch(IntPtr at, const char* source, size_t length) {
            uint oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            memcpy((void*)at, source, length);
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection);
        }
    public:
        uint Unprotect(void* at, size_t length) {
            DWORD oldProtection;
            VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            return oldProtection;
        }
        uint Unprotect(IntPtr at, size_t length) {
            DWORD oldProtection;
            VirtualProtect((void*)at, length, PAGE_EXECUTE_READWRITE, (PDWORD)&oldProtection);
            return oldProtection;
        }
        void Reprotect(void* at, size_t length, uint oldProtection) {
            DWORD oldProtection2;
            VirtualProtect(at, length, oldProtection, (PDWORD)&oldProtection2);
        }
        void Reprotect(IntPtr at, size_t length, uint oldProtection) {
            DWORD oldProtection2;
            VirtualProtect((void*)at, length, oldProtection, (PDWORD)&oldProtection2);
        }
    public:
        /*
        Nullable<IntPtr> FindSignature(string moduleName, string signature)
        {
            char pattern[100];
            char mask[100];
            Parse(signature, pattern, mask);
            IntPtr result = (IntPtr)ScanModIn(pattern, mask, std::move(moduleName));
            return result == 0 ? Null : Nullable<IntPtr>(result);
        }
        Nullable<IntPtr> FindSignatureWithPattern(string moduleName, string pattern, string mask)
        {
            if (pattern == "" || mask == "") return Null;
            IntPtr result = (IntPtr)ScanModIn(pattern, mask, std::move(moduleName));
            return result == 0 ? Null : Nullable<IntPtr>(result);
        }
    private:
        char* ScanBasic(const char* pattern, const char* mask, char* begin, intptr_t size)
        {
            intptr_t patternLen = strlen(mask);

            for (int i = 0; i < size; i++)
            {
                bool found = true;
                for (int j = 0; j < patternLen; j++)
                {
                    if (mask[j] != '?' && pattern[j] != *(char*)((intptr_t)begin + i + j))
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return (begin + i);
                }
            }
            return nullptr;
        }
        char* ScanInternal(const char* pattern, const char* mask, char* begin, intptr_t size)
        {
            char* match{ nullptr };
            MEMORY_BASIC_INFORMATION mbi{};

            for (char* curr = begin; curr < begin + size; curr += mbi.RegionSize)
            {
                if (!VirtualQuery(curr, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || mbi.Protect == PAGE_NOACCESS) continue;

                match = ScanBasic(pattern, mask, curr, mbi.RegionSize);

                if (match != nullptr)
                {
                    break;
                }
            }
            return match;
        }
        char* TO_CHAR(wchar_t* string)
        {
            size_t len = wcslen(string) + 1;
            char* c_string = new char[len];
            size_t numCharsRead;
            wcstombs_s(&numCharsRead, c_string, len, string, _TRUNCATE);
            return c_string;
        }
        PEB* GetPEB()
        {
#ifdef _WIN64
            PEB* peb = (PEB*)__readgsqword(0x60);
#else
            PEB* peb = (PEB*)__readfsdword(0x30);
#endif
            return peb;
        }
        LDR_DATA_TABLE_ENTRY* GetLDREntry(const string& name)
        {
            LDR_DATA_TABLE_ENTRY* ldr = nullptr;

            PEB* peb = GetPEB();

            LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

            LIST_ENTRY curr = head;

            while (curr.Flink != head.Blink)
            {
                LDR_DATA_TABLE_ENTRY* mod = (LDR_DATA_TABLE_ENTRY*)CONTAINING_RECORD(curr.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

                if (mod->FullDllName.Buffer)
                {
                    char* cName = TO_CHAR(mod->BaseDllName.Buffer);

                    if (_stricmp(cName, name.c_str()) == 0)
                    {
                        ldr = mod;
                        break;
                    }
                    delete[] cName;
                }
                curr = *curr.Flink;
            }
            return ldr;
        }
        char* ScanModIn(const char* pattern, const char* mask, string modName)
        {
            LDR_DATA_TABLE_ENTRY* ldr = GetLDREntry(modName);

            char* match = ScanInternal(pattern, mask, (char*)ldr->DllBase, ldr->SizeOfImage);

            return match;
        }
        void Parse(const char* combo, char* pattern, char* mask)
        {
            char lastChar = ' ';
            unsigned int j = 0;

            for (unsigned int i = 0; i < strlen(combo); i++)
            {
                if ((combo[i] == '?' || combo[i] == '*') && (lastChar != '?' && lastChar != '*'))
                {
                    pattern[j] = mask[j] = '?';
                    j++;
                }

                else if (isspace(lastChar))
                {
                    pattern[j] = lastChar = (char)strtol(&combo[i], 0, 16);
                    mask[j] = 'x';
                    j++;
                }
                lastChar = combo[i];
            }
            pattern[j] = mask[j] = '\0';
        }

        */
    public:
        static Memory New()
        {
            auto baseAddress = (IntPtr)GetModuleHandleW(nullptr);
            auto mem = Memory(baseAddress);
            return mem;
        }
    };

    inline Memory Mem = Memory::New();
}