#include <iostream>
using namespace std;

template <class T>
class DynamicArray
{
public:
	DynamicArray(int size = 2) : lSize(0), phSize(size), arr(new T[size]) {}

	DynamicArray(const DynamicArray& other) : arr(nullptr) {
		*this = other;
	}
	~DynamicArray() {
		delete[] arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			lSize = other.lSize;
			phSize = other.phSize;
			delete[] arr;
			arr = new T[phSize];
			for (int i = 0; i < lSize; i++)
				arr[i] = other.arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const { return arr[i]; }
	T& operator[](int i) { return arr[i]; }

	void push_back(const T& value) {
		if (lSize == phSize)
			resize();
		arr[lSize++] = value;
	}

	const T& front()    const { return arr[0]; }
	int      size()     const { return lSize; }
	int      capacity() const { return phSize; }
	bool     empty()    const { return lSize == 0; }
	void     clear() { lSize = 0; }

	// standard STL iterator implementation:
	// (no duplication for const)
	template <bool is_const>
	class base_iterator
	{
	public:
		using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;

		using iterator_category = std::bidirectional_iterator_tag;
		// other options exist, e.g., std::forward_iterator_tag
		using different_type = std::ptrdiff_t;
		using value_type = std::conditional_t<is_const, const T, T>;
		using pointer = value_type*;
		using reference = value_type&;

		base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

		// we want to use the default copy constructor
		base_iterator(const base_iterator&) = default;

		// and the default assignment operator
		constexpr base_iterator& operator=(const base_iterator&) = default;

		// we want to allow construction of const_iterator from iterator
		friend class base_iterator<true>;
		template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
		base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}

		// comparison with another iterator
		bool operator==(const base_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const base_iterator& other) const {
			return !(*this == other);
		}

		// smart-pointer iterator methods
		reference operator*() {
			return _da->arr[_i];
		}
		pointer operator->() {
			return &_da->arr[_i];
		}

		// increment-decrement iterator methods
		base_iterator& operator++() {
			++_i;
			return *this;
		}
		base_iterator operator++(int) {
			base_iterator temp(*this);
			++_i;
			return temp;
		}
		base_iterator& operator--() {
			--_i;
			return *this;
		}
		base_iterator operator--(int) {
			base_iterator temp(*this);
			--_i;
			return temp;
		}
	private:
		ds_type* _da;
		int			_i;
	};
	using iterator = base_iterator<false>;
	using const_iterator = base_iterator<true>;

	// should return iterator to new element
	void insert(const iterator& pos, const T& val) {
		if (lSize == phSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++lSize;
	}

	// returns iterator to first element after deleted element/s
	iterator erase(const iterator& pos) {
		int index = 0, write = 0;
		iterator curPos = pos ;
		if (pos == end())
			return end();
		T* newArr = new T[lSize-1];
		for (iterator iter = begin(); iter != curPos; iter++) {
			newArr[write] = arr[index];
			index++;
			write++;
		}
		index++;
		for (iterator iter = ++curPos; iter != end() --; iter++) {
			newArr[write] = arr[index];
			index++;
			write++;
		}
		delete[]arr;
		arr = newArr;
		lSize--;
		return curPos;
	}
	iterator erase(const iterator& first, const iterator& last) {
		int index = 0, write = 0,counter=0;
		iterator curPos = first;
		iterator LastPos = last;
		if (first == last)
			return end();
		T* newArr = new T[lSize - 1];
		for (iterator iter = begin(); iter != curPos; iter++) {
			newArr[write] = arr[index];
			index++;
			write++;
		}
		while (curPos != LastPos) {
			curPos++;
			counter++;
		}
		index += counter;
		for (iterator iter =curPos; iter != end(); iter++) {
			newArr[write] = arr[index];
			index++;
			write++;
		}
		delete[]arr;
		arr = newArr;
		lSize-=counter;
		return curPos;
	}
	
	
	iterator begin() {
		return iterator(*this, 0);
	}
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}

	iterator end() {
		return iterator(*this, lSize);
	}
	const_iterator cend()const {
		return const_iterator(*this, lSize);
	}

	iterator rbegin() {
		return iterator(*this, lSize);
	}
	iterator rend() {
		return iterator(*this, 0);
	}


	void print() const {
		for (int i = 0; i < lSize; i++)
			cout << arr[i] << " ";
		cout << endl;
	}

private:
	void resize() {
		phSize *= 2;
		T* temp = new T[phSize];
		for (int i = 0; i < lSize; i++)
			temp[i] = arr[i];

		delete[] arr;
		arr = temp;
	}

	T* arr;
	int lSize;
	int phSize;
};