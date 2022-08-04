/*
 * Copyright 2019 Axel Waggershauser
 */
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "BinaryBitmap.h"
#include "DecodeHints.h"
#include "ImageView.h"
#include "Result.h"

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <vector>

namespace ZXing {

/**
 * Read barcode from an ImageView
 *
 * @param buffer  view of the image data including layout and format
 * @param hints  optional DecodeHints to parameterize / speed up decoding
 * @return #Result structure
 */
Result ReadBarcode(const ImageView& buffer, const DecodeHints& hints = {});

/**
 * Read barcodes from an ImageView
 *
 * @param buffer  view of the image data including layout and format
 * @param hints  optional DecodeHints to parameterize / speed up decoding
 * @return #Results list of results found, may be empty
 */
Results ReadBarcodes(
	const ImageView& buffer, const DecodeHints& hints = {},
	std::optional<
		std::reference_wrapper<std::vector<std::vector<std::map<std::pair<int, bool>, std::pair<std::vector<uint16_t>, bool>>>>>>
		debugInfo = {},
	std::optional<std::reference_wrapper<std::vector<std::unique_ptr<OwningBinaryBitmap>>>> bitmap_out = {},
	std::optional<std::reference_wrapper<std::vector<std::vector<std::chrono::milliseconds>>>> time = {});

} // namespace ZXing
