#ifndef INEURONET_H
#define INEURONET_H

#include <random>
#include <vector>

#include "inlayer.h"
#include "nlayeracrtg.h"
#include "nlayersoftsign.h"
#include "nlayertanh.h"

template <typename NType>
class INeuroNet {
   public:
	INeuroNet();
	INeuroNet(const INeuroNet<NType>& obj);
	INeuroNet<NType>& operator=(const INeuroNet<NType>& obj);
	explicit INeuroNet(int size);

	~INeuroNet();

   public:
	std::vector<INLayer<NType>*> m_lay;

   protected:
	NType m_valueWeight;
	NArray<NType>* m_output;
	std::mt19937 m_gen;

   public:
	void setValueWeight(NType value);
	NType getValueWeight() const;
	NArray<NType>* getOutput() const;

	INLayer<NType>* newLayer(NLayerType type);

	virtual NArray<NType>* run(const NArray<NType>& x);
	virtual void init();
	virtual void init(const NArray<int>& n, NArray<NLayerType>& lay_type);

	virtual void ginit();
	virtual void ginit(const NArray<int>& n, NArray<NLayerType>& lay_type);
};

template <typename NType>
INeuroNet<NType>::INeuroNet()
    : m_valueWeight(0)
    , m_output(nullptr)
    , m_gen(std::random_device()()) {
}

template <typename NType>
INeuroNet<NType>::INeuroNet(const INeuroNet<NType>& obj)
    : m_valueWeight(obj.getValueWeight())
    , m_gen(obj.m_gen) {
	INLayer<NType>* layer;
	for (int i = 0; i < obj.m_lay.size(); ++i) {
		if (obj.m_lay[i]->m_type == NLayerType::Tanh) {
			layer = new NLayerTanh<NType>(*obj.m_lay[i]);
		} else if (obj.m_lay[i]->m_type == NLayerType::Softsign) {
			layer = new NLayerSoftsign<NType>(*obj.m_lay[i]);
		} else if (obj.m_lay[i]->m_type == NLayerType::Arctg) {
			layer = new NLayerArctg<NType>(*obj.m_lay[i]);
		}
		m_lay.push_back(*layer);
	}
	m_output = &(layer->m_output);
}

template <typename NType>
INeuroNet<NType>& INeuroNet<NType>::operator=(const INeuroNet<NType>& obj) {
	if (this == &obj)
		return *this;
	for (int i = 0; i < m_lay.size(); ++i) {
		delete m_lay[i];
	}
	m_lay.erase();

	m_valueWeight = obj.getValueWeight();
	INLayer<NType>* layer;
	for (int i = 0; i < obj.m_lay.size(); ++i) {
		if (obj.m_lay[i]->m_type == NLayerType::Tanh) {
			layer = new NLayerTanh<NType>(*obj.m_lay[i]);
		} else if (obj.m_lay[i]->m_type == NLayerType::Softsign) {
			layer = new NLayerSoftsign<NType>(*obj.m_lay[i]);
		} else if (obj.m_lay[i]->m_type == NLayerType::Arctg) {
			layer = new NLayerArctg<NType>(*obj.m_lay[i]);
		}
		m_lay.push_back(*layer);
	}
	m_output = &(layer->m_output);

	return *this;
}

template <typename NType>
INeuroNet<NType>::INeuroNet(int size)
    : m_lay(size)
    , m_valueWeight(0)
    , m_output(nullptr) {
}

template <typename NType>
INeuroNet<NType>::~INeuroNet() {
	for (int i = 0; i < m_lay.size(); ++i) {
		if (m_lay[i] != nullptr) {
			delete m_lay[i];
			m_lay[i] = nullptr;
		}
	}
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
NArray<NType>* INeuroNet<NType>::getOutput() const {
	return m_output;
}

template <typename NType>
INLayer<NType>* INeuroNet<NType>::newLayer(NLayerType lay_type) {
	INLayer<NType>* layer = nullptr;
	if (lay_type == NLayerType::Tanh) {
		layer = new NLayerTanh<NType>();
	} else if (lay_type == NLayerType::Softsign) {
		layer = new NLayerSoftsign<NType>();
	} else if (lay_type == NLayerType::Arctg) {
		layer = new NLayerArctg<NType>();
	}
	return layer;
}

template <typename NType>
NArray<NType>* INeuroNet<NType>::run(const NArray<NType>& x) {
	m_lay[0]->run(x);
	auto size = m_lay.size();
	for (int i = 0; i < size; ++i) {
		m_lay[i]->run(m_lay[i - 1]->m_output);
	}
	m_output = &(m_lay[size - 1]->m_output);
	return m_output;
}

template <typename NType>
void INeuroNet<NType>::init() {
	auto size = m_lay.size();
	for (int i = 0; i < size; ++i) {
		m_lay[i]->init(m_valueWeight);
	}
}

template <typename NType>
void INeuroNet<NType>::init(const NArray<int>& num, NArray<NLayerType>& lay_type) {
	auto len_layer = num.getLenght() - 1;
	m_lay.init(len_layer);
	for (int i = 0; i < lay_type.getLenght(); ++i) {
		INLayer<NType>* layer;
		layer = newLayer(lay_type.get(i));
		layer->init(num.get(i), num.get(i + 1), m_valueWeight);
		m_lay.push_back(*layer);
	}
}

template <typename NType>
void INeuroNet<NType>::ginit() {
	auto size = m_lay.size();
	for (int i = 0; i < size; ++i) {
		m_lay[i]->ginit(m_valueWeight);
	}
}

template <typename NType>
void INeuroNet<NType>::ginit(const NArray<int>& num, NArray<NLayerType>& lay_type) {
	auto len_layer = num.getLenght() - 1;
	m_lay.ginit(len_layer);
	for (int i = 0; i < lay_type.getLenght(); ++i) {
		INLayer<NType>* layer;
		layer = newLayer(lay_type.get(i));
		layer->ginit(num.get(i), num.get(i + 1), m_valueWeight);
		m_lay.push_back(*layer);
	}
}

#endif  // INEURONET_H
