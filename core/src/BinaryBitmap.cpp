/*
* Copyright 2020 Axel Waggershauser
*/
// SPDX-License-Identifier: Apache-2.0

#include "BinaryBitmap.h"

#include "BitMatrix.h"

#include <mutex>

namespace ZXing {

struct BinaryBitmap::Cache
{
	std::once_flag once;
	std::shared_ptr<const BitMatrix> matrix;
};

BinaryBitmap::BinaryBitmap(const ImageView& buffer) : _cache(new Cache), _buffer(buffer) {}

BinaryBitmap::~BinaryBitmap() = default;

const BitMatrix* BinaryBitmap::getBitMatrix() const
{
	std::call_once(_cache->once, [&](){_cache->matrix = getBlackMatrix();});
	return _cache->matrix.get();
}

void BinaryBitmap::invert()
{
	if (_cache->matrix) {
		auto matrix = const_cast<BitMatrix*>(_cache->matrix.get());
		matrix->flipAll();
	}
	_inverted = true;
}

std::vector<std::vector<bool>> BinaryBitmap::getBits(){
	std::vector<std::vector<bool>> res(height());
	for(auto&& row: res){
		row.resize(width(), false);
	}

	auto ptr = getBitMatrix();
	for(int i = 0; i < height(); ++i){
		for(int j = 0; j < width(); ++j){
			res[i][j] = ptr->get(j, i);
		}
	}

	return res;
}

std::vector<std::vector<bool>> BinaryBitmap::getRows(bool isVertical){
	std::vector<std::vector<bool>> res(height());
	for(auto&& row: res){
		row.resize(width(), false);
	}

	size_t outer = isVertical ? width() : height();
	size_t inner = isVertical ? height() : width();

	for(size_t i = 0; i < outer; ++i){
		ZXing::PatternRow row;
		bool succeeded = getPatternRow(i, isVertical ? 270 : 0, row);
		if(!succeeded){
			for(size_t j = 0; j < inner; ++j){
				if(isVertical){
					res[j][i] = true;	// All black
				}
				else{
					res[i][j] = true;	// All black
				}
			}
		}
		else{
			size_t colIndex = 0;
			for(size_t index = 0; index < row.size(); ++index){
				bool isWhite = index % 2 == 0;
				for(size_t j = 0; j < row[index]; ++j){
					if(isVertical){
						res[colIndex][i] = !isWhite;	// True for black
					}
					else{
						res[i][colIndex] = !isWhite;	// True for black
					}
					colIndex++;
				}
			}
			assert(colIndex == inner);
		}
	}

	return res;
}

} // ZXing
