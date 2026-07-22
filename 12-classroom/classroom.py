# Ngôn ngữ: Python
#
# Công dụng: Classroom minh họa một class QUẢN LÝ TẬP HỢP nhiều object khác
# cùng loại (list các Student) — thêm phần tử, và tính toán tổng hợp
# (average, top) bằng cách duyệt qua cả tập hợp.
#
# Tại sao cần học: dữ liệu thật hiếm khi chỉ có 1 object đơn lẻ — một lớp có
# nhiều học sinh, một đơn hàng có nhiều sản phẩm, một giỏ hàng có nhiều món.
# Biết cách một class "chứa nhiều object con" và tổng hợp dữ liệu từ chúng
# là kỹ năng nền cho hầu hết hệ thống thực tế.


class Student:  # class phụ trợ — mỗi học sinh có tên và điểm
    def __init__(self, name, score):  # constructor — chạy khi tạo một học sinh
        if score < 0 or score > 10:  # validate ở biên: điểm phải hợp lệ
            raise ValueError("Điểm phải trong khoảng 0-10")  # ném lỗi để object sai không được tạo
        self._name = name  # tên học sinh — riêng cho từng object, không đổi sau khi tạo
        self._score = score  # điểm số — riêng cho từng object, không đổi sau khi tạo

    def get_name(self):  # getter — xem tên học sinh
        return self._name  # trả về tên

    def get_score(self):  # getter — xem điểm học sinh
        return self._score  # trả về điểm


class Classroom:  # khai báo class — khuôn mẫu để tạo ra các object Classroom
    def __init__(self, name):  # constructor — chạy khi tạo một lớp học, ban đầu chưa có học sinh nào
        self._name = name  # tên lớp — riêng cho từng object, không đổi sau khi tạo
        self._students = []  # TẬP HỢP: Classroom chứa nhiều Student, mỗi lớp giữ danh sách riêng của mình (list rỗng ban đầu)

    def get_name(self):  # getter — xem tên lớp
        return self._name  # trả về tên lớp

    def add_student(self, student):  # thêm một học sinh vào lớp
        self._students.append(student)  # đưa vào cuối danh sách

    def size(self):  # đếm số học sinh hiện có trong lớp
        return len(self._students)  # kích thước danh sách

    def average_score(self):  # tính điểm trung bình cả lớp — TỔNG HỢP dữ liệu từ nhiều object con
        if not self._students:  # lớp rỗng: quy ước trung bình là 0, tránh chia cho 0
            return 0  # trả về 0 khi chưa có học sinh nào
        total = sum(s.get_score() for s in self._students)  # duyệt qua từng học sinh, cộng điểm của nó vào tổng
        return total / len(self._students)  # trung bình = tổng điểm / số học sinh

    def top_student(self):  # tìm tên học sinh điểm cao nhất — TỔNG HỢP dữ liệu bằng cách so sánh qua từng object con
        if not self._students:  # không có gì để tìm nếu lớp rỗng
            raise ValueError("Lớp chưa có học sinh nào")  # báo lỗi rõ ràng thay vì trả về giá trị vô nghĩa
        top = max(self._students, key=lambda s: s.get_score())  # max() với key: tìm phần tử có điểm lớn nhất, duyệt toàn bộ danh sách
        return top.get_name()  # trả về tên học sinh điểm cao nhất


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python classroom.py"
    room = Classroom("10A")  # tạo lớp 10A, ban đầu rỗng
    assert room.get_name() == "10A", "tên lớp phải giữ đúng như lúc tạo"  # getter trả đúng dữ liệu đã gán
    assert room.size() == 0, "lớp mới tạo chưa có học sinh nào"  # chưa add_student lần nào

    room.add_student(Student("An", 8.0))    # thêm học sinh An, điểm 8.0
    room.add_student(Student("Binh", 9.5))  # thêm học sinh Binh, điểm 9.5
    room.add_student(Student("Chi", 7.0))   # thêm học sinh Chi, điểm 7.0

    assert room.size() == 3, "lớp phải có 3 học sinh"  # đếm đúng số phần tử đã thêm
    assert abs(room.average_score() - 8.1666666667) < 1e-6, "điểm trung bình tính sai"  # (8.0+9.5+7.0)/3, so sánh gần đúng vì số thực
    assert room.top_student() == "Binh", "học sinh điểm cao nhất phải là Binh"  # 9.5 là điểm cao nhất

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
