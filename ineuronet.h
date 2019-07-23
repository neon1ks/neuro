#ifndef INEURONET_H
#define INEURONET_H

#include <vector>
#include "inlayer.h"

template <typename NType>
class INeuroNet {
   public:
	INeuroNet();
	INeuroNet(INeuroNet<NType>& obj);
	explicit INeuroNet(int size);
	//INeuroNet<NType>& operator=(const INeuroNet<NType>& obj);
	~INeuroNet();

   public:
	//NArray<INLayer<NType>> m_lay;
	std::vector<INLayer<NType>> m_lay;

   protected:
	NType m_valueWeight;

   public:
	void setValueWeight(NType value);
	NType getValueWeight() const;

	virtual void run(const NArray<NType>& x);
	virtual void initWeight();
	void init(int n1, int n2, int n3);
	void init(int n1, int n2, int n3, int n4);
	void init(const NArray<int>& n);
};

template <typename NType>
INeuroNet<NType>::INeuroNet()
    : m_valueWeight(0) {
}

template <typename NType>
INeuroNet<NType>::INeuroNet(INeuroNet<NType>& obj)
    : m_lay(obj.m_lay)
    , m_valueWeight(obj.getValueWeight()) {
}

template <typename NType>
INeuroNet<NType>::INeuroNet(int size)
    : m_valueWeight(0)
    , m_lay(size) {
}

template <typename NType>
INeuroNet<NType>::~INeuroNet() {
}

template <typename NType>
void INeuroNet<NType>::setValueWeight(NType value) {
	m_valueWeight = value;
}

template <typename NType>
NType INeuroNet<NType>::getValueWeight() const {
	return m_valueWeight;
}

template <typename NType>
void INeuroNet<NType>::run(const NArray<NType>& x) {
	for (int i = 0; i < m_lay.size(); ++i) {
		m_lay[i]->run(x);
	}
}

template <typename NType>
void INeuroNet<NType>::initWeight() {
}

template <typename NType>
void INeuroNet<NType>::init(int n1, int n2, int n3) {
}

template <typename NType>
void INeuroNet<NType>::init(int n1, int n2, int n3, int n4) {
}

template <typename NType>
void INeuroNet<NType>::init(const NArray<int>& n) {
}

#endif  // INEURONET_H
