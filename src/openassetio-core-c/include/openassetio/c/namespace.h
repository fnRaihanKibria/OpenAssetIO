// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include <openassetio/export.h>  // For OPENASSETIO_VERSION

/**
 * @addtogroup CAPI C API
 * @{
 */

/**
 * Prefix `openassetio_vX_Y_` to a given symbol name, where `X_Y` is
 * the current API version.
 *
 * @hideinitializer
 */
#define OPENASSETIO_NS(symbol) OPENASSETIO_NS_WITH_VER(OPENASSETIO_VERSION, symbol)

/**
 * @}
 */

// Utility to work around token pasting macro expansion rules.
#define OPENASSETIO_NS_WITH_VER(ver, symbol) OPENASSETIO_NS_WITH_VER_IMPL(ver, symbol)
// Utility to work around token pasting macro expansion rules.
#define OPENASSETIO_NS_WITH_VER_IMPL(ver, symbol) openassetio_##ver##_##symbol