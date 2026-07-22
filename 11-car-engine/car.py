# Ngôn ngữ: Python
#
# Công dụng: Car minh họa KẾT HỢP (composition) — Car tự tạo ra Engine của
# riêng mình ngay trong constructor, Engine sống chết theo Car (không object
# nào khác nắm giữ Engine này). Car "ủy quyền" (delegate) các phương thức
# start()/is_running() cho engine bên trong thay vì tự làm hết.
#
# Tại sao cần học: bài 05 cho object khác làm THAM SỐ (aggregation — hai
# object độc lập, không sở hữu nhau). Bài này khác: Car SỞ HỮU Engine — quan
# hệ "toàn thể - bộ phận" (whole-part). Đây là cách OOP mô hình hóa vật thật
# gồm nhiều bộ phận: Car có Engine, Order có Address, Computer có CPU.


class Engine:  # class phụ trợ — chỉ Car (cùng file) cần dùng; thế giới bên ngoài chỉ làm việc với Car
    def __init__(self, horsepower):  # constructor — chạy khi Car tạo Engine bên trong nó
        if horsepower <= 0:  # validate ở biên: động cơ không thể có mã lực âm hoặc 0
            raise ValueError("Mã lực phải > 0")  # ném lỗi để object sai không được tạo
        self._horsepower = horsepower  # mã lực — riêng cho từng động cơ, không đổi sau khi tạo
        self._running = False  # trạng thái chạy/tắt — riêng cho từng động cơ, thay đổi được qua start()

    def start(self):  # khởi động động cơ
        self._running = True  # chuyển trạng thái sang đang chạy

    def is_running(self):  # kiểm tra động cơ có đang chạy không
        return self._running  # trả về trạng thái hiện tại

    def get_horsepower(self):  # getter — xem mã lực động cơ
        return self._horsepower  # trả về mã lực


class Car:  # khai báo class — khuôn mẫu để tạo ra các object Car
    def __init__(self, model, horsepower):  # constructor — nhận thông tin xe VÀ thông tin động cơ để tự tạo Engine bên trong
        if not model:  # validate ở biên: tên xe bắt buộc phải có
            raise ValueError("Tên xe không được rỗng")  # chặn ngay tại biên
        self._model = model  # tên dòng xe — riêng cho từng object, không đổi sau khi tạo
        self._engine = Engine(horsepower)  # KẾT HỢP: Car TỰ TẠO Engine của mình — đây chính là composition, không ai truyền Engine từ bên ngoài vào

    def start(self):  # khởi động xe — Car không tự biết cách nổ máy, nó NHỜ Engine của mình làm việc đó
        self._engine.start()  # ủy quyền (delegate) hành vi cho object bên trong

    def is_running(self):  # kiểm tra xe có đang chạy không
        return self._engine.is_running()  # ủy quyền: hỏi thẳng Engine bên trong, Car không tự giữ trạng thái này

    def describe(self):  # mô tả xe — kết hợp dữ liệu của Car và dữ liệu của Engine bên trong nó
        return f"{self._model} ({self._engine.get_horsepower()}hp)"  # ví dụ: "Toyota Vios (120hp)"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python car.py"
    car = Car("Toyota Vios", 120)  # tạo xe — Engine(120) được tạo tự động bên trong constructor của Car
    assert not car.is_running(), "xe chưa start thì chưa được chạy"  # trạng thái ban đầu: chưa nổ máy
    assert car.describe() == "Toyota Vios (120hp)", "describe phải ghép đúng tên xe và mã lực"  # dữ liệu Car + Engine ghép lại đúng

    car.start()  # khởi động xe — thực chất là gọi engine.start() bên trong
    assert car.is_running(), "sau start xe phải đang chạy"  # trạng thái đã đổi, dù Car không tự giữ biến "running"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
