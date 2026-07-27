# Leaderboard — thứ tự tự nhiên của object (Comparable / natural ordering)

## 1. Đề bài
Xây dựng lớp `Player` (`name`, `score`) và lớp `Leaderboard` quản lý một danh sách
`Player`, cung cấp:
- `addPlayer(name, score)`: thêm người chơi.
- `Player` tự định nghĩa được **cách so sánh với nhau** theo `score` (điểm cao đứng trước).
- `getRanking()`: trả về danh sách người chơi đã **sắp xếp** theo `score` giảm dần —
  không phải theo thứ tự được thêm vào.
- **Ràng buộc:** `score >= 0`, tên không được rỗng.

## 2. Ý tưởng
Bài 09 (`Money`) dạy so sánh **bằng nhau** (`equals`/`==`). Bài này dạy một dạng so sánh
khác: so sánh **hơn/kém** để sắp xếp — gọi là **thứ tự tự nhiên** (natural ordering).
Thay vì viết một hàm so sánh rời rạc bên ngoài rồi truyền vào `sort` mỗi lần cần dùng,
`Player` tự khai báo **chính nó biết so sánh với một `Player` khác như thế nào**
(Java: `implements Comparable<Player>` + `compareTo`; C++: `operator<`; Python: `__lt__`).
Nhờ vậy, mọi hàm sắp xếp có sẵn của ngôn ngữ (`Collections.sort`, `std::sort`, `sorted()`)
đều dùng được ngay trên danh sách `Player` mà không cần viết thêm logic so sánh ở nơi gọi.

## 3. Độ phức tạp
- `addPlayer`: `O(1)` (amortized).
- `getRanking`: `O(n log n)` — phải sắp xếp toàn bộ danh sách mỗi lần gọi.

## 4. Lời giải
Xem [`Leaderboard.java`](Leaderboard.java) · [`Leaderboard.cpp`](Leaderboard.cpp) ·
[`leaderboard.py`](leaderboard.py).

## 5. Thực tế đi làm
- Đây là kỹ thuật dùng hàng ngày: sắp xếp sản phẩm theo giá, nhân viên theo lương, đơn
  hàng theo ngày tạo, kết quả tìm kiếm theo độ liên quan. Định nghĩa "thứ tự tự nhiên"
  ngay trong class giúp code gọi chỉ cần `sort(list)` mà không phải nhớ viết lại logic so
  sánh ở từng nơi dùng tới.
- Khi cần sắp xếp theo **nhiều tiêu chí khác nhau** tùy ngữ cảnh (ví dụ vừa cần sort theo
  `score`, vừa cần sort theo `name`), thứ tự tự nhiên chỉ nên là **một lựa chọn mặc định**;
  các ngôn ngữ đều cho phép truyền một hàm so sánh **khác** vào lúc gọi sort (Java:
  `Comparator`; C++: truyền lambda cho `std::sort`; Python: tham số `key=`) mà không cần
  sửa class.

## 6. Self-check
```bash
javac Leaderboard.java && java Leaderboard                       # in "OK"
g++ -std=c++17 -o leaderboard Leaderboard.cpp && ./leaderboard    # in "OK"
python leaderboard.py                                                # in "OK"
```
