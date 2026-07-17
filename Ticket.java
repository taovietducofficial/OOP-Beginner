/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Ticket minh họa biến static THAY ĐỔI ĐƯỢC — một bộ đếm duy nhất
 * thuộc về class, mọi lệnh new đều cộng vào nó; mỗi object chép giá trị bộ
 * đếm tại thời điểm tạo vào id riêng của mình. Dữ liệu class (tổng số vé)
 * và dữ liệu instance (id từng vé) phối hợp với nhau.
 *
 * Tại sao cần học: đây là cơ chế đằng sau id tự tăng của database, số hóa
 * đơn, mã đơn hàng. Đồng thời là bài học về cạm bẫy: static thay đổi được
 * là trạng thái toàn cục — nhiều thread cùng new sẽ cấp trùng id.
 */
public class Ticket { // khai báo class — khuôn mẫu để tạo ra các object Ticket

    private static int totalIssued = 0; // bộ đếm CLASS: chỉ có 1 bản duy nhất, mọi lệnh new đều cộng vào đây — KHÔNG final vì nó thay đổi
    // ponytail: int thường, đủ cho bài học đơn luồng; code thật nhiều thread dùng AtomicLong hoặc để database cấp số

    private final int id; // id INSTANCE: mỗi vé giữ số thứ tự riêng của mình, gán một lần lúc tạo

    public Ticket() { // constructor — chạy khi gọi "new Ticket()"
        totalIssued++;         // cộng bộ đếm chung của class: thêm một vé đã phát
        this.id = totalIssued; // chép giá trị bộ đếm TẠI THỜI ĐIỂM NÀY vào id riêng của vé
    }

    public int getId() { // getter — xem số thứ tự của vé này
        return id; // trả về id riêng của object hiện tại
    }

    public static int getTotalIssued() { // phương thức STATIC: hỏi class, không cần object nào — "đã phát tổng cộng bao nhiêu vé?"
        return totalIssued; // trả về bộ đếm chung
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Ticket"
        check(Ticket.getTotalIssued() == 0, "chưa phát vé nào thì tổng phải là 0"); // gọi qua tên class — chưa cần object nào tồn tại

        Ticket t1 = new Ticket(); // phát vé thứ nhất
        Ticket t2 = new Ticket(); // phát vé thứ hai
        Ticket t3 = new Ticket(); // phát vé thứ ba

        check(t1.getId() == 1, "vé đầu tiên phải mang số 1");  // mỗi vé giữ số cấp tại thời điểm tạo
        check(t2.getId() == 2, "vé thứ hai phải mang số 2");   // id tự tăng, không trùng
        check(t3.getId() == 3, "vé thứ ba phải mang số 3");    // tiếp tục tăng
        check(Ticket.getTotalIssued() == 3, "tổng vé đã phát phải là 3"); // bộ đếm class phản ánh mọi lệnh new

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
