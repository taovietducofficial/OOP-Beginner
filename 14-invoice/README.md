# Invoice — overload phương thức (method overloading)

## 1. Đề bài
Xây dựng lớp `Invoice` (hóa đơn), cung cấp:
- `addItem(name, price)`: thêm hàng, số lượng ngầm định là 1.
- `addItem(name, price, quantity)`: thêm hàng với số lượng chỉ định.
- `getTotal()`: tổng tiền hóa đơn.
- **Ràng buộc:** `price > 0`, `quantity > 0`.

## 2. Ý tưởng
Bài 07 overload **constructor**. Bài này overload một **phương thức thường** — cùng tên
`addItem`, khác số lượng tham số, trình biên dịch tự chọn đúng bản dựa trên lời gọi. Bản
ít tham số hơn không chép lại logic mà **ủy quyền** cho bản đầy đủ (giống nguyên tắc
`this(...)` ở bài 07): validate và tính toán chỉ tồn tại ở **một chỗ**.

Lưu ý ngôn ngữ: **Java và C++ hỗ trợ overload thật** (nhiều hàm cùng tên, khác chữ ký).
**Python thì không** — định nghĩa `add_item` hai lần thì bản sau đè bản trước. Python giải
quyết cùng bài toán bằng **tham số có giá trị mặc định** (`quantity=1`): chỉ một hàm duy
nhất, gọi có hoặc không truyền `quantity` đều được.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Invoice.java`](Invoice.java) · [`Invoice.cpp`](Invoice.cpp) · [`invoice.py`](invoice.py).

## 5. Thực tế đi làm
- Overload giúp API dễ dùng: `Files.readString(path)` và `Files.readString(path, charset)`
  trong Java — người gọi không phải nhớ giá trị mặc định của charset là gì.
- Cạm bẫy khi mang tư duy từ ngôn ngữ này sang ngôn ngữ khác: dev quen Java/C++ mới học
  Python hay cố viết `def f(x)` rồi `def f(x, y)` mong chúng "overload" — Python âm thầm
  chỉ giữ lại bản định nghĩa sau cùng, không báo lỗi, dễ gây bug khó hiểu.

## 6. Self-check
```bash
javac Invoice.java && java Invoice                    # in "OK"
g++ -std=c++17 -o invoice Invoice.cpp && ./invoice     # in "OK"
python invoice.py                                       # in "OK"
```
