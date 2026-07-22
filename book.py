# Ngôn ngữ: Python
#
# Công dụng: Book minh họa GHI ĐÈ __str__ — mọi class đều thừa hưởng __str__
# từ object, nhưng bản mặc định in "<__main__.Book object at 0x...>" vô dụng;
# ghi đè để object tự giới thiệu bằng chuỗi người đọc hiểu được.
#
# Tại sao cần học: __str__ tốt là công cụ debug số một — print, log, f-string
# đều gọi nó. Đây cũng là lần đầu chạm vào khái niệm "ghi đè phương thức thừa
# hưởng" (Python gọi là dunder/magic method) — nền của đa hình ở các tầng sau.


class Book:  # khai báo class — khuôn mẫu để tạo ra các object Book
    def __init__(self, title, author, year):  # constructor — chạy khi gọi "Book(...)"
        if not title:  # validate: tựa sách bắt buộc
            raise ValueError("Tựa sách không được rỗng")  # ném lỗi ngay tại biên
        if not author:  # validate: tác giả bắt buộc
            raise ValueError("Tác giả không được rỗng")  # ném lỗi ngay tại biên
        self._title = title  # gán tựa sách truyền vào cho object
        self._author = author  # gán tác giả truyền vào cho object
        self._year = year  # gán năm xuất bản truyền vào cho object

    def __str__(self):  # ghi đè bản mặc định thừa hưởng từ object — object tự mô tả chính nó (Java gọi là toString)
        return f"{self._title} — {self._author} ({self._year})"  # chuỗi dễ đọc thay cho "<__main__.Book object at 0x...>"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python book.py"
    b = Book("Dế Mèn Phiêu Lưu Ký", "Tô Hoài", 1941)  # tạo object Book

    assert str(b) == "Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)", "__str__ sai định dạng"  # str(b) gọi __str__ của object
    assert f"Sách: {b}" == "Sách: Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)", "f-string phải tự gọi __str__"  # Python tự gọi __str__ khi đưa object vào f-string/print

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
