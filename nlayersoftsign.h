#ifndef NLAYERSOFTSIGN_H
#define NLAYERSOFTSIGN_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerSoftsign final : public INLayer<NType> {
   public:
	NLayerSoftsign();
	~NLayerSoftsign();

   public:
	NType activation(NType& x) override;
	NType derivative(NType& y) override;
};

template <typename NType>
NLayerSoftsign<NType>::NLayerSoftsign()
    : INLayer<NType>(1, NLayerType::Softsign) {
}

template <typename NType>
NLayerSoftsign<NType>::~NLayerSoftsign() {
}

template <typename NType>
NType NLayerSoftsign<NType>::activation(NType& x) {
	return x / (1 / this->m_koef + abs(x));
}

template <typename NType>
NType NLayerSoftsign<NType>::derivative(NType& y) {
	return this->m_koef / pow(1 + this->m_koef * abs(y), 2);
}

#endif  // NLAYERSOFTSIGN_H
