# Ngôn ngữ: Python
#
# Công dụng: Counter minh họa object có TRẠNG THÁI (state) thay đổi qua thời
# gian — mỗi lần gọi increment()/decrement() làm dữ liệu bên trong object đổi,
# và mỗi object Counter giữ trạng thái độc lập với object khác cùng class.
#
# Tại sao cần học: đây là ý tưởng lõi của MỌI object có trạng thái trong thực
# tế — giỏ hàng, phiên đăng nhập, kết nối mạng. Nếu không hiểu rõ mỗi object
# có state riêng, độc lập, rất dễ viết bug chia sẻ dữ liệu ngoài ý muốn khi
# hệ thống lớn lên (đặc biệt trong môi trường nhiều luồng/nhiều người dùng).


class Counter:  # khai báo class — khuôn mẫu để tạo ra các object Counter
    def __init__(self):  # constructor không tham số — chạy khi gọi "Counter()"
        self._value = 0  # giá trị khởi tạo luôn bắt đầu từ 0 — đây là "trạng thái" thay đổi theo thời gian

    def increment(self):  # hàm tăng — thay đổi trạng thái của object
        self._value += 1  # cộng thêm 1 vào giá trị hiện tại (Python không có toán tử ++)

    def decrement(self):  # hàm giảm — thay đổi trạng thái, có kiểm tra ràng buộc
        if self._value == 0:  # validate: chặn giảm xuống âm
            raise ValueError("Không thể giảm dưới 0")  # ném lỗi thay vì để trạng thái sai tồn tại
        self._value -= 1  # trừ 1 khỏi giá trị hiện tại

    def reset(self):  # hàm đưa trạng thái về ban đầu
        self._value = 0  # gán lại giá trị về 0

    def get_value(self):  # getter — cho phép đọc trạng thái hiện tại từ bên ngoài, không khuyến khích sửa trực tiếp
        return self._value  # trả về giá trị hiện tại của object


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python counter.py"
    c = Counter()  # tạo object Counter, value bắt đầu = 0
    assert c.get_value() == 0, "khởi tạo phải là 0"  # kiểm tra giá trị khởi tạo

    c.increment()  # tăng lần 1 -> value = 1
    c.increment()  # tăng lần 2 -> value = 2
    c.increment()  # tăng lần 3 -> value = 3
    assert c.get_value() == 3, "sau 3 lần tăng phải là 3"  # kiểm tra sau 3 lần tăng

    c.decrement()  # giảm 1 lần -> value = 2
    assert c.get_value() == 2, "sau 1 lần giảm phải là 2"  # kiểm tra sau khi giảm

    c.reset()  # đưa value về 0
    assert c.get_value() == 0, "sau reset phải là 0"  # kiểm tra sau reset

    # Object khác của cùng class có trạng thái độc lập.
    other = Counter()  # tạo object thứ hai, hoàn toàn tách biệt với "c"
    other.increment()  # tăng riêng trên object "other" -> other._value = 1
    assert other.get_value() == 1 and c.get_value() == 0, "hai object phải độc lập nhau"  # "c" không bị ảnh hưởng bởi "other"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
