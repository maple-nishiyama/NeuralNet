//
//  Layer.h
//  neuralnet
//
//  Created by 西山 大輔 on 2016/02/11.
//  Copyright (c) 2016年 maplesystems. All rights reserved.
//

#ifndef __neuralnet__Layer__
#define __neuralnet__Layer__

#include <stdio.h>
#include <vector>
#include "Neuron.h"


/*
 * ニューラルネットを構成する一つの層を表すクラス
 */
class Layer {
public:
	Layer(const std::vector<Neuron>& neurons);
	virtual ~Layer();

	std::vector<double> process(const std::vector<double>& inputs);

private:
	std::vector<Neuron> _neurons;

};

#endif /* defined(__neuralnet__Layer__) */
