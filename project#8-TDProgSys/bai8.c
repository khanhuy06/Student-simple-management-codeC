#include <unistd.h> // Hàm write và pathconf
#include <errno.h> // Biến errno
#include <string.h> // Hàm strlen
#include <stdio.h> // Hàm printf

void pr_pathconf(char *path, int name, char *msg) {
    errno = 0;
    long limit = pathconf (path, name);
    if (limit == -1 && errno != 0) {
        write (1, "Loi duong dan hoac tham so", 26);
        write (1,"\n",1);
    }
    else {
        //write (1, msg, strlen(msg));
        // write (1, limit, sizeof(int)); Nếu gõ như này, write sẽ mò đến ô nhớ số "limit" để tìm dữ liệu, bị sai.
            // Write k xem limit là 1 chuỗi chữ số được, nên ta phải biến nó thành 1 chuỗi chữ số để đọc. 
        //write (1,"\n",1);
        printf ("%s : %ld\n", msg, limit); // Bài này k cấm dùng printf.
    }
    return; // Vì là hàm void.
}
// --------------------------------------------------------- //
//Bài 9 :
int main(void) {
    // Ta lấy thư mục hiện tại "." để chạy thử nghiệm các hằng số POSIX.1:
    // 1. Thử kiểm tra độ dài tên file tối đa
    pr_pathconf(".", _PC_NAME_MAX, "Do dai toi da ten file");
    // 2. Thử kiểm tra độ dài cả đường dẫn tối đa
    pr_pathconf(".", _PC_PATH_MAX, "Do dai toi da duong dan");
    // 3. Thử kiểm tra kích thước bộ đệm Pipe
    pr_pathconf(".", _PC_PIPE_BUF, "Kich thuoc bo dem Pipe");
    // 4. Thử cố tình truyền đường dẫn sai để xem hàm có in chữ "Loi" không
    pr_pathconf("duong_dan_khong_ton_tai", _PC_NAME_MAX, "Test duong dan sai");
    return 0;
}