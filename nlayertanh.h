#ifndef NLAYERTANH_H
#define NLAYERTANH_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerTanh : public INLayer<NType> {
   public:
	NLayerTanh();
	virtual ~NLayerTanh();

   public:
	virtual NType activation(NType& x);
	virtual NType derivative(NType& y);
};

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
