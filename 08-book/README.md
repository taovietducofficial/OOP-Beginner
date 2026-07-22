# Book — object tự mô tả chính nó (`toString`)

## 1. Đề bài
Xây dựng lớp `Book` với `title`, `author`, `year`, ghi đè `toString()` trả về chuỗi
dạng `"<title> — <author> (<year>)"`.

## 2. Ý tưởng
Mọi class trong Java đều ngầm kế thừa từ `Object`, nên đều có sẵn `toString()` — nhưng
bản mặc định in ra dạng `Book@1b6d3586` (tên class + mã băm), vô dụng với người đọc.
**Ghi đè (`@Override`) `toString()`** để object tự giới thiệu bằng chuỗi dễ hiểu; từ đó
`System.out.println(book)` hay nối chuỗi `"..." + book` tự động dùng bản của ta.

## 3. Độ phức tạp
- `toString()` là `O(n)` theo độ dài chuỗi kết quả.

## 4. Lời giải
Xem [`Book.java`](Book.java) · [`Book.cpp`](Book.cpp) · [`book.py`](book.py).

## 5. Thực tế đi làm
- `toString()` tốt là công cụ debug số một: log, debugger, thông báo lỗi đều gọi nó.
  Object in ra `Order@4f3f5b24` trong log lúc 3h sáng là ác mộng của người trực hệ thống.
- Annotation `@Override` không bắt buộc nhưng luôn nên ghi: nếu gõ nhầm tên phương thức
  (vd. `tostring`), compiler báo lỗi ngay thay vì lặng lẽ tạo phương thức mới không ai gọi.

## 6. Self-check
```bash
javac Book.java && java Book                    # in "OK"
g++ -std=c++17 -o book Book.cpp && ./book   # in "OK"
python book.py                                   # in "OK"
```
