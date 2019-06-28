#ifndef NMATRIX_H
#define NMATRIX_H

template <typename NType>
class NMatrix {
   public:
	NMatrix();
	NMatrix(NMatrix<NType>& obj);
	~NMatrix();

   protected:
	NType* m_data;  ///< Указатель на хранящиеся данные
	int m_len_row;
	int m_len_column;
	int m_size_row;
	int m_size_column;

   public:
	void init(int len_row, int len_column, const NType& value);
	void addRow(int pos_row);
	void delRow(int pos_row);
	void addColumn(int pos_column);
	void delColumn(int pos_column);
	void set(const NType& value, int pos_row, int pos_column);
	NType get(int pos_row, int pos_column);

	NType* getData();

	void resize(int size_row, int size_column);

	int getLenRow();
	int getLenColumn();
	int getSizeRow();
	int getSizeColumn();
};

template <typename NType>
NMatrix<NType>::NMatrix()
    : m_size_row(0)
    , m_size_column(0)
    , m_len_row(0)
    , m_len_column(0)
    , m_data(nullptr) {
}

#endif  // NMATRIX_H
