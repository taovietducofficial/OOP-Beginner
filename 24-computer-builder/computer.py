# Ngôn ngữ: Python

# Công dụng: Computer/ComputerBuilder minh họa BUILDER PATTERN —
# ComputerBuilder là một object TẠM THỜI, riêng biệt, dùng để gom dữ liệu
# cấu hình qua nhiều bước (set_cpu, set_ram, set_ssd, theo thứ tự bất kỳ).
# Computer THẬT SỰ chưa tồn tại cho tới khi gọi build() — lúc đó nó được tạo
# MỘT LẦN, đầy đủ, và bất biến từ đầu.

# Tại sao cần học: bài 18 (PizzaOrder) dùng fluent interface — object đã tồn
# tại từ đầu, mỗi lần gọi add_topping() là SỬA NGAY chính nó. Bài này khác:
# Computer KHÔNG có setter nào cả, không thể sửa sau khi build(); mọi việc
# "sửa dần" chỉ xảy ra trên ComputerBuilder tạm thời, không phải trên chính
# Computer.


class Computer:  # sản phẩm cuối — BẤT BIẾN theo quy ước (chỉ getter, không setter — giống Fraction ở bài 16)
    def __init__(self, cpu, ram, has_ssd):  # không gọi trực tiếp từ bên ngoài theo quy ước — luôn đi qua ComputerBuilder.build()
        self._cpu = cpu
        self._ram = ram
        self._has_ssd = has_ssd

    def get_cpu(self):  # getter — xem cpu đã cấu hình
        return self._cpu

    def get_ram(self):  # getter — xem dung lượng RAM (GB)
        return self._ram

    def has_ssd(self):  # getter — có ổ SSD hay không
        return self._has_ssd

    def __str__(self):  # object tự mô tả chính nó (bài 08)
        disk = "SSD" if self._has_ssd else "HDD"
        return f"{self._cpu} / {self._ram}GB RAM / {disk}"


class ComputerBuilder:  # object TẠM THỜI — gom dữ liệu qua nhiều bước, chưa phải Computer thật
    def __init__(self):
        self._cpu = None      # chưa set thì vẫn None — build() phải kiểm tra bắt buộc
        self._ram = 8          # giá trị mặc định nếu người dùng không gọi set_ram()
        self._has_ssd = False  # giá trị mặc định nếu người dùng không gọi set_ssd()

    def set_cpu(self, cpu):  # mỗi bước trả về self để có thể gọi tiếp (giống fluent interface bài 18), nhưng KHÔNG sửa Computer nào — vì Computer chưa tồn tại
        if not cpu:  # validate ở biên
            raise ValueError("CPU không được rỗng")
        self._cpu = cpu
        return self

    def set_ram(self, ram):
        if ram <= 0:  # validate ở biên
            raise ValueError("RAM phải dương")
        self._ram = ram
        return self

    def set_ssd(self, has_ssd):
        self._has_ssd = has_ssd
        return self

    def build(self):  # chốt lại — tạo MỘT Computer bất biến, đây là lần DUY NHẤT dữ liệu được "đóng băng"
        if self._cpu is None:  # validate: trường bắt buộc chưa có
            raise ValueError("Phải set_cpu(...) trước khi build()")
        return Computer(self._cpu, self._ram, self._has_ssd)


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python computer.py"
    full = (
        ComputerBuilder()  # dựng qua nhiều bước, thứ tự bất kỳ
        .set_cpu("Intel i7")
        .set_ram(16)
        .set_ssd(True)
        .build()
    )
    assert full.get_cpu() == "Intel i7", "cpu phải đúng giá trị đã set"
    assert full.get_ram() == 16, "ram phải đúng giá trị đã set"
    assert full.has_ssd(), "has_ssd phải đúng giá trị đã set"

    defaults = ComputerBuilder().set_cpu("AMD Ryzen").build()  # chỉ set cpu — ram và has_ssd dùng giá trị mặc định
    assert defaults.get_ram() == 8, "không set_ram() thì phải dùng mặc định 8"
    assert not defaults.has_ssd(), "không set_ssd() thì phải dùng mặc định False"

    blocked_no_cpu = False  # cờ đánh dấu: build() thiếu cpu bắt buộc có bị chặn không
    try:
        ComputerBuilder().set_ram(32).build()
    except ValueError:
        blocked_no_cpu = True
    assert blocked_no_cpu, "build() không có set_cpu(...) trước đó phải bị chặn"

    blocked_bad_ram = False  # cờ đánh dấu: RAM không dương có bị chặn không
    try:
        ComputerBuilder().set_ram(0)
    except ValueError:
        blocked_bad_ram = True
    assert blocked_bad_ram, "set_ram(0) phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
