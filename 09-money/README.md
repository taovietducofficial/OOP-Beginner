# Money — so sánh object: `==` khác `equals()`

## 1. Đề bài
Xây dựng lớp `Money` với `amount` (số tiền) và `currency` (loại tiền), ghi đè
`equals()` (kèm `hashCode()`) sao cho hai object cùng số tiền + cùng loại tiền
được coi là **bằng nhau**.

## 2. Ý tưởng
Với object, `==` so sánh **địa chỉ** (có phải cùng một object trong bộ nhớ không),
còn `equals()` so sánh **nội dung**. Hai tờ tiền `100_000 VND` tạo bằng hai lệnh `new`
là hai object khác nhau (`==` cho `false`) nhưng về nghiệp vụ là một giá trị
(`equals` phải cho `true`). Quy ước bắt buộc của Java: **ghi đè `equals` thì phải ghi
đè `hashCode`** — hai object bằng nhau phải có cùng mã băm.

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Money.java`](Money.java) · [`Money.cpp`](Money.cpp) · [`money.py`](money.py).

## 5. Thực tế đi làm
- Dùng `==` thay vì `equals` để so chuỗi/object là lỗi phỏng vấn và lỗi production kinh
  điển nhất của Java — bug chập chờn vì đôi khi hai biến tình cờ trỏ cùng object.
- Quên `hashCode` khi đã ghi đè `equals` làm object "biến mất" trong `HashSet`/`HashMap`
  — cấu trúc băm tìm theo mã băm trước rồi mới gọi `equals`.

## 6. Self-check
```bash
javac Money.java && java Money                    # in "OK"
g++ -std=c++17 -o money Money.cpp && ./money   # in "OK"
python money.py                                   # in "OK"
```
