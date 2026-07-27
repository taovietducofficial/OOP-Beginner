/*
 * Ngôn ngữ: Java
 * Công dụng: TextUtils minh họa STATIC UTILITY CLASS — một class KHÔNG đại
 * diện cho thực thể nào, không có trạng thái, chỉ gom nhóm các hàm xử lý
 * chuỗi liên quan tới nhau. Mọi phương thức đều static; constructor bị khóa
 * (private) để không ai lỡ gọi "new TextUtils()" — làm vậy chẳng có ý nghĩa
 * gì vì class này không có gì để "là một object" cả.
 * Tại sao cần học: mọi class từ bài 01 đều tạo object rồi gọi phương thức
 * TRÊN object đó. Bài này đẩy ý tưởng "static final" ở bài 03 (hằng số dùng
 * chung) đi xa hơn — biến CẢ CLASS thành một namespace chứa hàm, không phải
 * khuôn tạo object.
 */
public final class TextUtils { // "final": không cho kế thừa — một namespace hàm không cần (và không nên) có lớp con

    private TextUtils() { // constructor PRIVATE — chặn "new TextUtils()" ngay từ lúc biên dịch bên ngoài class
        throw new AssertionError("TextUtils không được phép tạo object"); // phòng hờ nếu có ai gọi constructor từ bên trong chính class
    }

    public static String capitalize(String text) { // viết hoa ký tự đầu tiên, giữ nguyên phần còn lại
        if (text == null || text.isEmpty()) throw new IllegalArgumentException("Chuỗi không được rỗng"); // validate ở biên
        return Character.toUpperCase(text.charAt(0)) + text.substring(1);
    }

    public static String truncate(String text, int maxLength) { // cắt ngắn chuỗi nếu vượt quá maxLength, thêm "..."
        if (text == null) throw new IllegalArgumentException("Chuỗi không được null"); // validate ở biên
        if (maxLength <= 0) throw new IllegalArgumentException("maxLength phải dương"); // validate ở biên
        if (text.length() <= maxLength) return text; // đủ ngắn — giữ nguyên
        return text.substring(0, maxLength) + "..."; // dài hơn — cắt còn maxLength ký tự rồi thêm "..."
    }

    public static String slugify(String text) { // chuyển thành dạng URL-slug: chữ thường, khoảng trắng thành "-"
        if (text == null || text.isEmpty()) throw new IllegalArgumentException("Chuỗi không được rỗng"); // validate ở biên
        return text.trim().toLowerCase().replaceAll("\\s+", "-"); // trim đầu/cuối, hạ chữ thường, gộp khoảng trắng liên tiếp thành một dấu "-"
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java TextUtils"
        check(capitalize("hello").equals("Hello"), "capitalize phải viết hoa ký tự đầu, giữ nguyên phần còn lại");
        check(truncate("Hello world", 5).equals("Hello..."), "truncate phải cắt còn 5 ký tự rồi thêm ...");
        check(truncate("Hi", 5).equals("Hi"), "truncate không được đổi chuỗi đã đủ ngắn");
        check(slugify("  Hello   World  ").equals("hello-world"), "slugify phải hạ chữ thường và gộp khoảng trắng thành dấu -");

        boolean blocked = false; // cờ đánh dấu: gọi constructor (được phép cú pháp vì main nằm TRONG chính class TextUtils) có tự chặn ở runtime không
        try { new TextUtils(); } catch (AssertionError e) { blocked = true; } // constructor private vẫn gọi được từ bên trong class — nhưng tự ném lỗi ngay khi chạy
        check(blocked, "tạo object TextUtils phải tự chặn bằng cách ném lỗi ngay trong constructor");

        boolean blockedEmpty = false; // cờ đánh dấu: chuỗi rỗng truyền vào capitalize có bị chặn không
        try { capitalize(""); } catch (IllegalArgumentException e) { blockedEmpty = true; }
        check(blockedEmpty, "capitalize với chuỗi rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
