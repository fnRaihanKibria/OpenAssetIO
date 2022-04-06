// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include <unordered_map>
#include <variant>

#include <openassetio/export.h>
#include <openassetio/typedefs.hpp>

namespace openassetio {
inline namespace OPENASSETIO_VERSION {
/// Types available as values in a SimpleMap.
using SimpleMapValue = std::variant<Bool, Int, Float, Str>;
/**
 * SimpleMap type used for \fqref{managerAPI::ManagerInterface::info}
 * "ManagerInterface::info".
 */
using SimpleMap = std::unordered_map<Str, SimpleMapValue>;
}  // namespace OPENASSETIO_VERSION
}  // namespace openassetio
