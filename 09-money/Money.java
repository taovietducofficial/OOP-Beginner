/*
 * Ngôn ngữ: Java
 * Công dụng: Money minh họa sự khác nhau giữa == (so sánh ĐỊA CHỈ — có phải
 * cùng một object trong bộ nhớ) và equals() (so sánh NỘI DUNG — hai object
 * có cùng giá trị nghiệp vụ không), kèm quy ước bắt buộc: ghi đè equals
 * thì phải ghi đè hashCode.
 * Tại sao cần học: dùng == thay equals là lỗi Java kinh điển nhất — bug
 * chập chờn vì đôi khi hai biến tình cờ trỏ cùng object. Quên hashCode làm
 * object "biến mất" trong HashSet/HashMap.
 */
import java.util.Objects; // thư viện chuẩn: Objects.hash giúp sinh mã băm từ nhiều field

public class Money { // khai báo class — khuôn mẫu để tạo ra các object Money

    private final long amount;      // số tiền (đơn vị nhỏ nhất) — dùng long, không dùng double cho tiền
    private final String currency;  // loại tiền, vd. "VND", "USD"

    public Money(long amount, String currency) { // constructor — chạy khi gọi "new Money(...)"
        if (amount < 0) throw new IllegalArgumentException("Số tiền không được âm"); // validate: chặn tiền âm
        if (currency == null || currency.isEmpty()) throw new IllegalArgumentException("Loại tiền không được rỗng"); // validate: loại tiền bắt buộc
        this.amount = amount;     // gán số tiền truyền vào cho object
        this.currency = currency; // gán loại tiền truyền vào cho object
    }

    @Override // ghi đè equals thừa hưởng từ Object (bản mặc định chỉ so địa chỉ, y hệt ==)
    public boolean equals(Object o) { // nhận Object bất kỳ — chữ ký bắt buộc phải đúng như vậy mới là ghi đè
        if (this == o) return true;                          // cùng một object trong bộ nhớ → chắc chắn bằng nhau
        if (!(o instanceof Money)) return false;             // khác class (hoặc null) → không thể bằng nhau
        Money other = (Money) o;                             // ép kiểu về Money để đọc được field
        return amount == other.amount && currency.equals(other.currency); // bằng nhau khi CÙNG số tiền và CÙNG loại tiền
    }

    @Override // quy ước bắt buộc: đã ghi đè equals thì phải ghi đè hashCode
    public int hashCode() { // hai object equals nhau PHẢI trả về cùng mã băm
        return Objects.hash(amount, currency); // dùng thư viện chuẩn sinh mã băm từ đúng các field mà equals so sánh
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Money"
        Money a = new Money(100_000, "VND"); // tạo object thứ nhất
        Money b = new Money(100_000, "VND"); // tạo object thứ hai — CÙNG giá trị nhưng KHÁC object trong bộ nhớ

        check(a != b, "hai lệnh new phải tạo hai object khác nhau");           // == so địa chỉ: hai object riêng biệt
        check(a.equals(b), "cùng số tiền + loại tiền phải equals nhau");        // equals so nội dung: cùng giá trị nghiệp vụ
        check(a.hashCode() == b.hashCode(), "equals nhau phải cùng hashCode");  // quy ước equals/hashCode
        check(!a.equals(new Money(100_000, "USD")), "khác loại tiền không được equals"); // 100k VND khác 100k USD
        check(!a.equals(new Money(50_000, "VND")), "khác số tiền không được equals");    // 100k khác 50k
        check(!a.equals(null), "so với null phải trả về false");                          // equals với null không được ném lỗi

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
