// SPDX-License-Identifier: Apache-2.0
// Copyright 2013-2022 The Foundry Visionmongers Ltd

#include <openassetio/c/SimpleMap.h>
#include <openassetio/c/SimpleString.h>
#include <openassetio/SimpleMap.hpp>
#include <openassetio/typedefs.hpp>
#include <openassetio/c/errors.h>

#include <cstring>  // for strncpy
#include <stdexcept>

namespace {
  class VariantMismatchException : public std::runtime_error
  {
  public:
      VariantMismatchException(const std::string& what = "") : std::runtime_error(what) {}
  };

  class InternalErrorException : public std::runtime_error
  {
  public:
      InternalErrorException(const std::string& what = "") : std::runtime_error(what) {}
  };

  void CopyNullterminatedToSimpleString(OPENASSETIO_NS(SimpleString) * dst, const char* src)
  {
    const auto msgLen = strlen(src);
    if (msgLen < dst->maxSize) {
      strncpy(dst->buffer, src, msgLen);
      dst->usedSize = msgLen;
    }
  }
}

extern "C" {
OPENASSETIO_NS(SimpleMap_s) OPENASSETIO_NS(SimpleMap_suite)() {
  return {// dtor
          [](OPENASSETIO_NS(SimpleMap_h) handle) {
            auto *map = reinterpret_cast<openassetio::SimpleMap *>(handle);
            delete map;
          },
          // get
          [](OPENASSETIO_NS(SimpleString) * error, OPENASSETIO_NS(SimpleMapValue) * value,
             OPENASSETIO_NS(SimpleMap_h) handle, const OPENASSETIO_NS(SimpleString) key) {
            auto *map = reinterpret_cast<openassetio::SimpleMap *>(handle);
            int errorCode = 0;
            try {
              const openassetio::Str keyStr{key.buffer, key.usedSize};
              const auto &variant = map->at(keyStr);
              std::visit(
                  [&value, &error](auto &&arg) {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, openassetio::Bool>) {
                      if (value->type != OPENASSETIO_NS(SimpleMapValueType_Bool)) {
                        throw VariantMismatchException("expected Bool value but was different type");
                      }
                      value->data.asBool = arg;
                    } else if constexpr (std::is_same_v<T, openassetio::Int>) {
                      if (value->type != OPENASSETIO_NS(SimpleMapValueType_Int)) {
                        throw VariantMismatchException("expected Int value but was different type");
                      }
                      value->data.asInt = arg;
                    } else if constexpr (std::is_same_v<T, openassetio::Float>) {
                      if (value->type != OPENASSETIO_NS(SimpleMapValueType_Float)) {
                        throw VariantMismatchException("expected Float value but was different type");
                      }
                      value->data.asFloat = arg;
                    } else if constexpr (std::is_same_v<T, openassetio::Str>) {
                      if (value->type != OPENASSETIO_NS(SimpleMapValueType_Str)) {
                        throw VariantMismatchException("expected Str value but was different type");
                      }
                      const auto valueSize = arg.size();
                      if (valueSize > value->data.asStr.maxSize) {
                        throw std::length_error("not enough space in buffer to store string value");
                      }
                      value->data.asStr.usedSize = valueSize;
                      strncpy(value->data.asStr.buffer, arg.c_str(), valueSize);
                    } else {
                      throw InternalErrorException("variant not recognized");
                    }
                  },
                  variant);
            }
            catch (VariantMismatchException &exc) {
              errorCode = OPENASSETIO_NS(kTypeMismatch);
              CopyNullterminatedToSimpleString(error, exc.what());
            }
            catch (std::length_error &exc) {
              errorCode = OPENASSETIO_NS(kLength);
              CopyNullterminatedToSimpleString(error, exc.what());
            }
            catch (std::out_of_range &exc) {
              errorCode = OPENASSETIO_NS(kOutOfRange);
              CopyNullterminatedToSimpleString(error, exc.what());
            }
            catch (InternalErrorException &exc) {
              errorCode = OPENASSETIO_NS(kInternal);
              CopyNullterminatedToSimpleString(error, exc.what());
            }
            catch (const std::exception &exc) {
              errorCode = OPENASSETIO_NS(kUnknown);
              CopyNullterminatedToSimpleString(error, exc.what());
            }
            catch (...) {
              errorCode = OPENASSETIO_NS(kUnknown);
            }
            return errorCode;
          }};
}
}
