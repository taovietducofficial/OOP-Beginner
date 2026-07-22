/*
 * Ngôn ngữ: Java
 *
 * Công dụng: Order minh họa OBJECT CÓ TRẠNG THÁI RỜI RẠC (state machine) —
 * một đơn hàng chỉ được đi qua các bước PENDING -> PAID -> SHIPPED ->
 * DELIVERED theo ĐÚNG THỨ TỰ; mỗi phương thức chuyển trạng thái tự kiểm
 * tra trạng thái hiện tại trước khi cho phép đổi.
 *
 * Tại sao cần học: bài 06 (BankAccount) đóng gói một con SỐ chỉ đổi qua
 * phương thức có validate. Bài này đóng gói một TRẠNG THÁI RỜI RẠC (một
 * trong vài giá trị cố định) — validate ở đây không kiểm tra số, mà kiểm
 * tra "đang ở bước nào thì được phép nhảy sang bước nào". Đây là nền cho
 * mọi hệ thống có vòng đời (đơn hàng, vé máy bay, ticket hỗ trợ...).
 */
public class Order { // khai báo class — khuôn mẫu để tạo ra các object Order

    private String status = "PENDING"; // trạng thái đơn hàng — mọi đơn mới tạo đều bắt đầu ở "PENDING" (chờ thanh toán)

    public void pay() { // chuyển trạng thái: PENDING -> PAID
        if (!status.equals("PENDING")) throw new IllegalStateException("Chỉ đơn PENDING mới thanh toán được"); // guard: chặn nếu không đúng bước
        status = "PAID"; // hợp lệ: cập nhật trạng thái
    }

    public void ship() { // chuyển trạng thái: PAID -> SHIPPED
        if (!status.equals("PAID")) throw new IllegalStateException("Chỉ đơn PAID mới giao được"); // guard: chặn nếu không đúng bước
        status = "SHIPPED"; // hợp lệ: cập nhật trạng thái
    }

    public void deliver() { // chuyển trạng thái: SHIPPED -> DELIVERED
        if (!status.equals("SHIPPED")) throw new IllegalStateException("Chỉ đơn SHIPPED mới hoàn tất được"); // guard: chặn nếu không đúng bước
        status = "DELIVERED"; // hợp lệ: cập nhật trạng thái
    }

    public void cancel() { // hủy đơn — CHỈ cho phép khi chưa giao hàng (PENDING hoặc PAID)
        if (!status.equals("PENDING") && !status.equals("PAID")) { // guard: đơn đã SHIPPED/DELIVERED thì không hủy được nữa
            throw new IllegalStateException("Đơn đã giao thì không hủy được"); // chặn hủy khi đã quá muộn
        }
        status = "CANCELLED"; // hợp lệ: cập nhật trạng thái
    }

    public String getStatus() { // getter — xem trạng thái hiện tại của đơn hàng
        return status; // trả về trạng thái
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Order"
        Order o = new Order(); // tạo đơn hàng mới — bắt đầu ở PENDING
        check(o.getStatus().equals("PENDING"), "đơn mới tạo phải ở PENDING"); // trạng thái khởi tạo đúng

        o.pay(); // thanh toán — PENDING -> PAID
        check(o.getStatus().equals("PAID"), "sau pay() phải ở PAID"); // đúng bước tiếp theo

        o.ship(); // giao vận — PAID -> SHIPPED
        check(o.getStatus().equals("SHIPPED"), "sau ship() phải ở SHIPPED"); // đúng bước tiếp theo

        boolean blocked = false; // cờ đánh dấu: hủy đơn đã SHIPPED có bị chặn không
        try { o.cancel(); } catch (IllegalStateException e) { blocked = true; } // cố hủy khi đã SHIPPED — phải bị chặn
        check(blocked, "đơn đã SHIPPED thì không được hủy"); // xác nhận guard hoạt động
        check(o.getStatus().equals("SHIPPED"), "trạng thái không đổi khi bước hủy bị chặn"); // thao tác lỗi thì trạng thái giữ nguyên

        o.deliver(); // hoàn tất — SHIPPED -> DELIVERED
        check(o.getStatus().equals("DELIVERED"), "sau deliver() phải ở DELIVERED"); // đúng bước cuối cùng

        Order skipped = new Order(); // tạo đơn khác để thử nhảy bước sai thứ tự
        boolean skipBlocked = false; // cờ đánh dấu: giao hàng khi chưa thanh toán có bị chặn không
        try { skipped.ship(); } catch (IllegalStateException e) { skipBlocked = true; } // cố ship() khi còn PENDING, chưa pay() — phải bị chặn
        check(skipBlocked, "chưa pay() thì không được ship()"); // xác nhận không thể nhảy cóc bước

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
