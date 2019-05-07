#ifndef NARRAY_H
#define NARRAY_H

template <typename NType>
class NArray {
   public:
	NArray();                                            ///< Конструктор по умолчанию (OK)
	NArray(NArray<NType>& obj);                          ///< Конструктор копирования
	NArray<NType>& operator=(const NArray<NType>& obj);  ///< Оператор копирования
	explicit NArray(int size);
	~NArray();

   protected:
	int m_size;     ///< Размер доступной памяти
	int m_lenght;   ///< Длина реальных данных
	int m_block;    ///< Шаг изменения размера данных
	NType* m_data;  ///< Указатель на хранящиеся данные

   public:
	void init(int lenght, NType& value);
	void add(NType element, int pos);
	NType del(int pos);

	void push(NType element);
	NType pop();

	void set(NType element, int pos);  ///< Установка значения одному элементу (OK)
	NType get(int pos);                ///< Получение значения одного элемента (OK)

	void setBlock(int block);  ///< Изменение шага изменения размера данных (OK)

	int getSize();     ///< Получение размера данных (OK)
	int getLenght();   ///< Получение длины данных (OK)
	int getBlock();    ///< Получение шага изменения размера данных (OK)
	NType* getData();  ///< Получение указателя на данные (OK)

	void resize(int size);
};

template <typename NType>
NArray<NType>::NArray()
    : m_size(0)
    , m_lenght(0)
    , m_block(1)
    , m_data(nullptr) {
}

// Конструктор копирования
template <typename NType>
NArray<NType>::NArray(NArray<NType>& obj) {
	m_size = obj.getSize();
	m_lenght = obj.getLenght();
	m_block = obj.getBlock();
	m_data = new NType[m_size];

	auto p = obj.getData();
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] = p[i];
	}
}

// Assignment operator
template <typename NType>
NArray<NType>& NArray<NType>::operator=(const NArray<NType>& obj) {
	if (this != &obj) {
		if (obj.getSize() != m_size) {
			if (m_data != nullptr) {
				delete[] m_data;
			}
			m_size = 0;
			m_data = nullptr;

			m_size = obj.getSize();
			m_lenght = obj.getLenght();
			m_block = obj.getBlock();
			m_data = new int[m_size];
		}
		auto p = obj.getData();
		for (int i = 0; i < m_lenght; ++i) {
			m_data[i] = p[i];
		}
	}
	return *this;
}

template <typename NType>
NArray<NType>::NArray(int size)
    : m_size(size)
    , m_lenght(0)
    , m_block(1) {
	m_data = new NType[size];
}

template <typename NType>
NArray<NType>::~NArray() {
}

template <typename NType>
void NArray<NType>::init(int lenght, NType& value) {
	if (lenght > m_size) {
		resize(lenght);
	}
	m_lenght = lenght;
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] = value;
	}
}

template <typename NType>
void NArray<NType>::add(NType element, int pos) {
	if (m_lenght >= m_size) {
		resize(m_size + m_block);
	}

	for (int i = m_lenght; i > pos; --i) {
		m_data[i] = m_data[i - 1];
	}
	m_data[pos] = element;
	++m_lenght;
}

template <typename NType>
NType NArray<NType>::del(int pos) {
	NType result = m_data[pos];
	--m_lenght;
	for (int i = pos; i < m_lenght; ++i) {
		m_data[i] = m_data[i + 1];
	}
	return result;
}

template <typename NType>
void NArray<NType>::push(NType element) {
	if (m_lenght >= m_size) {
		resize(m_size + m_block);
	}
	m_data[m_lenght] = element;
	++m_lenght;
}

template <typename NType>
NType NArray<NType>::pop() {
	--m_lenght;
	return m_data[m_lenght];
}

template <typename NType>
void NArray<NType>::set(NType element, int pos) {
	if (m_size > pos) {
		m_data[pos] = element;
		if (m_lenght <= pos) {
			m_lenght = pos + 1;
		}
	}
}

template <typename NType>
NType NArray<NType>::get(int pos) {
	return m_data[pos];
}

template <typename NType>
void NArray<NType>::setBlock(int block) {
	if (block > 0) {
		m_block = block;
	}
}

template <typename NType>
int NArray<NType>::getSize() {
	return m_size;
}

template <typename NType>
int NArray<NType>::getLenght() {
	return m_lenght;
}

template <typename NType>
int NArray<NType>::getBlock() {
	return m_block;
}

template <typename NType>
NType* NArray<NType>::getData() {
	return this->m_data;
}

// Метод resize не может уменьшить размер массива удалив данные.
// Влияет только на два параметра m_data и m_size
template <typename NType>
void NArray<NType>::resize(int size) {
	size = size > m_lenght ? size : m_lenght;
	if (m_data == nullptr) {
		m_data = new NType[size];
		m_size = size;
	} else if (m_size != size) {
		auto p = m_data;
		m_data = new NType[size];
		m_size = size;
		for (int i = 0; i < m_lenght; ++i) {
			m_data[i] = p[i];
		}
		delete[] p;
	}
}

#endif  // NARRAY_H
