#pragma once

#ifndef NMATRIX_H
#define NMATRIX_H

#include "narray.h"

template <typename NType>
class NArray;

template <typename NType>
class NMatrix {
   public:
	NMatrix();
	NMatrix(NMatrix<NType>& obj);
	NMatrix<NType>& operator=(const NMatrix<NType>& obj);
	~NMatrix();

   protected:
	int m_size_row;
	int m_size_column;
	int m_len_row;
	int m_len_column;
	NType* m_data;  ///< Указатель на хранящиеся данные

   public:
	void init(int len_row, int len_column, const NType& value);  ///< Инициализация матрицы значением (OK)

	void addRow(int pos_row, const NType& value);        ///< Добавление строки в матрицу, существующие сдвигаются (OK)
	void delRow(int pos_row);                            ///< Удаление строки из матрицу, существующие сдвигаются (OK)
	void addColumn(int pos_column, const NType& value);  ///< Добавление строки в матрицу, существующие сдвигаются (OK)
	void delColumn(int pos_column);                      ///< Удаление сстолбца из матрицу, существующие сдвигаются (OK)

	void set(const NType& value, int pos_row, int pos_column);  ///< Установка значения одному элементу (OK)
	NType get(int pos_row, int pos_column);                     ///< Получение значения одного элемента (OK)

	int getSizeRow() const;     ///< Получение выделенного размера данных для строк (OK)
	int getSizeColumn() const;  ///< Получение выделенного размера данных для столбцов (OK)
	int getLenRow() const;      ///< Получение количества строк (OK)
	int getLenColumn() const;   ///< Получение количества столбцов (OK)
	NType* getData() const;     ///< Получение указателя на данные (OK

	void resize(int size_row, int size_column);  ///< Изменение размера доступной памяти для матрицы (OK)

   public:
	// Возвращаем *this
	NMatrix<NType>& valsum(const NType& value);                             ///< Сложение матрицы с числом
	NMatrix<NType>& valmul(const NType& value);                             ///< Умножение матрицы на число
	NMatrix<NType>& sum(const NMatrix<NType>& B);                           ///< Сложение матриц
	NMatrix<NType>& mul(const NMatrix<NType>& A, const NMatrix<NType>& B);  ///< Умножение матриц
	NMatrix<NType>& matmul(const NMatrix<NType>& B);                        ///< Математическое умножение матриц

	NMatrix<NType> operator+(const NType& value) const;  // (OK)
	NMatrix<NType> operator-(const NType& value) const;  // (OK)
	NMatrix<NType> operator*(const NType& value) const;  // (OK)
	NMatrix<NType> operator/(const NType& value) const;  // (OK)

	NMatrix<NType> operator+(const NMatrix<NType>& B) const;  // (OK)
	NMatrix<NType> operator-(const NMatrix<NType>& B) const;  // (OK)
	NMatrix<NType> operator*(const NMatrix<NType>& B) const;  // (OK)

	NArray<NType> operator*(const NArray<NType>& B) const;  // (OK)
};

template <typename NType>
NMatrix<NType>::NMatrix()
    : m_size_row(0)
    , m_size_column(0)
    , m_len_row(0)
    , m_len_column(0)
    , m_data(nullptr) {
}

template <typename NType>
NMatrix<NType>::NMatrix(NMatrix<NType>& obj) {
	m_size_row = obj.getSizeRow();
	m_size_column = obj.getLenColumn();
	m_len_row = obj.getSizeRow();
	m_len_column = obj.getSizeColumn();

	m_data = new NType[m_size_row * m_size_column];

	auto p = obj.getData();
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = p[i * m_size_column + j];
		}
	}
}

// Assignment operator
template <typename NType>
NMatrix<NType>& NMatrix<NType>::operator=(const NMatrix<NType>& obj) {
	if (this != &obj) {
		if (obj.getSizeRow() != m_size_row || obj.getSizeColumn() != m_size_column) {
			if (m_data != nullptr) {
				delete[] m_data;
			}
			m_size_row = 0;
			m_size_column = 0;
			m_data = nullptr;

			m_size_row = obj.getSizeRow();
			m_size_column = obj.getSizeColumn();
			m_data = new NType[m_size_row * m_size_column];
		}
		m_len_row = obj.getLenRow();
		m_len_column = obj.getLenColumn();
		auto p = obj.getData();
		for (int i = 0; i < m_len_row; ++i) {
			for (int j = 0; j < m_len_column; ++j) {
				m_data[i * m_size_column + j] = p[i * m_size_column + j];
			}
		}
	}
	return *this;
}

template <typename NType>
NMatrix<NType>::~NMatrix() {
	if (m_data != nullptr) {
		delete[] m_data;
	}
}

