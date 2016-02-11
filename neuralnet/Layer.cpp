//
//  Layer.cpp
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#include "Layer.h"

Layer::Layer(const std::vector<Neuron>& neurons)
: _neurons(neurons)
{

}

Layer::~Layer()
{

}

std::vector<double> Layer::process(const std::vector<double> &inputs)
{
	std::vector<double> outputs;
	for (auto&& n : this->_neurons) {
		outputs.push_back(n.react(inputs));
	};

	return outputs;
}