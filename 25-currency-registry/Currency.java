/*
 * Ngôn ngữ: Java
 * Công dụng: Currency minh họa CACHED/INTERNED FACTORY — Currency.of(code)
 * tra một Map nội bộ trước: nếu "code" đã từng được tạo, TRẢ LẠI ĐÚNG object
 * cũ thay vì tạo mới; nếu chưa, tạo một lần rồi lưu vào Map để lần sau dùng
 * lại. Gọi of("USD") nhiều lần luôn trả về CÙNG MỘT object (== đúng, không
 * chỉ equals() đúng).
 * Tại sao cần học: bài 13 (Temperature) dùng static factory nhưng mỗi lần
 * gọi vẫn "new" một object mới. Bài này thêm một lớp: factory còn NHỚ LẠI
 * kết quả trước đó theo khóa (code), tránh tạo trùng lặp những object có
 * cùng nội dung.
 */
import java.util.HashMap; // thư viện chuẩn: cấu trúc key-value làm "sổ đăng ký"
import java.util.Map;

public class Currency { // đại diện một loại tiền tệ — chỉ tạo được qua of(code), không có constructor public
    private static final Map<String, Currency> REGISTRY = new HashMap<>(); // "sổ đăng ký" dùng chung — lưu MỌI Currency đã từng tạo, theo khóa code
    private static final Map<String, String> SUPPORTED_SYMBOLS = new HashMap<>(); // danh sách mã tiền tệ hợp lệ và ký hiệu tương ứng

    static { // khối khởi tạo static — chạy MỘT LẦN khi class được nạp, trước khi bất kỳ ai gọi of()
        SUPPORTED_SYMBOLS.put("USD", "$");
        SUPPORTED_SYMBOLS.put("VND", "₫");
        SUPPORTED_SYMBOLS.put("EUR", "€");
    }

    private final String code;   // mã tiền tệ, ví dụ "USD"
    private final String symbol; // ký hiệu tương ứng, ví dụ "$"

    private Currency(String code, String symbol) { // constructor PRIVATE — không ai được new Currency(...) trực tiếp, chỉ of() được gọi
        this.code = code;
        this.symbol = symbol;
    }

    public static Currency of(String code) { // static factory CÓ CACHE — trái tim của bài này
        if (REGISTRY.containsKey(code)) { // đã từng tạo trước đó — trả lại ĐÚNG object cũ, KHÔNG tạo mới
            return REGISTRY.get(code);
        }
        String symbol = SUPPORTED_SYMBOLS.get(code); // tra ký hiệu — null nếu code không được hỗ trợ
        if (symbol == null) throw new IllegalArgumentException("Mã tiền tệ không được hỗ trợ: " + code); // validate ở biên
        Currency created = new Currency(code, symbol); // CHỈ tạo mới khi thật sự chưa có trong sổ đăng ký
        REGISTRY.put(code, created); // lưu lại để LẦN SAU gọi of(cùng code) trả về đúng object này
        return created;
    }

    public String getCode() { return code; } // getter — xem mã tiền tệ

    public String getSymbol() { return symbol; } // getter — xem ký hiệu

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Currency"
        Currency usd1 = Currency.of("USD");
        Currency usd2 = Currency.of("USD"); // gọi lần thứ hai với CÙNG code
        check(usd1 == usd2, "gọi of(\"USD\") hai lần phải trả về CÙNG MỘT object (reference equality), không phải hai bản sao");
        check(usd1.getSymbol().equals("$"), "ký hiệu USD phải là $");

        Currency vnd = Currency.of("VND");
        check(vnd != usd1, "hai code khác nhau phải là hai object khác nhau");
        check(vnd.getSymbol().equals("₫"), "ký hiệu VND phải là ₫");

        boolean blocked = false; // cờ đánh dấu: mã tiền tệ không hỗ trợ có bị chặn không
        try { Currency.of("XYZ"); } catch (IllegalArgumentException e) { blocked = true; }
        check(blocked, "mã tiền tệ không được hỗ trợ phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
