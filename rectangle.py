# Ngôn ngữ: Python
#
# Công dụng: Rectangle gói dữ liệu (width, height) và hành vi (area, perimeter)
# vào chung một class — bài đầu tiên minh họa Class & Object.
#
# Tại sao cần học: đây là viên gạch nền của toàn bộ OOP. Mọi hệ thống thực tế
# (đơn hàng, tài khoản, sản phẩm...) đều được mô hình hóa bằng class/object
# như thế này. Không nắm chắc bước "gom dữ liệu + hành vi vào 1 class" thì
# không thể hiểu các bài sau về đóng gói, kế thừa, đa hình.


class Rectangle:  # khai báo class — khuôn mẫu để tạo ra các object Rectangle
    def __init__(self, width, height):  # constructor — chạy khi gọi "Rectangle(...)" để khởi tạo object (self = object đang được tạo)
        if width <= 0 or height <= 0:  # validate ở biên: chặn dữ liệu sai ngay lúc tạo object
            raise ValueError("Cạnh phải > 0")  # ném lỗi để object sai không bao giờ được tạo ra
        self._width = width  # thuộc tính: chiều rộng — dấu "_" là quy ước "private" của Python (không có private thật như Java)
        self._height = height  # thuộc tính: chiều cao — riêng cho từng object

    def area(self):  # hàm tính diện tích — hành vi của object, dùng dữ liệu (width, height) của chính nó
        return self._width * self._height  # công thức diện tích hình chữ nhật = rộng * cao

    def perimeter(self):  # hàm tính chu vi — cũng là hành vi thao tác trên dữ liệu riêng của object
        return 2 * (self._width + self._height)  # công thức chu vi = 2 * (rộng + cao)


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python rectangle.py" (không chạy khi bị import)
    r = Rectangle(4, 5)  # tạo object Rectangle với rộng=4, cao=5 — Python không có từ khóa "new"
    assert r.area() == 20, "diện tích 4x5 phải là 20"  # assert: nếu điều kiện sai thì dừng ngay kèm thông điệp
    assert r.perimeter() == 18, "chu vi 4x5 phải là 18"  # kiểm tra perimeter() tính đúng: 2*(4+5)=18

    square = Rectangle(3, 3)  # tạo thêm 1 object khác — hình vuông là trường hợp đặc biệt của hình chữ nhật (rộng = cao)
    assert square.area() == 9, "diện tích hình vuông cạnh 3 phải là 9"  # kiểm tra diện tích: 3*3=9

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
