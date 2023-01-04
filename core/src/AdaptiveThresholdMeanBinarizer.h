/*
* Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
* Copyright 2023 ZXing authors
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "BinaryBitmap.h"

namespace ZXing {

/**
* This Binarizer implementation is taken from wechat_qrcode module in opencv_contrib
*
* @author Qingnan.Duan@microsoft.com (Qingnan Duan)
*/
class AdaptiveThresholdMeanBinarizer: public BinaryBitmap
{
public:
    explicit AdaptiveThresholdMeanBinarizer(const ImageView& buffer);
	~AdaptiveThresholdMeanBinarizer() override;

	bool getPatternRow(int row, int rotation, PatternRow &res) const override;

protected:
	std::shared_ptr<const BitMatrix> getBlackMatrix() const override;
};

} // ZXing
