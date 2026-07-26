# Ngôn ngữ: Python
#
# Công dụng: ShoppingCart là bài ÔN TẬP tổng hợp mọi kỹ thuật đã học ở tầng
# beginner trong một bài toán duy nhất: đóng gói + validate ở biên (bài 06),
# tham số mặc định thay overload (bài 14), một class quản lý tập hợp nhiều
# object con và tổng hợp dữ liệu (bài 12), defensive copy khi để lộ danh
# sách ra ngoài (bài 17), và object tự mô tả chính nó qua __str__ (bài 08).
#
# Tại sao cần học: đây là hình dạng gần với code thực tế nhất trong cả tầng
# — một class không dạy một khái niệm mới, mà PHỐI HỢP nhiều khái niệm cũ để
# giải quyết một bài toán hoàn chỉnh. Từ bài sau (tầng 02-student), 4 trụ
# cột OOP (đóng gói, kế thừa, đa hình, trừu tượng) sẽ mở rộng đúng nền này —
# ví dụ ShoppingCart tính giảm giá khác nhau theo loại khách hàng.


class CartItem:  # class phụ trợ — một dòng hàng trong giỏ: tên, đơn giá, số lượng
    def __init__(self, name, price, quantity):  # constructor — chạy khi thêm một dòng hàng
        if not name:  # validate ở biên
            raise ValueError("Tên món hàng không được rỗng")
        if price <= 0:  # validate ở biên
            raise ValueError("Đơn giá phải > 0")
        if quantity <= 0:  # validate ở biên
            raise ValueError("Số lượng phải > 0")
        self._name = name          # tên món hàng — riêng cho từng object, không đổi sau khi tạo
        self._price = price        # đơn giá (đồng) — số nguyên, không dùng float cho tiền (như bài 09 Money)
        self._quantity = quantity  # số lượng — riêng cho từng object, không đổi sau khi tạo

    def get_name(self):  # getter — xem tên món hàng
        return self._name

    def get_subtotal(self):  # thành tiền của riêng dòng hàng này
        return self._price * self._quantity

    def __str__(self):  # dòng hàng tự mô tả chính nó, vd. "Áo thun x1 = 100000đ"
        return f"{self._name} x{self._quantity} = {self.get_subtotal()}đ"


class ShoppingCart:  # khai báo class — khuôn mẫu để tạo ra các object ShoppingCart
    def __init__(self, customer_name):  # constructor — chạy khi tạo giỏ hàng mới, ban đầu chưa có món nào
        if not customer_name:  # validate ở biên
            raise ValueError("Tên khách hàng không được rỗng")
        self._customer_name = customer_name  # tên khách hàng — riêng cho từng object, không đổi sau khi tạo
        self._items = []  # TẬP HỢP: giỏ hàng chứa nhiều CartItem (giống Classroom chứa nhiều Student ở bài 12)

    def add_item(self, name, price, quantity=1):  # MỘT phương thức duy nhất, quantity mặc định = 1 — thay cho overload (giống bài 14 Invoice)
        self._items.append(CartItem(name, price, quantity))  # CartItem tự validate trong constructor của nó

    def get_items(self):  # getter — trả về danh sách dòng hàng
        return list(self._items)  # DEFENSIVE COPY (bài 17) — không để lộ tham chiếu tới danh sách nội bộ

    def get_total(self):  # tổng tiền giỏ hàng — TỔNG HỢP dữ liệu từ nhiều CartItem (giống average_score ở bài 12)
        return sum(item.get_subtotal() for item in self._items)  # cộng dồn thành tiền từng dòng hàng

    def __str__(self):  # giỏ hàng tự mô tả chính nó (bài 08)
        return f"Giỏ hàng của {self._customer_name}: {len(self._items)} món, tổng {self.get_total()}đ"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python shopping_cart.py"
    cart = ShoppingCart("An")  # tạo giỏ hàng của An, ban đầu rỗng
    cart.add_item("Áo thun", 100_000)          # không truyền quantity — dùng giá trị mặc định là 1
    cart.add_item("Quần jean", 200_000, 2)     # truyền quantity rõ ràng là 2

    assert len(cart.get_items()) == 2, "giỏ hàng phải có 2 dòng hàng"  # đếm đúng số phần tử đã thêm
    assert cart.get_total() == 100_000 + 200_000 * 2, "tổng tiền giỏ hàng tính sai"  # 100.000 + 400.000 = 500.000
    assert str(cart) == "Giỏ hàng của An: 2 món, tổng 500000đ", "__str__ sai định dạng"

    copy = cart.get_items()  # lấy bản sao ra ngoài
    copy.clear()  # sửa bản sao — mô phỏng code ngoài tự ý xóa hết
    assert len(cart.get_items()) == 2, "sửa list lấy từ get_items() không được ảnh hưởng tới giỏ hàng gốc"  # defensive copy vẫn giữ vững

    blocked = False  # cờ đánh dấu: đơn giá không hợp lệ có bị chặn không
    try:
        cart.add_item("Lỗi", -1000)
    except ValueError:
        blocked = True
    assert blocked, "đơn giá âm phải bị chặn"

    no_customer = False  # cờ đánh dấu: tên khách hàng rỗng có bị chặn không
    try:
        ShoppingCart("")
    except ValueError:
        no_customer = True
    assert no_customer, "tên khách hàng rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
