# Ngôn ngữ: Python
#
# Công dụng: Playlist minh họa DEFENSIVE COPY — khi một object nắm giữ một
# danh sách (mutable) bên trong, getter KHÔNG được trả thẳng tham chiếu tới
# danh sách gốc, mà phải trả về một BẢN SAO. Nếu không, code bên ngoài giữ
# tham chiếu đó có thể tự ý sửa (append/remove) dữ liệu nội bộ của object mà
# không đi qua bất kỳ phương thức nào của Playlist — phá vỡ đóng gói.
#
# Tại sao cần học: bài 12 (Classroom) đã cho một class chứa danh sách object
# con, nhưng chưa để lộ danh sách đó ra ngoài qua getter. Python, mọi biến
# list đều là THAM CHIẾU — "return self._songs" trả thẳng tham chiếu tới list
# nội bộ, code ngoài gọi .append() trên kết quả đó là sửa xuyên qua vào tận
# bên trong object, y hệt cạm bẫy trong Java.


class Playlist:  # khai báo class — khuôn mẫu để tạo ra các object Playlist
    def __init__(self, name):  # constructor — chạy khi tạo playlist mới, ban đầu chưa có bài hát nào
        self._name = name  # tên playlist — riêng cho từng object, không đổi sau khi tạo
        self._songs = []  # danh sách bài hát — dữ liệu MUTABLE nằm bên trong object

    def get_name(self):  # getter — xem tên playlist
        return self._name

    def add_song(self, title):  # thêm một bài hát vào playlist
        if not title:  # validate ở biên
            raise ValueError("Tên bài hát không được rỗng")
        self._songs.append(title)  # đưa vào cuối danh sách nội bộ

    def size(self):  # đếm số bài hát hiện có
        return len(self._songs)

    def get_songs(self):  # getter — trả về danh sách bài hát
        return list(self._songs)  # DEFENSIVE COPY: list(...) tạo list MỚI chép nội dung; "return self._songs" sẽ để lộ tham chiếu nội bộ, cho phép code ngoài append/remove thẳng vào Playlist mà không qua add_song()


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python playlist.py"
    p = Playlist("Lofi Chill")  # tạo playlist mới, ban đầu rỗng
    p.add_song("Song A")  # thêm bài A
    p.add_song("Song B")  # thêm bài B
    assert p.size() == 2, "playlist phải có 2 bài sau khi thêm 2 lần"

    copy = p.get_songs()  # lấy bản sao ra ngoài
    copy.append("Hacked Song")  # sửa bản sao — CỐ Ý mô phỏng code ngoài tự ý thêm bài
    assert p.size() == 2, "sửa list lấy từ get_songs() không được ảnh hưởng tới Playlist gốc"  # nếu get_songs() không copy, size() sẽ thành 3

    copy2 = p.get_songs()  # gọi lần nữa
    assert copy2 is not copy, "hai lần gọi get_songs() phải trả về hai bản sao khác nhau, không phải cùng một tham chiếu"  # mỗi lần gọi là một copy mới, độc lập

    blocked = False  # cờ đánh dấu: thêm bài hát tên rỗng có bị chặn không
    try:
        p.add_song("")  # tên rỗng phải bị chặn
    except ValueError:
        blocked = True
    assert blocked, "tên bài hát rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
