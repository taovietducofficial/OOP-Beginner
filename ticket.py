# Ngôn ngữ: Python
#
# Công dụng: Ticket minh họa thuộc tính CLASS thay đổi được — một bộ đếm duy
# nhất thuộc về class, mọi lần tạo object đều cộng vào nó; mỗi object chép giá
# trị bộ đếm tại thời điểm tạo vào id riêng của mình. Dữ liệu class (tổng số
# vé) và dữ liệu instance (id từng vé) phối hợp với nhau.
#
# Tại sao cần học: đây là cơ chế đằng sau id tự tăng của database, số hóa
# đơn, mã đơn hàng. Đồng thời là bài học về cạm bẫy: thuộc tính class thay đổi
# được là trạng thái toàn cục — nhiều thread cùng tạo object sẽ cấp trùng id;
# và trong Python, viết "self.total_issued = ..." sẽ tạo NHẦM thuộc tính
# instance che mất bộ đếm class — phải cộng qua tên class (Ticket.total_issued).


class Ticket:  # khai báo class — khuôn mẫu để tạo ra các object Ticket
    _total_issued = 0  # bộ đếm CLASS: khai báo trong thân class, chỉ có 1 bản duy nhất, mọi lần tạo object đều cộng vào đây
    # ponytail: int thường, đủ cho bài học đơn luồng; code thật nhiều thread dùng khóa (threading.Lock) hoặc để database cấp số

    def __init__(self):  # constructor — chạy khi gọi "Ticket()"
        Ticket._total_issued += 1  # cộng bộ đếm chung QUA TÊN CLASS — dùng "self._total_issued += 1" sẽ tạo nhầm bản sao instance che mất bộ đếm
        self._id = Ticket._total_issued  # chép giá trị bộ đếm TẠI THỜI ĐIỂM NÀY vào id riêng của vé (gán qua self = thuộc tính instance)

    def get_id(self):  # getter — xem số thứ tự của vé này
        return self._id  # trả về id riêng của object hiện tại

    @classmethod  # phương thức CLASS: hỏi class, không cần object nào — tương đương static method của Java/C++
    def get_total_issued(cls):  # "cls" là chính class Ticket, như "self" là chính object
        return cls._total_issued  # trả về bộ đếm chung


# ---- Self-check ----
if __name__ == "__main__":  # chỉ chạy khi thực thi trực tiếp "python ticket.py"
    assert Ticket.get_total_issued() == 0, "chưa phát vé nào thì tổng phải là 0"  # gọi qua tên class — chưa cần object nào tồn tại

    t1 = Ticket()  # phát vé thứ nhất
    t2 = Ticket()  # phát vé thứ hai
    t3 = Ticket()  # phát vé thứ ba

    assert t1.get_id() == 1, "vé đầu tiên phải mang số 1"  # mỗi vé giữ số cấp tại thời điểm tạo
    assert t2.get_id() == 2, "vé thứ hai phải mang số 2"  # id tự tăng, không trùng
    assert t3.get_id() == 3, "vé thứ ba phải mang số 3"  # tiếp tục tăng
    assert Ticket.get_total_issued() == 3, "tổng vé đã phát phải là 3"  # bộ đếm class phản ánh mọi lần tạo object

    print("OK")  # in "OK" nếu mọi assert ở trên đều đúng
