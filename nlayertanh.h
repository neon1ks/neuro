#ifndef NLAYERTANH_H
#define NLAYERTANH_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerTanh final : public INLayer<NType> {
   public:
	NLayerTanh();
	~NLayerTanh();

   public:
	NType activation(NType& x) override;
	NType derivative(NType& y) override;
};

template <typename NType>
NLayerTanh<NType>::NLayerTanh()
    : INLayer<NType>(2, NLayerType::Tanh) {
}

template <typename NType>
NLayerTanh<NType>::~NLayerTanh() {
}

template <typename NType>
NType NLayerTanh<NType>::activation(NType& x) {
	NType val = exp(this->m_koef * x);
	return (val - 1) / (val + 1);
}

template <typename NType>
NType NLayerTanh<NType>::derivative(NType& y) {
	return (1 - y * y);
}

#endif  // NLAYERTANH_H
