#pragma once

#ifndef NARRAY_H
#define NARRAY_H

#include "nmatrix.h"

template <typename NType>
class NMatrix;

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
	void init(const NType& value);
	void init(int lenght, const NType& value);  ///< Инициализация массива значением (OK)
	void add(NType element, int pos);           ///< Добавление элемента в массив, существующие сдвигаются
	NType del(int pos);

	void push(NType element);
	NType pop();

	void set(NType element, int pos);  ///< Установка значения одному элементу (OK)
	NType get(int pos) const;          ///< Получение значения одного элемента (OK)

	void setBlock(int block);  ///< Изменение шага изменения размера данных (OK)

	int getSize() const;     ///< Получение размера данных (OK)
	int getLenght() const;   ///< Получение длины данных (OK)
	int getBlock() const;    ///< Получение шага изменения размера данных (OK)
	NType* getData() const;  ///< Получение указателя на данные (OK)

	void resize(int size);  ///< Изменение размера доступной памяти (OK)

   public:
	NArray<NType>& sum(const NArray<NType>& B);  ///< Сложение векторов
	NArray<NType>& mul(const NArray<NType>& B);  ///< Умножение векторов
	NArray<NType>& valsum(const NType& value);   ///< Сложение вектора с числом
	NArray<NType>& valmul(const NType& value);   ///< Умножение вектора на число

	NArray<NType>& matrix_mul(const NArray<NType>& A, const NMatrix<NType>& B);  ///< Умножение вектора на матрицу
	NArray<NType>& matrix_mul(const NMatrix<NType>& A, const NArray<NType>& B);  ///< Умножение матрицы на вектор

	NArray<NType> operator+(const NType& value) const;  // (OK)
	NArray<NType> operator-(const NType& value) const;  // (OK)
	NArray<NType> operator*(const NType& value) const;  // (OK)
	NArray<NType> operator/(const NType& value) const;  // (OK)

	NArray<NType> operator+(const NArray<NType>& B) const;  // (OK)
	NArray<NType> operator-(const NArray<NType>& B) const;  // (OK)
	NArray<NType> operator*(const NArray<NType>& B) const;  // (OK)

	NArray<NType> operator*(const NMatrix<NType>& B) const;  // (OK)
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
			m_data = new NType[m_size];
		}
		m_lenght = obj.getLenght();
		m_block = obj.getBlock();
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
	if (m_data != nullptr) {
		delete[] m_data;
	}
}

template <typename NType>
void NArray<NType>::init(const NType& value) {
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] = value;
	}
}

template <typename NType>
void NArray<NType>::init(int lenght, const NType& value) {
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
NType NArray<NType>::get(int pos) const {
	// TODO - кинуть исключение, если нет такого элемента
	return m_data[pos];
}

template <typename NType>
void NArray<NType>::setBlock(int block) {
	if (block > 0) {
		m_block = block;
	}
}

template <typename NType>
int NArray<NType>::getSize() const {
	return m_size;
}

template <typename NType>
int NArray<NType>::getLenght() const {
	return m_lenght;
}

template <typename NType>
int NArray<NType>::getBlock() const {
	return m_block;
}

template <typename NType>
NType* NArray<NType>::getData() const {
	return m_data;
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

template <typename NType>
NArray<NType>& NArray<NType>::sum(const NArray<NType>& B) {
	// Длина векторов одинакова
	NType* pB = B.getData();
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] += pB[i];
	}
	return *this;
}

template <typename NType>
NArray<NType>& NArray<NType>::mul(const NArray<NType>& B) {
	// Длина векторов одинакова
	NType* pB = B.getData();
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] *= pB[i];
	}
	return *this;
}

template <typename NType>
NArray<NType>& NArray<NType>::valsum(const NType& value) {
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] += value;
	}
	return *this;
}

template <typename NType>
NArray<NType>& NArray<NType>::valmul(const NType& value) {
	for (int i = 0; i < m_lenght; ++i) {
		m_data[i] *= value;
	}
	return *this;
}

template <typename NType>
NArray<NType>& NArray<NType>::matrix_mul(const NArray<NType>& array, const NMatrix<NType>& matrix) {
	NType value = 0;
	NType* p_array = array.getData();
	NType* p_matrix = matrix.getData();

	int len_row_matrix = matrix.getLenRow();
	int len_column_matrix = matrix.getLenColumn();
	int size_column_matrix = matrix.getSizeColumn();

	init(len_column_matrix, value);

	// Размер вектора совпадает с количеством строк матрицы!
	for (int i = 0; i < len_row_matrix; ++i) {
		for (int j = 0; j < len_column_matrix; ++j) {
			m_data[j] += p_array[i] * p_matrix[i * size_column_matrix + j];
		}
	}
	return *this;
}

template <typename NType>
NArray<NType>& NArray<NType>::matrix_mul(const NMatrix<NType>& matrix, const NArray<NType>& array) {
	NType value = 0;
	NType* p_matrix = matrix.getData();
	NType* p_array = array.getData();

	int len_row_matrix = matrix.getLenRow();
	int len_column_matrix = matrix.getLenColumn();
	int size_column_matrix = matrix.getSizeColumn();

	init(len_row_matrix, value);

	// Количество столбцов матрицы совпадает с размером вектора!
	for (int i = 0; i < len_row_matrix; ++i) {
		for (int j = 0; j < len_column_matrix; ++j) {
			m_data[i] += p_matrix[i * size_column_matrix + j] * p_array[j];
		}
	}
	return *this;
}

template <typename NType>
NArray<NType> NArray<NType>::operator+(const NType& value) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);

	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] + value, i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator-(const NType& value) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);

	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] - value, i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator*(const NType& value) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);

	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] * value, i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator/(const NType& value) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);

	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] / value, i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator+(const NArray<NType>& B) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);
	NType* pB = B.getData();
	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] + pB[i], i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator-(const NArray<NType>& B) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);
	NType* pB = B.getData();
	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] - pB[i], i);
	}
	return result;
}

template <typename NType>
NArray<NType> NArray<NType>::operator*(const NArray<NType>& B) const {
	NArray<NType> result;
	NType temp = 0;
	result.init(m_lenght, temp);
	NType* pB = B.getData();
	for (int i = 0; i < m_lenght; ++i) {
		result.set(m_data[i] * pB[i], i);
	}
	return result;
}

// 1 x 4 matrix * 4 x 5 matrix = 1 x 5 matrix
template <typename NType>
NArray<NType> NArray<NType>::operator*(const NMatrix<NType>& matrix) const {
	NType value = 0;
	NType* p_matrix = matrix.getData();

	int len_row_matrix = matrix.getLenRow();
	int len_column_matrix = matrix.getLenColumn();
	int size_column_matrix = matrix.getSizeColumn();

	NArray<NType> result;
	result.init(len_column_matrix, value);

	// Размер входного вектора совпадает с количеством строк матрицы!
	for (int j = 0; j < len_column_matrix; ++j) {
		value = 0;
		for (int i = 0; i < len_row_matrix; ++i) {
			value += m_data[i] * p_matrix[i * size_column_matrix + j];
		}
		result.set(value, j);
	}

	return result;
}

#endif  // NARRAY_H
