# Ngôn ngữ: Python
#
# Công dụng: Circle làm quen với thuộc tính CLASS (hằng số PI khai báo ngay
# trong thân class, dùng chung cho mọi object) khác với thuộc tính INSTANCE
# như radius (gán qua self, thuộc về TỪNG object, mỗi object một giá trị riêng).
#
# Tại sao cần học: nhầm lẫn giữa thuộc tính class và thuộc tính instance là lỗi
# rất phổ biến của người mới, gây ra bug khó tìm (dữ liệu bị "dùng chung" ngoài
# ý muốn giữa các object). Hiểu đúng khái niệm này là điều kiện bắt buộc trước
# khi học classmethod, singleton, hay biến đếm toàn cục.


class Circle:  # khai báo class — khuôn mẫu để tạo ra các object Circle
    PI = 3.14159  # thuộc tính CLASS: chỉ có 1 bản duy nhất, mọi object Circle dùng chung (Python không có "final" — VIẾT HOA là quy ước hằng số)

    def __init__(self, radius):  # constructor — chạy khi gọi "Circle(...)"
        if radius <= 0:  # validate ở biên: chặn bán kính không hợp lệ
            raise ValueError("Bán kính phải > 0")  # ném lỗi để object sai không được tạo
        self._radius = radius  # thuộc tính INSTANCE: mỗi object Circle có bán kính riêng của mình

    def area(self):  # hàm tính diện tích — dùng hằng số chung PI + dữ liệu riêng radius
        return Circle.PI * self._radius * self._radius  # truy cập hằng qua TÊN CLASS (Circle.PI) — nói rõ nó là dữ liệu dùng chung

    def circumference(self):  # hàm tính chu vi
        return 2 * Circle.PI * self._radius  # công thức chu vi hình tròn = 2 * PI * r


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python circle.py"
    c = Circle(2)  # tạo object Circle với bán kính = 2
    assert abs(c.area() - 12.56636) < 1e-5, "diện tích bán kính 2 sai"  # so sánh gần đúng vì số thực có sai số dấu phẩy động
    assert abs(c.circumference() - 12.56636) < 1e-5, "chu vi bán kính 2 sai"  # tương tự, kiểm tra chu vi gần đúng

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
