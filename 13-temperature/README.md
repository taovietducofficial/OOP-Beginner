# Temperature — static factory method thay cho constructor mù mờ

## 1. Đề bài
Xây dựng lớp `Temperature`, cung cấp:
- `Temperature.fromCelsius(c)`: tạo nhiệt độ từ độ C.
- `Temperature.fromFahrenheit(f)`: tạo nhiệt độ từ độ F.
- `toCelsius()` / `toFahrenheit()`: đọc lại theo từng đơn vị.
- **Ràng buộc:** không cho tạo nhiệt độ thấp hơn 0 tuyệt đối (-273.15°C).

## 2. Ý tưởng
Bài 07 overload constructor khi tham số **khác kiểu/số lượng**. Ở đây `fromCelsius(double)`
và `fromFahrenheit(double)` có **cùng chữ ký** — không thể tách thành hai constructor vì
trùng nhau, và nếu chỉ có một `Temperature(double)` thì người gọi không biết con số đó
là độ C hay độ F. Giải pháp: **static factory method** — khóa constructor lại (`private`),
mở ra các phương thức `static` mang tên rõ nghĩa để tạo object. Bên trong, lớp vẫn chỉ lưu
**một đơn vị chuẩn** (độ C), factory nào cũng quy đổi về đó trước khi gọi constructor —
validate ở constructor chạy đúng một lần, áp dụng cho mọi con đường tạo object.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Temperature.java`](Temperature.java) · [`Temperature.cpp`](Temperature.cpp) · [`temperature.py`](temperature.py).

## 5. Thực tế đi làm
- Static factory method là mẫu hình chuẩn trong nhiều thư viện: `LocalDate.of(...)`,
  `List.of(...)`, `Optional.of(...)` trong Java — tên phương thức mô tả rõ **cách** tạo,
  thay vì buộc người đọc suy đoán qua tham số của constructor.
- Chọn một đơn vị lưu trữ nội bộ duy nhất (ở đây là độ C) là kỹ thuật chung khi một class
  có nhiều "định dạng nhập vào": tiền tệ quy về đơn vị nhỏ nhất, thời gian quy về UTC,
  khoảng cách quy về mét — quy đổi diễn ra ở biên (factory), lõi chỉ xử lý một dạng.

## 6. Self-check
```bash
javac Temperature.java && java Temperature                          # in "OK"
g++ -std=c++17 -o temperature Temperature.cpp && ./temperature      # in "OK"
python temperature.py                                                # in "OK"
```
