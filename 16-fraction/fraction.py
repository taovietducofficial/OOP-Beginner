# Ngôn ngữ: Python
#
# Công dụng: Fraction minh họa OBJECT BẤT BIẾN (immutable) — không có
# setter nào, mọi phép toán (add, multiply) không sửa object đang có mà
# TRẢ VỀ MỘT OBJECT MỚI. Tử số/mẫu số được rút gọn và chuẩn hóa dấu ngay
# trong constructor, chạy đúng một lần.
#
# Tại sao cần học: bài 04 (Counter) và bài 06 (BankAccount) đều là object
# CÓ TRẠNG THÁI THAY ĐỔI — phương thức sửa dữ liệu ngay trên chính object.
# Bài này đối lập hoàn toàn: object bất biến an toàn hơn khi chia sẻ giữa
# nhiều nơi trong chương trình (không ai vô tình sửa được nó) — nền tảng
# của tuple, str, frozenset trong Python.

import math  # thư viện chuẩn: math.gcd — ước chung lớn nhất, không cần tự viết thuật toán Euclid


class Fraction:  # khai báo class — khuôn mẫu để tạo ra các object Fraction
    def __init__(self, numerator, denominator):  # constructor — chạy khi gọi "Fraction(...)"
        if denominator == 0:  # validate ở biên
            raise ValueError("Mẫu số không được bằng 0")

        if denominator < 0:  # chuẩn hóa dấu: mẫu số luôn dương, dấu âm (nếu có) dồn hết về tử số
            numerator = -numerator
            denominator = -denominator

        g = math.gcd(numerator, denominator)  # math.gcd tự lấy giá trị tuyệt đối, luôn trả về ước chung không âm
        self._numerator = numerator // g      # rút gọn tử số — chia nguyên vì g luôn chia hết cả hai
        self._denominator = denominator // g  # rút gọn mẫu số

    def get_numerator(self):  # getter — xem tử số hiện tại (đã rút gọn)
        return self._numerator

    def get_denominator(self):  # getter — xem mẫu số hiện tại (đã rút gọn)
        return self._denominator

    def add(self, other):  # cộng phân số — KHÔNG sửa self hay other, trả về Fraction MỚI
        return Fraction(
            self._numerator * other._denominator + other._numerator * self._denominator,
            self._denominator * other._denominator,
        )  # a/b + c/d = (ad + bc) / bd — constructor mới tự rút gọn kết quả

    def multiply(self, other):  # nhân phân số — KHÔNG sửa self hay other, trả về Fraction MỚI
        return Fraction(self._numerator * other._numerator, self._denominator * other._denominator)  # a/b * c/d = ac / bd

    def __str__(self):  # object tự mô tả chính nó, vd. "1/2"
        return f"{self._numerator}/{self._denominator}"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python fraction.py"
    a = Fraction(2, 4)  # 2/4 phải tự rút gọn
    assert str(a) == "1/2", "2/4 phải tự rút gọn thành 1/2"

    b = Fraction(-1, -2)  # cả tử lẫn mẫu âm — phải chuẩn hóa thành dương
    assert str(b) == "1/2", "cả tử lẫn mẫu âm phải chuẩn hóa thành dương"

    c = Fraction(1, -2)  # mẫu âm — dấu phải dồn về tử số
    assert str(c) == "-1/2", "dấu âm phải dồn về tử số, mẫu số luôn dương"

    total = a.add(Fraction(1, 3))  # 1/2 + 1/3 = 5/6
    assert str(total) == "5/6", "1/2 + 1/3 phải bằng 5/6"
    assert str(a) == "1/2", "add() không được sửa object gốc — object bất biến"  # a giữ nguyên sau add()

    product = a.multiply(Fraction(2, 3))  # 1/2 * 2/3 = 2/6 = 1/3
    assert str(product) == "1/3", "1/2 * 2/3 phải rút gọn thành 1/3"

    blocked = False  # cờ đánh dấu: mẫu số 0 có bị chặn không
    try:
        Fraction(1, 0)  # mẫu số 0 phải bị chặn
    except ValueError:
        blocked = True
    assert blocked, "mẫu số bằng 0 phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
