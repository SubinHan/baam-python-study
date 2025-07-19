#pragma once

template <typename T>
class Array {
private:
    T* _data;
    int _length;

public:
    // 생성자: 주어진 길이만큼 배열을 동적 할당합니다.
    GBArray(int length) : _length(length) {
        if (length <= 0) {
            throw std::invalid_argument("Length must be a positive integer");
        }
        _data = new T[length];
    }

    // 복사 생성자
    GBArray(const GBArray& other) : _length(other._length) {
        _data = new T[_length];
        for (int i = 0; i < _length; ++i) {
            _data[i] = other._data[i];
        }
    }

    // 소멸자: 동적 할당된 메모리를 해제합니다.
    ~GBArray() {
        delete[] _data;
    }

    // 배열의 길이를 반환합니다.
    int size() const {
        return _length;
    }

    // 인덱스를 이용한 배열 원소 접근 (const 버전)
    const T& operator[](int index) const {
        if (index < 0 || index >= _length) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    // 인덱스를 이용한 배열 원소 접근
    T& operator[](int index) {
        if (index < 0 || index >= _length) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
};