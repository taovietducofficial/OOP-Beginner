# Ngôn ngữ: Python
#
# Công dụng: StudentRecord có nhiều thuộc tính (name, age, score) và cho thấy
# một phương thức (summary) gọi lại phương thức khác (is_passed) trên cùng object.
#
# Tại sao cần học: dữ liệu thực tế (user, order, product...) luôn có nhiều field
# liên quan với nhau, và quy tắc nghiệp vụ (vd. "điểm >= 5 là đậu") phải nằm
# TRONG class, dùng lại qua gọi hàm nội bộ — thay vì lặp lại điều kiện đó ở
# nhiều nơi trong code. Đây là thói quen giúp code dễ sửa, ít bug khi quy tắc đổi.


class StudentRecord:  # khai báo class — khuôn mẫu để tạo ra các object StudentRecord
    def __init__(self, name, age, score):  # constructor — chạy khi gọi "StudentRecord(...)"
        if not name:  # validate: tên không được thiếu (chuỗi rỗng hoặc None đều bị chặn)
            raise ValueError("Tên không được rỗng")  # ném lỗi ngay tại biên
        if age <= 0:  # validate: tuổi phải hợp lệ
            raise ValueError("Tuổi phải > 0")  # ném lỗi ngay tại biên
        if score < 0 or score > 10:  # validate: điểm phải nằm trong thang điểm
            raise ValueError("Điểm phải trong [0,10]")  # ném lỗi ngay tại biên
        self._name = name  # gán tham số truyền vào cho thuộc tính name (dấu "_" = quy ước private)
        self._age = age  # gán tham số truyền vào cho thuộc tính age
        self._score = score  # gán tham số truyền vào cho thuộc tính score

    def is_passed(self):  # hàm kiểm tra đậu/rớt — hành vi dựa trên dữ liệu score của chính object
        return self._score >= 5  # quy tắc nghiệp vụ: đậu nếu điểm >= 5

    def summary(self):  # hàm tạo chuỗi mô tả tổng hợp — gọi lại is_passed() thay vì viết lại điều kiện
        status = "Đậu" if self.is_passed() else "Rớt"  # dùng lại quy tắc nghiệp vụ qua gọi hàm nội bộ
        return f"{self._name} ({self._age} tuổi) - điểm {self._score} - {status}"  # f-string: ghép các thuộc tính thành 1 chuỗi


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python student_record.py"
    an = StudentRecord("An", 20, 7.5)  # tạo object An, điểm 7.5 (đậu)
    assert an.is_passed(), "điểm 7.5 phải đậu"  # kiểm tra is_passed() trả về True
    assert an.summary() == "An (20 tuổi) - điểm 7.5 - Đậu", "summary sai"  # kiểm tra summary() ghép chuỗi đúng

    binh = StudentRecord("Binh", 21, 3.0)  # tạo object Binh, điểm 3.0 (rớt)
    assert not binh.is_passed(), "điểm 3.0 phải rớt"  # kiểm tra is_passed() trả về False

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
