/*
 * Ngôn ngữ: C++
 * Công dụng: Player/Leaderboard minh họa THỨ TỰ TỰ NHIÊN (natural ordering)
 * — Player tự khai báo cách so sánh với một Player khác bằng operator<. Nhờ
 * vậy std::sort dùng được ngay trên danh sách Player mà không cần viết thêm
 * hàm so sánh rời rạc ở nơi gọi.
 * Tại sao cần học: bài 09 (Money) dạy so sánh BẰNG NHAU (operator==). Bài
 * này dạy so sánh HƠN/KÉM để sắp xếp — một khái niệm khác, dùng cho một mục
 * đích khác (== trả lời "có giống nhau không", < trả lời "ai đứng trước ai").
 */
#include <algorithm> // thư viện chuẩn: std::sort
#include <cstdlib>   // thư viện chuẩn: std::exit để dừng chương trình khi self-check thất bại
#include <iostream>  // thư viện chuẩn: std::cout/std::cerr để in ra màn hình
#include <stdexcept> // thư viện chuẩn: std::invalid_argument để báo lỗi dữ liệu sai
#include <string>    // thư viện chuẩn: std::string cho tên
#include <vector>    // thư viện chuẩn: danh sách động

class Player { // đại diện một người chơi có tên và điểm số
private:
    std::string name; // tên người chơi
    int score;          // điểm số — càng cao càng đứng trước trong bảng xếp hạng

public:
    Player(std::string name, int score) : score(score) { // constructor — chạy khi tạo một người chơi
        if (name.empty()) throw std::invalid_argument("Ten nguoi choi khong duoc rong"); // validate ở biên
        if (score < 0) throw std::invalid_argument("Diem so khong duoc am"); // validate ở biên
        this->name = std::move(name);
    }

    const std::string& getName() const { // getter — xem tên người chơi
        return name;
    }

    int getScore() const { // getter — xem điểm số hiện tại
        return score;
    }

    bool operator<(const Player& other) const { // THỨ TỰ TỰ NHIÊN: điểm cao hơn thì "nhỏ hơn" (đứng trước) trong sắp xếp tăng dần
        return this->score > other.score; // đảo chiều so sánh để std::sort tăng dần cho ra thứ tự ĐIỂM GIẢM DẦN
    }
};

class Leaderboard { // khai báo class — quản lý tập hợp Player và tính bảng xếp hạng
private:
    std::vector<Player> players; // tập hợp các Player đã thêm — CHƯA sắp xếp theo thứ tự thêm vào

public:
    void addPlayer(const std::string& name, int score) { // thêm một người chơi mới vào bảng
        players.push_back(Player(name, score));
    }

    std::vector<Player> getRanking() const { // trả về danh sách đã SẮP XẾP theo score giảm dần — không đổi thứ tự nội bộ của "players"
        std::vector<Player> ranking = players; // bản sao (bài 17) — sort không được phép làm xáo trộn danh sách gốc ngoài ý muốn
        std::sort(ranking.begin(), ranking.end()); // dùng ĐÚNG operator< đã khai báo trong Player — không cần viết hàm so sánh riêng
        return ranking;
    }
};

// ---- Self-check ----
static void check(bool ok, const std::string& msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
    if (!ok) { std::cerr << "FAIL: " << msg << "\n"; std::exit(1); } // in chỗ sai rồi dừng ngay
}

int main() { // điểm bắt đầu chạy chương trình sau khi biên dịch
    Leaderboard board;
    board.addPlayer("An", 50);   // thêm THEO THỨ TỰ: An, Binh, Chi — không phải thứ tự điểm số
    board.addPlayer("Binh", 90);
    board.addPlayer("Chi", 70);

    std::vector<Player> ranking = board.getRanking();
    check(ranking.size() == 3, "bang xep hang phai co du 3 nguoi choi");
    check(ranking[0].getName() == "Binh", "diem cao nhat (90) phai dung dau bang xep hang");
    check(ranking[1].getName() == "Chi", "diem nhi (70) phai dung thu hai");
    check(ranking[2].getName() == "An", "diem thap nhat (50) phai dung cuoi");

    Player p1("X", 100);
    Player p2("Y", 80);
    check(p1 < p2, "nguoi choi diem cao hon phai 'nho hon' (operator<) de dung truoc khi sort tang dan");

    bool blockedScore = false; // cờ đánh dấu: điểm âm có bị chặn không
    try { Player bad("Z", -1); } catch (const std::invalid_argument&) { blockedScore = true; }
    check(blockedScore, "diem so am phai bi chan");

    bool blockedName = false; // cờ đánh dấu: tên rỗng có bị chặn không
    try { Player bad("", 10); } catch (const std::invalid_argument&) { blockedName = true; }
    check(blockedName, "ten nguoi choi rong phai bi chan");

    std::cout << "OK\n"; // in "OK" nếu mọi check ở trên đều đúng
    return 0; // báo chương trình kết thúc thành công
}
