# Ngôn ngữ: Python
#
# Công dụng: Person minh họa một object nhận OBJECT KHÁC làm tham số
# (greet(other)) và gọi phương thức trên object đó (other.get_name()).
#
# Tại sao cần học: đây là cách các object THỰC SỰ cộng tác với nhau trong hệ
# thống thực tế — vd. order.apply_discount(coupon), account.transfer_to(other_account).
# Nắm được cách 1 object thao tác dựa trên dữ liệu của object khác là bước đệm
# bắt buộc trước khi học kế thừa và đa hình ở các tầng tiếp theo.


class Person:  # khai báo class — khuôn mẫu để tạo ra các object Person
    def __init__(self, name):  # constructor — chạy khi gọi "Person(...)"
        if not name:  # validate: tên không được thiếu (chuỗi rỗng hoặc None đều bị chặn)
            raise ValueError("Tên không được rỗng")  # ném lỗi ngay tại biên
        self._name = name  # gán tham số truyền vào cho thuộc tính name (dấu "_" = quy ước private)

    def get_name(self):  # getter — cho object khác đọc được tên, không khuyến khích sửa trực tiếp
        return self._name  # trả về tên của object hiện tại

    def greet(self, other):  # hàm nhận object Person khác làm tham số — hai object tương tác với nhau
        return f"{self._name} chào {other.get_name()}"  # dùng tên của chính mình (self._name) + gọi get_name() trên object "other"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python person.py"
    an = Person("An")  # tạo object thứ nhất
    binh = Person("Binh")  # tạo object thứ hai

    assert an.greet(binh) == "An chào Binh", "An chào Binh sai"  # "an" chào "binh" — truyền binh làm tham số
    assert binh.greet(an) == "Binh chào An", "Binh chào An sai"  # ngược lại — truyền an làm tham số

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
