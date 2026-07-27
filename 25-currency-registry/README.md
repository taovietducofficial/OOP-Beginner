# Currency — factory trả về object dùng chung, không tạo mới mỗi lần (cached/interned instance)

## 1. Đề bài
Xây dựng lớp `Currency` (`code`, `symbol`) với **duy nhất một cách tạo object**:
- `Currency.of(code)`: tra một "sổ đăng ký" nội bộ; nếu `code` (`"USD"`, `"VND"`, `"EUR"`)
  đã từng được tạo trước đó, **trả lại đúng object cũ**; nếu chưa, tạo mới rồi lưu vào sổ
  đăng ký để lần sau dùng lại.
- `getCode()`, `getSymbol()`: đọc thông tin.
- **Ràng buộc:** mã tiền tệ không nằm trong danh sách hỗ trợ (`USD`, `VND`, `EUR`) phải bị
  từ chối.

## 2. Ý tưởng
Bài 13 (`Temperature`) dùng static factory (`fromCelsius`) — nhưng **mỗi lần gọi vẫn tạo
một object mới**. Bài này đẩy thêm một bước: factory không chỉ giấu `new` phía sau một cái
tên rõ nghĩa, mà còn **nhớ lại** những gì đã tạo trước đó — gọi `Currency.of("USD")` hai lần
phải trả về **cùng một object y hệt**, không phải hai bản sao có nội dung giống nhau. Đây
gọi là kỹ thuật **cache/intern theo khóa** (caching theo `code`), khác hẳn bài 09 (`Money`)
nơi hai object nội dung giống nhau vẫn là **hai object khác nhau về danh tính**
(`equals()` đúng nhưng `==` sai). Ở bài này, cùng một `code` thì **chính là cùng một
object** — `==`/`is` cũng đúng, không chỉ `equals()`.

## 3. Độ phức tạp
- `of(code)`: `O(1)` tra cứu/lưu vào sổ đăng ký (dùng cấu trúc kiểu map/dictionary).

## 4. Lời giải
Xem [`Currency.java`](Currency.java) · [`Currency.cpp`](Currency.cpp) ·
[`currency.py`](currency.py).

## 5. Thực tế đi làm
- Đây chính là cách nhiều ngôn ngữ tối ưu các giá trị dùng lại nhiều: Java cache sẵn các
  `Integer` từ -128 tới 127 (`Integer.valueOf`) và literal `String` (string pool); Python
  cache các số nguyên nhỏ và một số chuỗi ngắn tương tự — gọi `Currency.of("USD")` ở đây mô
  phỏng đúng cơ chế đó ở quy mô nhỏ, tự viết tay.
- Lợi ích thực tế: nếu `Currency` sau này có thêm dữ liệu nặng (tỷ giá, lịch sử cập nhật),
  cache theo `code` tránh phải tạo lại và nạp lại dữ liệu đó mỗi lần cần dùng tới một loại
  tiền tệ đã dùng trước đó — đổi lại, phải cẩn thận vì object dùng chung là **shared
  reference** (bài 19): sửa nó ở một chỗ ảnh hưởng tới **mọi nơi** đang giữ cùng object.

## 6. Self-check
```bash
javac Currency.java && java Currency                     # in "OK"
g++ -std=c++17 -o currency Currency.cpp && ./currency     # in "OK"
python currency.py                                           # in "OK"
```
