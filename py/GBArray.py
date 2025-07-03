class GBArray:
    def __init__(self, length):
        if length <= 0:
            raise ValueError("Length must be a positive integer")
        self._length = length
        self._data = [None] * length  # 초기화된 고정 길이 배열

    def __getitem__(self, key):
        """
        정수 인덱스 또는 슬라이스를 사용하여 항목을 가져옵니다.
        - 정수 인덱스: 단일 항목을 반환합니다.
        - 슬라이스: 슬라이싱된 결과를 담은 *새로운* GBArray 객체를 반환합니다.
        """
        if isinstance(key, int):
            # 정수 인덱스 처리 (기존과 동일)
            if not 0 <= key < self._length:
                raise IndexError(f"Index {key} out of bounds for GBArray of length {self._length}")
            return self._data[key]
        
        elif isinstance(key, slice):
            # 슬라이스 처리: 내부 리스트를 슬라이싱하여 새로운 GBArray를 만듭니다.
            sliced_data = self._data[key]
            new_array = GBArray(len(sliced_data))
            new_array._data = sliced_data # 내부 데이터를 직접 설정
            return new_array
        
        else:
            raise TypeError("GBArray indices must be integers or slices")

    def __setitem__(self, key, value):
        """
        정수 인덱스 또는 슬라이스를 사용하여 항목을 설정합니다.
        - 슬라이스 할당 시, 슬라이스의 길이와 할당하려는 시퀀스의 길이가
          반드시 동일해야 합니다. (GBArray의 고정 길이 유지를 위함)
        """
        if isinstance(key, int):
            # 정수 인덱스 처리 (기존과 동일)
            if not 0 <= key < self._length:
                raise IndexError(f"Index {key} out of bounds for GBArray of length {self._length}")
            self._data[key] = value
            
        elif isinstance(key, slice):
            # 슬라이스 할당 처리
            # 1. 슬라이스에 해당하는 실제 인덱스 범위를 계산합니다.
            #    slice.indices(length)는 음수 인덱스, None 등을 실제 값으로 변환해줍니다.
            start, stop, step = key.indices(self._length)
            slice_len = len(range(start, stop, step))

            # 2. 할당하려는 값(value)의 길이가 슬라이스 범위의 길이와 다른지 확인합니다.
            try:
                value_len = len(value)
            except TypeError:
                raise TypeError("can only assign an iterable to a slice")

            if slice_len != value_len:
                raise ValueError(
                    f"attempt to assign sequence of size {value_len} to slice of size {slice_len}"
                )

            # 3. 길이가 같다면 안전하게 할당합니다.
            self._data[key] = value
            
        else:
            raise TypeError("GBArray indices must be integers or slices")
    
    def __len__(self):
        return self._length

    def __repr__(self):
        return f"GBArray({self._data})"

if __name__ == "__main__":
    arr = GBArray(5)
    arr[0] = 42
    arr[1] = 13
    print(arr[0])  # 출력: 42
    print(len(arr))  # 출력: 5
    print(arr)  # 출력: GBArray([42, 13, None, None, None])

    arr[5] = 7  # IndexError: Index 5 out of bounds for GBArray of length 5