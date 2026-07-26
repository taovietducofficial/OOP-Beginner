# Employee & Department — tham chiếu dùng chung (shared reference)

## 1. Đề bài
Xây dựng lớp `Department` (`name`, có thể `rename()`) và lớp `Employee` (`name`,
`department`), cung cấp:
- `Employee(name, department)`: nhận một `Department` đã tồn tại sẵn từ bên ngoài.
- `getDepartmentName()`: tên phòng ban hiện tại của nhân viên.
- **Yêu cầu:** nhiều `Employee` có thể cùng thuộc một `Department`; đổi tên phòng ban qua
  `rename()` phải phản ánh ngay tới **mọi** `Employee` đang thuộc phòng đó.

## 2. Ý tưởng
Bài 11 (`Car`/`Engine`) là **composition**: `Car` tự tạo `Engine` của riêng nó, không ai
khác đụng tới — `Engine` sống chết theo `Car`. Bài 17 (`Playlist`) chủ động **cắt đứt**
tham chiếu (defensive copy) để bảo vệ dữ liệu nội bộ khỏi bị sửa từ ngoài. Bài này làm điều
**ngược lại có chủ đích**: `Department` được tạo **độc lập bên ngoài**, rồi nhiều `Employee`
cùng giữ **tham chiếu tới đúng một object** đó — không sở hữu, không sao chép. Đây gọi là
**aggregation** (quan hệ "có một" nhưng không sở hữu độc quyền, khác composition). Vì nhiều
`Employee` trỏ chung một `Department`, gọi `rename()` một lần qua bất kỳ tham chiếu nào
cũng làm **mọi nơi khác** thấy giá trị mới — đây chính là ý nghĩa của "tham chiếu dùng
chung" (shared mutable reference).

Lưu ý ngôn ngữ: **Java và Python** biến object mặc định luôn là tham chiếu — code gán
`this.department = department` (Java) hay `self._department = department` (Python) tự
động chia sẻ, không cần làm gì thêm. **C++ thì ngược lại**: mặc định là kiểu **giá trị**
(bài học ở 17). Nếu khai báo `Department department;` (không có `&`), constructor sẽ
**âm thầm copy** — mỗi `Employee` có bản sao riêng, `rename()` sẽ không lan tới ai cả.
Muốn chia sẻ thật trong C++, phải khai báo tường minh `Department&` (tham chiếu) hoặc dùng
con trỏ/smart pointer.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Employee.java`](Employee.java) · [`Employee.cpp`](Employee.cpp) · [`employee.py`](employee.py).

## 5. Thực tế đi làm
- Mẫu hình này gặp khắp nơi: nhiều `Order` cùng trỏ tới một `Customer`, nhiều `Player`
  cùng thuộc một `Team`, nhiều thành phần UI cùng đọc một object cấu hình dùng chung —
  đổi cấu hình một chỗ, mọi nơi tham chiếu tới nó đều cập nhật theo mà không cần đồng bộ
  thủ công.
- Mặt trái cần cảnh giác: tham chiếu dùng chung mà **mutable** dễ gây bug khó tìm nếu một
  nơi vô tình sửa dữ liệu mà nơi khác không ngờ tới — khác hẳn nguyên tắc "bảo vệ dữ liệu
  nội bộ" ở bài 17. Chọn chia sẻ tham chiếu (bài này) hay cô lập bằng bản sao (bài 17) là
  một **quyết định thiết kế có chủ đích**, không phải mặc định "cứ an toàn thì copy hết".

## 6. Self-check
```bash
javac Employee.java && java Employee                     # in "OK"
g++ -std=c++17 -o employee Employee.cpp && ./employee     # in "OK"
python employee.py                                          # in "OK"
```
