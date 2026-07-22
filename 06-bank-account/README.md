# BankAccount — đóng gói: trạng thái chỉ đổi qua phương thức có kiểm soát

## 1. Đề bài
Xây dựng lớp `BankAccount` với `balance` (số dư), cung cấp:
- `deposit(amount)`: nạp tiền, `amount > 0`.
- `withdraw(amount)`: rút tiền, `amount > 0` và không được rút quá số dư.
- `getBalance()`: xem số dư hiện tại.

## 2. Ý tưởng
Đây là ví dụ kinh điển nhất của **đóng gói (encapsulation)**: `balance` để `private`,
thế giới bên ngoài **không thể** gán `balance = -1000` trực tiếp — mọi thay đổi phải đi
qua `deposit`/`withdraw`, nơi các quy tắc (tiền > 0, không rút lố) được kiểm tra. Object
tự bảo vệ tính đúng đắn của dữ liệu bên trong nó.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`BankAccount.java`](BankAccount.java) · [`BankAccount.cpp`](BankAccount.cpp) · [`bank_account.py`](bank_account.py).

## 5. Thực tế đi làm
- Quy tắc "field private + thay đổi qua phương thức có validate" là chuẩn mực trong mọi
  codebase: nếu field để public, một dòng gán sai ở bất kỳ đâu cũng phá hỏng dữ liệu và
  cực khó truy vết.
- Tiền bạc trong hệ thống thật không dùng `double` (sai số dấu phẩy động) — dùng số
  nguyên (đơn vị nhỏ nhất, vd. đồng/xu) hoặc `BigDecimal`. Bài này dùng `long` (đồng).

## 6. Self-check
```bash
javac BankAccount.java && java BankAccount                    # in "OK"
g++ -std=c++17 -o bank_account BankAccount.cpp && ./bank_account   # in "OK"
python bank_account.py                                   # in "OK"
```
