# Ngôn ngữ: Python

# Công dụng: Currency minh họa CACHED/INTERNED FACTORY — Currency.of(code)
# tra một dict cấp module trước: nếu "code" đã từng được tạo, TRẢ LẠI ĐÚNG
# object cũ thay vì tạo mới; nếu chưa, tạo một lần rồi lưu vào dict để lần
# sau dùng lại. Gọi of("USD") nhiều lần luôn trả về CÙNG MỘT object ("is"
# đúng, không chỉ "==" đúng).

# Tại sao cần học: bài 13 (Temperature) dùng static factory nhưng mỗi lần
# gọi vẫn tạo một object mới. Bài này thêm một lớp: factory còn NHỚ LẠI kết
# quả trước đó theo khóa (code), tránh tạo trùng lặp những object có cùng
# nội dung — giống cách CPython tự cache sẵn các số nguyên nhỏ (-5..256).

_SUPPORTED_SYMBOLS = {"USD": "$", "VND": "₫", "EUR": "€"}  # danh sách mã tiền tệ hợp lệ và ký hiệu tương ứng — hằng số module, dùng chung


class Currency:  # đại diện một loại tiền tệ — chỉ tạo được qua of(code), không gọi Currency(...) trực tiếp
    _registry = {}  # "sổ đăng ký" dùng chung ở CẤP CLASS (không phải cấp instance) — lưu MỌI Currency đã từng tạo, theo khóa code

    def __init__(self, code, symbol):  # không gọi trực tiếp từ bên ngoài theo quy ước — luôn đi qua Currency.of(code)
        self._code = code
        self._symbol = symbol

    @staticmethod
    def of(code):  # static factory CÓ CACHE — trái tim của bài này
        if code in Currency._registry:  # đã từng tạo trước đó — trả lại ĐÚNG object cũ, KHÔNG tạo mới
            return Currency._registry[code]
        symbol = _SUPPORTED_SYMBOLS.get(code)
        if symbol is None:  # validate ở biên
            raise ValueError(f"Mã tiền tệ không được hỗ trợ: {code}")
        created = Currency(code, symbol)  # CHỈ tạo mới khi thật sự chưa có trong sổ đăng ký
        Currency._registry[code] = created  # lưu lại để LẦN SAU gọi of(cùng code) trả về đúng object này
        return created

    def get_code(self):  # getter — xem mã tiền tệ
        return self._code

    def get_symbol(self):  # getter — xem ký hiệu
        return self._symbol


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python currency.py"
    usd1 = Currency.of("USD")
    usd2 = Currency.of("USD")  # gọi lần thứ hai với CÙNG code
    assert usd1 is usd2, "gọi of('USD') hai lần phải trả về CÙNG MỘT object (is), không phải hai bản sao"
    assert usd1.get_symbol() == "$", "ký hiệu USD phải là $"

    vnd = Currency.of("VND")
    assert vnd is not usd1, "hai code khác nhau phải là hai object khác nhau"
    assert vnd.get_symbol() == "₫", "ký hiệu VND phải đúng"

    blocked = False  # cờ đánh dấu: mã tiền tệ không hỗ trợ có bị chặn không
    try:
        Currency.of("XYZ")
    except ValueError:
        blocked = True
    assert blocked, "mã tiền tệ không được hỗ trợ phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
