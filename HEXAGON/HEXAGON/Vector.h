#pragma once
#include <iostream>

template<typename _T>
class Vector {
private:
    _T* _data;
    int _capacity;             // Vector capacity
    int _size;                 // Current number of elements in vector
    float _sizeEnlarger;       // Coefficient increase

    void quickSort(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            quickSort(low, pivotIndex - 1);
            quickSort(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        _T pivot = _data[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (_data[j] <= pivot) {
                ++i;
                std::swap(_data[i], _data[j]);
            }
        }

        std::swap(_data[i + 1], _data[high]);
        return i + 1;
    }


public:
    Vector() : _size(0), _capacity(0), _sizeEnlarger(1.5), _data(nullptr) {}

    ~Vector() {
        clear();

    }
    void quickSort() {
        quickSort(0, _size - 1);
    }
    void insertionSort() {
        for (int i = 1; i < _size; ++i) {
            _T key = _data[i];
            int j = i - 1;
            while (j >= 0 && _data[j] > key) {
                _data[j + 1] = _data[j];
                j = j - 1;
            }
            _data[j + 1] = key;
        }
    }
    Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _sizeEnlarger(other._sizeEnlarger) {
        _data = new _T[_capacity];
        for (int i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    Vector(std::initializer_list<_T> _list) : _size(0), _capacity(0), _sizeEnlarger(1.5), _data(nullptr) {
        _capacity = _list.size();
        _data = new _T[_capacity];
        for (const auto& val : _list) {
            _data[_size++] = val;
        }
    }


    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] _data;
            _size = other._size;
            _capacity = other._capacity;
            _sizeEnlarger = other._sizeEnlarger;
            _data = new _T[_capacity];
            for (int i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    void push_back(const _T& data) {
        if (_size >= _capacity) {
            _capacity = static_cast<int>(_capacity * _sizeEnlarger) + 1;
            _T* _tempData = new _T[_capacity];
            for (int _index = 0; _index < _size; ++_index) {
                _tempData[_index] = _data[_index];
            }
            delete[] _data;
            _data = _tempData;
        }
        _data[_size++] = data;
    }

    void push_back_with_Sort(const _T& data) {
        if (_size >= _capacity) {
            _capacity = static_cast<int>(_capacity * _sizeEnlarger) + 1;
            _T* _tempData = new _T[_capacity];
            for (int _index = 0; _index < _size; ++_index) {
                _tempData[_index] = _data[_index];
            }
            delete[] _data;
            _data = _tempData;
        }
        _data[_size++] = data;
        quickSort();
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back() called on an empty vector");
        }
        --_size;
        if (_size < _capacity / 2) {
            _capacity = static_cast<int>(_size * _sizeEnlarger + 1);
            _T* _tempData = new _T[_capacity];
            for (int _index = 0; _index < _size; ++_index) {
                _tempData[_index] = _data[_index];
            }
            delete[] _data;
            _data = _tempData;
        }
    }
    void erase(int index) {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("erase() called with an invalid index");
        }
        if (_size == 1) {
            // если вектор состоит из одного элемента, просто освобождаем память
            clear();
            return;
        }
        // Сдвигаем элементы после удаляемого элемента влево
        for (int i = index; i < _size - 1; i++) {
            _data[i] = _data[i + 1];
        }

        // Уменьшаем размер вектора
        --_size;

        // Проверяем, нужно ли уменьшить емкость вектора
        if (_size < _capacity / 2) {
            _capacity = static_cast<int>(_size * _sizeEnlarger + 1);
            _T* _tempData = new _T[_capacity];
            for (int _index = 0; _index < _size; ++_index) {
                _tempData[_index] = _data[_index];
            }
            delete[] _data;
            _data = _tempData;
        }
    }
    void clear() {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    int size() const {
        return _size;
    }
    int capacity() {
        return _capacity;
    }
    bool empty() const {
        return _size == 0;
    }

    _T* begin() {
        return _data;
    }

    _T* end() {
        return _data + _size;
    }

    const _T* begin() const {
        return _data;
    }

    const _T* end() const {
        return _data + _size;
    }

    _T& operator[](int index) const {
        if (index < 0 || index >= _size) {
            throw std::out_of_range("operator [] called out of range");
        }
        return _data[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector<_T>& vec) {
        os << "[ ";
        for (int i = 0; i < vec._size; ++i) {
            os << vec._data[i] << ' ';
        }
        os << "]";
        return os;
    }
};
