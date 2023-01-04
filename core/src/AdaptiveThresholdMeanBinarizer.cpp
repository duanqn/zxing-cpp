/*
* Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
* Copyright 2023 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#include "AdaptiveThresholdMeanBinarizer.h"

namespace ZXing {

AdaptiveThresholdMeanBinarizer::AdaptiveThresholdMeanBinarizer(const ImageView& buffer) : GlobalHistogramBinarizer(buffer) {}
AdaptiveThresholdMeanBinarizer::~AdaptiveThresholdMeanBinarizer() = default;

std::shared_ptr<const BitMatrix> AdaptiveThresholdMeanBinarizer::getBlackMatrix() const
{
    if(_buffer.width() > BLOCK_SIZE && _buffer.height() > BLOCK_SIZE){

    }
    else{
        return GlobalHistogramBinarizer::getBlackMatrix();
    }
}

bool AdaptiveThresholdMeanBinarizer::getPatternRow(int row, int rotation, PatternRow &res) const
{

}

} // ZXing
