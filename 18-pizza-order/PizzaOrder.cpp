/*
 * Ngôn ngữ: C++
 * Công dụng: PizzaOrder minh họa FLUENT INTERFACE (method chaining) —
 * addTopping() trả về CHÍNH OBJECT ĐANG GỌI ("return *this") thay vì void,
 * cho phép nối nhiều lời gọi liên tiếp trên cùng một dòng:
 * order.addTopping("cheese").addTopping("bacon").
 * Tại sao cần học: bài 16 (Fraction) trả về object MỚI ở mỗi phép toán vì nó
 * bất biến. Bài này ngược lại — object CÓ trạng thái thay đổi (giống Counter,
 * BankAccount) nhưng thay vì mỗi phương thức trả về void, nó trả về "*this"
 * để người gọi CẤU HÌNH DẦN DẦN object qua một chuỗi lời gọi liền mạch, dễ
 * đọc. Đây là bước đệm tới Builder pattern chính thức ở tầng sau.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <map>       // thư viện chuẩn: std::map — bảng tra giá theo size
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho size và tên topping
#include <vector>    // thư viện chuẩn: std::vector — danh sách topping

class PizzaOrder { // khai báo class — khuôn mẫu để tạo ra các object PizzaOrder
private:
    static inline const std::map<std::string, int> BASE_PRICE = {{"S", 30000}, {"M", 45000}, {"L", 60000}}; // giá nền theo size — dùng chung cho mọi object (inline static, C++17)
    static constexpr int TOPPING_PRICE = 10000; // giá mỗi topping — dùng chung cho mọi object

    std::string size;               // size bánh — riêng cho từng object, không đổi sau khi tạo
    std::vector<std::string> toppings; // danh sách topping — dữ liệu MUTABLE nằm bên trong object

public:
    explicit PizzaOrder(std::string size) { // constructor — chạy khi tạo object
        if (BASE_PRICE.find(size) == BASE_PRICE.end()) throw std::invalid_argument("Size phải là S, M hoặc L"); // validate ở biên
        this->size = std::move(size); // gán size hợp lệ
    }

    PizzaOrder& addTopping(const std::string& name) { // thêm topping — trả về THAM CHIẾU tới CHÍNH object này để gọi tiếp được (fluent)
        if (name.empty()) throw std::invalid_argument("Tên topping không được rỗng"); // validate ở biên
        toppings.push_back(name); // đưa vào cuối danh sách nội bộ
        return *this; // trả về chính object đang gọi — KHÔNG tạo object mới (khác hẳn Fraction::add() ở bài 16, vốn trả về giá trị mới)
    }

    std::vector<std::string> getToppings() const { // trả BẰNG GIÁ TRỊ — copy constructor tự tạo bản sao độc lập (kỹ thuật đã học ở bài 17)
        return toppings;
    }

    int getTotal() const { // tổng tiền = giá nền theo size + số topping * giá mỗi topping
        return BASE_PRICE.at(size) + static_cast<int>(toppings.size()) * TOPPING_PRICE;
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    PizzaOrder order("M"); // tạo đơn pizza size M, chưa có topping nào

    PizzaOrder& chained = order.addTopping("cheese").addTopping("bacon"); // nối hai lời gọi liên tiếp trên cùng một object
    check(&chained == &order, "addTopping() phải trả về CHÍNH object đang gọi, không tạo object mới"); // so địa chỉ: cùng một object trong bộ nhớ

    std::vector<std::string> toppings = order.getToppings(); // lấy danh sách topping hiện tại
    check(toppings.size() == 2 && toppings[0] == "cheese" && toppings[1] == "bacon", "danh sách topping phải đúng thứ tự đã thêm");
    check(order.getTotal() == 45000 + 2 * 10000, "tổng tiền phải bằng giá nền size M cộng 2 topping");

    std::vector<std::string> copy = order.getToppings(); // lấy bản sao ra ngoài
    copy.push_back("Hacked Topping"); // sửa bản sao — mô phỏng code ngoài tự ý thêm
    check(order.getToppings().size() == 2, "sửa vector lấy từ getToppings() không được ảnh hưởng tới order gốc"); // defensive copy vẫn giữ vững

    bool badSize = false; // cờ đánh dấu: size không hợp lệ có bị chặn không
    try { PizzaOrder bad("XL"); } catch (const std::invalid_argument&) { badSize = true; }
    check(badSize, "size ngoài S/M/L phải bị chặn");

    bool emptyTopping = false; // cờ đánh dấu: topping tên rỗng có bị chặn không
    try { order.addTopping(""); } catch (const std::invalid_argument&) { emptyTopping = true; }
    check(emptyTopping, "topping tên rỗng phải bị chặn");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
