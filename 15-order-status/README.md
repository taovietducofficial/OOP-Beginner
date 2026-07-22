# Order — trạng thái rời rạc và chuyển bước có kiểm soát (state machine)

## 1. Đề bài
Xây dựng lớp `Order` (đơn hàng) với vòng đời `PENDING -> PAID -> SHIPPED -> DELIVERED`,
cung cấp `pay()`, `ship()`, `deliver()`, `cancel()`, `getStatus()`. Ràng buộc:
- Mỗi bước chỉ được gọi khi đơn đang ở đúng bước liền trước (không nhảy cóc).
- `cancel()` chỉ hợp lệ khi đơn còn ở `PENDING` hoặc `PAID` (chưa `SHIPPED`).

## 2. Ý tưởng
Bài 06 (`BankAccount`) đóng gói một **con số** — validate kiểm tra giá trị (âm, quá số dư).
Bài này đóng gói một **trạng thái rời rạc**: `status` chỉ nhận một trong vài giá trị cố
định, và validate không kiểm tra giá trị mà kiểm tra **thứ tự chuyển đổi** — "đơn đang ở
đâu thì được phép đi tới đâu". Mỗi phương thức là một "cửa" có gác: chỉ mở khi trạng thái
hiện tại đúng điều kiện, sai thì chặn lại và trạng thái giữ nguyên (không có nửa vời).

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Order.java`](Order.java) · [`Order.cpp`](Order.cpp) · [`order.py`](order.py).

## 5. Thực tế đi làm
- Đây là mô hình **state machine** thu nhỏ — gặp ở mọi hệ thống có vòng đời: đơn hàng,
  vé máy bay (đặt → xuất vé → check-in → đã bay), ticket hỗ trợ (mở → đang xử lý → đóng).
  Hệ thống lớn hơn thường tách bảng chuyển trạng thái ra khỏi `if/else` (dùng enum + map
  "trạng thái hiện tại -> tập trạng thái được phép tới"), nhưng nguyên lý là một.
- So sánh với `String status` ở bài này: hệ thống thật hay dùng `enum` (Java/C++) thay vì
  chuỗi để trình biên dịch tự bắt lỗi gõ sai tên trạng thái — bài học enum sẽ gặp ở tầng
  `02-student`.

## 6. Self-check
```bash
javac Order.java && java Order                # in "OK"
g++ -std=c++17 -o order Order.cpp && ./order   # in "OK"
python order.py                                 # in "OK"
```
