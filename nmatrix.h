#ifndef NMATRIX_H
#define NMATRIX_H

template <typename NType>
class NMatrix {
   public:
	NMatrix();
	NMatrix(NMatrix<NType>& obj);
	~NMatrix();

   protected:
	int m_size_row;
	int m_size_column;
	int m_len_row;
	int m_len_column;
	NType* m_data;  ///< Указатель на хранящиеся данные

   public:
	void init(int len_row, int len_column, const NType& value);
	void addRow(int pos_row, const NType& value);
	void delRow(int pos_row);
	void addColumn(int pos_column, const NType& value);
	void delColumn(int pos_column);
	void set(const NType& value, int pos_row, int pos_column);
	NType get(int pos_row, int pos_column);

	int getSizeRow() const;
	int getSizeColumn() const;
	int getLenRow() const;
	int getLenColumn() const;
	NType* getData() const;

	void resize(int size_row, int size_column);
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
	m_len_row = len_row;
	m_len_column = len_column;
}

template <typename NType>
void NMatrix<NType>::addRow(int pos_row, const NType& value) {
	if (pos_row >= m_size_row) {
		resize(m_size_row + 1, m_size_column);
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
		for (int i = m_len_row; i < pos_row; ++i) {
			for (int j = 0; j < m_len_column; ++j) {
				m_data[(i + 1) * m_size_column + j] = value;
			}
		}
		m_len_row = pos_row + 1;
	}
}

template <typename NType>
void NMatrix<NType>::delRow(int pos_row) {
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
		resize(m_size_row, m_size_column + 1);
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
			for (int j = m_len_column; j < pos_column; ++j) {
				m_data[i * m_size_column + j + 1] = value;
			}
		}
		m_len_column = pos_column + 1;
	}
}

template <typename NType>
void NMatrix<NType>::delColumn(int pos_column) {
	--m_len_column;
	for (int i = 0; i < m_len_row; ++i) {
		for (int j = pos_column; j < m_len_column; ++j) {
			m_data[i * m_size_column + j] = m_data[i * m_size_column + j + 1];
		}
	}
}

template <typename NType>
void NMatrix<NType>::set(const NType& value, int pos_row, int pos_column) {
	if (pos_row < m_len_row && pos_column < m_len_column) {
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

#endif  // NMATRIX_H
