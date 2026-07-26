# Caption Facebook/Threads — Series "Code4Life · OOP Beginner: Class & Object" (bài 06-10)

---

**Bài 06 — BankAccount (Tài khoản ngân hàng)**
Điều gì ngăn một dòng code vô danh nào đó gán số dư tài khoản của bạn thành -1 tỷ? Đóng gói.
`balance` để private, muốn đổi phải đi qua `deposit`/`withdraw` — nơi mọi quy tắc được kiểm tra. Object tự bảo vệ dữ liệu của chính nó. Đây là trụ cột đầu tiên của OOP, và là ví dụ kinh điển nhất để hiểu nó.
#Code4Life #OOP #Encapsulation

---

**Bài 07 — Point (Điểm trên mặt phẳng)**
`new ArrayList<>()` và `new ArrayList<>(100)` — cùng một class, hai cách khởi tạo. Làm sao được vậy?
Bài này bạn tự viết điều đó: nhiều constructor cùng tên, khác tham số (overloading). Mấu chốt: constructor rỗng gọi `this(0, 0)` thay vì chép lại code — logic khởi tạo chỉ nằm ở MỘT chỗ.
#Code4Life #OOP #JavaCoBan

---

**Bài 08 — Book (Object tự giới thiệu)**
Log lúc 3h sáng in ra `Order@4f3f5b24` — và người trực hệ thống khóc.
Mọi object đều có sẵn `toString()`, nhưng bản mặc định vô dụng. Ghi đè nó để object tự mô tả bằng chuỗi người đọc hiểu được. Bài đầu tiên chạm vào `@Override` — nền móng của đa hình sau này.
#Code4Life #OOP #CleanCode

---

**Bài 09 — Money (So sánh object)**
Hai tờ 100k giống hệt nhau, nhưng Java bảo chúng KHÁC nhau — nếu bạn so bằng `==`.
`==` so địa chỉ trong bộ nhớ, `equals()` so nội dung. Nhầm hai thứ này là lỗi Java kinh điển nhất trong cả phỏng vấn lẫn production. Kèm quy ước bắt buộc: ghi đè `equals` thì phải ghi đè `hashCode`.
#Code4Life #OOP #InterviewPrep

---

**Bài 10 — Ticket (Vé số thứ tự)**
Số hóa đơn, mã đơn hàng, id tự tăng trong database — tất cả chung một cơ chế: một bộ đếm duy nhất, mỗi bản ghi giữ số của riêng nó.
Bài này ghép hai thế giới đã học: dữ liệu CLASS (`static`, tổng vé đã phát) và dữ liệu INSTANCE (id từng vé) phối hợp trong cùng một class. Chốt tầng Beginner — hẹn gặp ở tầng tiếp theo với 4 trụ cột OOP.
#Code4Life #OOP #Static
