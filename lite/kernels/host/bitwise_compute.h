// Copyright (c) 2023 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "lite/core/kernel.h"
#include "lite/core/op_registry.h"
#ifdef LITE_WITH_PROFILE
#include <string>
#include "lite/core/profile/profiler.h"
#endif

namespace paddle {
namespace lite {
namespace kernels {
namespace host {

template <typename T>
class BitwiseAndCompute : public KernelLite<TARGET(kHost), PRECISION(kAny)> {
 public:
  using param_t = operators::BitwiseParam;

  void Run() override;

  virtual ~BitwiseAndCompute() = default;
#ifdef LITE_WITH_PROFILE
  virtual void SetProfileRuntimeKernelInfo(
      paddle::lite::profile::OpCharacter* ch) {
    ch->kernel_func_name = kernel_func_name_;
  }
  std::string kernel_func_name_{"NotImplForBitAnd"};
#endif
};

template <typename T>
class BitwiseNotCompute : public KernelLite<TARGET(kHost), PRECISION(kAny)> {
 public:
  using param_t = operators::BitwiseParam;

  void Run() override;

  virtual ~BitwiseNotCompute() = default;
#ifdef LITE_WITH_PROFILE
  virtual void SetProfileRuntimeKernelInfo(
      paddle::lite::profile::OpCharacter* ch) {
    ch->kernel_func_name = kernel_func_name_;
  }
  std::string kernel_func_name_{"NotImplForBitNot"};
#endif
};

}  // namespace host
}  // namespace kernels
}  // namespace lite
}  // namespace paddle
