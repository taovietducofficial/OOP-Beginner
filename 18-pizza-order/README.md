# PizzaOrder — fluent interface (method chaining)

## 1. Đề bài
Xây dựng lớp `PizzaOrder` với `size` (`"S"`/`"M"`/`"L"`), cung cấp:
- `addTopping(name)`: thêm một loại topping, **trả về chính object đang gọi** để nối
  tiếp được lời gọi khác.
- `getToppings()`: trả về danh sách topping hiện tại.
- `getTotal()`: giá nền theo size + `10.000đ` cho mỗi topping.
- **Ràng buộc:** `size` chỉ nhận `S`/`M`/`L`; tên topping không được rỗng.

## 2. Ý tưởng
Bài 16 (`Fraction`) là object **bất biến** — mỗi phép toán trả về một object **mới**.
Bài này là object **có trạng thái thay đổi** (giống `Counter` ở bài 04, `BankAccount` ở
bài 06), nhưng thay vì `addTopping()` trả về `void`/`None`, nó trả về **chính object đang
gọi** (`return this` / `return *this` / `return self`). Nhờ vậy, nhiều lời gọi có thể nối
liền nhau thành một chuỗi đọc tự nhiên như câu văn:
`order.addTopping("cheese").addTopping("bacon")` — đây gọi là **fluent interface**.
`getToppings()` vẫn áp dụng **defensive copy** đã học ở bài 17: object có trạng thái thay
đổi càng cần bảo vệ dữ liệu nội bộ khỏi bị sửa ngoài ý muốn.

## 3. Độ phức tạp
- `addTopping`: `O(1)` (số dư — amortized cho thao tác thêm vào cuối danh sách động).
- `getToppings`: `O(n)` với `n` là số topping — sao chép toàn bộ danh sách.
- `getTotal`: `O(1)`.

## 4. Lời giải
Xem [`PizzaOrder.java`](PizzaOrder.java) · [`PizzaOrder.cpp`](PizzaOrder.cpp) · [`pizza_order.py`](pizza_order.py).

## 5. Thực tế đi làm
- Fluent interface là mẫu hình quen thuộc trong nhiều thư viện: `StringBuilder` của Java
  (`sb.append("a").append("b")`), `Stream` (`list.stream().filter(...).map(...)`), jQuery
  (`$(el).addClass(...).show()`) — mỗi lời gọi trả về object để "móc" lời gọi tiếp theo.
- Đây là bước đệm trực tiếp tới **Builder pattern**: khi object có quá nhiều tham số tùy
  chọn, thay vì một constructor khổng lồ (hoặc rất nhiều overload như bài 14), người ta
  tách việc cấu hình ra thành chuỗi `set...()`/`add...()` trả về `this`, rồi gọi `build()`
  ở cuối để tạo object hoàn chỉnh — sẽ gặp chính thức ở tầng `03-junior`.

## 6. Self-check
```bash
javac PizzaOrder.java && java PizzaOrder                          # in "OK"
g++ -std=c++17 -o pizza_order PizzaOrder.cpp && ./pizza_order      # in "OK"
python pizza_order.py                                                # in "OK"
```
