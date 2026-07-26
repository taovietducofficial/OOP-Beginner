/*
 * Ngôn ngữ: Java
 * Công dụng: Book minh họa GHI ĐÈ toString() — mọi class đều thừa hưởng
 * toString() từ Object, nhưng bản mặc định in "Book@1b6d3586" vô dụng;
 * ghi đè để object tự giới thiệu bằng chuỗi người đọc hiểu được.
 * Tại sao cần học: toString() tốt là công cụ debug số một — log, debugger,
 * thông báo lỗi đều gọi nó. Đây cũng là lần đầu chạm vào khái niệm "ghi đè
 * phương thức thừa hưởng" (@Override) — nền của đa hình ở các tầng sau.
 */
public class Book { // khai báo class — khuôn mẫu để tạo ra các object Book

    private final String title;  // tựa sách — riêng cho từng object
    private final String author; // tác giả — riêng cho từng object
    private final int year;      // năm xuất bản — riêng cho từng object

    public Book(String title, String author, int year) { // constructor — chạy khi gọi "new Book(...)"
        if (title == null || title.isEmpty()) throw new IllegalArgumentException("Tựa sách không được rỗng");   // validate: tựa sách bắt buộc
        if (author == null || author.isEmpty()) throw new IllegalArgumentException("Tác giả không được rỗng");  // validate: tác giả bắt buộc
        this.title = title;   // gán tựa sách truyền vào cho object
        this.author = author; // gán tác giả truyền vào cho object
        this.year = year;     // gán năm xuất bản truyền vào cho object
    }

    @Override // báo cho compiler: ta ĐANG ghi đè phương thức thừa hưởng — gõ nhầm tên sẽ bị báo lỗi ngay
    public String toString() { // ghi đè bản mặc định của Object — object tự mô tả chính nó
        return title + " — " + author + " (" + year + ")"; // chuỗi dễ đọc thay cho "Book@1b6d3586"
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Book"
        Book b = new Book("Dế Mèn Phiêu Lưu Ký", "Tô Hoài", 1941); // tạo object Book

        check(b.toString().equals("Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)"), "toString sai định dạng"); // gọi trực tiếp toString()
        check(("Sách: " + b).equals("Sách: Dế Mèn Phiêu Lưu Ký — Tô Hoài (1941)"), "nối chuỗi phải tự gọi toString"); // Java tự gọi toString() khi nối object với chuỗi

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
