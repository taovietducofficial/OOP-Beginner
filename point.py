# Ngôn ngữ: Python
#
# Công dụng: Point minh họa cách Python thay thế NHIỀU CONSTRUCTOR (overloading)
# của Java/C++ — Python chỉ cho phép MỘT __init__, nên dùng THAM SỐ MẶC ĐỊNH
# (x=0.0, y=0.0): gọi Point() ra điểm gốc, gọi Point(3, 4) ra điểm bất kỳ.
#
# Tại sao cần học: mỗi ngôn ngữ giải cùng một bài toán "nhiều cách khởi tạo"
# theo kiểu riêng — Java/C++ overload constructor, Python dùng default argument
# (và classmethod cho các trường hợp phức tạp hơn). Logic khởi tạo vẫn dồn về
# MỘT chỗ — chép code ra nhiều nơi là nguồn bug khi hai bản bị chỉnh lệch nhau.

import math  # thư viện chuẩn: math.sqrt (căn bậc hai) — không tự viết lại


class Point:  # khai báo class — khuôn mẫu để tạo ra các object Point
    def __init__(self, x=0.0, y=0.0):  # MỘT constructor duy nhất — tham số mặc định thay cho overloading: Point() = (0,0), Point(3,4) = (3,4)
        self._x = x  # gán hoành độ truyền vào (hoặc mặc định 0.0) cho object
        self._y = y  # gán tung độ truyền vào (hoặc mặc định 0.0) cho object

    def distance_to(self, other):  # khoảng cách Euclid tới điểm khác — nhận object Point khác làm tham số
        dx = self._x - other._x  # chênh lệch hoành độ giữa hai điểm (cùng class nên đọc được field của "other")
        dy = self._y - other._y  # chênh lệch tung độ giữa hai điểm
        return math.sqrt(dx * dx + dy * dy)  # công thức Pythagoras: căn(dx² + dy²) — dùng math.sqrt của thư viện chuẩn


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python point.py"
    origin = Point()  # không truyền gì — dùng giá trị mặc định, điểm gốc (0, 0)
    p = Point(3, 4)  # truyền đầy đủ — điểm (3, 4)

    assert abs(origin.distance_to(p) - 5) < 1e-9, "khoảng cách (0,0)-(3,4) phải là 5"  # tam giác 3-4-5 kinh điển; so sánh gần đúng vì số thực
    assert abs(p.distance_to(origin) - 5) < 1e-9, "khoảng cách phải đối xứng"  # đo xuôi hay ngược đều cùng kết quả
    assert p.distance_to(p) == 0, "khoảng cách tới chính mình phải là 0"  # điểm cách chính nó 0

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
