# StudentRecord — nhiều thuộc tính + phương thức xử lý

## 1. Đề bài
Xây dựng lớp `StudentRecord` với `name`, `age`, `score`, cung cấp:
- `isPassed()`: đậu nếu `score >= 5`.
- `summary()`: chuỗi mô tả gồm tên, tuổi, điểm, trạng thái đậu/rớt.

- **Ràng buộc:** `age > 0`, `score` trong `[0, 10]`, `name` không rỗng.

## 2. Ý tưởng
Mở rộng từ bài Rectangle: object giờ có nhiều thuộc tính hơn, và một phương thức
(`summary()`) **dùng lại** kết quả của phương thức khác (`isPassed()`) trong cùng object —
minh họa các phương thức trong một class có thể gọi lẫn nhau trên cùng dữ liệu.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`StudentRecord.java`](StudentRecord.java) · [`StudentRecord.cpp`](StudentRecord.cpp) · [`student_record.py`](student_record.py).

## 5. Thực tế đi làm
- Validate ở constructor tránh việc tạo ra "học sinh" với tuổi âm hay điểm ngoài thang —
  lỗi dữ liệu bị chặn ngay chỗ tạo ra, không phải dò tìm ở tầng hiển thị.
- Gọi phương thức nội bộ (`summary()` gọi `isPassed()`) thay vì lặp lại điều kiện `score >= 5`
  ở nhiều nơi — sửa quy tắc đậu/rớt chỉ cần sửa một chỗ.

## 6. Self-check
```bash
javac StudentRecord.java && java StudentRecord                    # in "OK"
g++ -std=c++17 -o student_record StudentRecord.cpp && ./student_record   # in "OK"
python student_record.py                                   # in "OK"
```
