# Caption Facebook/Threads — Series "Code4Life · OOP Beginner: Class & Object" (bài 16-20)

---

**Bài 16 — Fraction (Object bất biến - Immutable)**
Gọi `a.add(b)` xong in `a` ra — sao vẫn là giá trị cũ, chẳng đổi gì cả?
Bài 04 (`Counter`) và bài 06 (`BankAccount`) là object CÓ trạng thái thay đổi — gọi phương thức là sửa dữ liệu ngay tại chỗ. Bài này đi ngược lại hoàn toàn: `Fraction` BẤT BIẾN — không setter nào cả, `add()`/`multiply()` không sửa gì trên object gốc mà luôn TRẢ VỀ MỘT OBJECT MỚI. Quên gán lại kết quả là dính bug y hệt lỗi `str.replace()` trong Python hay `String.trim()` trong Java. Đây là nền tảng của `String`, `LocalDate`, `BigDecimal`.
#Code4Life #OOP #Immutability

---

**Bài 17 — Playlist (Defensive copy)**
`getSongs()` rồi `.add()` thẳng vào kết quả đó — playlist gốc bị đổi theo, dù chưa hề gọi `addSong()` lần nào.
Bài 12 (`Classroom`) đã cho một class chứa danh sách object con, nhưng chưa để lộ nó ra ngoài qua getter. Đây chính là cái bẫy khi làm điều đó: trả THẲNG tham chiếu nội bộ cho phép code ngoài sửa dữ liệu object mà không đi qua bất kỳ validate nào — đóng gói (bài 06) chặn được setter sai, nhưng một getter "rò rỉ" tham chiếu là lỗ hổng khác, kín cổng nhưng hở tường. Cách sửa: getter luôn trả về BẢN SAO.
#Code4Life #OOP #DefensiveCopy

---

**Bài 18 — PizzaOrder (Fluent interface)**
`order.addTopping("cheese").addTopping("bacon")` — nối được cả chuỗi lời gọi trên một dòng, sao làm được vậy?
Khác `Fraction` ở bài 16 (trả object MỚI vì bất biến), `PizzaOrder` có trạng thái thay đổi (giống `Counter`, `BankAccount`) nhưng `addTopping()` trả về CHÍNH OBJECT ĐANG GỌI thay vì rỗng — người dùng "móc" được lời gọi tiếp theo ngay sau đó. Đây là mẫu hình đứng sau `StringBuilder`, `Stream`, jQuery — và là bước đệm trực tiếp tới Builder pattern ở tầng sau.
#Code4Life #OOP #FluentInterface

---

**Bài 19 — Employee & Department (Tham chiếu dùng chung)**
Đổi tên phòng ban qua MỘT nhân viên — nhân viên khác cùng phòng cũng thấy thay đổi ngay lập tức, dù chẳng ai đụng vào object của họ.
Bài 11 (`Car`/`Engine`) là composition — sở hữu riêng, không chia sẻ. Bài 17 chủ động CẮT ĐỨT tham chiếu để bảo vệ dữ liệu. Bài này làm điều NGƯỢC LẠI có chủ đích: nhiều `Employee` cùng giữ tham chiếu tới đúng MỘT `Department` — aggregation. Twist ở C++: phải khai báo tường minh `Department&`, nếu không constructor sẽ ÂM THẦM COPY và mất luôn khả năng chia sẻ — khác hẳn Java/Python, nơi biến object mặc định luôn là tham chiếu.
#Code4Life #OOP #Aggregation

---

**Bài 20 — ShoppingCart (Ôn tập tổng hợp)**
20 bài rồi — chốt lại bằng bài toán quen thuộc nhất: giỏ hàng.
Bài này không dạy khái niệm mới, nó GHÉP LẠI mọi kỹ thuật đã học suốt tầng Beginner: đóng gói + validate ở biên (bài 06), overload phương thức (bài 14), một class quản lý tập hợp và tổng hợp dữ liệu (bài 12), defensive copy khi để lộ danh sách (bài 17), object tự mô tả chính nó (bài 08). Đây là hình dạng gần với code thực tế nhất — không "thuần" một khái niệm sách vở, mà là tổ hợp của tất cả. Khép tầng Beginner (bài 01-20) — hẹn gặp lại ở tầng Student với 4 trụ cột OOP đầy đủ: đóng gói, kế thừa, đa hình, trừu tượng.
#Code4Life #OOP #Recap
