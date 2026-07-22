# Rectangle — Class & Object cơ bản

## 1. Đề bài
Xây dựng lớp `Rectangle` (hình chữ nhật) với hai cạnh `width`, `height`, cung cấp:
- `area()`: tính diện tích.
- `perimeter()`: tính chu vi.

- **Ràng buộc:** cạnh phải luôn `> 0` khi tạo object.

## 2. Ý tưởng
Đây là bài đầu tiên làm quen với **class** (khuôn mẫu) và **object** (thực thể tạo ra từ
khuôn mẫu đó). Mỗi object `Rectangle` có dữ liệu riêng (`width`, `height`) nhưng dùng chung
logic tính toán viết một lần trong class. `final` trên field vì hình chữ nhật một khi tạo
xong không đổi kích thước — hạn chế sửa nhầm từ bên ngoài.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Rectangle.java`](Rectangle.java) · [`Rectangle.cpp`](Rectangle.cpp) · [`rectangle.py`](rectangle.py).

## 5. Thực tế đi làm
- Constructor kiểm tra điều kiện hợp lệ (`width, height > 0`) ngay từ đầu — tránh object
  "nửa vời" tồn tại trong hệ thống.
- Đây là nền cho các bài sau: một khi đã quen tạo class đơn giản, bước tiếp theo là học
  cách **giấu** dữ liệu (đóng gói) và **tái sử dụng** giữa các class (kế thừa).

## 6. Self-check
```bash
javac Rectangle.java && java Rectangle                    # in "OK"
g++ -std=c++17 -o rectangle Rectangle.cpp && ./rectangle   # in "OK"
python rectangle.py                                   # in "OK"
```
