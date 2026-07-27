# Ngôn ngữ: Python
#
# Công dụng: TextUtils minh họa STATIC UTILITY CLASS — một class KHÔNG đại
# diện cho thực thể nào, không có trạng thái, chỉ gom nhóm các hàm xử lý
# chuỗi liên quan tới nhau. Mọi phương thức đều @staticmethod; __init__ tự
# ném lỗi ngay khi bị gọi để chặn "TextUtils()" — Python không có từ khóa
# "private" thật như Java/C++, nên đây là cách thông dụng nhất để báo "đừng
# tạo object từ class này".
#
# Tại sao cần học: mọi class từ bài 01 đều tạo object rồi gọi phương thức
# TRÊN object đó. Bài này đẩy ý tưởng "hằng số dùng chung" ở bài 03 đi xa
# hơn — biến CẢ CLASS thành một namespace chứa hàm, không phải khuôn tạo
# object. (Python thực ra hay dùng thẳng hàm module-level cho việc này —
# xem os.path, itertools — bài này giữ dạng class để nhất quán với Java/C++.)


class TextUtils:  # "namespace" dạng class — mọi phương thức đều static
    def __init__(self):  # tự chặn việc tạo object ngay khi có ai gọi TextUtils()
        raise AssertionError("TextUtils không được phép tạo object")

    @staticmethod
    def capitalize(text):  # viết hoa ký tự đầu tiên, giữ nguyên phần còn lại
        if not text:  # validate ở biên
            raise ValueError("Chuỗi không được rỗng")
        return text[0].upper() + text[1:]

    @staticmethod
    def truncate(text, max_length):  # cắt ngắn chuỗi nếu vượt quá max_length, thêm "..."
        if max_length <= 0:  # validate ở biên
            raise ValueError("max_length phải dương")
        if len(text) <= max_length:  # đủ ngắn — giữ nguyên
            return text
        return text[:max_length] + "..."  # dài hơn — cắt còn max_length ký tự rồi thêm "..."

    @staticmethod
    def slugify(text):  # chuyển thành dạng URL-slug: chữ thường, khoảng trắng thành "-"
        if not text:  # validate ở biên
            raise ValueError("Chuỗi không được rỗng")
        return "-".join(text.lower().split())  # split() không tham số tự gộp mọi khoảng trắng liên tiếp và bỏ đầu/cuối; join lại bằng "-"


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python text_utils.py"
    assert TextUtils.capitalize("hello") == "Hello", "capitalize phải viết hoa ký tự đầu, giữ nguyên phần còn lại"
    assert TextUtils.truncate("Hello world", 5) == "Hello...", "truncate phải cắt còn 5 ký tự rồi thêm ..."
    assert TextUtils.truncate("Hi", 5) == "Hi", "truncate không được đổi chuỗi đã đủ ngắn"
    assert TextUtils.slugify("  Hello   World  ") == "hello-world", "slugify phải hạ chữ thường và gộp khoảng trắng thành dấu -"

    blocked = False  # cờ đánh dấu: tạo object TextUtils có tự chặn không
    try:
        TextUtils()
    except AssertionError:
        blocked = True
    assert blocked, "tạo object TextUtils phải tự chặn bằng cách ném lỗi ngay trong __init__"

    blocked_empty = False  # cờ đánh dấu: chuỗi rỗng truyền vào capitalize có bị chặn không
    try:
        TextUtils.capitalize("")
    except ValueError:
        blocked_empty = True
    assert blocked_empty, "capitalize với chuỗi rỗng phải bị chặn"

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
