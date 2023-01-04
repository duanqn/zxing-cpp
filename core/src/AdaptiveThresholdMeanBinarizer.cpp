/*
* Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
* Copyright 2023 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#include "AdaptiveThresholdMeanBinarizer.h"

namespace ZXing {

AdaptiveThresholdMeanBinarizer::AdaptiveThresholdMeanBinarizer(const ImageView& buffer) : BinaryBitmap(buffer) {}
AdaptiveThresholdMeanBinarizer::~AdaptiveThresholdMeanBinarizer() = default;

std::shared_ptr<const BitMatrix> AdaptiveThresholdMeanBinarizer::getBlackMatrix() const
{

}

bool AdaptiveThresholdMeanBinarizer::getPatternRow(int row, int rotation, PatternRow &res) const
{

}

} // ZXing
