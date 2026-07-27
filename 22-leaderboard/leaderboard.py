# Ngôn ngữ: Python

# Công dụng: Player/Leaderboard minh họa THỨ TỰ TỰ NHIÊN (natural ordering)
# — Player tự khai báo cách so sánh với một Player khác bằng cách định nghĩa
# __lt__. Nhờ vậy sorted()/list.sort() dùng được ngay trên danh sách Player
# mà không cần viết thêm hàm so sánh rời rạc ở nơi gọi.

# Tại sao cần học: bài 09 (Money) dạy so sánh BẰNG NHAU (__eq__). Bài này
# dạy so sánh HƠN/KÉM để sắp xếp — một khái niệm khác, dùng cho một mục đích
# khác (__eq__ trả lời "có giống nhau không", __lt__ trả lời "ai đứng trước
# ai").


class Player:  # đại diện một người chơi có tên và điểm số
    def __init__(self, name, score):  # constructor — chạy khi tạo một người chơi
        if not name:  # validate ở biên
            raise ValueError("Tên người chơi không được rỗng")
        if score < 0:  # validate ở biên
            raise ValueError("Điểm số không được âm")
        self._name = name
        self._score = score

    def get_name(self):  # getter — xem tên người chơi
        return self._name

    def get_score(self):  # getter — xem điểm số hiện tại
        return self._score

    def __lt__(self, other):  # THỨ TỰ TỰ NHIÊN: điểm cao hơn thì "nhỏ hơn" (đứng trước) trong sắp xếp tăng dần
        return self._score > other._score  # đảo chiều so sánh để sorted() tăng dần cho ra thứ tự ĐIỂM GIẢM DẦN


class Leaderboard:  # khai báo class — quản lý tập hợp Player và tính bảng xếp hạng
    def __init__(self):
        self._players = []  # tập hợp các Player đã thêm — CHƯA sắp xếp theo thứ tự thêm vào

    def add_player(self, name, score):  # thêm một người chơi mới vào bảng
        self._players.append(Player(name, score))

    def get_ranking(self):  # trả về danh sách đã SẮP XẾP theo score giảm dần — không đổi thứ tự nội bộ của "_players"
        return sorted(self._players)  # sorted() trả về BẢN SAO đã sắp xếp (bài 17), dùng ĐÚNG __lt__ đã khai báo trong Player


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python leaderboard.py"
    board = Leaderboard()
    board.add_player("An", 50)   # thêm THEO THỨ TỰ: An, Binh, Chi — không phải thứ tự điểm số
    board.add_player("Binh", 90)
    board.add_player("Chi", 70)

    ranking = board.get_ranking()
    assert len(ranking) == 3, "bảng xếp hạng phải có đủ 3 người chơi"
    assert ranking[0].get_name() == "Binh", "điểm cao nhất (90) phải đứng đầu bảng xếp hạng"
    assert ranking[1].get_name() == "Chi", "điểm nhì (70) phải đứng thứ hai"
    assert ranking[2].get_name() == "An", "điểm thấp nhất (50) phải đứng cuối"

    p1 = Player("X", 100)
    p2 = Player("Y", 80)
    assert p1 < p2, "người chơi điểm cao hơn phải 'nhỏ hơn' (__lt__) để đứng trước khi sort tăng dần"

    blocked_score = False  # cờ đánh dấu: điểm âm có bị chặn không
    try:
        Player("Z", -1)
    except ValueError:
        blocked_score = True
    assert blocked_score, "điểm số âm phải bị chặn"

    blocked_name = False  # cờ đánh dấu: tên rỗng có bị chặn không
    try:
        Player("", 10)
    except ValueError:
        blocked_name = True
    assert blocked_name, "tên người chơi rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
