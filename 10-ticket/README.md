# Ticket — biến `static` thay đổi được: đếm số object đã tạo, cấp id tự tăng

## 1. Đề bài
Xây dựng lớp `Ticket` (vé số thứ tự) sao cho:
- Mỗi object khi tạo tự nhận một `id` **tự tăng** bắt đầu từ 1.
- `Ticket.getTotalIssued()`: tổng số vé đã phát (thuộc về class, không thuộc object nào).

## 2. Ý tưởng
Bài 03 dùng `static final` (hằng số dùng chung, không đổi). Bài này tiến thêm một bước:
biến `static` **thay đổi được** — một bộ đếm duy nhất thuộc về class, mọi lệnh `new`
đều cộng vào nó. Mỗi object chép giá trị bộ đếm tại thời điểm tạo vào `id` riêng của
mình: dữ liệu **class** (tổng số vé) và dữ liệu **instance** (id từng vé) cùng tồn tại
và phối hợp với nhau.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Ticket.java`](Ticket.java) · [`Ticket.cpp`](Ticket.cpp) · [`ticket.py`](ticket.py).

## 5. Thực tế đi làm
- Đây chính là cơ chế đằng sau id tự tăng (auto-increment) của database, số hóa đơn,
  mã đơn hàng — một nguồn cấp số duy nhất, mỗi bản ghi giữ số của riêng nó.
- Cạm bẫy lớn: biến `static` thay đổi được là **trạng thái toàn cục** — nhiều luồng
  (thread) cùng `new` một lúc sẽ đua nhau cộng bộ đếm và cấp trùng id. Code thật dùng
  `AtomicLong` hoặc để database cấp số.

## 6. Self-check
```bash
javac Ticket.java && java Ticket                    # in "OK"
g++ -std=c++17 -o ticket Ticket.cpp && ./ticket   # in "OK"
python ticket.py                                   # in "OK"
```
