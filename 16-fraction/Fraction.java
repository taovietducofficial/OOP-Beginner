/*
 * Ngôn ngữ: Java
 * Công dụng: Fraction minh họa OBJECT BẤT BIẾN (immutable) — không có
 * setter nào, mọi phép toán (add, multiply) không sửa object đang có mà
 * TRẢ VỀ MỘT OBJECT MỚI. Tử số/mẫu số được rút gọn và chuẩn hóa dấu ngay
 * trong constructor, chạy đúng một lần.
 * Tại sao cần học: bài 04 (Counter) và bài 06 (BankAccount) đều là object
 * CÓ TRẠNG THÁI THAY ĐỔI — phương thức sửa dữ liệu ngay trên chính object.
 * Bài này đối lập hoàn toàn: object bất biến an toàn hơn khi chia sẻ giữa
 * nhiều nơi trong chương trình (không ai vô tình sửa được nó) — nền tảng
 * của String, LocalDate, BigDecimal trong Java.
 */
public class Fraction { // khai báo class — khuôn mẫu để tạo ra các object Fraction

    private final int numerator;   // tử số — gán một lần trong constructor, không đổi sau đó
    private final int denominator; // mẫu số — luôn dương sau khi chuẩn hóa, không đổi sau đó

    public Fraction(int numerator, int denominator) { // constructor — chạy khi gọi "new Fraction(...)"
        if (denominator == 0) throw new IllegalArgumentException("Mẫu số không được bằng 0"); // validate ở biên

        if (denominator < 0) { // chuẩn hóa dấu: mẫu số luôn dương, dấu âm (nếu có) dồn hết về tử số
            numerator = -numerator;
            denominator = -denominator;
        }

        int g = gcd(Math.abs(numerator), denominator); // ước chung lớn nhất — dùng để rút gọn về dạng tối giản
        this.numerator = numerator / g;     // rút gọn tử số
        this.denominator = denominator / g; // rút gọn mẫu số
    }

    private static int gcd(int a, int b) { // Java không có sẵn gcd số nguyên đơn giản trong Math — tự viết thuật toán Euclid
        while (b != 0) { // lặp tới khi số dư bằng 0
            int t = b;
            b = a % b;
            a = t;
        }
        return a; // b luôn > 0 khi gọi (denominator đã validate != 0 và chuẩn hóa dương) nên a không thể là 0
    }

    public int getNumerator() { // getter — xem tử số hiện tại (đã rút gọn)
        return numerator;
    }

    public int getDenominator() { // getter — xem mẫu số hiện tại (đã rút gọn)
        return denominator;
    }

    public Fraction add(Fraction other) { // cộng phân số — KHÔNG sửa this hay other, trả về Fraction MỚI
        return new Fraction(
            numerator * other.denominator + other.numerator * denominator,
            denominator * other.denominator
        ); // a/b + c/d = (ad + bc) / bd — constructor mới tự rút gọn kết quả
    }

    public Fraction multiply(Fraction other) { // nhân phân số — KHÔNG sửa this hay other, trả về Fraction MỚI
        return new Fraction(numerator * other.numerator, denominator * other.denominator); // a/b * c/d = ac / bd
    }

    @Override
    public String toString() { // object tự mô tả chính nó, vd. "1/2"
        return numerator + "/" + denominator;
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Fraction"
        Fraction a = new Fraction(2, 4); // 2/4 phải tự rút gọn
        check(a.toString().equals("1/2"), "2/4 phải tự rút gọn thành 1/2");

        Fraction b = new Fraction(-1, -2); // cả tử lẫn mẫu âm — phải chuẩn hóa thành dương
        check(b.toString().equals("1/2"), "cả tử lẫn mẫu âm phải chuẩn hóa thành dương");

        Fraction c = new Fraction(1, -2); // mẫu âm — dấu phải dồn về tử số
        check(c.toString().equals("-1/2"), "dấu âm phải dồn về tử số, mẫu số luôn dương");

        Fraction sum = a.add(new Fraction(1, 3)); // 1/2 + 1/3 = 5/6
        check(sum.toString().equals("5/6"), "1/2 + 1/3 phải bằng 5/6");
        check(a.toString().equals("1/2"), "add() không được sửa object gốc — object bất biến"); // a giữ nguyên sau add()

        Fraction product = a.multiply(new Fraction(2, 3)); // 1/2 * 2/3 = 2/6 = 1/3
        check(product.toString().equals("1/3"), "1/2 * 2/3 phải rút gọn thành 1/3");

        boolean blocked = false; // cờ đánh dấu: mẫu số 0 có bị chặn không
        try { new Fraction(1, 0); } catch (IllegalArgumentException e) { blocked = true; } // mẫu số 0 phải bị chặn
        check(blocked, "mẫu số bằng 0 phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
