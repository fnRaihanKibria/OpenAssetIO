// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#pragma once

#include <openassetio/export.h>
#include <openassetio/c/export.h>

#include <openassetio/c/managerAPI/ManagerInterface.h>
#include <openassetio/managerAPI/ManagerInterface.hpp>

namespace openassetio {
inline namespace OPENASSETIO_VERSION {
namespace managerAPI {

class OPENASSETIO_CORE_C_EXPORT CManagerInterface : ManagerInterface {
 public:
  CManagerInterface(OPENASSETIO_NS(managerAPI_ManagerInterface_h) handle,
                    OPENASSETIO_NS(managerAPI_ManagerInterface_s) suite);

  ~CManagerInterface() override;

  [[nodiscard]] Str identifier() const override;
  [[nodiscard]] Str displayName() const override;

 private:
  OPENASSETIO_NS(managerAPI_ManagerInterface_h) handle_;
  OPENASSETIO_NS(managerAPI_ManagerInterface_s) suite_;
};

}  // namespace managerAPI
}  // namespace OPENASSETIO_VERSION
}  // namespace openassetio
