# Ngôn ngữ: Python
#
# Công dụng: BankAccount minh họa ĐÓNG GÓI (encapsulation) — số dư để "private"
# theo quy ước dấu "_", mọi thay đổi bắt buộc đi qua deposit/withdraw, nơi các
# quy tắc nghiệp vụ (tiền > 0, không rút quá số dư) được kiểm tra.
#
# Tại sao cần học: đóng gói là trụ cột đầu tiên của OOP. Nếu ai cũng gán thẳng
# balance = -1000 thì dữ liệu bị phá hỏng — bug kiểu này cực khó truy vết vì
# chỗ gãy nằm xa chỗ gán sai. Python không có private thật như Java/C++, nên
# kỷ luật "chỉ đổi state qua phương thức" càng phải tự giác giữ.


class BankAccount:  # khai báo class — khuôn mẫu để tạo ra các object BankAccount
    def __init__(self, initial_balance):  # constructor — chạy khi gọi "BankAccount(...)"
        if initial_balance < 0:  # validate ở biên: chặn số dư âm ngay từ lúc tạo
            raise ValueError("Số dư ban đầu không được âm")  # ném lỗi để object sai không được tạo
        self._balance = initial_balance  # số dư (đơn vị: đồng) — dấu "_" báo hiệu: bên ngoài đừng gán trực tiếp; dùng số nguyên, không dùng float cho tiền

    def deposit(self, amount):  # nạp tiền — cách HỢP LỆ duy nhất để tăng số dư
        if amount <= 0:  # quy tắc nghiệp vụ: không nạp số âm hoặc 0
            raise ValueError("Tiền nạp phải > 0")  # chặn ngay tại biên
        self._balance += amount  # cộng tiền vào số dư

    def withdraw(self, amount):  # rút tiền — cách HỢP LỆ duy nhất để giảm số dư
        if amount <= 0:  # quy tắc nghiệp vụ: không rút số âm hoặc 0
            raise ValueError("Tiền rút phải > 0")  # chặn ngay tại biên
        if amount > self._balance:  # quy tắc nghiệp vụ: không cho rút quá số dư
            raise ValueError("Số dư không đủ")  # chặn trước khi trừ tiền — số dư giữ nguyên
        self._balance -= amount  # trừ tiền khỏi số dư

    def get_balance(self):  # getter — cho bên ngoài XEM số dư mà không khuyến khích SỬA
        return self._balance  # trả về số dư hiện tại


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python bank_account.py"
    acc = BankAccount(100_000)  # tạo tài khoản với 100.000đ — Python cũng dùng _ phân tách hàng nghìn như Java
    acc.deposit(50_000)  # nạp thêm 50.000đ
    assert acc.get_balance() == 150_000, "nạp tiền sai"  # 100k + 50k = 150k
    acc.withdraw(70_000)  # rút 70.000đ
    assert acc.get_balance() == 80_000, "rút tiền sai"  # 150k - 70k = 80k

    blocked = False  # cờ đánh dấu: việc rút lố có bị chặn không
    try:  # cố rút 1 triệu khi chỉ còn 80k — phải bị ném lỗi
        acc.withdraw(1_000_000)  # giao dịch không hợp lệ
    except ValueError:  # bắt đúng loại lỗi mà withdraw ném ra
        blocked = True  # đánh dấu: quy tắc đã chặn thành công
    assert blocked, "rút quá số dư phải bị chặn"  # xác nhận quy tắc "không rút lố" hoạt động
    assert acc.get_balance() == 80_000, "số dư không được đổi khi giao dịch bị chặn"  # giao dịch lỗi thì số dư giữ nguyên

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
