// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include "./namespace.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup CAPI C API
 * @{
 */

/// Error code indicating an OK result from a C API function.
const int OPENASSETIO_NS(kOK) = 0;
const int OPENASSETIO_NS(kUnknown) = 1;
const int OPENASSETIO_NS(kTypeMismatch) = 2;
const int OPENASSETIO_NS(kOutOfRange) = 3;
const int OPENASSETIO_NS(kLength) = 4;
const int OPENASSETIO_NS(kInternal) = 5;

// TODO some sort of constant for minimum size of error output strings?

/**
 * @}
 */
#ifdef __cplusplus
}
#endif
