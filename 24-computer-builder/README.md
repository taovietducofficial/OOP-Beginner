# Computer & ComputerBuilder — dựng object qua từng bước (Builder pattern)

## 1. Đề bài
Xây dựng lớp `Computer` **bất biến** (`cpu`, `ram`, `hasSsd`) và một lớp `ComputerBuilder`
riêng để dựng nó, cung cấp:
- `ComputerBuilder.setCpu(cpu)`, `.setRam(ram)`, `.setSsd(hasSsd)`: từng bước khai báo cấu
  hình, có thể gọi theo bất kỳ thứ tự nào, không bắt buộc gọi hết.
- `ComputerBuilder.build()`: chốt lại, tạo ra **một** `Computer` bất biến từ những gì đã
  khai báo — `cpu` bắt buộc phải được set trước khi `build()`; `ram` mặc định `8` (GB) và
  `hasSsd` mặc định `false` nếu không set.
- `Computer` chỉ có getter, không có setter — không đổi được sau khi `build()`.

## 2. Ý tưởng
Bài 18 (`PizzaOrder`) dùng **fluent interface**: mỗi lần gọi `addTopping(...)` là **sửa
ngay** chính object `PizzaOrder` đó rồi trả về `this` để gọi tiếp — object đã tồn tại từ
đầu, chỉ đang bị chỉnh dần. Bài này khác về bản chất: `ComputerBuilder` là một object
**tạm thời, riêng biệt**, dùng để **gom dữ liệu** qua nhiều bước; `Computer` thật sự
**chưa hề tồn tại** cho tới khi gọi `build()` — lúc đó nó được tạo **một lần**, đầy đủ,
và bất biến từ đầu (giống bài 16 `Fraction`, không phải "tạo trước rồi sửa dần" như
`PizzaOrder`).

Vì sao cần một `Builder` riêng thay vì để `Computer` tự có `setCpu()`/`setRam()`?
`Computer` cần **bất biến sau khi tạo xong** (để dùng an toàn ở nhiều nơi, không lo bị sửa
ngầm — bài 16), nhưng đồng thời cấu hình nó cần **nhiều bước tùy chọn**, không thể nhét hết
vào một constructor dài với thứ tự tham số dễ nhầm. `Builder` giải quyết cả hai: có trạng
thái tạm để gom dữ liệu dần dần, nhưng sản phẩm cuối (`Computer`) thì bất biến tuyệt đối.

## 3. Độ phức tạp
- Mỗi bước `set...`, `build()`: `O(1)`.

## 4. Lời giải
Xem [`Computer.java`](Computer.java) · [`Computer.cpp`](Computer.cpp) ·
[`computer.py`](computer.py).

## 5. Thực tế đi làm
- Builder pattern gặp nhiều trong thư viện thật khi object cuối cùng có **nhiều tham số
  tùy chọn**: `AlertDialog.Builder` (Android), `StringBuilder`/`Stream.Builder` (Java),
  `HttpRequest.Builder` — đều tách "quá trình dựng" (có trạng thái tạm, có thể sai/sửa
  giữa chừng) ra khỏi "sản phẩm cuối" (bất biến, luôn hợp lệ ngay khi tồn tại).
- So với việc thêm hàng loạt constructor overload cho mọi tổ hợp tham số tùy chọn (bài 07,
  bài 14) — cách đó **bùng nổ tổ hợp** khi số tham số tùy chọn tăng lên; `Builder` xử lý
  việc này gọn hơn hẳn bằng cách cho phép set từng phần một, theo thứ tự bất kỳ.

## 6. Self-check
```bash
javac Computer.java && java Computer                     # in "OK"
g++ -std=c++17 -o computer Computer.cpp && ./computer     # in "OK"
python computer.py                                          # in "OK"
```
