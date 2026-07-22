# Counter — object có trạng thái thay đổi theo thời gian

## 1. Đề bài
Xây dựng lớp `Counter` với `increment()`, `decrement()`, `reset()`, `getValue()`.
- **Ràng buộc:** không được giảm xuống dưới 0.

## 2. Ý tưởng
Khác với `Rectangle`/`Circle` (dữ liệu cố định từ lúc tạo), `Counter` minh họa object có
**trạng thái (state) thay đổi** qua các lần gọi phương thức — gọi `increment()` nhiều lần
làm `value` tăng dần, và mỗi object `Counter` giữ trạng thái **độc lập** với object khác
cùng class.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Counter.java`](Counter.java) · [`Counter.cpp`](Counter.cpp) · [`counter.py`](counter.py).

## 5. Thực tế đi làm
- Đây là ý tưởng lõi của mọi object có state: giỏ hàng, phiên đăng nhập, kết nối mạng...
  đều là "dữ liệu thay đổi theo thời gian, được đóng gói trong object".
- Cạm bẫy hay gặp: nhầm lẫn giữa biến `static` (dùng chung mọi object) và field thường
  (mỗi object một bản riêng) — test `other` độc lập với `c` ở cuối bài để làm rõ điều này.

## 6. Self-check
```bash
javac Counter.java && java Counter                    # in "OK"
g++ -std=c++17 -o counter Counter.cpp && ./counter   # in "OK"
python counter.py                                   # in "OK"
```
