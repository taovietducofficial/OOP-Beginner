# Person — object làm tham số cho phương thức của object khác

## 1. Đề bài
Xây dựng lớp `Person` với `name`, cung cấp `greet(Person other)` trả về chuỗi
`"<tên mình> chào <tên other>"`.

## 2. Ý tưởng
Các bài trước, mỗi object tự tính toán trên dữ liệu của chính nó. Bài này minh họa điều
làm nên sức mạnh của OOP: **một object có thể nhận object khác làm tham số** và gọi
phương thức (`other.getName()`) trên object đó — đây là nền cho mọi tương tác giữa nhiều
class sau này (kế thừa, đa hình đều xây trên khả năng "object nói chuyện với object").

## 3. Độ phức tạp
- Mỗi phương thức `O(1)`.

## 4. Lời giải
Xem [`Person.java`](Person.java) · [`Person.cpp`](Person.cpp) · [`person.py`](person.py).

## 5. Thực tế đi làm
- Đây là mẫu hình cực phổ biến: `order.applyDiscount(coupon)`, `account.transferTo(otherAccount)`
  — một object thao tác dựa trên dữ liệu public (qua getter) của object khác.
- Cạm bẫy: object nhận vào có thể là `null` — code thực tế nên kiểm tra `other != null`
  trước khi gọi phương thức trên nó (tránh `NullPointerException`).

## 6. Self-check
```bash
javac Person.java && java Person                    # in "OK"
g++ -std=c++17 -o person Person.cpp && ./person   # in "OK"
python person.py                                   # in "OK"
```
