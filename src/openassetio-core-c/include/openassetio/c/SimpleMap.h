// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include <cstddef>
#include <stdint.h>

#include <openassetio/c/export.h>

#include "./namespace.h"
#include "./SimpleString.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup CAPI C API
 * @{
 */

enum OPENASSETIO_NS(SimpleMapValueType) { OPENASSETIO_NS(SimpleMapValueType_Invalid),
    OPENASSETIO_NS(SimpleMapValueType_Bool),
    OPENASSETIO_NS(SimpleMapValueType_Int),
    OPENASSETIO_NS(SimpleMapValueType_Float),
    OPENASSETIO_NS(SimpleMapValueType_Str)
    };

// TODO the types here should be common to C++
typedef union {
    OPENASSETIO_NS(SimpleString) asStr; // has to go first so it can be initialized
    bool asBool;
    int64_t asInt;
    double asFloat;
} OPENASSETIO_NS(SimpleMapValueData);

typedef struct {
    OPENASSETIO_NS(SimpleMapValueType) type;
    OPENASSETIO_NS(SimpleMapValueData) data;
} OPENASSETIO_NS(SimpleMapValue);

typedef struct OPENASSETIO_NS(SimpleMap_t) *
    OPENASSETIO_NS(SimpleMap_h);

// NOLINTNEXTLINE(modernize-use-using)
typedef struct {
    // TODO destructor that should be called when done with the map
    void (*dtor)(OPENASSETIO_NS(SimpleMap_h) handle);

    // TODO caller must initialize value with expected type
    // also for string a buffer must be allocated
    int (*get)(OPENASSETIO_NS(SimpleString) * error, OPENASSETIO_NS(SimpleMapValue)* value, 
        OPENASSETIO_NS(SimpleMap_h) handle, const OPENASSETIO_NS(SimpleString) key);

} OPENASSETIO_NS(SimpleMap_s);

OPENASSETIO_CORE_C_EXPORT OPENASSETIO_NS(SimpleMap_s) OPENASSETIO_NS(SimpleMap_suite)();

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
