# TextUtils — class chỉ chứa hàm tĩnh, không tạo object (static utility class)

## 1. Đề bài
Xây dựng lớp `TextUtils` gồm toàn phương thức `static`, **không ai được phép tạo object**
từ lớp này:
- `capitalize(text)`: viết hoa ký tự đầu tiên, giữ nguyên phần còn lại.
- `truncate(text, maxLength)`: nếu `text` dài hơn `maxLength`, cắt còn `maxLength` ký tự và
  thêm `"..."` vào cuối; nếu không, giữ nguyên.
- `slugify(text)`: chuyển thành dạng URL-slug — chữ thường, khoảng trắng thành `-`.
- **Ràng buộc:** `maxLength > 0`; cố tình tạo object `TextUtils` (`new TextUtils()`) phải bị
  chặn ngay từ lúc biên dịch/chạy.

## 2. Ý tưởng
Mọi class đã gặp từ bài 01 đều đại diện cho một **thực thể có trạng thái** (một hình chữ
nhật, một tài khoản, một đơn hàng...) — luôn tạo object rồi gọi phương thức trên object đó.
`TextUtils` khác hẳn: nó không đại diện cho *cái gì* cả, không có thuộc tính, không có
trạng thái — nó chỉ là một **nơi gom nhóm các hàm xử lý chuỗi liên quan tới nhau**. Vì
vậy mọi phương thức đều `static` (không cần object mới gọi được), và constructor bị
**khóa lại chủ động** để không ai lỡ viết `new TextUtils()` rồi tưởng nó có ý nghĩa gì đó
(Java/C++: constructor `private`; Python: `raise` ngay trong `__init__`, hoặc dùng hàm
module-level thay vì class — bài này vẫn gói trong class cho nhất quán với 2 ngôn ngữ kia).

So sánh với bài 03 (`Circle`): bài 03 dùng `static final` cho **hằng số dùng chung**, nhưng
`Circle` vẫn là một class tạo object bình thường. Bài này đẩy ý tưởng "dùng chung, không
qua object" tới toàn bộ class — biến nó thành một **namespace chứa hàm**, không phải một
khuôn tạo object.

## 3. Độ phức tạp
- `capitalize`: `O(1)` xử lý ký tự đầu, nhưng tạo chuỗi mới nên tổng thể `O(n)` với `n` là
  độ dài chuỗi (mọi ngôn ngữ ở đây đều copy chuỗi khi ghép).
- `truncate`: `O(maxLength)`.
- `slugify`: `O(n)`.

## 4. Lời giải
Xem [`TextUtils.java`](TextUtils.java) · [`TextUtils.cpp`](TextUtils.cpp) ·
[`text_utils.py`](text_utils.py).

## 5. Thực tế đi làm
- Mẫu hình này xuất hiện khắp nơi trong thư viện chuẩn và codebase thật: `Math`/`Collections`
  (Java), `<algorithm>` (C++), hàm module-level trong `os.path`/`itertools` (Python) — đều
  là tập hợp hàm xử lý liên quan tới nhau, không gắn với trạng thái của một object cụ thể.
  Nhiều dự án tự viết `StringUtils`, `DateUtils`, `ValidationUtils` theo đúng khuôn này.
- Cảnh báo thường gặp trong review code: nếu một "Utils" class dần dần **có thêm trạng
  thái** (một biến instance nào đó, không còn thuần static nữa), đó là dấu hiệu nó nên được
  tách thành một class thực thụ (có constructor, có object) thay vì tiếp tục nhét hàm vào
  một namespace giả danh class.

## 6. Self-check
```bash
javac TextUtils.java && java TextUtils                     # in "OK"
g++ -std=c++17 -o text_utils TextUtils.cpp && ./text_utils  # in "OK"
python text_utils.py                                           # in "OK"
```
