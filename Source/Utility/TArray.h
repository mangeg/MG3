//------------------------------------------------------------------------|
#pragma once
//------------------------------------------------------------------------|
namespace MG3
{
	template<class T>
	class TArray
	{
	public:
		TArray();
		TArray(const TArray& c);
		~TArray();

		TArray& operator=(const TArray& c);
		T& operator[](int i);
		const T& operator[](int i) const;

		void Add(const T& item);
		void Remove(int index);
		void Clear();
		bool Contains(const T& item) const;
		int Find(const T& item) const;
		bool InRange(int i) const;
		void Resize(int size) const;
		int Size();

	private:
		void _IncreaseSize();

		int	m_iSize;
		int m_iCapacity;
		T*	m_aData;
	};

#include "TArray.inl"
}