# Classroom — một class quản lý tập hợp nhiều object khác

## 1. Đề bài
Xây dựng lớp `Student` (`name`, `score` từ 0-10) và lớp `Classroom` (`name`), cung cấp:
- `addStudent(Student)`: thêm học sinh vào lớp.
- `size()`: số học sinh hiện có.
- `averageScore()`: điểm trung bình cả lớp (lớp rỗng → 0).
- `topStudent()`: tên học sinh điểm cao nhất (lớp rỗng → báo lỗi).

## 2. Ý tưởng
Bài 12 chuyển từ "1 object chứa dữ liệu đơn" sang **1 object chứa nhiều object khác cùng
loại**: `Classroom` giữ một danh sách `Student` bên trong. Các phương thức tổng hợp
(`averageScore`, `topStudent`) không có công thức đóng — chúng phải **duyệt qua từng
phần tử** trong tập hợp và gộp kết quả lại. Đây là hình dạng phổ biến nhất của dữ liệu
thực tế: một thực thể "cha" luôn đi kèm nhiều thực thể "con".

## 3. Độ phức tạp
- `addStudent`, `size`: `O(1)`.
- `averageScore`, `topStudent`: `O(n)` với `n` là số học sinh — phải duyệt hết danh sách.

## 4. Lời giải
Xem [`Classroom.java`](Classroom.java) · [`Classroom.cpp`](Classroom.cpp) · [`classroom.py`](classroom.py).

## 5. Thực tế đi làm
- Mẫu hình "object cha chứa danh sách object con + phương thức tổng hợp" gặp khắp nơi:
  `Order` chứa danh sách `OrderItem` và có `getTotal()`, `Cart` chứa danh sách `Product`
  và có `getTotalPrice()`.
- Bài này chưa cần interface hay kế thừa — vòng lặp `for` đủ dùng để tổng hợp dữ liệu.
  Khi tập dữ liệu lớn hoặc phép tổng hợp phức tạp hơn, các ngôn ngữ có công cụ chuyên
  dụng (Java Stream, Python `sum`/`max` với `key`, C++ `<algorithm>`) — bài sau ở tầng
  cao hơn sẽ đụng tới.

## 6. Self-check
```bash
javac Classroom.java && java Classroom               # in "OK"
g++ -std=c++17 -o classroom Classroom.cpp && ./classroom   # in "OK"
python classroom.py                                   # in "OK"
```
