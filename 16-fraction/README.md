# Fraction — object bất biến (immutable value object)

## 1. Đề bài
Xây dựng lớp `Fraction` (phân số) với `numerator` (tử số), `denominator` (mẫu số), cung cấp:
- Constructor tự động **rút gọn** về dạng tối giản và **chuẩn hóa dấu** (mẫu số luôn dương).
- `add(Fraction other)`: cộng hai phân số, trả về phân số **mới**.
- `multiply(Fraction other)`: nhân hai phân số, trả về phân số **mới**.
- **Ràng buộc:** mẫu số không được bằng 0.

## 2. Ý tưởng
Bài 04 (`Counter`) và bài 06 (`BankAccount`) là object **có trạng thái thay đổi** — gọi
phương thức là sửa dữ liệu ngay trên chính object đó. Bài này đi theo hướng ngược lại:
`Fraction` là **object bất biến (immutable)** — không có phương thức nào ghi đè
`numerator`/`denominator` sau khi tạo. `add()` và `multiply()` không sửa `this` hay tham
số truyền vào, mà luôn **tạo và trả về một object `Fraction` hoàn toàn mới**. Việc rút gọn
phân số (ước chung lớn nhất) chỉ chạy **một lần** trong constructor, áp dụng cho mọi con
đường tạo object — cùng nguyên tắc "validate một chỗ" đã gặp ở static factory (bài 13).

## 3. Độ phức tạp
- Constructor, `add`, `multiply`: `O(log(min(a, b)))` do thuật toán Euclid tính ước chung
  lớn nhất; các getter còn lại `O(1)`.

## 4. Lời giải
Xem [`Fraction.java`](Fraction.java) · [`Fraction.cpp`](Fraction.cpp) · [`fraction.py`](fraction.py).

## 5. Thực tế đi làm
- Object bất biến an toàn hơn khi truyền qua lại giữa nhiều hàm/luồng (thread): không ai
  vô tình sửa được nó, nên không cần lo "object này có đang bị chỗ khác đổi giữa chừng
  không". Đây là lý do `String`, `LocalDate`, `BigDecimal` (Java) hay `int`, `str`, `tuple`
  (Python) đều bất biến.
- Cạm bẫy kinh điển: tưởng `a.add(b)` sẽ đổi `a`, giống các phương thức mutable đã gặp
  trước đó (`Counter.increment()`, `BankAccount.deposit()`) — quên rằng kết quả phải được
  **gán lại** (`a = a.add(b)`), y hệt lỗi thường gặp với `str.replace()` trong Python hay
  `String.trim()` trong Java (đều trả về chuỗi mới, không sửa chuỗi gốc).

## 6. Self-check
```bash
javac Fraction.java && java Fraction                     # in "OK"
g++ -std=c++17 -o fraction Fraction.cpp && ./fraction     # in "OK"
python fraction.py                                         # in "OK"
```
