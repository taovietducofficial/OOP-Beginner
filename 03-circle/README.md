# Circle — hằng số dùng chung giữa các object (`static`)

## 1. Đề bài
Xây dựng lớp `Circle` (hình tròn) với `radius`, cung cấp:
- `area()`: diện tích = `PI * r^2`.
- `circumference()`: chu vi = `2 * PI * r`.

- **Ràng buộc:** `radius > 0`.

## 2. Ý tưởng
`PI` là hằng số toán học **giống nhau cho mọi object** `Circle` — không cần mỗi object tự
lưu một bản riêng. Khai báo `static final` để nó thuộc về class (dùng chung, không đổi),
khác với `radius` là `private final` vì mỗi object có bán kính riêng của mình.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Circle.java`](Circle.java) · [`Circle.cpp`](Circle.cpp) · [`circle.py`](circle.py).

## 5. Thực tế đi làm
- Phân biệt `static` (thuộc về class, dùng chung) và instance field (thuộc về từng object)
  là nền tảng bắt buộc trước khi học `static method`, `singleton`, hay biến đếm toàn cục.
- Với số thực, so sánh bằng `==` dễ sai do sai số dấu phẩy động — self-check dùng
  `Math.abs(a - b) < epsilon` thay vì so bằng tuyệt đối.

## 6. Self-check
```bash
javac Circle.java && java Circle                    # in "OK"
g++ -std=c++17 -o circle Circle.cpp && ./circle   # in "OK"
python circle.py                                   # in "OK"
```
