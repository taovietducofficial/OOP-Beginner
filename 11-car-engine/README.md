# Car & Engine — kết hợp (composition): object sở hữu object khác

## 1. Đề bài
Xây dựng lớp `Car` (xe hơi) với `model`, `horsepower`, cung cấp:
- `start()`: khởi động xe.
- `isRunning()`: xe có đang chạy không.
- `describe()`: trả về chuỗi mô tả, vd. `"Toyota Vios (120hp)"`.

Bên trong, `Car` phải tự tạo và quản lý một object `Engine` (động cơ) của riêng nó.

## 2. Ý tưởng
Bài 05 cho một object khác làm **tham số** — hai object độc lập, không sở hữu nhau
(aggregation). Bài này khác: `Car` **sở hữu** `Engine` — tự tạo nó ngay trong constructor,
không ai truyền `Engine` từ bên ngoài vào. Đây là **kết hợp (composition)**, quan hệ
"toàn thể - bộ phận": `Engine` sống chết theo `Car`. Các phương thức của `Car` không tự
làm hết mà **ủy quyền (delegate)** cho `Engine` bên trong — `Car` chỉ biết "nhờ ai làm",
không cần biết Engine làm thế nào.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Car.java`](Car.java) · [`Car.cpp`](Car.cpp) · [`car.py`](car.py).

## 5. Thực tế đi làm
- Composition là cách mô hình hóa vật thật gồm nhiều bộ phận: `Order` có `Address`,
  `Computer` có `CPU`, `Car` có `Engine`. Khác với kế thừa ("là một"), composition là
  "có một" — và trong thực tế, composition thường được ưu tiên hơn kế thừa vì linh hoạt
  hơn (nguyên tắc "composition over inheritance" sẽ gặp lại ở tầng `03-junior`).
- Ủy quyền (delegation) giúp mỗi class chỉ lo một việc: `Engine` lo chuyện máy móc,
  `Car` lo chuyện điều phối — dễ sửa, dễ test riêng từng phần.

## 6. Self-check
```bash
javac Car.java && java Car                    # in "OK"
g++ -std=c++17 -o car Car.cpp && ./car         # in "OK"
python car.py                                  # in "OK"
```
