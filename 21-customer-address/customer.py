# Ngôn ngữ: Python

# Công dụng: Customer/Address minh họa NULL OBJECT PATTERN — thay vì biểu
# diễn "khách chưa có địa chỉ" bằng None rồi kiểm tra "if address is None"
# khắp nơi, ta tạo một Address ĐẶC BIỆT (UNKNOWN) đại diện cho sự vắng mặt
# đó. UNKNOWN vẫn là một Address thật — vẫn gọi được get_display_text() bình
# thường, tự nó biết trả lời "chưa có địa chỉ" thay vì bắt nơi gọi phải
# kiểm tra None trước mỗi lần dùng.

# Tại sao cần học: bài 13 (Temperature) dùng static factory để tạo object
# đại diện cho một GIÁ TRỊ CÓ THẬT. Bài này dùng đúng kỹ thuật đó nhưng cho
# mục đích ngược lại — tạo object đại diện cho SỰ VẮNG MẶT của giá trị.


class Address:  # đại diện một địa chỉ giao hàng — hoặc "chưa có địa chỉ nào"
    def __init__(self, street, city, unknown=False):  # constructor "thô" — thường không gọi trực tiếp từ bên ngoài, xem of()/UNKNOWN bên dưới
        self._street = street  # tên đường — rỗng nếu là UNKNOWN
        self._city = city      # thành phố — rỗng nếu là UNKNOWN
        self._unknown = unknown  # cờ đánh dấu đây có phải Address đặc biệt (UNKNOWN) hay không

    @staticmethod
    def of(street, city):  # static factory — tạo địa chỉ CỤ THỂ, có thật
        if not street:  # validate ở biên
            raise ValueError("Tên đường không được rỗng")
        if not city:  # validate ở biên
            raise ValueError("Thành phố không được rỗng")
        return Address(street, city, False)  # False: không phải UNKNOWN

    def is_unknown(self):  # kiểm tra: đây có phải Address "chưa có gì" hay không
        return self._unknown

    def get_display_text(self):  # TỰ BIẾT hiển thị đúng cách — nơi gọi không cần kiểm tra None trước
        if self._unknown:  # hành vi an toàn khi không có dữ liệu thật
            return "Chưa có địa chỉ giao hàng"
        return f"{self._street}, {self._city}"  # hành vi bình thường khi có dữ liệu thật


Address.UNKNOWN = Address("", "", True)  # hằng số dùng chung ở mức module — MỘT object duy nhất đại diện "chưa có địa chỉ"


class Customer:  # khai báo class — khuôn mẫu để tạo ra các object Customer
    def __init__(self, name, address=None):  # address=None chỉ là "chưa truyền tham số"; NGAY SAU ĐÂY sẽ quy về Address.UNKNOWN, không giữ None
        if not name:  # validate ở biên
            raise ValueError("Tên khách hàng không được rỗng")
        self._name = name
        self._address = address if address is not None else Address.UNKNOWN  # quy None (tham số mặc định) thành Address.UNKNOWN — self._address KHÔNG BAO GIỜ là None

    def has_address(self):  # có địa chỉ THẬT hay không — hỏi thẳng Address thay vì so sánh với None
        return not self._address.is_unknown()

    def get_shipping_label(self):  # nhãn giao hàng — KHÔNG cần "if self._address is None": get_display_text() tự lo phần đó
        return f"{self._name}: {self._address.get_display_text()}"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python customer.py"
    guest = Customer("An")  # chưa cung cấp địa chỉ — tự động là Address.UNKNOWN, không phải None
    assert not guest.has_address(), "khách chưa cung cấp địa chỉ thì has_address() phải là False"
    assert guest.get_shipping_label() == "An: Chưa có địa chỉ giao hàng", "nhãn giao hàng khi chưa có địa chỉ phải đúng thông báo mặc định"

    home = Address.of("123 Lê Lợi", "Đà Nẵng")  # địa chỉ cụ thể, có thật
    binh = Customer("Binh", home)
    assert binh.has_address(), "khách có địa chỉ cụ thể thì has_address() phải là True"
    assert binh.get_shipping_label() == "Binh: 123 Lê Lợi, Đà Nẵng", "nhãn giao hàng khi có địa chỉ phải in đúng street, city"

    assert Address.UNKNOWN.is_unknown(), "Address.UNKNOWN phải tự nhận là unknown"
    assert not home.is_unknown(), "Address cụ thể không được coi là unknown"

    blocked_street = False  # cờ đánh dấu: đường rỗng có bị chặn không
    try:
        Address.of("", "Hà Nội")
    except ValueError:
        blocked_street = True
    assert blocked_street, "tên đường rỗng phải bị chặn khi tạo Address cụ thể"

    blocked_name = False  # cờ đánh dấu: tên khách hàng rỗng có bị chặn không
    try:
        Customer("")
    except ValueError:
        blocked_name = True
    assert blocked_name, "tên khách hàng rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
