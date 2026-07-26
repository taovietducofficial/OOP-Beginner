/*
 * Ngôn ngữ: C++
 * Công dụng: Playlist minh họa DEFENSIVE COPY — khi một object nắm giữ một
 * danh sách (mutable) bên trong, getter KHÔNG được để lộ tham chiếu/con trỏ
 * tới danh sách gốc, mà phải trả về một BẢN SAO. Nếu không, code bên ngoài
 * giữ tham chiếu đó có thể tự ý sửa (add/remove) dữ liệu nội bộ của object
 * mà không đi qua bất kỳ phương thức nào của Playlist — phá vỡ đóng gói.
 * Tại sao cần học: bài 12 (Classroom) đã cho một class chứa danh sách object
 * con, nhưng chưa để lộ danh sách đó ra ngoài qua getter. Khác với Java/Python
 * (biến object luôn là tham chiếu), C++ có kiểu GIÁ TRỊ: trả về
 * "std::vector<std::string>" BẰNG GIÁ TRỊ (không phải "const&") đã tự động
 * tạo một bản sao độc lập — chỉ cần không lỡ tay đổi kiểu trả về thành tham
 * chiếu/con trỏ tới thành viên nội bộ là an toàn.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên bài hát
#include <vector>    // thư viện chuẩn: std::vector — danh sách động

class Playlist { // khai báo class — khuôn mẫu để tạo ra các object Playlist
private:
    std::string name;              // tên playlist — riêng cho từng object, không đổi sau khi tạo
    std::vector<std::string> songs; // danh sách bài hát — dữ liệu MUTABLE nằm bên trong object

public:
    explicit Playlist(std::string name) : name(std::move(name)) { // constructor — chạy khi tạo playlist mới, ban đầu chưa có bài hát nào
    }

    const std::string& getName() const { // getter — xem tên playlist
        return name;
    }

    void addSong(const std::string& title) { // thêm một bài hát vào playlist
        if (title.empty()) throw std::invalid_argument("Tên bài hát không được rỗng"); // validate ở biên
        songs.push_back(title); // đưa vào cuối danh sách nội bộ
    }

    std::size_t size() const { // đếm số bài hát hiện có
        return songs.size();
    }

    std::vector<std::string> getSongs() const { // trả BẰNG GIÁ TRỊ (không phải const&) — copy constructor của vector tự tạo bản sao độc lập, đây chính là "defensive copy" của C++
        return songs; // trả về bản sao; code ngoài có sửa bản sao này thoải mái, "songs" bên trong Playlist không hề hấn gì
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Playlist p("Lofi Chill"); // tạo playlist mới, ban đầu rỗng
    p.addSong("Song A"); // thêm bài A
    p.addSong("Song B"); // thêm bài B
    check(p.size() == 2, "playlist phải có 2 bài sau khi thêm 2 lần");

    std::vector<std::string> copy = p.getSongs(); // lấy bản sao ra ngoài
    copy.push_back("Hacked Song"); // sửa bản sao — CỐ Ý mô phỏng code ngoài tự ý thêm bài
    check(p.size() == 2, "sửa vector lấy từ getSongs() không được ảnh hưởng tới Playlist gốc"); // nếu getSongs() trả về tham chiếu, size() sẽ thành 3

    std::vector<std::string> copy2 = p.getSongs(); // gọi lần nữa, lấy bản sao mới từ trạng thái gốc
    check(copy2.size() == 2, "bản sao lần hai phải phản ánh đúng trạng thái gốc, không dính bản sao lần trước"); // xác nhận Playlist gốc không bị "Hacked Song" làm bẩn

    bool blocked = false; // cờ đánh dấu: thêm bài hát tên rỗng có bị chặn không
    try { p.addSong(""); } catch (const std::invalid_argument&) { blocked = true; } // tên rỗng phải bị chặn
    check(blocked, "tên bài hát rỗng phải bị chặn");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
