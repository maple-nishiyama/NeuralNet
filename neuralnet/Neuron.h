//
//  Neuron.h
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#ifndef __neuralnet__Neuron__
#define __neuralnet__Neuron__

#include <stdio.h>
#include <vector>
#include <functional>

static const size_t DEFAULT_NUM_WAIT = 100;

/**
 * ひとつのニューロンを表すクラス
 */
class Neuron {
public:
	Neuron();
	Neuron(const std::vector<double>& waits, const std::function<double(const double&)>& activationFunction);
	virtual ~Neuron();
	double react(const std::vector<double>& inputs);

private:
	std::vector<double> _waits;
	std::function<double(const double&)> _activationFunction;
};

#endif /* defined(__neuralnet__Neuron__) */
