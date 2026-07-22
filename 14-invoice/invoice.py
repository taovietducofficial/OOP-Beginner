# Ngôn ngữ: Python
#
# Công dụng: Invoice minh họa Python KHÔNG CÓ overload thật (khác Java/C++)
# — không thể định nghĩa hai "def add_item" cùng tên với số tham số khác
# nhau, bản sau sẽ ĐÈ bản trước. Cách Python làm việc tương đương: một
# phương thức DUY NHẤT với THAM SỐ CÓ GIÁ TRỊ MẶC ĐỊNH (quantity=1).
#
# Tại sao cần học: đây là khác biệt quan trọng giữa các ngôn ngữ khi cùng
# giải quyết một bài toán (bài 07 + Java/C++ dùng overload constructor,
# Python dùng tham số mặc định + *args/**kwargs). Biết rõ ngôn ngữ mình
# dùng KHÔNG hỗ trợ gì giúp tránh việc cố "bê" nguyên xi thiết kế từ ngôn
# ngữ khác sang.


class Invoice:  # khai báo class — khuôn mẫu để tạo ra các object Invoice
    def __init__(self):  # constructor — chạy khi tạo hóa đơn mới
        self._total = 0  # tổng tiền hóa đơn — thay đổi mỗi khi thêm dòng hàng mới

    def add_item(self, name, price, quantity=1):  # MỘT phương thức duy nhất, quantity mặc định = 1 nếu không truyền — thay cho overload
        del name  # tên hàng không dùng để tính tổng, chỉ để minh họa chữ ký thực tế của add_item trên hóa đơn
        if price <= 0:  # validate ở biên: đơn giá không hợp lệ
            raise ValueError("Đơn giá phải > 0")  # chặn ngay tại biên
        if quantity <= 0:  # validate ở biên: số lượng không hợp lệ
            raise ValueError("Số lượng phải > 0")  # chặn ngay tại biên
        self._total += price * quantity  # cộng dồn thành tiền của dòng hàng này vào tổng hóa đơn

    def get_total(self):  # getter — xem tổng tiền hóa đơn hiện tại
        return self._total  # trả về tổng đã cộng dồn


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python invoice.py"
    inv = Invoice()  # tạo hóa đơn mới, tổng tiền = 0
    inv.add_item("But", 5000)         # không truyền quantity — dùng giá trị mặc định là 1
    inv.add_item("Vo", 8000, 3)       # truyền quantity rõ ràng là 3
    assert inv.get_total() == 5000 + 8000 * 3, "tổng tiền hóa đơn tính sai"  # 5.000 + 24.000 = 29.000

    blocked = False  # cờ đánh dấu: đơn giá không hợp lệ có bị chặn không
    try:  # cố thêm hàng với đơn giá âm
        inv.add_item("Loi", -1000)  # giá trị không hợp lệ
    except ValueError:  # bắt đúng loại lỗi mà add_item ném ra
        blocked = True  # đánh dấu: validate đã chặn thành công
    assert blocked, "đơn giá âm phải bị chặn"  # xác nhận validate hoạt động dù gọi có truyền quantity hay không

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
