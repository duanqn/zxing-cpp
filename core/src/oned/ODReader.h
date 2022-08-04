/*
 * Copyright 2016 Nu-book Inc.
 * Copyright 2016 ZXing authors
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Reader.h"

#include <memory>
#include <vector>

namespace ZXing {

class DecodeHints;

namespace OneD {

class RowReader;

class Reader : public ZXing::Reader
{
public:
	explicit Reader(const DecodeHints& hints);
	~Reader() override;

	Result decode(
		const BinaryBitmap& image,
		[[maybe_unused]] std::optional<std::reference_wrapper<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>>
			debugInfo = {}) const override;
	Results decode(
		const BinaryBitmap& image, int maxSymbols,
		[[maybe_unused]] std::optional<std::reference_wrapper<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>>
			debugInfo = {}) const override;

private:
	std::vector<std::unique_ptr<RowReader>> _readers;
};

} // namespace OneD
} // namespace ZXing
