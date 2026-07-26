/*
 * Ngôn ngữ: Java
 * Công dụng: Playlist minh họa DEFENSIVE COPY — khi một object nắm giữ một
 * danh sách (mutable) bên trong, getter KHÔNG được trả thẳng tham chiếu tới
 * danh sách gốc, mà phải trả về một BẢN SAO. Nếu không, code bên ngoài giữ
 * tham chiếu đó có thể tự ý sửa (add/remove) dữ liệu nội bộ của object mà
 * không đi qua bất kỳ phương thức nào của Playlist — phá vỡ đóng gói.
 * Tại sao cần học: bài 12 (Classroom) đã cho một class chứa danh sách object
 * con, nhưng chưa để lộ danh sách đó ra ngoài qua getter. Đây là cạm bẫy
 * thường gặp nhất khi làm điều đó: đóng gói (bài 06) chặn được ghi sai qua
 * SETTER, nhưng một getter trả về tham chiếu thô vẫn là một lỗ hổng khác.
 */
import java.util.ArrayList; // thư viện chuẩn: danh sách động
import java.util.List;      // thư viện chuẩn: kiểu interface cho danh sách

public class Playlist { // khai báo class — khuôn mẫu để tạo ra các object Playlist

    private final String name;             // tên playlist — riêng cho từng object, không đổi sau khi tạo
    private final List<String> songs = new ArrayList<>(); // danh sách bài hát — dữ liệu MUTABLE nằm bên trong object

    public Playlist(String name) { // constructor — chạy khi tạo playlist mới, ban đầu chưa có bài hát nào
        this.name = name; // gán tên playlist
    }

    public String getName() { // getter — xem tên playlist
        return name;
    }

    public void addSong(String title) { // thêm một bài hát vào playlist
        if (title == null || title.isEmpty()) throw new IllegalArgumentException("Tên bài hát không được rỗng"); // validate ở biên
        songs.add(title); // đưa vào cuối danh sách nội bộ
    }

    public int size() { // đếm số bài hát hiện có
        return songs.size();
    }

    public List<String> getSongs() { // getter — trả về danh sách bài hát
        return new ArrayList<>(songs); // DEFENSIVE COPY: tạo list MỚI chép nội dung; trả "songs" trực tiếp sẽ để lộ tham chiếu nội bộ, cho phép code ngoài add/remove thẳng vào Playlist mà không qua addSong()
    }

    // ---- Self-check ----
    private static void check(boolean ok, String msg) { // hàm phụ trợ: nếu "ok" sai thì báo lỗi kèm thông điệp "msg"
        if (!ok) throw new AssertionError(msg); // ném lỗi để dừng ngay và chỉ rõ chỗ sai
    }

    public static void main(String[] args) { // điểm bắt đầu chạy chương trình khi gõ "java Playlist"
        Playlist p = new Playlist("Lofi Chill"); // tạo playlist mới, ban đầu rỗng
        p.addSong("Song A"); // thêm bài A
        p.addSong("Song B"); // thêm bài B
        check(p.size() == 2, "playlist phải có 2 bài sau khi thêm 2 lần");

        List<String> copy = p.getSongs(); // lấy bản sao ra ngoài
        copy.add("Hacked Song"); // sửa bản sao — CỐ Ý mô phỏng code ngoài tự ý thêm bài
        check(p.size() == 2, "sửa danh sách lấy từ getSongs() không được ảnh hưởng tới Playlist gốc"); // nếu getSongs() không copy, size() sẽ thành 3

        List<String> copy2 = p.getSongs(); // gọi lần nữa
        check(copy2 != copy, "hai lần gọi getSongs() phải trả về hai bản sao khác nhau, không phải cùng một tham chiếu"); // mỗi lần gọi là một copy mới, độc lập

        boolean blocked = false; // cờ đánh dấu: thêm bài hát tên rỗng có bị chặn không
        try { p.addSong(""); } catch (IllegalArgumentException e) { blocked = true; } // tên rỗng phải bị chặn
        check(blocked, "tên bài hát rỗng phải bị chặn");

        System.out.println("OK"); // in "OK" nếu mọi check ở trên đều đúng
    }
}
