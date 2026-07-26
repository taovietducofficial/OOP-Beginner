/*
 * Ngôn ngữ: C++
 * Công dụng: Order minh họa OBJECT CÓ TRẠNG THÁI RỜI RẠC (state machine) —
 * một đơn hàng chỉ được đi qua các bước PENDING -> PAID -> SHIPPED ->
 * DELIVERED theo ĐÚNG THỨ TỰ; mỗi phương thức chuyển trạng thái tự kiểm
 * tra trạng thái hiện tại trước khi cho phép đổi.
 * Tại sao cần học: bài 06 (BankAccount) đóng gói một con SỐ chỉ đổi qua
 * phương thức có validate. Bài này đóng gói một TRẠNG THÁI RỜI RẠC (một
 * trong vài giá trị cố định) — validate ở đây không kiểm tra số, mà kiểm
 * tra "đang ở bước nào thì được phép nhảy sang bước nào". Đây là nền cho
 * mọi hệ thống có vòng đời (đơn hàng, vé máy bay, ticket hỗ trợ...).
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::logic_error để báo lỗi chuyển trạng thái sai
#include <string>    // thư viện chuẩn: std::string lưu trạng thái

class Order { // khai báo class — khuôn mẫu để tạo ra các object Order
private:
    std::string status = "PENDING"; // trạng thái đơn hàng — mọi đơn mới tạo đều bắt đầu ở "PENDING" (chờ thanh toán)

public:
    void pay() { // chuyển trạng thái: PENDING -> PAID
        if (status != "PENDING") throw std::logic_error("Chỉ đơn PENDING mới thanh toán được"); // guard: chặn nếu không đúng bước
        status = "PAID"; // hợp lệ: cập nhật trạng thái
    }

    void ship() { // chuyển trạng thái: PAID -> SHIPPED
        if (status != "PAID") throw std::logic_error("Chỉ đơn PAID mới giao được"); // guard: chặn nếu không đúng bước
        status = "SHIPPED"; // hợp lệ: cập nhật trạng thái
    }

    void deliver() { // chuyển trạng thái: SHIPPED -> DELIVERED
        if (status != "SHIPPED") throw std::logic_error("Chỉ đơn SHIPPED mới hoàn tất được"); // guard: chặn nếu không đúng bước
        status = "DELIVERED"; // hợp lệ: cập nhật trạng thái
    }

    void cancel() { // hủy đơn — CHỈ cho phép khi chưa giao hàng (PENDING hoặc PAID)
        if (status != "PENDING" && status != "PAID") { // guard: đơn đã SHIPPED/DELIVERED thì không hủy được nữa
            throw std::logic_error("Đơn đã giao thì không hủy được"); // chặn hủy khi đã quá muộn
        }
        status = "CANCELLED"; // hợp lệ: cập nhật trạng thái
    }

    const std::string& getStatus() const { // getter — xem trạng thái hiện tại của đơn hàng
        return status; // trả về trạng thái
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Order o; // tạo đơn hàng mới — bắt đầu ở PENDING
    check(o.getStatus() == "PENDING", "đơn mới tạo phải ở PENDING"); // trạng thái khởi tạo đúng

    o.pay(); // thanh toán — PENDING -> PAID
    check(o.getStatus() == "PAID", "sau pay() phải ở PAID"); // đúng bước tiếp theo

    o.ship(); // giao vận — PAID -> SHIPPED
    check(o.getStatus() == "SHIPPED", "sau ship() phải ở SHIPPED"); // đúng bước tiếp theo

    bool blocked = false; // cờ đánh dấu: hủy đơn đã SHIPPED có bị chặn không
    try { o.cancel(); } catch (const std::logic_error&) { blocked = true; } // cố hủy khi đã SHIPPED — phải bị chặn
    check(blocked, "đơn đã SHIPPED thì không được hủy"); // xác nhận guard hoạt động
    check(o.getStatus() == "SHIPPED", "trạng thái không đổi khi bước hủy bị chặn"); // thao tác lỗi thì trạng thái giữ nguyên

    o.deliver(); // hoàn tất — SHIPPED -> DELIVERED
    check(o.getStatus() == "DELIVERED", "sau deliver() phải ở DELIVERED"); // đúng bước cuối cùng

    Order skipped; // tạo đơn khác để thử nhảy bước sai thứ tự
    bool skipBlocked = false; // cờ đánh dấu: giao hàng khi chưa thanh toán có bị chặn không
    try { skipped.ship(); } catch (const std::logic_error&) { skipBlocked = true; } // cố ship() khi còn PENDING, chưa pay() — phải bị chặn
    check(skipBlocked, "chưa pay() thì không được ship()"); // xác nhận không thể nhảy cóc bước

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
