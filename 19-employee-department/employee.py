# Ngôn ngữ: Python
#
# Công dụng: Employee minh họa THAM CHIẾU DÙNG CHUNG (shared reference) —
# Department được tạo BÊN NGOÀI rồi truyền vào constructor của Employee,
# KHÔNG bị sao chép. Nhiều Employee có thể cùng giữ tham chiếu tới đúng MỘT
# Department; đổi Department qua một Employee thì mọi Employee khác cùng
# phòng ban đều "thấy" thay đổi đó ngay lập tức.
#
# Tại sao cần học: bài 11 (Car/Engine) là composition — Engine bị Car tạo ra
# và SỞ HỮU riêng, không ai khác đụng tới. Bài 17 (Playlist) chủ động CẮT ĐỨT
# tham chiếu (defensive copy) để bảo vệ dữ liệu nội bộ khỏi bị sửa từ ngoài.
# Bài này làm điều NGƯỢC LẠI có chủ đích: GIỮ NGUYÊN tham chiếu, vì đó chính
# là mục đích — nhiều object cùng phản ánh một nguồn dữ liệu dùng chung. Ở
# Python, đây thực ra là hành vi MẶC ĐỊNH: gán "self._department = department"
# không hề copy — mọi biến object trong Python vốn luôn là tham chiếu (đã
# chạm khái niệm này ở bài 09 với "is" khác "==").


class Department:  # class phụ trợ — phòng ban, được tạo và sống ĐỘC LẬP với bất kỳ Employee nào
    def __init__(self, name):  # constructor — chạy khi tạo một phòng ban
        if not name:  # validate ở biên
            raise ValueError("Tên phòng ban không được rỗng")
        self._name = name  # tên phòng ban — CÓ THỂ đổi qua rename(), không "bất biến" như Fraction ở bài 16

    def get_name(self):  # getter — xem tên phòng ban hiện tại
        return self._name

    def rename(self, new_name):  # đổi tên phòng ban — mọi Employee đang giữ tham chiếu tới object này đều thấy thay đổi
        if not new_name:  # validate ở biên
            raise ValueError("Tên phòng ban không được rỗng")
        self._name = new_name  # cập nhật tại chỗ — chính là lý do mọi tham chiếu dùng chung đều "thấy" thay đổi


class Employee:  # khai báo class — khuôn mẫu để tạo ra các object Employee
    def __init__(self, name, department):  # constructor — nhận Department đã tồn tại sẵn từ BÊN NGOÀI
        if not name:  # validate ở biên
            raise ValueError("Tên nhân viên không được rỗng")
        self._name = name  # gán tên
        self._department = department  # gán THẲNG tham chiếu — không tạo Department mới, không copy dữ liệu

    def get_name(self):  # getter — xem tên nhân viên
        return self._name

    def get_department(self):  # getter — trả THẲNG tham chiếu Department dùng chung (cố ý — xem README)
        return self._department

    def get_department_name(self):  # ủy quyền: hỏi thẳng Department hiện tại tên là gì
        return self._department.get_name()


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python employee.py"
    eng = Department("Engineering")  # tạo phòng ban BÊN NGOÀI, độc lập với bất kỳ Employee nào
    e1 = Employee("An", eng)   # An thuộc phòng eng
    e2 = Employee("Binh", eng)  # Binh CŨNG thuộc CHÍNH phòng eng — cùng một object Department

    assert e1.get_department() is e2.get_department(), "hai nhân viên cùng phòng phải giữ CHUNG một object Department"
    assert e1.get_department_name() == "Engineering", "tên phòng ban đọc qua Employee phải đúng ban đầu"

    eng.rename("Platform Engineering")  # đổi tên phòng ban CHỈ MỘT LẦN, qua chính object Department
    assert e1.get_department_name() == "Platform Engineering", "đổi tên Department phải phản ánh qua e1 (cùng tham chiếu)"
    assert e2.get_department_name() == "Platform Engineering", "đổi tên Department phải phản ánh qua e2 (cùng tham chiếu)"

    hr = Department("HR")  # phòng ban KHÁC — object hoàn toàn riêng biệt
    e3 = Employee("Chi", hr)  # Chi thuộc phòng hr, không liên quan gì tới eng
    eng.rename("Something Else")  # đổi tiếp phòng eng
    assert e3.get_department_name() == "HR", "đổi Department eng không được ảnh hưởng tới Employee thuộc Department khác"

    blocked = False  # cờ đánh dấu: tên nhân viên rỗng có bị chặn không
    try:
        Employee("", eng)
    except ValueError:
        blocked = True
    assert blocked, "tên nhân viên rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
