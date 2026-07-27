/*
 * Ngôn ngữ: C++
 * Công dụng: TextUtils minh họa STATIC UTILITY CLASS — một class KHÔNG đại
 * diện cho thực thể nào, không có trạng thái, chỉ gom nhóm các hàm xử lý
 * chuỗi liên quan tới nhau. Mọi phương thức đều static; constructor bị xóa
 * ("= delete") để KHÔNG AI, kể cả code trong chính file này, tạo được object
 * TextUtils — chặn ngay từ lúc BIÊN DỊCH, không cần chờ tới runtime.
 * Tại sao cần học: mọi class từ bài 01 đều tạo object rồi gọi phương thức
 * TRÊN object đó. Bài này đẩy ý tưởng "static" ở bài 03 (hằng số dùng chung)
 * đi xa hơn — biến CẢ CLASS thành một namespace chứa hàm, không phải khuôn
 * tạo object. (C++ thực ra có "namespace" làm đúng việc này gọn hơn, nhưng
 * bài này giữ dạng class để nhất quán với Java/Python.)
 */
#include <algorithm> // thư viện chuẩn: std::transform, std::unique
#include <cctype>    // thư viện chuẩn: std::toupper, std::tolower, std::isspace
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string

class TextUtils { // "namespace" dạng class — mọi thành viên đều static
public:
    TextUtils() = delete; // XÓA constructor — "TextUtils t;" hay "new TextUtils()" đều là LỖI BIÊN DỊCH, không cần chờ runtime

    static std::string capitalize(const std::string& text) { // viết hoa ký tự đầu tiên, giữ nguyên phần còn lại
        if (text.empty()) throw std::invalid_argument("Chuoi khong duoc rong"); // validate ở biên
        std::string result = text;
        result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
        return result;
    }

    static std::string truncate(const std::string& text, int maxLength) { // cắt ngắn chuỗi nếu vượt quá maxLength, thêm "..."
        if (maxLength <= 0) throw std::invalid_argument("maxLength phai duong"); // validate ở biên
        if (static_cast<int>(text.size()) <= maxLength) return text; // đủ ngắn — giữ nguyên
        return text.substr(0, maxLength) + "..."; // dài hơn — cắt còn maxLength ký tự rồi thêm "..."
    }

    static std::string slugify(const std::string& text) { // chuyển thành dạng URL-slug: chữ thường, khoảng trắng thành "-"
        if (text.empty()) throw std::invalid_argument("Chuoi khong duoc rong"); // validate ở biên
        size_t start = text.find_first_not_of(" \t\n"); // vị trí ký tự không phải khoảng trắng đầu tiên
        size_t end = text.find_last_not_of(" \t\n");    // vị trí ký tự không phải khoảng trắng cuối cùng
        std::string trimmed = (start == std::string::npos) ? "" : text.substr(start, end - start + 1); // cắt khoảng trắng đầu/cuối

        std::string result;
        bool lastWasSpace = false; // cờ đánh dấu ký tự trước đó có phải khoảng trắng không — để gộp nhiều khoảng trắng liên tiếp thành một "-"
        for (char c : trimmed) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!lastWasSpace) result += '-'; // chỉ thêm MỘT dấu "-" cho một chuỗi khoảng trắng liên tiếp
                lastWasSpace = true;
            } else {
                result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                lastWasSpace = false;
            }
        }
        return result;
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    check(TextUtils::capitalize("hello") == "Hello", "capitalize phai viet hoa ky tu dau, giu nguyen phan con lai");
    check(TextUtils::truncate("Hello world", 5) == "Hello...", "truncate phai cat con 5 ky tu roi them ...");
    check(TextUtils::truncate("Hi", 5) == "Hi", "truncate khong duoc doi chuoi da du ngan");
    check(TextUtils::slugify("  Hello   World  ") == "hello-world", "slugify phai ha chu thuong va gop khoang trang thanh dau -");

    // "TextUtils t;" hoặc "new TextUtils()" ở đây sẽ KHÔNG BIÊN DỊCH ĐƯỢC — đó chính là bằng chứng constructor đã bị chặn (= delete),
    // mạnh hơn cả một self-check runtime: lỗi bị bắt ngay khi biên dịch chứ không phải khi chạy.

    bool blockedEmpty = false; // cờ đánh dấu: chuỗi rỗng truyền vào capitalize có bị chặn không
    try { TextUtils::capitalize(""); } catch (const std::invalid_argument&) { blockedEmpty = true; }
    check(blockedEmpty, "capitalize voi chuoi rong phai bi chan");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
