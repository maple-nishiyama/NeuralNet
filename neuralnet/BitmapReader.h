//
//  BitmapReader.h
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#ifndef __neuralnet__BitmapReader__
#define __neuralnet__BitmapReader__

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <fstream>

#pragma pack(1)

/**
 * ビットマップファイルヘッダ構造体
 */
struct BITMAPFILEHEADER {
	uint16_t bfType;
	int32_t  bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
};

/**
 * ビットマップ情報ヘッダ構造体
 */
struct BITMAPINFOHEADER {
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPixPerMeter;
	int32_t  biYPixPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

/*
 * 24bit ビットマップの1ピクセルを表す
 */
struct RGB24 {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

#pragma pack()

/**
 * ビットマップのピクセルデータをファイルから読み出す
 */
class BitmapReader {

public:
	BitmapReader(const std::string& filePath);
	std::vector<RGB24>* getPixels();

private:
	const std::string _filePath;

	std::ifstream _openFile();
	BITMAPFILEHEADER _readFileHeader(std::ifstream& ifs);
	BITMAPINFOHEADER _readInfoHeader(std::ifstream& ifs);
	std::vector<RGB24>* _readPixels24(std::ifstream& ifs, const BITMAPFILEHEADER& fHeader, const BITMAPINFOHEADER& iHeader);
};

#endif /* defined(__neuralnet__BitmapReader__) */
