/*
 * Copyright 2016 Nu-book Inc.
 * Copyright 2016 ZXing authors
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

namespace ZXing::Aztec {

class Reader : public ZXing::Reader
{
public:
	using ZXing::Reader::Reader;

	Result decode(
		const BinaryBitmap& image,
		[[maybe_unused]] std::optional<std::reference_wrapper<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>>
			debugInfo = {}) const override;
};

} // namespace ZXing::Aztec
