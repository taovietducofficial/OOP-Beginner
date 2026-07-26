# Ngôn ngữ: Python
#
# Công dụng: PizzaOrder minh họa FLUENT INTERFACE (method chaining) —
# add_topping() trả về CHÍNH OBJECT ĐANG GỌI ("return self") thay vì None,
# cho phép nối nhiều lời gọi liên tiếp trên cùng một dòng:
# order.add_topping("cheese").add_topping("bacon").
#
# Tại sao cần học: bài 16 (Fraction) trả về object MỚI ở mỗi phép toán vì nó
# bất biến. Bài này ngược lại — object CÓ trạng thái thay đổi (giống Counter,
# BankAccount) nhưng thay vì mỗi phương thức trả về None, nó trả về "self" để
# người gọi CẤU HÌNH DẦN DẦN object qua một chuỗi lời gọi liền mạch, dễ đọc.
# Đây là bước đệm tới Builder pattern chính thức ở tầng sau.

BASE_PRICE = {"S": 30_000, "M": 45_000, "L": 60_000}  # giá nền theo size — dùng chung cho mọi object
TOPPING_PRICE = 10_000  # giá mỗi topping — dùng chung cho mọi object


class PizzaOrder:  # khai báo class — khuôn mẫu để tạo ra các object PizzaOrder
    def __init__(self, size):  # constructor — chạy khi gọi "PizzaOrder(...)"
        if size not in BASE_PRICE:  # validate ở biên
            raise ValueError("Size phải là S, M hoặc L")
        self._size = size  # gán size hợp lệ
        self._toppings = []  # danh sách topping — dữ liệu MUTABLE nằm bên trong object

    def add_topping(self, name):  # thêm topping — trả về CHÍNH OBJECT NÀY để gọi tiếp được (fluent)
        if not name:  # validate ở biên
            raise ValueError("Tên topping không được rỗng")
        self._toppings.append(name)  # đưa vào cuối danh sách nội bộ
        return self  # trả về chính object đang gọi — KHÔNG tạo object mới (khác hẳn Fraction.add() ở bài 16)

    def get_toppings(self):  # getter — trả về danh sách topping
        return list(self._toppings)  # DEFENSIVE COPY (kỹ thuật đã học ở bài 17) — không để lộ tham chiếu nội bộ

    def get_total(self):  # tổng tiền = giá nền theo size + số topping * giá mỗi topping
        return BASE_PRICE[self._size] + len(self._toppings) * TOPPING_PRICE


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python pizza_order.py"
    order = PizzaOrder("M")  # tạo đơn pizza size M, chưa có topping nào

    chained = order.add_topping("cheese").add_topping("bacon")  # nối hai lời gọi liên tiếp trên cùng một object
    assert chained is order, "add_topping() phải trả về CHÍNH object đang gọi, không tạo object mới"  # "is" so địa chỉ: cùng một object trong bộ nhớ

    assert order.get_toppings() == ["cheese", "bacon"], "danh sách topping phải đúng thứ tự đã thêm"
    assert order.get_total() == 45_000 + 2 * 10_000, "tổng tiền phải bằng giá nền size M cộng 2 topping"

    copy = order.get_toppings()  # lấy bản sao ra ngoài
    copy.append("Hacked Topping")  # sửa bản sao — mô phỏng code ngoài tự ý thêm
    assert len(order.get_toppings()) == 2, "sửa list lấy từ get_toppings() không được ảnh hưởng tới order gốc"  # defensive copy vẫn giữ vững

    bad_size = False  # cờ đánh dấu: size không hợp lệ có bị chặn không
    try:
        PizzaOrder("XL")
    except ValueError:
        bad_size = True
    assert bad_size, "size ngoài S/M/L phải bị chặn"

    empty_topping = False  # cờ đánh dấu: topping tên rỗng có bị chặn không
    try:
        order.add_topping("")
    except ValueError:
        empty_topping = True
    assert empty_topping, "topping tên rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
