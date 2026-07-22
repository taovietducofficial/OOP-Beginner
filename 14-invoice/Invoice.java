/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Invoice minh họa OVERLOAD PHƯƠNG THỨC (method overloading) —
 * hai phương thức cùng tên "addItem" nhưng khác SỐ LƯỢNG tham số; bản ít
 * tham số hơn gọi lại bản đủ tham số với giá trị mặc định, giống cách bài
 * 07 dùng this(...) cho constructor.
 *
 * Tại sao cần học: bài 07 overload CONSTRUCTOR. Overload thường (phương
 * thức không phải constructor) còn phổ biến hơn: người dùng class được
 * chọn gọi bản "rút gọn" khi không cần nêu hết mọi tham số, mà không phải
 * nhớ giá trị mặc định là gì hay tự gõ lại nó mỗi lần.
 */
public class Invoice { // khai báo class — khuôn mẫu để tạo ra các object Invoice

    private double total = 0; // tổng tiền hóa đơn — thay đổi mỗi khi thêm dòng hàng mới

    public void addItem(String name, double price) { // OVERLOAD 1: thêm hàng với số lượng mặc định là 1
        addItem(name, price, 1); // ủy quyền cho bản đầy đủ — logic tính toán CHỈ nằm ở một chỗ duy nhất
    }

    public void addItem(String name, double price, int quantity) { // OVERLOAD 2: thêm hàng với số lượng chỉ định rõ
        if (price <= 0) throw new IllegalArgumentException("Đơn giá phải > 0"); // validate ở biên: đơn giá không hợp lệ
        if (quantity <= 0) throw new IllegalArgumentException("Số lượng phải > 0"); // validate ở biên: số lượng không hợp lệ
        total += price * quantity; // cộng dồn thành tiền của dòng hàng này vào tổng hóa đơn
    }

    public double getTotal() { // getter — xem tổng tiền hóa đơn hiện tại
        return total; // trả về tổng đã cộng dồn
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Invoice"
        Invoice inv = new Invoice(); // tạo hóa đơn mới, tổng tiền = 0
        inv.addItem("But", 5000);        // gọi bản 2 tham số — số lượng ngầm định là 1
        inv.addItem("Vo", 8000, 3);      // gọi bản 3 tham số — số lượng chỉ định rõ là 3
        check(inv.getTotal() == 5000 + 8000 * 3, "tổng tiền hóa đơn tính sai"); // 5.000 + 24.000 = 29.000

        boolean blocked = false; // cờ đánh dấu: đơn giá không hợp lệ có bị chặn không
        try { inv.addItem("Loi", -1000); } catch (IllegalArgumentException e) { blocked = true; } // đơn giá âm — phải bị chặn dù đi qua bản overload nào
        check(blocked, "đơn giá âm phải bị chặn"); // xác nhận validate hoạt động ở bản đầy đủ, áp dụng cho cả bản rút gọn

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
