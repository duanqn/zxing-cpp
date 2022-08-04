/*
* Copyright 2016 Nu-book Inc.
* Copyright 2016 ZXing authors
* Copyright 2021 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ImageView.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

namespace ZXing {

class BitMatrix;

using PatternRow = std::vector<uint16_t>;

/**
* This class is the core bitmap class used by ZXing to represent 1 bit data. Reader objects
* accept a BinaryBitmap and attempt to decode it.
*/
class BinaryBitmap
{
	struct Cache;
	std::unique_ptr<Cache> _cache;
	bool _inverted = false;

protected:
	ImageView _buffer;

	/**
	* Converts a 2D array of luminance data to 1 bit (true means black).
	*
	* @return The 2D array of bits for the image, nullptr on error.
	*/
	virtual std::shared_ptr<const BitMatrix> getBlackMatrix() const = 0;

public:
	BinaryBitmap(const ImageView& buffer);
	virtual ~BinaryBitmap();

	int width() const { return _buffer.width(); }
	int height() const { return _buffer.height(); }

	/**
	* Converts one row of luminance data to a vector of ints denoting the widths of the bars and spaces.
	*/
	virtual bool getPatternRow(int row, int rotation, PatternRow& res) const = 0;

	const BitMatrix* getBitMatrix() const;

	void invert();
	bool inverted() const { return _inverted; }

	const ImageView& buffer(){
		return _buffer;
	}

	void setBuffer(const ImageView& view){
		_buffer = view;
	}

	std::vector<std::vector<bool>> getBits();

	std::vector<std::vector<bool>> getRows(bool isVertical);
};

class OwningBinaryBitmap final {
	private:
	std::unique_ptr<BinaryBitmap> m_bitmap;
	std::unique_ptr<uint8_t[]> m_memory;

	public:
	OwningBinaryBitmap(std::unique_ptr<BinaryBitmap>&& bitmap): m_bitmap(std::move(bitmap)){
		m_memory = std::make_unique<uint8_t[]>(m_bitmap->width() * m_bitmap->height());
		memcpy(m_memory.get(), m_bitmap->buffer().data(0, 0), m_bitmap->width() * m_bitmap->height());
		const ImageView& oldView = m_bitmap->buffer();
		ImageView newView {m_memory.get(), oldView.width(), oldView.height(), oldView.format(), oldView.rowStride(), oldView.pixStride()};
		m_bitmap->setBuffer(newView);
	}

	std::unique_ptr<BinaryBitmap>& bitmap(){
		return m_bitmap;
	}

	std::unique_ptr<BinaryBitmap> const& bitmap() const{
		return m_bitmap;
	}
};

} // ZXing