template <typename NType>
void NMatrix<NType>::init(int len_row, int len_column, const NType& value) {
	if (len_row > m_size_row) {
		if (len_column > m_size_column) {
			resize(len_row, len_column);
		} else {
			resize(len_row, m_size_column);
		}
	} else {
		if (len_column > m_size_column) {
			resize(m_size_row, len_column);
		}
	}

	for (int i = 0; i < len_row; ++i) {
		for (int j = 0; j < len_column; ++j) {
			m_data[i * m_size_column + j] = value;
		}
	}

	for (int i = len_row; i < m_size_row; ++i) {
		for (int j = len_column; j < m_size_column; ++j) {
			m_data[i * m_size_column + j] = 0;
		}
	}

	m_len_row = len_row;
	m_len_column = len_column;
}

template <typename NType>
void NMatrix<NType>::addRow(int pos_row, const NType& value) {
	if (pos_row >= m_size_row) {
		resize(pos_row + 1, m_size_column);
	}

	if (pos_row < m_len_row) {
		for (int i = m_len_row; i > pos_row; --i) {
			for (int j = 0; j < m_len_column; ++j) {
				m_data[i * m_size_column + j] = m_data[(i - 1) * m_size_column + j];
			}
		}
		for (int j = 0; j < m_len_column; ++j) {
			m_data[pos_row * m_size_column + j] = value;
		}
		++m_len_row;
	} else {
		for (int i = m_len_row; i < pos_row + 1; ++i) {
			for (int j = 0; j < m_len_column; ++j) {
				m_data[i * m_size_column + j] = value;
			}
		}
		m_len_row = pos_row + 1;
	}
}

template <typename NType>
void NMatrix<NType>::delRow(int pos_row) {
	if (pos_row >= m_len_row) {
		return;
	}
	--m_len_row;
	for (int i = pos_row; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[(i + 1) * m_size_column + j];
		}
	}
}

template <typename NType>
void NMatrix<NType>::addColumn(int pos_column, const NType& value) {
	if (pos_column >= m_size_column) {
		resize(m_size_row, pos_column + 1);
	}

	if (pos_column < m_len_column) {
		for (int i = 0; i < m_len_row; ++i) {
			for (int j = m_len_column; j > pos_column; --j) {
				m_data[i * m_size_column + j] = m_data[i * m_size_column + j - 1];
			}
		}
		for (int i = 0; i < m_len_row; ++i) {
			m_data[i * m_size_column + pos_column] = value;
		}
		++m_len_column;
	} else {
		for (int i = 0; i < m_len_row; ++i) {
			for (int j = m_len_column; j < pos_column + 1; ++j) {
				m_data[i * m_size_column + j] = value;
			}
		}
		m_len_column = pos_column + 1;
	}
}

template <typename NType>
void NMatrix<NType>::delColumn(int pos_column) {
	if (pos_column >= m_len_column) {
		return;
	}
	--m_len_column;
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = pos_column; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j + 1];
		}
	}
}

template <typename NType>
void NMatrix<NType>::set(const NType& value, int pos_row, int pos_column) {
	if (pos_row >= 0 && pos_row < m_len_row && pos_column >= 0 && pos_column < m_len_column) {
		m_data[pos_row * m_size_column + pos_column] = value;
	}
}

template <typename NType>
NType NMatrix<NType>::get(int pos_row, int pos_column) {
	// TODO - кинуть исключение, если нет такого элемента
	return m_data[pos_row * m_size_column + pos_column];
}

template <typename NType>
int NMatrix<NType>::getSizeRow() const {
	return m_size_row;
}

template <typename NType>
int NMatrix<NType>::getSizeColumn() const {
	return m_size_column;
}

template <typename NType>
int NMatrix<NType>::getLenRow() const {
	return m_len_row;
}

template <typename NType>
int NMatrix<NType>::getLenColumn() const {
	return m_len_column;
}

template <typename NType>
NType* NMatrix<NType>::getData() const {
	return m_data;
}

template <typename NType>
void NMatrix<NType>::resize(int size_row, int size_column) {
	size_row = size_row > m_size_row ? size_row : m_size_row;
	size_column = size_column > m_size_column ? size_column : m_size_column;
	if (m_data == nullptr) {
		m_data = new NType[size_column * size_row];
		m_size_row = size_row;
		m_size_column = size_column;
	} else if (m_size_row != size_row || m_size_column != size_column) {
		auto p = m_data;
		m_data = new NType[size_column * size_row];
		for (int i = 0; i < m_len_row; ++i) {
			for (int j = 0; j < m_len_column; ++j) {
				m_data[i * size_column + j] = p[i * m_size_column + j];
			}
		}
		m_size_row = size_row;
		m_size_column = size_column;
		delete[] p;
	}
}

