// Hazno - 2026

#pragma once

#define DTL_ATLAS_MERGE(a, b) a ## b
#define DTL_ATLAS_MERGE_WRAP(a, b) DTL_ATLAS_MERGE(a, b)

#define ATLAS_PADDING(size) uint8 DTL_ATLAS_MERGE_WRAP(pad, __COUNTER__)[size]

#define ATLAS_STUB_R(ret, ...) ret DTL_ATLAS_MERGE_WRAP(funcStub, __COUNTER__)(__VA_ARGS__) = 0
#define ATLAS_STUB(...) ATLAS_STUB_R(virtual int64, __VA_ARGS__)

#define ATLAS_VALIDATE_SIZE(type, size) static_assert(sizeof(type) == size, "Invalid size for " #type)