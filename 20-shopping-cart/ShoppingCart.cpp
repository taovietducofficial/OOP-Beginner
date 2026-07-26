/*
 * Ngôn ngữ: C++
 * Công dụng: ShoppingCart là bài ÔN TẬP tổng hợp mọi kỹ thuật đã học ở tầng
 * beginner trong một bài toán duy nhất: đóng gói + validate ở biên (bài 06),
 * overload phương thức (bài 14), một class quản lý tập hợp nhiều object con
 * và tổng hợp dữ liệu (bài 12), defensive copy khi để lộ danh sách ra ngoài
 * (bài 17), và object tự mô tả chính nó qua toString (bài 08).
 * Tại sao cần học: đây là hình dạng gần với code thực tế nhất trong cả tầng
 * — một class không dạy một khái niệm mới, mà PHỐI HỢP nhiều khái niệm cũ
 * để giải quyết một bài toán hoàn chỉnh. Từ bài sau (tầng 02-student), 4 trụ
 * cột OOP (đóng gói, kế thừa, đa hình, trừu tượng) sẽ mở rộng đúng nền này —
 * ví dụ ShoppingCart tính giảm giá khác nhau theo loại khách hàng.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <sstream>   // thư viện chuẩn: std::ostringstream để ghép chuỗi từ nhiều kiểu dữ liệu
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên
#include <vector>    // thư viện chuẩn: std::vector — danh sách động

class CartItem { // class phụ trợ — một dòng hàng trong giỏ: tên, đơn giá, số lượng
private:
    std::string name; // tên món hàng — riêng cho từng object, không đổi sau khi tạo
    int price;         // đơn giá (đồng) — số nguyên, không dùng float cho tiền (như bài 09 Money)
    int quantity;      // số lượng — riêng cho từng object, không đổi sau khi tạo

public:
    CartItem(std::string name, int price, int quantity) : price(price), quantity(quantity) { // constructor — chạy khi thêm một dòng hàng
        if (name.empty()) throw std::invalid_argument("Tên món hàng không được rỗng"); // validate ở biên
        if (price <= 0) throw std::invalid_argument("Đơn giá phải > 0");   // validate ở biên
        if (quantity <= 0) throw std::invalid_argument("Số lượng phải > 0"); // validate ở biên
        this->name = std::move(name);
    }

    const std::string& getName() const { return name; }        // getter — xem tên món hàng
    int getSubtotal() const { return price * quantity; } // thành tiền của riêng dòng hàng này

    std::string toString() const { // dòng hàng tự mô tả chính nó, vd. "Áo thun x1 = 100000đ"
        std::ostringstream out;
        out << name << " x" << quantity << " = " << getSubtotal() << "đ";
        return out.str();
    }
};

class ShoppingCart { // khai báo class — khuôn mẫu để tạo ra các object ShoppingCart
private:
    std::string customerName;    // tên khách hàng — riêng cho từng object, không đổi sau khi tạo
    std::vector<CartItem> items; // TẬP HỢP: giỏ hàng chứa nhiều CartItem (giống Classroom chứa nhiều Student ở bài 12)

public:
    explicit ShoppingCart(std::string customerName) { // constructor — chạy khi tạo giỏ hàng mới, ban đầu chưa có món nào
        if (customerName.empty()) throw std::invalid_argument("Tên khách hàng không được rỗng"); // validate ở biên
        this->customerName = std::move(customerName);
    }

    void addItem(const std::string& name, int price) { // OVERLOAD 1: thêm hàng với số lượng mặc định là 1 (giống bài 14 Invoice)
        addItem(name, price, 1); // ủy quyền cho bản đầy đủ — logic tạo CartItem (và validate của nó) chỉ nằm ở một chỗ duy nhất
    }

    void addItem(const std::string& name, int price, int quantity) { // OVERLOAD 2: thêm hàng với số lượng chỉ định rõ
        items.push_back(CartItem(name, price, quantity)); // CartItem tự validate trong constructor của nó
    }

    std::vector<CartItem> getItems() const { // trả BẰNG GIÁ TRỊ — copy constructor tự tạo bản sao độc lập (kỹ thuật đã học ở bài 17)
        return items;
    }

    int getTotal() const { // tổng tiền giỏ hàng — TỔNG HỢP dữ liệu từ nhiều CartItem (giống averageScore ở bài 12)
        int sum = 0;
        for (const CartItem& item : items) sum += item.getSubtotal(); // cộng dồn thành tiền từng dòng hàng
        return sum;
    }

    std::string toString() const { // giỏ hàng tự mô tả chính nó (bài 08)
        std::ostringstream out;
        out << "Giỏ hàng của " << customerName << ": " << items.size() << " món, tổng " << getTotal() << "đ";
        return out.str();
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    ShoppingCart cart("An"); // tạo giỏ hàng của An, ban đầu rỗng
    cart.addItem("Áo thun", 100000);        // OVERLOAD 1 — số lượng ngầm định là 1
    cart.addItem("Quần jean", 200000, 2);   // OVERLOAD 2 — số lượng chỉ định rõ là 2

    check(cart.getItems().size() == 2, "giỏ hàng phải có 2 dòng hàng"); // đếm đúng số phần tử đã thêm
    check(cart.getTotal() == 100000 + 200000 * 2, "tổng tiền giỏ hàng tính sai"); // 100.000 + 400.000 = 500.000
    check(cart.toString() == "Giỏ hàng của An: 2 món, tổng 500000đ", "toString sai định dạng");

    std::vector<CartItem> copy = cart.getItems(); // lấy bản sao ra ngoài
    copy.clear(); // sửa bản sao — mô phỏng code ngoài tự ý xóa hết
    check(cart.getItems().size() == 2, "sửa vector lấy từ getItems() không được ảnh hưởng tới giỏ hàng gốc"); // defensive copy vẫn giữ vững

    bool blocked = false; // cờ đánh dấu: đơn giá không hợp lệ có bị chặn không
    try { cart.addItem("Lỗi", -1000); } catch (const std::invalid_argument&) { blocked = true; }
    check(blocked, "đơn giá âm phải bị chặn");

    bool noCustomer = false; // cờ đánh dấu: tên khách hàng rỗng có bị chặn không
    try { ShoppingCart bad(""); } catch (const std::invalid_argument&) { noCustomer = true; }
    check(noCustomer, "tên khách hàng rỗng phải bị chặn");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
