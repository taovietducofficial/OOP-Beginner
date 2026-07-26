/*
 * Ngôn ngữ: C++
 * Công dụng: Book minh họa cách một object TỰ MÔ TẢ chính nó bằng chuỗi —
 * C++ không có toString() thừa hưởng sẵn như Java, quy ước của C++ là viết
 * hàm toString() + nạp chồng toán tử << để object in thẳng ra std::cout.
 * Tại sao cần học: chuỗi mô tả tốt là công cụ debug số một — log, thông báo
 * lỗi đều cần nó. Đây cũng là lần đầu chạm vào NẠP CHỒNG TOÁN TỬ (operator
 * overloading) — cách C++ cho phép kiểu tự định nghĩa dùng được cú pháp
 * của kiểu có sẵn, nền của nhiều idiom C++ về sau.
 */
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr và std::ostream để in ra màn hình
#include <sstream>   // thư viện chuẩn: std::ostringstream để ghép chuỗi từ nhiều kiểu dữ liệu
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tựa sách, tác giả

class Book { // khai báo class — khuôn mẫu để tạo ra các object Book
private:
    const std::string title;  // tựa sách — riêng cho từng object
    const std::string author; // tác giả — riêng cho từng object
    const int year;           // năm xuất bản — riêng cho từng object

public:
    Book(const std::string& title, const std::string& author, int year) : title(title), author(author), year(year) { // constructor — chạy khi tạo object
        if (title.empty()) throw std::invalid_argument("Tựa sách không được rỗng");  // validate: tựa sách bắt buộc
        if (author.empty()) throw std::invalid_argument("Tác giả không được rỗng"); // validate: tác giả bắt buộc
    }

    std::string toString() const { // hàm mô tả — object tự giới thiệu bằng chuỗi người đọc hiểu được
        std::ostringstream out; // luồng ghép chuỗi — cách chuẩn của C++ để nối chữ và số
        out << title << " — " << author << " (" << year << ")"; // ghép các thuộc tính thành chuỗi dễ đọc
        return out.str(); // lấy chuỗi kết quả ra khỏi luồng
    }
};

std::ostream& operator<<(std::ostream& os, const Book& b) { // nạp chồng toán tử << — cho phép viết "std::cout << book" như với kiểu có sẵn
    return os << b.toString(); // ủy quyền cho toString() — logic mô tả chỉ viết MỘT chỗ
}

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Book b("Dế Mèn Phiêu Lưu Ký", "Tô Hoài", 1941); // tạo object Book

    check(b.toString() == "Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)", "toString sai định dạng"); // gọi trực tiếp toString()

    std::ostringstream out; // luồng chuỗi đóng vai std::cout để kiểm tra được kết quả in
    out << "Sách: " << b;   // toán tử << tự gọi bản nạp chồng cho Book — như Java tự gọi toString() khi nối chuỗi
    check(out.str() == "Sách: Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)", "operator<< phải tự gọi toString"); // xác nhận object in đúng qua <<

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
