// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <openassetio/c/ns.h>

#include <managerAPI/CManagerInterface.hpp>

struct MockCAPI {
  MAKE_MOCK1(dtor, void(OPENASSETIO_NS(managerAPI_ManagerInterface_h)));

  MAKE_MOCK3(identifier, int(OPENASSETIO_NS(SimpleString) *, OPENASSETIO_NS(SimpleString) *,
                             OPENASSETIO_NS(managerAPI_ManagerInterface_h)));

  MAKE_MOCK3(displayName, int(OPENASSETIO_NS(SimpleString) *, OPENASSETIO_NS(SimpleString) *,
                              OPENASSETIO_NS(managerAPI_ManagerInterface_h)));
};

SCENARIO("CManagerInterface") {
  GIVEN("An opaque handle and function suite") {
    MockCAPI capi;

    auto *handle = reinterpret_cast<OPENASSETIO_NS(managerAPI_ManagerInterface_h)>(&capi);

    OPENASSETIO_NS(managerAPI_ManagerInterface_s)
    suite{// dtor
          [](OPENASSETIO_NS(managerAPI_ManagerInterface_h) h) {
            auto *api = reinterpret_cast<MockCAPI *>(h);
            api->dtor(h);
          },
          // identifier
          [](OPENASSETIO_NS(SimpleString) * err, OPENASSETIO_NS(SimpleString) * out,
             OPENASSETIO_NS(managerAPI_ManagerInterface_h) h) {
            auto *api = reinterpret_cast<MockCAPI *>(h);
            return api->identifier(err, out, h);
          },
          // displayName
          [](OPENASSETIO_NS(SimpleString) * err, OPENASSETIO_NS(SimpleString) * out,
             OPENASSETIO_NS(managerAPI_ManagerInterface_h) h) {
            auto *api = reinterpret_cast<MockCAPI *>(h);
            return api->displayName(err, out, h);
          }};

    THEN("CManagerInterface's destructor calls the suite's dtor") {
      REQUIRE_CALL(capi, dtor(handle));

      openassetio::managerAPI::CManagerInterface cManagerInterface{handle, suite};
    }
  }
}
