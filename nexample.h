#ifndef NEXAMPLE_H
#define NEXAMPLE_H

#include "narray.h"

template <typename NType>
class NExample {
   public:
	NExample();
	NExample(NExample<NType>& obj);
	NExample<NType>& operator=(const NExample<NType>& obj);
	~NExample();

   public:
	NArray<NType> m_input;
	NArray<NType> m_output;

   protected:
	NType m_energy;

   public:
	void init(int lenght_in, int lenght_out, NType value);
	void setEnergy(NType energy);
	NType getEnergy();
};

template <typename NType>
NExample<NType>::NExample()
    : m_energy(0) {
}

template <typename NType>
NExample<NType>::NExample(NExample<NType>& obj)
    : m_input(obj.m_input)
    , m_output(obj.m_output)
    , m_energy(obj.getEnergy()) {
}

template <typename NType>
NExample<NType>& NExample<NType>::operator=(const NExample<NType>& obj) {
	if (this != &obj) {
		this->m_input = obj.m_input;
		this->m_output = obj.m_output;
		this->m_energy = obj.getEnergy();
	}
	return *this;
}

template <typename NType>
NExample<NType>::~NExample() {
}

template <typename NType>
void NExample<NType>::init(int lenght_in, int lenght_out, NType value) {
	m_input.init(lenght_in, value);
	m_output.init(lenght_out, value);
}

template <typename NType>
void NExample<NType>::setEnergy(NType energy) {
	m_energy = energy;
}

template <typename NType>
NType NExample<NType>::getEnergy() {
	return m_energy;
}

#endif  // NEXAMPLE_H
