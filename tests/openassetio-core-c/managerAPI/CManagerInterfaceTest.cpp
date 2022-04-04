// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <openassetio/c/errors.h>
#include <openassetio/c/ns.h>

#include <managerAPI/CManagerInterface.hpp>

struct MockCAPI {
  MAKE_MOCK1(dtor, void(OPENASSETIO_NS(managerAPI_ManagerInterface_h)));

  MAKE_MOCK3(identifier, int(OPENASSETIO_NS(SimpleString) *, OPENASSETIO_NS(SimpleString) *,
                             OPENASSETIO_NS(managerAPI_ManagerInterface_h)));

  MAKE_MOCK3(displayName, int(OPENASSETIO_NS(SimpleString) *, OPENASSETIO_NS(SimpleString) *,
                              OPENASSETIO_NS(managerAPI_ManagerInterface_h)));
};

OPENASSETIO_NS(managerAPI_ManagerInterface_s) getSuite() {
  return {// dtor
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
}

SCENARIO("CManagerInterface destructor") {
  GIVEN("An opaque handle and function suite") {
    MockCAPI capi;

    auto *handle = reinterpret_cast<OPENASSETIO_NS(managerAPI_ManagerInterface_h)>(&capi);
    auto const suite = getSuite();

    THEN("CManagerInterface's destructor calls the suite's dtor") {
      REQUIRE_CALL(capi, dtor(handle));

      openassetio::managerAPI::CManagerInterface cManagerInterface{handle, suite};
    }
  }
}

SCENARIO("CManagerInterface::identifier") {
  GIVEN("A CManagerInterface wrapping an opaque handle and function suite") {
    MockCAPI capi;

    auto *handle = reinterpret_cast<OPENASSETIO_NS(managerAPI_ManagerInterface_h)>(&capi);
    auto const suite = getSuite();

    // Expect the destructor to be called, i.e. when cManagerInterface
    // goes out of scope.
    // TODO(DF): Mysteriously, this must come _before_ the construction
    //  of cManagerInterface...
    REQUIRE_CALL(capi, dtor(handle));

    openassetio::managerAPI::CManagerInterface cManagerInterface{handle, suite};

    AND_GIVEN("the C suite's identifier() call succeeds") {
      const std::string_view expectedIdentifier = "my.id";

      using trompeloeil::_;

      // Check that `identifier` is called properly and update out-parameter.
      REQUIRE_CALL(capi, identifier(_, _, handle))
          // Ensure max size is reasonable.
          .LR_WITH(_2->maxSize >= 500)
          // Update SimpleString out-parameter.
          .LR_SIDE_EFFECT(
              strncpy(_2->buffer, expectedIdentifier.data(), expectedIdentifier.size()))
          .LR_SIDE_EFFECT(_2->usedSize = expectedIdentifier.size())
          // Return OK code.
          .RETURN(OPENASSETIO_NS(kOK));

      WHEN("The manager's identifier is queried") {
        const openassetio::Str actualIdentifier = cManagerInterface.identifier();

        THEN("Returned identifier matches expected identifier") {
          CHECK(actualIdentifier == expectedIdentifier);
        }
      }
    }
  }
}
