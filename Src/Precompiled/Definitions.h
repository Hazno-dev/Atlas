// Hazno - 2026

#pragma once

#if defined(ATLAS_PLATFORM_MSVC)
  #define ATLAS_FORCEINLINE __forceinline
#elif defined(ATLAS_PLATFORM_CLANG) || defined(ATLAS_PLATFORM_GNU)
  #define ATLAS_FORCEINLINE inline __attribute__((always_inline))
#else
  #define ATLAS_FORCEINLINE inline
#endif