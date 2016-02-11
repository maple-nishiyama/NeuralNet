//
//  main.cpp
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#include <iostream>
#include <memory>
#include "BitmapReader.h"
#include "Utils.h"
#include "Neuron.h"
#include "Layer.h"

int main(int argc, const char * argv[]) {

	std::unique_ptr<BitmapReader> bmpReader(new BitmapReader("/Users/nishiyama/Downloads/logo_blog.bmp"));
	auto pics = bmpReader->getPixels();

	// ピクセルデータをニューラルネットに入れられる形（vector<double>） に変換
	size_t s = pics->size();
	std::vector<double> inputs(3*s);
	for (int i = 0; i < 3*s; ++i) {
		RGB24* p = &(*pics)[i];
		inputs[i++] = p->r;
		inputs[i++] = p->g;
		inputs[i++] = p->b;
	}
	delete pics;

	// 2層のネットワークを作る

	// 1層目：ニューロン100個
	std::vector<Neuron> neurons1(100);
	// 1つ目のレイヤー
	Layer layer1(neurons1);
	auto result1 = layer1.process(inputs);

	// 2層目：ニューロン10個
	std::vector<Neuron> neurons2(10);
	// 2つ目のレイヤー
	Layer layer2(neurons2);
	auto result2 = layer2.process(result1);

	// 結果を出力
	int i = 0;
	for (auto d : result2) {
		LOG("d[%d] = %f\n", i, d);
		i++;
	}

	return 0;
}
