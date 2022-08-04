/*
 * Copyright 2016 Nu-book Inc.
 * Copyright 2016 ZXing authors
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "DecodeHints.h"
#include "Result.h"

#include <functional>
#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace ZXing {

class BinaryBitmap;
class DecodeHints;

class Reader
{
protected:
	const DecodeHints& _hints;

public:
	const bool supportsInversion;

	explicit Reader(const DecodeHints& hints, bool supportsInversion = false) : _hints(hints), supportsInversion(supportsInversion) {}
	explicit Reader(DecodeHints&& hints) = delete;
	virtual ~Reader() = default;

	virtual Result decode(const BinaryBitmap& image,
						  [[maybe_unused]] std::optional<std::reference_wrapper<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>> debugInfo = {}) const = 0;

	// WARNING: this API is experimental and may change/disappear
	virtual Results decode(const BinaryBitmap& image, [[maybe_unused]] int maxSymbols,
						   std::optional<std::reference_wrapper<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>> debugInfo = {}) const
	{
		auto res = decode(image, debugInfo);
		return res.isValid() || (_hints.returnErrors() && res.format() != BarcodeFormat::None) ? Results{std::move(res)} : Results{};
	}
};

} // namespace ZXing
