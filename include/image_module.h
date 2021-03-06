// SPDX-License-Identifier: Apache-2.0
#pragma once

#include "runtime/importobj.h"

namespace WasmEdge {
namespace Host {

class WasmEdgeImageModule : public Runtime::ImportObject {
public:
  WasmEdgeImageModule();
  ~WasmEdgeImageModule() = default;
};

} // namespace Host
} // namespace WasmEdge
