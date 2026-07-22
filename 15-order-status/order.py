# Ngôn ngữ: Python
#
# Công dụng: Order minh họa OBJECT CÓ TRẠNG THÁI RỜI RẠC (state machine) —
# một đơn hàng chỉ được đi qua các bước PENDING -> PAID -> SHIPPED ->
# DELIVERED theo ĐÚNG THỨ TỰ; mỗi phương thức chuyển trạng thái tự kiểm tra
# trạng thái hiện tại trước khi cho phép đổi.
#
# Tại sao cần học: bài 06 (BankAccount) đóng gói một con SỐ chỉ đổi qua
# phương thức có validate. Bài này đóng gói một TRẠNG THÁI RỜI RẠC (một
# trong vài giá trị cố định) — validate ở đây không kiểm tra số, mà kiểm tra
# "đang ở bước nào thì được phép nhảy sang bước nào". Đây là nền cho mọi hệ
# thống có vòng đời (đơn hàng, vé máy bay, ticket hỗ trợ...).


class Order:  # khai báo class — khuôn mẫu để tạo ra các object Order
    def __init__(self):  # constructor — chạy khi tạo đơn hàng mới
        self._status = "PENDING"  # trạng thái đơn hàng — mọi đơn mới tạo đều bắt đầu ở "PENDING" (chờ thanh toán)

    def pay(self):  # chuyển trạng thái: PENDING -> PAID
        if self._status != "PENDING":  # guard: chặn nếu không đúng bước
            raise ValueError("Chỉ đơn PENDING mới thanh toán được")  # báo lỗi rõ nguyên nhân
        self._status = "PAID"  # hợp lệ: cập nhật trạng thái

    def ship(self):  # chuyển trạng thái: PAID -> SHIPPED
        if self._status != "PAID":  # guard: chặn nếu không đúng bước
            raise ValueError("Chỉ đơn PAID mới giao được")  # báo lỗi rõ nguyên nhân
        self._status = "SHIPPED"  # hợp lệ: cập nhật trạng thái

    def deliver(self):  # chuyển trạng thái: SHIPPED -> DELIVERED
        if self._status != "SHIPPED":  # guard: chặn nếu không đúng bước
            raise ValueError("Chỉ đơn SHIPPED mới hoàn tất được")  # báo lỗi rõ nguyên nhân
        self._status = "DELIVERED"  # hợp lệ: cập nhật trạng thái

    def cancel(self):  # hủy đơn — CHỈ cho phép khi chưa giao hàng (PENDING hoặc PAID)
        if self._status not in ("PENDING", "PAID"):  # guard: đơn đã SHIPPED/DELIVERED thì không hủy được nữa
            raise ValueError("Đơn đã giao thì không hủy được")  # chặn hủy khi đã quá muộn
        self._status = "CANCELLED"  # hợp lệ: cập nhật trạng thái

    def get_status(self):  # getter — xem trạng thái hiện tại của đơn hàng
        return self._status  # trả về trạng thái


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python order.py"
    o = Order()  # tạo đơn hàng mới — bắt đầu ở PENDING
    assert o.get_status() == "PENDING", "đơn mới tạo phải ở PENDING"  # trạng thái khởi tạo đúng

    o.pay()  # thanh toán — PENDING -> PAID
    assert o.get_status() == "PAID", "sau pay() phải ở PAID"  # đúng bước tiếp theo

    o.ship()  # giao vận — PAID -> SHIPPED
    assert o.get_status() == "SHIPPED", "sau ship() phải ở SHIPPED"  # đúng bước tiếp theo

    blocked = False  # cờ đánh dấu: hủy đơn đã SHIPPED có bị chặn không
    try:  # cố hủy khi đã SHIPPED
        o.cancel()  # thao tác không hợp lệ ở bước này
    except ValueError:  # bắt đúng loại lỗi mà cancel() ném ra
        blocked = True  # đánh dấu: guard đã chặn thành công
    assert blocked, "đơn đã SHIPPED thì không được hủy"  # xác nhận guard hoạt động
    assert o.get_status() == "SHIPPED", "trạng thái không đổi khi bước hủy bị chặn"  # thao tác lỗi thì trạng thái giữ nguyên

    o.deliver()  # hoàn tất — SHIPPED -> DELIVERED
    assert o.get_status() == "DELIVERED", "sau deliver() phải ở DELIVERED"  # đúng bước cuối cùng

    skipped = Order()  # tạo đơn khác để thử nhảy bước sai thứ tự
    skip_blocked = False  # cờ đánh dấu: giao hàng khi chưa thanh toán có bị chặn không
    try:  # cố ship() khi còn PENDING, chưa pay()
        skipped.ship()  # thao tác không hợp lệ
    except ValueError:  # bắt đúng loại lỗi mà ship() ném ra
        skip_blocked = True  # đánh dấu: guard đã chặn thành công
    assert skip_blocked, "chưa pay() thì không được ship()"  # xác nhận không thể nhảy cóc bước

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
