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
		explicit Memory(IntPtr minecraftBase)
		{
			Base = minecraftBase;
		}

	public:
		Memory() = delete;

	public:
		IntPtr Base;
	public:
		template<class T>
		constexpr T &Read(void *at)
		{
			return *(T *) (at);
		}

		template<class T>
		constexpr T &Read(IntPtr at)
		{
			return *(T *) (at);
		}

		template<class T>
		constexpr T &ReadOr(void *at, T _or)
		{
			return at != nullptr ? *(T *) (at) : _or;
		}

		template<class T>
		constexpr T &ReadOr(IntPtr at, T _or)
		{
			return at != 0 ? *(T *) (at) : _or;
		}

		template<class T>
		constexpr T &ReadStatic(IntPtr offset)
		{
			return Read<T>(Base += offset);
		}

		template<class T>
		constexpr T &TryReadOr(void *at, T _or)
		{
			try
			{
				return *(T *) (at);
			}
			catch (...)
			{
				return _or;
			}
		}

		template<class T>
		constexpr T &TryReadOr(IntPtr at, T _or)
		{
			try
			{
				return *(T *) (at);
			}
			catch (...)
			{
				return _or;
			}
		}

		template<class T>
		constexpr T &TryReadStaticOr(IntPtr offset, T _or)
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
		template<class T>
		constexpr void Write(void *at, T value)
		{
			*(T *) (at) = value;
		}

		template<class T>
		constexpr void Write(IntPtr at, T value)
		{
			*(T *) (at) = value;
		}

#ifndef INDEX_NO_WINDOWS_H

		template<class T>
		constexpr void WriteProtected(void *at, T value)
		{
			uint oldProtection;
			VirtualProtect(at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			*(T *) (at) = value;
			VirtualProtect(at, sizeof(T), oldProtection, (PDWORD) &oldProtection);
		}

		template<class T>
		constexpr void WriteProtected(IntPtr at, T value)
		{
			uint oldProtection;
			VirtualProtect((void *) at, sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			*(T *) (at) = value;
			VirtualProtect((void *) at, sizeof(T), oldProtection, (PDWORD) &oldProtection);
		}

#endif

		template<class T>
		constexpr void WriteStatic(IntPtr at, T value)
		{
			*(T *) (Base + at) = value;
		}

#ifndef INDEX_NO_WINDOWS_H

		template<class T>
		constexpr void WriteStaticProtected(IntPtr offset, T value)
		{
			uint oldProtection;
			VirtualProtect((void *) (Base + offset), sizeof(T), PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection
			);
			*(T *) (Base + offset) = value;
			VirtualProtect((void *) (Base + offset), sizeof(T), oldProtection, (PDWORD) &oldProtection);
		}

#endif
	public:
#ifndef INDEX_NO_WINDOWS_H

		void PatchBytes(void *at, List<byte> bytes)
		{
			uint oldProtection;
			VirtualProtect(at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, &bytes.First, bytes.Length);
			VirtualProtect(at, bytes.Length, oldProtection, (PDWORD) &oldProtection);
		}

		void PatchBytes(IntPtr at, List<byte> bytes)
		{
			uint oldProtection;
			VirtualProtect((void *) at, bytes.Length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, &bytes.First, bytes.Length);
			VirtualProtect((void *) at, bytes.Length, oldProtection, (PDWORD) &oldProtection);
		}

		void Patch(void *at, byte *source, size_t length)
		{
			uint oldProtection;
			VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, source, length);
			VirtualProtect(at, length, oldProtection, (PDWORD) &oldProtection);
		}

		void Patch(IntPtr at, byte *source, size_t length)
		{
			uint oldProtection;
			VirtualProtect((void *) at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, source, length);
			VirtualProtect((void *) at, length, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void Patch(void *at, byte(&bytes)[TSize])
		{
			uint oldProtection;
			VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, &bytes, TSize);
			VirtualProtect(at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void Patch(IntPtr at, byte(&bytes)[TSize])
		{
			uint oldProtection;
			VirtualProtect((void *) at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, &bytes, TSize);
			VirtualProtect((void *) at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void Patch(void *at, byte(&&bytes)[TSize])
		{
			uint oldProtection;
			VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, &bytes, TSize);
			VirtualProtect(at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void Patch(IntPtr at, byte(&&bytes)[TSize])
		{
			uint oldProtection;
			VirtualProtect((void *) at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, &bytes, TSize);
			VirtualProtect((void *) at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void PatchChars(void *at, const char(&chars)[TSize])
		{
			uint oldProtection;
			VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, &chars, TSize);
			VirtualProtect(at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void PatchChars(IntPtr at, const char(&chars)[TSize])
		{
			uint oldProtection;
			VirtualProtect((void *) at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, &chars, TSize);
			VirtualProtect((void *) at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void PatchChars(void *at, const char(&&chars)[TSize])
		{
			uint oldProtection;
			VirtualProtect(at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, &chars, TSize);
			VirtualProtect(at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		template<size_t TSize>
		void PatchChars(IntPtr at, const char(&&chars)[TSize])
		{
			uint oldProtection;
			VirtualProtect((void *) at, TSize, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, &chars, TSize);
			VirtualProtect((void *) at, TSize, oldProtection, (PDWORD) &oldProtection);
		}

		void Patch(void *at, const char *source, size_t length)
		{
			uint oldProtection;
			VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy(at, source, length);
			VirtualProtect(at, length, oldProtection, (PDWORD) &oldProtection);
		}

		void Patch(IntPtr at, const char *source, size_t length)
		{
			uint oldProtection;
			VirtualProtect((void *) at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			memcpy((void *) at, source, length);
			VirtualProtect((void *) at, length, oldProtection, (PDWORD) &oldProtection);
		}

	public:
		uint Unprotect(void *at, size_t length)
		{
			DWORD oldProtection;
			VirtualProtect(at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			return oldProtection;
		}

		uint Unprotect(IntPtr at, size_t length)
		{
			DWORD oldProtection;
			VirtualProtect((void *) at, length, PAGE_EXECUTE_READWRITE, (PDWORD) &oldProtection);
			return oldProtection;
		}

		void Reprotect(void *at, size_t length, uint oldProtection)
		{
			DWORD oldProtection2;
			VirtualProtect(at, length, oldProtection, (PDWORD) &oldProtection2);
		}

		void Reprotect(IntPtr at, size_t length, uint oldProtection)
		{
			DWORD oldProtection2;
			VirtualProtect((void *) at, length, oldProtection, (PDWORD) &oldProtection2);
		}

#endif

	public:
		static Memory New()
		{
#ifndef INDEX_NO_WINDOWS_H
			auto baseAddress = (IntPtr) GetModuleHandleW(nullptr);
			auto mem = Memory(baseAddress);
			return mem;
#endif
		}

		static Memory New(IntPtr baseAddress)
		{
			return Memory(baseAddress);
		}

		static Memory New(void *baseAddress)
		{
			return Memory((IntPtr) baseAddress);
		}
	};

	inline Memory Mem = Memory::New();
}