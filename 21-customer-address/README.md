# Customer & Address — thay `null` bằng một object thật (Null Object pattern)

## 1. Đề bài
Xây dựng lớp `Address` (`street`, `city`) và lớp `Customer` (`name`, `address`), cung cấp:
- `Address.of(street, city)`: tạo địa chỉ cụ thể — `street`/`city` không được rỗng.
- Một địa chỉ đặc biệt đại diện **"chưa có địa chỉ"** (`Address.UNKNOWN`/`Address.unknown()`),
  dùng khi khách hàng chưa cung cấp địa chỉ giao hàng.
- `Customer(name)`: khách chưa có địa chỉ — tự gán địa chỉ đặc biệt ở trên.
- `Customer(name, address)`: khách có địa chỉ cụ thể ngay từ đầu.
- `hasAddress()`: có địa chỉ thật hay không.
- `getShippingLabel()`: nhãn giao hàng — nếu chưa có địa chỉ, in thông báo phù hợp; nếu có,
  in `"street, city"`.

## 2. Ý tưởng
Cách quen thuộc để biểu diễn "không có dữ liệu" là dùng `null`/`None`, rồi rải
`if (address == null)` ở **mọi nơi** trước khi dùng nó — chỉ cần quên một chỗ là
`NullPointerException`/`AttributeError`. Bài này dùng **Null Object pattern**: thay vì
`null`, tạo một **object thật** đại diện cho "sự vắng mặt", với hành vi an toàn của riêng
nó. `Address.UNKNOWN` vẫn là một `Address` hợp lệ — có thể gọi `getDisplayText()` bình
thường, nó tự biết trả về thông báo "chưa có địa chỉ" thay vì phải kiểm tra `null` ở
`Customer.getShippingLabel()` hay bất kỳ nơi nào khác gọi tới.

So sánh với bài 13 (`Temperature`, static factory): factory ở bài 13 luôn tạo ra object
đại diện cho một **giá trị có thật**. Ở bài này, factory/hằng số tạo ra một object đại
diện cho **sự vắng mặt của giá trị** — nhưng vẫn là object, vẫn dùng được như bình thường,
không cần nhánh `null` riêng ở nơi gọi.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Customer.java`](Customer.java) · [`Customer.cpp`](Customer.cpp) · [`customer.py`](customer.py).

## 5. Thực tế đi làm
- Mẫu hình này gặp nhiều trong thư viện thật: `Optional.empty()` (Java) thay vì trả `null`;
  một `NullLogger` không ghi gì thay vì kiểm tra `if (logger != null)` trước mỗi lần log;
  giỏ hàng trống trả về một `Cart` rỗng thay vì `cart == null`.
- Lợi ích chính: logic "phải làm gì khi không có dữ liệu" được gom về **một chỗ duy nhất**
  (trong chính object đặc biệt đó), thay vì lặp lại rải rác ở mọi nơi gọi tới — giảm hẳn
  nguy cơ quên check và crash khi hệ thống lớn dần.

## 6. Self-check
```bash
javac Customer.java && java Customer                       # in "OK"
g++ -std=c++17 -o customer Customer.cpp && ./customer       # in "OK"
python customer.py                                             # in "OK"
```
