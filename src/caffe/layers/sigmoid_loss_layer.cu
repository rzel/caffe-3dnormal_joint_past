// Copyright 2013 Yangqing Jia

#include <algorithm>
#include <cfloat>
#include <vector>

#include "caffe/layer.hpp"
#include "caffe/vision_layers.hpp"
#include "caffe/util/math_functions.hpp"

using std::max;

namespace caffe {

template<typename Dtype>
Dtype SigmoidWithLossLayer<Dtype>::Forward_gpu(
		const vector<Blob<Dtype>*>& bottom, vector<Blob<Dtype>*>* top) {
	// The forward pass computes the sigmoid prob values.
	return Forward_cpu(bottom, top);
	
}

template<typename Dtype>
void SigmoidWithLossLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
		const bool propagate_down, vector<Blob<Dtype>*>* bottom) {
	// TODO(Yangqing): implement the GPU version of sigmoid.
	Backward_cpu(top, propagate_down, bottom);
}

INSTANTIATE_CLASS(SigmoidWithLossLayer);

}  // namespace caffe
