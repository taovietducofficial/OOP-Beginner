# ShoppingCart — bài ôn tập tổng hợp tầng beginner

## 1. Đề bài
Xây dựng lớp `CartItem` (`name`, `price`, `quantity`) và lớp `ShoppingCart`
(`customerName`), cung cấp:
- `addItem(name, price)`: thêm món hàng, số lượng ngầm định là 1.
- `addItem(name, price, quantity)`: thêm món hàng với số lượng chỉ định.
- `getItems()`: danh sách các dòng hàng hiện có.
- `getTotal()`: tổng tiền cả giỏ hàng.
- **Ràng buộc:** `price > 0`, `quantity > 0`, tên khách hàng không được rỗng.

## 2. Ý tưởng
Bài này không đưa ra khái niệm mới — nó **ghép lại** những kỹ thuật đã học suốt tầng
beginner để giải một bài toán hoàn chỉnh, gần với code thực tế nhất:
- Đóng gói + validate ở biên trong constructor của `CartItem` (bài 06).
- Hai phiên bản `addItem` — một rút gọn, một đầy đủ (bài 14; Python dùng tham số mặc định
  vì không có overload thật, như đã ghi chú ở bài đó).
- `ShoppingCart` quản lý một **tập hợp** `CartItem` và **tổng hợp** dữ liệu bằng cách duyệt
  qua từng phần tử để tính `getTotal()` (bài 12).
- `getItems()` trả về **bản sao**, không để lộ danh sách nội bộ (bài 17).
- `toString()`/`__str__` để giỏ hàng tự mô tả chính nó thay vì địa chỉ bộ nhớ vô nghĩa
  (bài 08).

## 3. Độ phức tạp
- `addItem`: `O(1)` (amortized).
- `getItems`, `getTotal`, `toString`: `O(n)` với `n` là số dòng hàng — đều phải duyệt/copy
  toàn bộ danh sách.

## 4. Lời giải
Xem [`ShoppingCart.java`](ShoppingCart.java) · [`ShoppingCart.cpp`](ShoppingCart.cpp) · [`shopping_cart.py`](shopping_cart.py).

## 5. Thực tế đi làm
- Đây chính là hình dạng của phần lớn class nghiệp vụ thực tế: không "thuần" một khái niệm
  sách giáo khoa, mà là tổ hợp của validate, tập hợp con, tổng hợp dữ liệu, và mô tả chính
  nó — `Order` có `OrderItem`, `Invoice` có dòng hàng, `Cart` có `Product`, đều theo đúng
  khuôn này.
- Đây cũng là điểm khép lại tầng `01-beginner`: 20 bài đã đi từ một object đơn giản
  (`Rectangle`) tới một class phối hợp nhiều kỹ thuật cùng lúc. Tầng `02-student` tiếp
  theo mở rộng đúng bài toán `ShoppingCart`/`Order` này với 4 trụ cột OOP đầy đủ — ví dụ
  tính giảm giá khác nhau theo từng loại khách hàng bằng **đa hình** thay vì `if/else`
  chồng chất.

## 6. Self-check
```bash
javac ShoppingCart.java && java ShoppingCart                            # in "OK"
g++ -std=c++17 -o shopping_cart ShoppingCart.cpp && ./shopping_cart      # in "OK"
python shopping_cart.py                                                    # in "OK"
```
