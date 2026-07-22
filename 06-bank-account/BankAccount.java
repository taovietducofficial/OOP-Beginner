/*
 * Ngôn ngữ: Java
 *
 * Công dụng: BankAccount minh họa ĐÓNG GÓI (encapsulation) — số dư để private,
 * mọi thay đổi bắt buộc đi qua deposit/withdraw, nơi các quy tắc nghiệp vụ
 * (tiền > 0, không rút quá số dư) được kiểm tra.
 *
 * Tại sao cần học: đóng gói là trụ cột đầu tiên của OOP. Nếu field để public,
 * bất kỳ dòng code nào cũng có thể gán balance = -1000 và phá hỏng dữ liệu —
 * bug kiểu này cực khó truy vết vì chỗ gãy nằm xa chỗ gán sai.
 */
public class BankAccount { // khai báo class — khuôn mẫu để tạo ra các object BankAccount

    private long balance; // số dư (đơn vị: đồng) — private: bên ngoài KHÔNG gán trực tiếp được; dùng long thay vì double để tránh sai số dấu phẩy động với tiền

    public BankAccount(long initialBalance) { // constructor — chạy khi gọi "new BankAccount(...)"
        if (initialBalance < 0) throw new IllegalArgumentException("Số dư ban đầu không được âm"); // validate ở biên: chặn số dư âm ngay từ lúc tạo
        this.balance = initialBalance; // gán số dư ban đầu cho object
    }

    public void deposit(long amount) { // nạp tiền — cách HỢP LỆ duy nhất để tăng số dư
        if (amount <= 0) throw new IllegalArgumentException("Tiền nạp phải > 0"); // quy tắc nghiệp vụ: không nạp số âm hoặc 0
        balance += amount; // cộng tiền vào số dư
    }

    public void withdraw(long amount) { // rút tiền — cách HỢP LỆ duy nhất để giảm số dư
        if (amount <= 0) throw new IllegalArgumentException("Tiền rút phải > 0"); // quy tắc nghiệp vụ: không rút số âm hoặc 0
        if (amount > balance) throw new IllegalArgumentException("Số dư không đủ"); // quy tắc nghiệp vụ: không cho rút quá số dư
        balance -= amount; // trừ tiền khỏi số dư
    }

    public long getBalance() { // getter — cho bên ngoài XEM số dư, nhưng không SỬA được
        return balance; // trả về số dư hiện tại
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java BankAccount"
        BankAccount acc = new BankAccount(100_000); // tạo tài khoản với 100.000đ
        acc.deposit(50_000); // nạp thêm 50.000đ
        check(acc.getBalance() == 150_000, "nạp tiền sai"); // 100k + 50k = 150k
        acc.withdraw(70_000); // rút 70.000đ
        check(acc.getBalance() == 80_000, "rút tiền sai"); // 150k - 70k = 80k

        boolean blocked = false; // cờ đánh dấu: việc rút lố có bị chặn không
        try { acc.withdraw(1_000_000); } catch (IllegalArgumentException e) { blocked = true; } // cố rút 1 triệu khi chỉ còn 80k — phải bị ném lỗi
        check(blocked, "rút quá số dư phải bị chặn"); // xác nhận quy tắc "không rút lố" hoạt động
        check(acc.getBalance() == 80_000, "số dư không được đổi khi giao dịch bị chặn"); // giao dịch lỗi thì số dư giữ nguyên

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