template <typename NType>
NMatrix<NType>& NMatrix<NType>::valsum(const NType& value) {
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j] + value;
		}
	}
	return *this;
}

template <typename NType>
NMatrix<NType>& NMatrix<NType>::valmul(const NType& value) {
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j] * value;
		}
	}
	return *this;
}

template <typename NType>
NMatrix<NType>& NMatrix<NType>::sum(const NMatrix<NType>& B) {
	NType* pB = B.getData();
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j] + pB[i * m_size_column + j];
		}
	}
	return *this;
}

// 3 x 4 matrix * 4 x 5 matrix = 3 x 5 matrix
//C_ij = сумма по к(a_ik * b_kj)
// i - номер строки первой матрицы
// j - номер столбка второй матрицы
template <typename NType>
NMatrix<NType>& NMatrix<NType>::mul(const NMatrix<NType>& A, const NMatrix<NType>& B) {
	NType value = 0;
	NType* pA = A.getData();
	NType* pB = B.getData();

	int len_column_A = A.getLenColumn();
	int size_column_A = A.getSizeColumn();
	int size_column_B = B.getSizeColumn();

	init(A.getLenRow(), B.getLenColumn(), value);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			value = 0;
			for (int k = 0; k < len_column_A; ++k) {
				value += pA[i * size_column_A + k] * pB[k * size_column_B + j];
			}
			m_data[i * m_size_column + j] = value;
		}
	}

	return *this;
}

template <typename NType>
NMatrix<NType>& NMatrix<NType>::matmul(const NMatrix<NType>& B) {
	NType* pB = B.getData();
	int size_column_B = B.getSizeColumn();
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j] * pB[i * size_column_B + j];
		}
	}
	return *this;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator+(const NType& value) const {
	NMatrix<NType> result;
	NType temp = 0;
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] + value, i, j);
		}
	}
	return result;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator-(const NType& value) const {
	NMatrix<NType> result;
	NType temp = 0;
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] - value, i, j);
		}
	}
	return result;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator*(const NType& value) const {
	NMatrix<NType> result;
	NType temp = 0;
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] * value, i, j);
		}
	}
	return result;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator/(const NType& value) const {
	NMatrix<NType> result;
	NType temp = 0;
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] / value, i, j);
		}
	}
	return result;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator+(const NMatrix<NType>& B) const {
	NMatrix<NType> result;
	NType temp = 0;
	NType* pB = B.getData();
	int size_column_B = B.getSizeColumn();
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] + pB[i * size_column_B + j], i, j);
		}
	}
	return result;
}

template <typename NType>
NMatrix<NType> NMatrix<NType>::operator-(const NMatrix<NType>& B) const {
	NMatrix<NType> result;
	NType temp = 0;
	NType* pB = B.getData();
	int size_column_B = B.getSizeColumn();
	result.init(m_len_row, m_len_column, temp);
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < m_len_column; ++j) {
			result.set(m_data[i * m_size_column + j] - pB[i * size_column_B + j], i, j);
		}
	}
	return result;
}

// 3 x 4 matrix * 4 x 5 matrix = 3 x 5 matrix
//C_ij = сумма по к(a_ik * b_kj)
// i - номер строки первой матрицы
// j - номер столбка второй матрицы
template <typename NType>
NMatrix<NType> NMatrix<NType>::operator*(const NMatrix<NType>& B) const {
	NMatrix<NType> result;
	NType temp = 0;
	NType* pB = B.getData();
	int size_column_B = B.getSizeColumn();
	int len_column_B = B.getLenColumn();
	result.init(m_len_row, len_column_B, temp);

	// Количество столбцов первой матрицы равно количество строк второй матрицы!!!
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = 0; j < len_column_B; ++j) {
			temp = 0;
			for (int k = 0; k < m_len_column; ++k) {
				temp += m_data[i * m_size_column + k] * pB[k * size_column_B + j];
			}
			result.set(temp, i, j);
		}
	}

	return result;
}

template <typename NType>
NArray<NType> NMatrix<NType>::operator*(const NArray<NType>& array) const {
	NArray<NType> result;
	NType value = 0;
	NType temp = 0;
	NType* p_array = array.getData();
	result.init(m_len_row, value);

	// Количество столбцов матрицы совпадает с размером вектора!
	for (int i = 0; i < m_len_row; ++i) {
		temp = 0;
		for (int j = 0; j < m_len_column; ++j) {
			temp += m_data[i * m_size_column + j] * p_array[j];
		}
		result.set(temp, i);
	}
	return result;
}

#endif  // NMATRIX_H
