#ifndef NLAYERACRTG_H
#define NLAYERACRTG_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerArctg : public INLayer<NType> {
   public:
	NLayerArctg();
	virtual ~NLayerArctg();

   public:
	virtual NType activation(NType& x) override;
	virtual NType derivative(NType& y) override;
};

template <typename NType>
NLayerArctg<NType>::NLayerArctg() {
	this->m_koef = 2;
}

template <typename NType>
NLayerArctg<NType>::~NLayerArctg() {
}

template <typename NType>
NType NLayerArctg<NType>::activation(NType& x) {
	return atan(this->m_koef * x);
}

template <typename NType>
NType NLayerArctg<NType>::derivative(NType& y) {
	return this->m_koef / (pow(this->m_koef * y, 2) + 1);
}

#endif  // NLAYERACRTG_H