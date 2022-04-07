// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd
#include <catch2/catch.hpp>

#include <openassetio/c/SimpleString.h>
#include <openassetio/c/SimpleMap.h>
#include <openassetio/c/errors.h>
#include <openassetio/c/namespace.h>
#include <openassetio/SimpleMap.hpp>
// private headers
#include <errors.hpp>

SCENARIO("SimpleMap passed to C") {
  GIVEN("a C++ SimpleMap") {
    auto sm = new openassetio::SimpleMap();

    const char boolKey[] = "aBool";
    const auto expectedBoolValue = true;
    sm->insert({{ boolKey, expectedBoolValue}});

    const char intKey[] = "anInt";
    const auto expectedIntValue = 123l;
    sm->insert({{ intKey, expectedIntValue}});

    const char floatKey[] = "aFloat";
    const auto expectedFloatValue = 0.456;
    sm->insert({{ floatKey, expectedFloatValue}});

    const char strKey[] = "aStr";
    const auto expectedStrValue = "string value";
    sm->insert({{ strKey, openassetio::Str(expectedStrValue)}});

    WHEN("accessed with a function suite") {
      const auto suite = OPENASSETIO_NS(SimpleMap_suite)();
      char errBuffer[500];
      OPENASSETIO_NS(SimpleString) err{sizeof(errBuffer), errBuffer, 0};

      AND_WHEN("accessing a valid Bool value") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Bool)};
        OPENASSETIO_NS(SimpleString) key{sizeof(boolKey), const_cast<char*>(boolKey), sizeof(boolKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), key);
        THEN("the value is retrieved successfully") {
          REQUIRE(errorCode == OPENASSETIO_NS(kOK));
          AND_THEN("the value is retrieved correctly") {
            REQUIRE(value.data.asBool == expectedBoolValue);
          }
        }
      }

      AND_WHEN("accessing a valid Int value") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Int)};
        OPENASSETIO_NS(SimpleString) key{sizeof(intKey), const_cast<char*>(intKey), sizeof(intKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), key);
        THEN("the value is retrieved successfully") {
          REQUIRE(errorCode == OPENASSETIO_NS(kOK));
          AND_THEN("the value is retrieved correctly") {
            REQUIRE(value.data.asInt == expectedIntValue);
          }
        }
      }

      AND_WHEN("accessing a valid Float value") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Float)};
        OPENASSETIO_NS(SimpleString) key{sizeof(floatKey), const_cast<char*>(floatKey), sizeof(floatKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), key);
        THEN("the value is retrieved successfully") {
          REQUIRE(errorCode == OPENASSETIO_NS(kOK));
          AND_THEN("the value is retrieved correctly") {
            REQUIRE(value.data.asFloat == expectedFloatValue);
          }
        }
      }

      AND_WHEN("accessing a valid Str value") {
        char buffer[500];
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Str), {{sizeof(buffer), buffer, 0}}};
        OPENASSETIO_NS(SimpleString) key{sizeof(strKey), const_cast<char*>(strKey), sizeof(strKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), key);
        THEN("the value is retrieved successfully") {
          REQUIRE(errorCode == OPENASSETIO_NS(kOK));
          AND_THEN("the value is retrieved correctly") {
            std::string result{value.data.asStr.buffer, value.data.asStr.usedSize};
            REQUIRE(result == expectedStrValue);
          }
        }
      }

      AND_WHEN("accessing a nonexistent key") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Int)};
        const char nonexistentKey[] = "nonexistentKey";
        OPENASSETIO_NS(SimpleString) nonexistKeySstr{sizeof(nonexistentKey), const_cast<char*>(nonexistentKey), sizeof(nonexistentKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), nonexistKeySstr);
        THEN("get() returns out of range error code") {
          REQUIRE(errorCode == OPENASSETIO_NS(kOutOfRange));
        }
        AND_THEN("the error output string is set") {
          std::string errorMsg{err.buffer, err.usedSize};
          REQUIRE(errorMsg.length() > 0);
        }
      }

      AND_WHEN("accessing a value with the wrong type") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Int)};
        OPENASSETIO_NS(SimpleString) nonexistKeySstr{sizeof(floatKey), const_cast<char*>(floatKey), sizeof(floatKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), nonexistKeySstr);
        THEN("get() returns type mismatch error code") {
          REQUIRE(errorCode == OPENASSETIO_NS(kTypeMismatch));
        }
        AND_THEN("the error output string is set") {
          std::string errorMsg{err.buffer, err.usedSize};
          REQUIRE(errorMsg.length() > 0);
        }
      }

      AND_WHEN("accessing a valid Str value with a too small output buffer") {
        OPENASSETIO_NS(SimpleMapValue) value{OPENASSETIO_NS(SimpleMapValueType_Str), {{0, nullptr, 0}}};
        OPENASSETIO_NS(SimpleString) key{sizeof(strKey), const_cast<char*>(strKey), sizeof(strKey)-1};
        const auto errorCode = suite.get(&err, &value, reinterpret_cast<OPENASSETIO_NS(SimpleMap_h)>(sm), key);
        THEN("get() returns length error code") {
          REQUIRE(errorCode == OPENASSETIO_NS(kLength));
        }
        AND_THEN("the error output string is set") {
          std::string errorMsg{err.buffer, err.usedSize};
          REQUIRE(errorMsg.length() > 0);
        }
      }

    }

  }
}
