# Ngôn ngữ: Python
#
# Công dụng: Money minh họa sự khác nhau giữa "is" (so sánh ĐỊA CHỈ — có phải
# cùng một object trong bộ nhớ) và == (so sánh NỘI DUNG — gọi __eq__ mà ta ghi
# đè), kèm quy ước bắt buộc: ghi đè __eq__ thì phải ghi đè __hash__.
#
# Tại sao cần học: dùng "is" thay == (hoặc ngược lại) là lỗi Python kinh điển —
# bug chập chờn vì đôi khi hai biến tình cờ trỏ cùng object. Ghi đè __eq__ mà
# quên __hash__ làm object không bỏ được vào set/dict (Python tự vô hiệu hóa
# __hash__ khi chỉ ghi đè __eq__).


class Money:  # khai báo class — khuôn mẫu để tạo ra các object Money
    def __init__(self, amount, currency):  # constructor — chạy khi gọi "Money(...)"
        if amount < 0:  # validate: chặn tiền âm
            raise ValueError("Số tiền không được âm")  # ném lỗi ngay tại biên
        if not currency:  # validate: loại tiền bắt buộc
            raise ValueError("Loại tiền không được rỗng")  # ném lỗi ngay tại biên
        self._amount = amount  # số tiền (đơn vị nhỏ nhất) — dùng số nguyên, không dùng float cho tiền
        self._currency = currency  # loại tiền, vd. "VND", "USD"

    def __eq__(self, other):  # ghi đè == thừa hưởng từ object (bản mặc định chỉ so địa chỉ, y hệt "is")
        if not isinstance(other, Money):  # khác class (hoặc None) → không thể bằng nhau
            return NotImplemented  # quy ước Python: trả NotImplemented để nhường quyền so sánh cho phía bên kia
        return self._amount == other._amount and self._currency == other._currency  # bằng nhau khi CÙNG số tiền và CÙNG loại tiền

    def __hash__(self):  # quy ước bắt buộc: đã ghi đè __eq__ thì phải ghi đè __hash__
        return hash((self._amount, self._currency))  # băm tuple gồm đúng các field mà __eq__ so sánh — thư viện chuẩn lo phần còn lại


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python money.py"
    a = Money(100_000, "VND")  # tạo object thứ nhất
    b = Money(100_000, "VND")  # tạo object thứ hai — CÙNG giá trị nhưng KHÁC object trong bộ nhớ

    assert a is not b, "hai lần khởi tạo phải tạo hai object khác nhau"  # "is" so địa chỉ: hai object riêng biệt
    assert a == b, "cùng số tiền + loại tiền phải bằng nhau"  # == gọi __eq__ ta ghi đè: so nội dung
    assert hash(a) == hash(b), "bằng nhau phải cùng hash"  # quy ước __eq__/__hash__
    assert a != Money(100_000, "USD"), "khác loại tiền không được bằng nhau"  # 100k VND khác 100k USD
    assert a != Money(50_000, "VND"), "khác số tiền không được bằng nhau"  # 100k khác 50k
    assert a != None, "so với None phải trả về False"  # so với None không được ném lỗi (NotImplemented → Python tự kết luận khác nhau)

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
