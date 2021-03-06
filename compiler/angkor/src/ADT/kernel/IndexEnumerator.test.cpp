/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "nncc/core/ADT/kernel/IndexEnumerator.h"

#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

using nncc::core::ADT::kernel::Shape;
using nncc::core::ADT::kernel::IndexEnumerator;

TEST(ADT_KERNEL_INDEX_ENUMERATOR, iterate_full_range)
{
  const uint32_t N = 2;
  const uint32_t C = 3;
  const uint32_t H = 4;
  const uint32_t W = 5;

  const Shape shape{N, C, H, W};

  std::vector<uint32_t> count;
  count.resize(N * C * H * W, 0);

  for (IndexEnumerator e{shape}; e.valid(); e.advance())
  {
    const uint32_t offset = ((e.count() * C + e.depth()) * H + e.height()) * W + e.width();
    count.at(offset) += 1;
  }

  ASSERT_TRUE(std::all_of(count.begin(), count.end(), [](uint32_t n) { return n == 1; }));
}
