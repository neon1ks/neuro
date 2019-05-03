#ifndef NARRAY_H
#define NARRAY_H

template <typename NType>
class NArray {
   public:
	NArray();
	NArray(NArray<NType>& obj);  ///< Конструктор копирования
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

	void set(NType element, int pos);
	NType get(int pos);

	void setBlock(int block);

	int getSize();
	int getLenght();
	int getBlock();

	void resize(int size);
	NType* getData();
};

#endif  // NARRAY_H
