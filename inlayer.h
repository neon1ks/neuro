#ifndef INLAYER_H
#define INLAYER_H

#include "narray.h"
#include "nmatrix.h"

template <typename NType>
class INLayer {
   public:
	INLayer();
	virtual ~INLayer();

   public:
	NMatrix<NType> m_weight;  // матрица весов
	NArray<NType> m_bias;     // Массив смещений
	NType m_koef;
	NArray<NType> m_output;

   public:
	virtual void init(const NType& value);
	virtual void init(int len_row, int len_column, const NType& value);
	virtual NType activation(NType& x) = 0;
	virtual NType derivative(NType& y) = 0;
	virtual void run(const NArray<NType>& array_x);
};

template <typename NType>
INLayer<NType>::INLayer()
    : m_koef(1) {
}

template <typename NType>
INLayer<NType>::~INLayer() {
}

template <typename NType>
void INLayer<NType>::init(const NType& value) {
	m_weight.init(value);
	m_bias.init(value);
	m_output.init(value);
}

template <typename NType>
void INLayer<NType>::init(int len_row, int len_column, const NType& value) {
	m_weight.init(len_row, len_column, value);
	m_bias.init(len_row, value);
	m_output.init(len_row, value);
}

template <typename NType>
void INLayer<NType>::run(const NArray<NType>& array_x) {
	m_output = m_weight * array_x;
	m_output.sum(m_bias);
	NType* p_out = m_output.getData();
	for (int i = 0; i < m_output.getLenght(); ++i) {
		m_output.set(activation(p_out[i]), i);
	}
}

#endif  // INLAYER_H
