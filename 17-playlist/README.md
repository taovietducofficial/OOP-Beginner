# Playlist — defensive copy (không để lộ tham chiếu nội bộ)

## 1. Đề bài
Xây dựng lớp `Playlist` (danh sách phát) với `name`, cung cấp:
- `addSong(title)`: thêm một bài hát.
- `size()`: số bài hát hiện có.
- `getSongs()`: trả về danh sách bài hát hiện tại.
- **Ràng buộc:** tên bài hát không được rỗng.

## 2. Ý tưởng
Bài 12 (`Classroom`) đã cho một class chứa danh sách object con, nhưng chưa để lộ danh
sách đó ra bên ngoài. Bài này khai thác đúng chỗ hở đó: nếu `getSongs()` trả **thẳng**
tham chiếu tới danh sách nội bộ, code gọi nó có thể `add`/`remove` trực tiếp lên danh
sách đó — dữ liệu của `Playlist` bị sửa mà không đi qua `addSong()`, tức là không qua
validate, không qua bất kỳ kiểm soát nào. Đóng gói (bài 06) chặn được ghi sai qua
**setter**, nhưng một getter "rò rỉ" tham chiếu là một lỗ hổng đóng gói khác — kín cổng
nhưng hở tường. Cách sửa: `getSongs()` luôn trả về một **bản sao (defensive copy)**,
không phải bản gốc.

Lưu ý ngôn ngữ: **Java và Python** biến kiểu danh sách luôn là **tham chiếu** — copy phải
làm **thủ công** (`new ArrayList<>(songs)` / `list(self._songs)`). **C++** có kiểu **giá
trị**: trả về `std::vector<...>` **bằng giá trị** (không phải `const&`) đã tự động là một
bản sao độc lập nhờ copy constructor — chỉ cần không lỡ trả về tham chiếu/con trỏ tới
thành viên nội bộ.

## 3. Độ phức tạp
- `addSong`, `size`: `O(1)`.
- `getSongs`: `O(n)` với `n` là số bài hát — sao chép toàn bộ danh sách.

## 4. Lời giải
Xem [`Playlist.java`](Playlist.java) · [`Playlist.cpp`](Playlist.cpp) · [`playlist.py`](playlist.py).

## 5. Thực tế đi làm
- Đây là lỗi bảo mật/đúng đắn dữ liệu thực sự, không chỉ lý thuyết: getter trả về mảng,
  `List`, `Map`, hay `Date` (mutable) nội bộ mà không copy là một trong các mục kiểm tra
  chuẩn của SpotBugs/FindBugs (`EI_EXPOSE_REP`) trong hệ sinh thái Java.
- Nguyên tắc áp dụng ở **cả hai đầu**: constructor nhận một danh sách từ bên ngoài cũng
  nên copy vào (tránh caller giữ tham chiếu rồi sửa sau khi object đã tạo xong), không
  chỉ getter trả ra. Bài này tập trung vào getter vì đó là chỗ dễ bị bỏ sót nhất.

## 6. Self-check
```bash
javac Playlist.java && java Playlist                       # in "OK"
g++ -std=c++17 -o playlist Playlist.cpp && ./playlist       # in "OK"
python playlist.py                                            # in "OK"
```
