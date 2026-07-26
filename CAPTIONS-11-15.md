# Caption Facebook/Threads — Series "Code4Life · OOP Beginner: Class & Object" (bài 11-15)

---

**Bài 11 — Car & Engine (Kết hợp - Composition)**
Xe hơi có "mượn" động cơ từ đâu đó, hay tự nó sinh ra động cơ của chính mình?
Bài 05 cho một object khác làm THAM SỐ — hai object độc lập, không sở hữu nhau. Bài này khác: `Car` tự tạo `Engine` ngay trong constructor — quan hệ "toàn thể - bộ phận". `Car` không tự nổ máy, nó ỦY QUYỀN cho `Engine` bên trong làm việc đó. Đây là cách OOP mô hình hóa mọi vật thật gồm nhiều bộ phận.
#Code4Life #OOP #Composition

---

**Bài 12 — Classroom (Tập hợp object)**
Một lớp học không chỉ có 1 học sinh — vậy điểm trung bình cả lớp tính thế nào, ai là học sinh giỏi nhất?
Bài này chuyển từ "1 object chứa dữ liệu đơn" sang "1 object chứa cả một DANH SÁCH object khác cùng loại". Không có công thức đóng nào cho `averageScore()` — phải duyệt qua từng phần tử và gộp kết quả lại. Đây là hình dạng phổ biến nhất của dữ liệu thực tế: `Order` luôn có nhiều `OrderItem`, `Cart` luôn có nhiều `Product`.
#Code4Life #OOP #Collections

---

**Bài 13 — Temperature (Static factory method)**
`fromCelsius(100)` và `fromFahrenheit(212)` — cùng nhận vào một con số `double`, sao phân biệt được là độ gì?
Không thể overload constructor vì trùng chữ ký (bài 07 xử lý được vì tham số khác nhau, đây thì không). Giải pháp: khóa constructor lại (`private`), mở static factory method mang TÊN RÕ NGHĨA để tạo object. Đây chính là mẫu hình đứng sau `LocalDate.of(...)`, `List.of(...)` mà bạn dùng hằng ngày.
#Code4Life #OOP #StaticFactory

---

**Bài 14 — Invoice (Overload phương thức)**
`addItem("Bút", 5000)` và `addItem("Vở", 8000, 3)` — cùng tên, cùng class, nhưng khác số tham số.
Bài 07 overload CONSTRUCTOR, bài này overload một PHƯƠNG THỨC THƯỜNG — bản ít tham số ủy quyền cho bản đầy đủ, validate chỉ nằm một chỗ. Twist quan trọng: Java/C++ overload được thật, còn Python thì KHÔNG — định nghĩa hai hàm trùng tên, bản sau âm thầm đè bản trước. Dev quen tay từ ngôn ngữ khác hay dính bug này khi mới học Python.
#Code4Life #OOP #Overloading

---

**Bài 15 — Order (Trạng thái & state machine)**
Một đơn hàng đang "chờ thanh toán" có thể nhảy cóc thẳng lên "đã giao" được không? Tất nhiên là không.
Bài 06 (`BankAccount`) đóng gói một con SỐ. Bài này đóng gói một TRẠNG THÁI RỜI RẠC — validate không kiểm tra giá trị mà kiểm tra THỨ TỰ chuyển đổi: đang ở đâu thì được phép đi tới đâu. Đây là state machine thu nhỏ, mô hình đứng sau vòng đời của mọi đơn hàng, vé máy bay, ticket hỗ trợ. Chốt phần mở rộng của tầng Beginner (bài 11-15) — hẹn gặp lại ở tầng Student với 4 trụ cột OOP.
#Code4Life #OOP #StateMachine
