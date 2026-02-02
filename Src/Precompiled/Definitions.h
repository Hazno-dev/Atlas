// Hazno - 2026

// ReSharper disable CppInconsistentNaming
#pragma once

#if defined(ATLAS_PLATFORM_MSVC)
#define ATLAS_FORCE_INLINE __forceinline
#elif defined(ATLAS_PLATFORM_CLANG) || defined(ATLAS_PLATFORM_GNU)
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define ATLAS_FORCE_INLINE inline __attribute__((always_inline))
#else
#define ATLAS_FORCE_INLINE inline
#endif

#define ATLAS_NODISCARD [[nodiscard]]
