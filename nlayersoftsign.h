#ifndef NLAYERSOFTSIGN_H
#define NLAYERSOFTSIGN_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerSoftsign final : public INLayer<NType> {
   public:
	NLayerSoftsign();
	virtual ~NLayerSoftsign();

   public:
	NType activation(NType& x) override;
	NType derivative(NType& y) override;
	void init(const NType& value) override;
	void init(int len_row, int len_column, const NType& value) override;
	// void run(const NArray<NType>& array_x) override;
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

template <typename NType>
void NLayerSoftsign<NType>::init(const NType& value) {
	INLayer<NType>::init(value);
}

template <typename NType>
void NLayerSoftsign<NType>::init(int len_row, int len_column, const NType& value) {
	INLayer<NType>::init(len_row, len_column, value);
}

#endif  // NLAYERSOFTSIGN_H
