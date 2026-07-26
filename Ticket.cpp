/*
 * Ngôn ngữ: C++
 * Công dụng: Ticket minh họa biến static THAY ĐỔI ĐƯỢC — một bộ đếm duy nhất
 * thuộc về class, mọi lần tạo object đều cộng vào nó; mỗi object chép giá trị
 * bộ đếm tại thời điểm tạo vào id riêng của mình. Dữ liệu class (tổng số vé)
 * và dữ liệu instance (id từng vé) phối hợp với nhau.
 * Tại sao cần học: đây là cơ chế đằng sau id tự tăng của database, số hóa
 * đơn, mã đơn hàng. Đồng thời là bài học về cạm bẫy: static thay đổi được
 * là trạng thái toàn cục — nhiều thread cùng tạo object sẽ cấp trùng id.
 */
#include <cstdlib>  // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream> // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <string>   // thư viện chuẩn: std::string cho thông điệp lỗi

class Ticket { // khai báo class — khuôn mẫu để tạo ra các object Ticket
private:
    static int totalIssued; // bộ đếm CLASS: chỉ có 1 bản duy nhất, mọi lần tạo object đều cộng vào đây — KHÔNG const vì nó thay đổi; C++ chỉ KHAI BÁO ở đây, định nghĩa nằm ngoài class
    // ponytail: int thường, đủ cho bài học đơn luồng; code thật nhiều thread dùng std::atomic<int> hoặc để database cấp số

    const int id; // id INSTANCE: mỗi vé giữ số thứ tự riêng của mình, gán một lần lúc tạo

public:
    Ticket() : id(++totalIssued) { // constructor — cộng bộ đếm chung TRƯỚC rồi chép giá trị tại thời điểm này vào id riêng của vé
    }

    int getId() const { // getter — xem số thứ tự của vé này
        return id; // trả về id riêng của object hiện tại
    }

    static int getTotalIssued() { // phương thức STATIC: hỏi class, không cần object nào — "đã phát tổng cộng bao nhiêu vé?"
        return totalIssued; // trả về bộ đếm chung
    }
};

int Ticket::totalIssued = 0; // định nghĩa biến static của class — cấp bộ nhớ 1 lần duy nhất, khởi tạo bằng 0 (đặc thù C++: khai báo trong class chưa đủ)

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    check(Ticket::getTotalIssued() == 0, "chưa phát vé nào thì tổng phải là 0"); // gọi qua tên class (dấu ::) — chưa cần object nào tồn tại

    Ticket t1; // phát vé thứ nhất
    Ticket t2; // phát vé thứ hai
    Ticket t3; // phát vé thứ ba

    check(t1.getId() == 1, "vé đầu tiên phải mang số 1");  // mỗi vé giữ số cấp tại thời điểm tạo
    check(t2.getId() == 2, "vé thứ hai phải mang số 2");   // id tự tăng, không trùng
    check(t3.getId() == 3, "vé thứ ba phải mang số 3");    // tiếp tục tăng
    check(Ticket::getTotalIssued() == 3, "tổng vé đã phát phải là 3"); // bộ đếm class phản ánh mọi lần tạo object

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
