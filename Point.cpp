/*
 * Ngôn ngữ: C++
 *
 * Công dụng: Point minh họa NHIỀU CONSTRUCTOR cùng tên khác tham số
 * (overloading) và constructor ủy quyền (delegating constructor, C++11) —
 * constructor rỗng gọi lại constructor đầy đủ thay vì chép lại code khởi tạo.
 *
 * Tại sao cần học: overloading constructor xuất hiện khắp thư viện chuẩn
 * (std::vector<int> v; / std::vector<int> v(100);). Kỹ thuật ủy quyền dồn
 * logic khởi tạo về MỘT chỗ — chép code ra nhiều constructor là nguồn bug khi
 * hai bản bị chỉnh lệch nhau.
 */
#include <cmath>    // thư viện chuẩn: std::sqrt (căn bậc hai) và std::abs cho số thực
#include <cstdlib>  // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream> // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <string>   // thư viện chuẩn: std::string cho thông điệp lỗi

class Point { // khai báo class — khuôn mẫu để tạo ra các object Point
private:
    const double x; // hoành độ — riêng cho từng object
    const double y; // tung độ — riêng cho từng object

public:
    Point(double x, double y) : x(x), y(y) { // constructor "chính" — nhận đầy đủ tọa độ
    }

    Point() : Point(0, 0) { // constructor rỗng — ủy quyền cho constructor chính (delegating constructor), KHÔNG chép lại code khởi tạo
    }

    double distanceTo(const Point& other) const { // khoảng cách Euclid tới điểm khác — nhận object Point khác làm tham số (mượn để đọc, không sao chép)
        double dx = x - other.x; // chênh lệch hoành độ giữa hai điểm
        double dy = y - other.y; // chênh lệch tung độ giữa hai điểm
        return std::sqrt(dx * dx + dy * dy); // công thức Pythagoras: căn(dx² + dy²) — dùng std::sqrt của thư viện chuẩn
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Point origin;    // dùng constructor rỗng — điểm gốc (0, 0); chú ý: KHÔNG viết "Point origin();" — C++ sẽ hiểu nhầm là khai báo hàm
    Point p(3, 4);   // dùng constructor đầy đủ — điểm (3, 4)

    check(std::abs(origin.distanceTo(p) - 5) < 1e-9, "khoảng cách (0,0)-(3,4) phải là 5"); // tam giác 3-4-5 kinh điển; so sánh gần đúng vì số thực
    check(std::abs(p.distanceTo(origin) - 5) < 1e-9, "khoảng cách phải đối xứng");         // đo xuôi hay ngược đều cùng kết quả
    check(p.distanceTo(p) == 0, "khoảng cách tới chính mình phải là 0");                    // điểm cách chính nó 0

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
