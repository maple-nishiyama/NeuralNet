//
//  BitmapReader.cpp
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#include "BitmapReader.h"
#include <iostream>
#include "Utils.h"

BitmapReader::BitmapReader(const std::string& filePath)
: _filePath(filePath)
{

}

std::vector<RGB24>* BitmapReader::getPixels()
{
	auto ifs = this->_openFile();
	auto fHeader = this->_readFileHeader(ifs);
	auto iHeader = this->_readInfoHeader(ifs);
	return this->_readPixels24(ifs, fHeader, iHeader);
}



std::ifstream BitmapReader::_openFile()
{
	std::ifstream ifs;
	ifs.open(this->_filePath, std::ios::in | std::ios::binary);
	return ifs;
}

BITMAPFILEHEADER BitmapReader::_readFileHeader(std::ifstream& ifs)
{
	BITMAPFILEHEADER fHeader;
	ifs.read((char*)&fHeader, sizeof(fHeader));
	LOG("\n======== ビットマップファイルヘッダ ============\n");
	LOG("ファイルタイプ = %x\n", fHeader.bfType);
	LOG("ファイルサイズ = %d\n", fHeader.bfSize);
	LOG("予約領域1 = %d\n", fHeader.bfReserved1);
	LOG("予約領域2 = %d\n", fHeader.bfReserved2);
	LOG("オフセット = %d\n", fHeader.bfOffBits);

	return fHeader;
}

BITMAPINFOHEADER BitmapReader::_readInfoHeader(std::ifstream& ifs)
{
	BITMAPINFOHEADER iHeader;
	ifs.read((char*)&iHeader, sizeof(iHeader));

	LOG("\n======== ビットマップ情報ヘッダ ============\n");
	LOG("情報ヘッダサイズ = %d\n", iHeader.biSize);
	LOG("画像の幅 = %dピクセル\n", iHeader.biWidth);
	LOG("画像の高さ = %dピクセル\n", iHeader.biHeight);
	LOG("プレーン数 = %d\n", iHeader.biPlanes);
	LOG("色ビット数 = %d\n", iHeader.biBitCount);
	LOG("圧縮形式 = %d\n", iHeader.biCompression);
	LOG("画像データサイズ = %dバイト\n", iHeader.biSizeImage);
	LOG("水平解像度 = %d[dots/m]\n", iHeader.biXPixPerMeter);
	LOG("垂直解像度 = %d[dots/m]\n", iHeader.biYPixPerMeter);
	LOG("格納パレット数 = %d色\n", iHeader.biClrUsed);
	LOG("重要色数 = %d色\n", iHeader.biClrImportant);
	LOG("===============================================\n");

	return iHeader;
}

std::vector<RGB24>* BitmapReader::_readPixels24(std::ifstream& ifs,
											   const BITMAPFILEHEADER& fHeader,
											   const BITMAPINFOHEADER& iHeader)
{
	// パディングが必要か？
	int res = (iHeader.biWidth * 3) % 4;
	int padding = res > 0 ? 4 - res : 0;
	char b; // パディング読み捨て用バッファ

	// 領域確保
	size_t numPics = iHeader.biWidth * iHeader.biHeight;
	auto pics = new std::vector<RGB24>(numPics);

	// ピクセルデータまでポインタを移動させる
	ifs.seekg(fHeader.bfOffBits);
	for (int i = 0; i < iHeader.biHeight; ++i) {
		for (int j = 0; j < iHeader.biWidth; ++j) {
			ifs.read((char*)&(*pics)[i * iHeader.biWidth + j], sizeof(RGB24));
		}
		// パディング分ポインタを進める
		for (int p = 0; p < padding; ++p) {
			ifs.read(&b, sizeof(char));
		}
	}

	return pics;
}
