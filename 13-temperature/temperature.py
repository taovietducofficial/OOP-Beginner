# Ngôn ngữ: Python
#
# Công dụng: Temperature minh họa STATIC FACTORY METHOD — constructor "ẩn"
# bằng dấu "_", object chỉ nên được tạo qua các classmethod có TÊN RÕ NGHĨA
# (from_celsius, from_fahrenheit) thay vì gọi "Temperature(...)" mù mờ.
#
# Tại sao cần học: bài 07 overload nhiều constructor cùng tên khi THAM SỐ
# khác kiểu/số lượng. Nhưng ở đây from_celsius(x) và from_fahrenheit(x) có
# CÙNG kiểu tham số (số) — không thể overload constructor vì trùng chữ ký
# (Python cũng không hỗ trợ overload thật, xem thêm bài 14). Static factory
# method giải quyết đúng vấn đề này: tên phương thức tự nói lên ý nghĩa.

ABSOLUTE_ZERO_C = -273.15  # hằng số MODULE: 0 tuyệt đối theo độ C — dùng chung, không đổi


class Temperature:  # khai báo class — khuôn mẫu để tạo ra các object Temperature
    def __init__(self, celsius):  # constructor — Python không có "private" thật, quy ước: đừng gọi thẳng, hãy dùng from_celsius/from_fahrenheit bên dưới
        if celsius < ABSOLUTE_ZERO_C:  # validate ở biên: chặn giá trị vô lý về mặt vật lý
            raise ValueError("Nhiệt độ không thể thấp hơn 0 tuyệt đối")  # ném lỗi để object sai không được tạo
        self._celsius = celsius  # nhiệt độ lưu trữ nội bộ luôn theo độ C — chọn 1 đơn vị chuẩn để tính toán, quy đổi khi cần hiển thị

    @classmethod  # FACTORY METHOD: tạo Temperature từ độ C — tên tự giải thích, khỏi cần đoán tham số là đơn vị gì
    def from_celsius(cls, celsius):
        return cls(celsius)  # độ C đã là đơn vị chuẩn nội bộ, không cần quy đổi

    @classmethod  # FACTORY METHOD: tạo Temperature từ độ F — quy đổi sang độ C rồi mới gọi constructor
    def from_fahrenheit(cls, fahrenheit):
        return cls((fahrenheit - 32) * 5 / 9)  # công thức quy đổi F sang C

    def to_celsius(self):  # đọc nhiệt độ theo độ C
        return self._celsius  # đơn vị chuẩn nội bộ, trả thẳng ra

    def to_fahrenheit(self):  # đọc nhiệt độ theo độ F
        return self._celsius * 9 / 5 + 32  # công thức quy đổi C sang F


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python temperature.py"
    boiling = Temperature.from_celsius(100)  # tạo qua factory "from_celsius" — rõ ràng đây là 100 độ C
    assert boiling.to_fahrenheit() == 212, "100°C phải bằng 212°F"  # nước sôi: mốc quy đổi kinh điển

    freezing = Temperature.from_fahrenheit(32)  # tạo qua factory "from_fahrenheit" — rõ ràng đây là 32 độ F
    assert freezing.to_celsius() == 0, "32°F phải bằng 0°C"  # nước đóng băng: mốc quy đổi kinh điển

    blocked = False  # cờ đánh dấu: nhiệt độ dưới 0 tuyệt đối có bị chặn không
    try:  # cố tạo -300°C — thấp hơn 0 tuyệt đối (-273.15°C)
        Temperature.from_celsius(-300)  # giá trị không hợp lệ
    except ValueError:  # bắt đúng loại lỗi mà constructor ném ra
        blocked = True  # đánh dấu: validate đã chặn thành công
    assert blocked, "nhiệt độ dưới 0 tuyệt đối phải bị chặn"  # xác nhận validate hoạt động dù tạo qua factory nào

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
