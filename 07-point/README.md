# Point — nhiều constructor (overloading) và `this(...)`

## 1. Đề bài
Xây dựng lớp `Point` (điểm trên mặt phẳng) với `x`, `y`, cung cấp:
- Constructor `Point(x, y)`: tạo điểm bất kỳ.
- Constructor `Point()`: tạo điểm gốc tọa độ `(0, 0)`.
- `distanceTo(Point other)`: khoảng cách Euclid tới điểm khác.

## 2. Ý tưởng
Một class có thể có **nhiều constructor** cùng tên, khác tham số (overloading) — người
dùng class chọn cách tạo object tiện nhất. Điểm mấu chốt: constructor rỗng **không chép
lại code** mà gọi `this(0, 0)` để ủy quyền cho constructor đầy đủ — logic khởi tạo (và
validate nếu có) chỉ nằm ở **một chỗ duy nhất**.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Point.java`](Point.java) · [`Point.cpp`](Point.cpp) · [`point.py`](point.py).

## 5. Thực tế đi làm
- Overloading constructor gặp khắp nơi: `new ArrayList<>()` và `new ArrayList<>(100)`,
  `new Scanner(System.in)` và `new Scanner(file)` — cùng class, nhiều cách khởi tạo.
- Quy tắc `this(...)` để dồn logic về một constructor "chính" giúp sửa một chỗ là xong;
  chép code khởi tạo ra nhiều constructor là nguồn bug khi hai bản chỉnh lệch nhau.

## 6. Self-check
```bash
javac Point.java && java Point                    # in "OK"
g++ -std=c++17 -o point Point.cpp && ./point   # in "OK"
python point.py                                   # in "OK"
```
