#ifndef NLAYERACRTG_H
#define NLAYERACRTG_H

#include <cmath>
#include "inlayer.h"

template <typename NType>
class NLayerArctg final : public INLayer<NType> {
   public:
	NLayerArctg();
	~NLayerArctg();

   public:
	NType activation(NType& x) override;
	NType derivative(NType& y) override;
	void init(const NType& value) override;
	void init(int len_row, int len_column, const NType& value) override;
	// void run(const NArray<NType>& array_x) override;
};

template <typename NType>
NLayerArctg<NType>::NLayerArctg()
    : INLayer<NType>(2, NLayerType::Arctg) {
}

template <typename NType>
NLayerArctg<NType>::~NLayerArctg() {
}

template <typename NType>
NType NLayerArctg<NType>::activation(NType& x) {
	return atan(INLayer<NType>::m_koef * x);
}

template <typename NType>
NType NLayerArctg<NType>::derivative(NType& y) {
	return this->m_koef / (pow(INLayer<NType>::m_koef * y, 2) + 1);
}

template <typename NType>
void NLayerArctg<NType>::init(const NType& value) {
	INLayer<NType>::init(value);
}

template <typename NType>
void NLayerArctg<NType>::init(int len_row, int len_column, const NType& value) {
	INLayer<NType>::init(len_row, len_column, value);
}

#endif  // NLAYERACRTG_H
