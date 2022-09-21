// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
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

#include "lite/kernels/xpu/softmax_compute.h"
#include <vector>
#include "lite/backends/xpu/xpu_header_sitter.h"
#include "lite/core/op_registry.h"

namespace paddle {
namespace lite {
namespace kernels {
namespace xpu {

void SoftmaxCompute::Run() {
  auto& param = this->template Param<param_t>();
  auto& ctx = this->ctx_->template As<XPUContext>();

  std::vector<int> xdims;
  for (auto i = 0; i < param.x->dims().size(); i++) {
    xdims.push_back(param.x->dims().data()[i]);
  }
  int axis = param.axis < 0 ? param.axis + xdims.size() : param.axis;

  // size_t input_copy_size = param.x->data_size();
  // std::vector<float> input_copy_cpu(input_copy_size);
  // TargetWrapperXPU::MemcpySync(
  //   input_copy_cpu.data(), param.x->data<float>(), input_copy_size * sizeof(float), IoDirection::DtoH);
  
  // for (size_t x=0; x < input_copy_size; x += 100) {
  //   std::cout << x << " " << input_copy_cpu[x] << std::endl;
  // }

  int r = xdnn::softmax(ctx.GetRawContext(),
                        param.x->data<float>(),
                        param.output->mutable_data<float>(TARGET(kXPU)),
                        xdims,
                        axis);

  // size_t output_copy_size = param.output->data_size();
  // if (output_copy_size > 200000 ) {
  //   std::cout << "softmax output =======" << std::endl;
  //   // std::cout << "zsoftmax size = " << std::dec << output_copy_size << std::endl;
  //   // size_t output_copy_size = param.output->data_size();
  //   std::vector<float> output_copy_cpu(output_copy_size);
  //   TargetWrapperXPU::MemcpySync(
  //     output_copy_cpu.data(), param.output->template mutable_data<float>(), output_copy_size * sizeof(float), IoDirection::DtoH);
  //   std::cout << "zsoft ";
  //   for (size_t x=0; x < output_copy_size; x += 1000) {
  //     std::cout << output_copy_cpu[x] << " ";
  //     if (x == 9000) 
  //       break;
  //   }
  //   std::cout << std::endl;
  // }
  
  CHECK_EQ(r, 0);
}

}  // namespace xpu
}  // namespace kernels
}  // namespace lite
}  // namespace paddle

REGISTER_LITE_KERNEL(softmax,
                     kXPU,
                     kFloat,
                     kNCHW,
                     paddle::lite::kernels::xpu::SoftmaxCompute,
                     def)
    .BindInput("X", {LiteType::GetTensorTy(TARGET(kXPU))})
    .BindOutput("Out", {LiteType::GetTensorTy(TARGET(kXPU))})
    .Finalize();
