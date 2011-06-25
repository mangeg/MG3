//------------------------------------------------------------------------|
using namespace MG3;
//------------------------------------------------------------------------|
template <class T>
TArray<T>::TArray()
{
	m_iCapacity = 5;
	m_iSize = 0;
	
	m_aData = new T[m_iCapacity];
}
//------------------------------------------------------------------------|
template <class T>
TArray<T>::TArray(const TArray& c)
{
	m_aData = NULL;
	*this = c;
}
//------------------------------------------------------------------------|
template <class T>
TArray<T>::~TArray()
{
	delete [] m_aData;
}
//------------------------------------------------------------------------|
template <class T>
TArray<T>& TArray<T>::operator=(const TArray& c)
{
	m_iCapacity = c.m_iCapacity;
	m_iSize = c.m_iSize;

	delete [] m_aData;

	m_aData = new T[m_iCapacity];

	for (int i = 0; i < m_iCapacity; i++)
	{
		m_aData[i] = c.m_aData[i];
	}

	return *this;
}
//------------------------------------------------------------------------|
template <class T>
void TArray<T>::Add(const T& item)
{
	if(m_iCapacity == m_iSize)
	{
		_IncreaseSize();
	}
	m_aData[m_iSize++] = item;
}
//------------------------------------------------------------------------|
template <class T>
void TArray<T>::Remove(int index)
{
	if(index >= 0 && index < m_iSize)
	{
		for(int i = index; i < m_iSize - 1; i++)
		{
			m_aData[i] = m_aData[i + 1];
		}
		m_iSize--;
	}
}
//------------------------------------------------------------------------|
template <class T>
int TArray<T>::Size()
{
	return m_iSize;
}
//------------------------------------------------------------------------|
template <class T>
void TArray<T>::Clear()
{
	m_iSize = 0;
}
//------------------------------------------------------------------------|
template <class T>
bool TArray<T>::Contains(const T& item) const
{
	for(int i = 0; i < m_iSize; i++)
	{
		if(m_aData[i] == item)
			return true;
	}
	return false;
}
//------------------------------------------------------------------------|
template <class T>
int TArray<T>::Find(const T& item) const
{
	for(int i = 0; i < m_iSize; i++)
	{
		if(m_aData[i] == item)
			return i;
	}
	return -1;
}
//------------------------------------------------------------------------|
template <class T>
bool TArray<T>::InRange(int i) const
{
	return (index >= 0 && index < m_iSize);
}
//--------------------------------------------------------------------------------
template <class T>
void TArray<T>::Resize( int size ) const
{
	int elements = min( size, m_iQuantity );

	T* newArray = new T[size];
	for ( int i = 0; i < elements; i++ )
		newArray[i] = m_aData[i];

	m_iSize = elements;
	m_iCapacity = size;

	delete [] m_aData;
	m_aData = aNewArray;
}

//------------------------------------------------------------------------|
template <class T>
T& TArray<T>::operator [](int i)
{
	if(i < 0)
		i = 0;
	if(i > m_iSize)
		i = m_iSize - 1;

	return m_aData[i];
}
//------------------------------------------------------------------------|
template <class T>
const T& TArray<T>::operator [](int i) const
{
	if(i < 0)
		i = 0;
	if(i > m_iSize)
		i = m_iSize - 1;

	return m_aData[i];
}

template <class T>
void TArray<T>::_IncreaseSize()
{
	m_iCapacity = m_iCapacity * 2 + 1;

	T* newArray = new T[m_iCapacity];
	for(int i = 0; i < m_iSize; i++)
		newArray[i] = m_aData[i];

	delete [] m_aData;
	m_aData = newArray;
}

