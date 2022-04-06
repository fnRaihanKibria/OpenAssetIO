// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include <string>

#include <openassetio/export.h>

namespace openassetio {
inline namespace OPENASSETIO_VERSION {
/// Boolean value type for dictionaries.
using Bool = bool;
/// Integer value type for dictionaries.
using Int = int64_t;
/// Real value type for dictionaries.
using Float = double;
/// String type used throughout OpenAssetIO.
using Str = std::string;
}  // namespace OPENASSETIO_VERSION
}  // namespace openassetio
