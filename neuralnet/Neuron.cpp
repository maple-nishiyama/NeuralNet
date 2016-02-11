//
//  Neuron.cpp
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#include "Neuron.h"
#include <random>
#include "Utils.h"

// デフォルトコンストラクタ
Neuron::Neuron()
: _waits(std::vector<double>(DEFAULT_NUM_WAIT))
, _activationFunction([](const double& input) -> double {
	// 活性化階段関数として、階段関数を使ってみる。
	return input > 0 ? 1 : 0;
})
{
	// パラメータをランダムで初期化してみる（-100.0 から +100.0 の間）
	std::random_device rnd;
	std::mt19937 mt(rnd());
	for (int i = 0; i < DEFAULT_NUM_WAIT; ++i) {
		_waits[i] = (double)(mt() % 200 - 100.0);
	}
}

Neuron::Neuron(const std::vector<double>& waits, const std::function<double(const double&)>& activationFunction)
: _waits(waits)
, _activationFunction(activationFunction)
{

}

Neuron::~Neuron(){

}

double Neuron::react(const std::vector<double>& inputs)
{
	double in = 0.0;
	size_t s = this->_waits.size();
	for (int i = 0; i < s; ++i) {
		in += this->_waits[i] * inputs[i];
	}
	LOG("input = %f\n", in);
	return this->_activationFunction(in);
}

