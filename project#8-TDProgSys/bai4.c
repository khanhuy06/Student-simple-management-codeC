#include <unistd.h> // Thằng này để dùng hàm write() ghi ra màn hình.
#include <stdio.h> 
#include <string.h> // Thằng này để dùng hàm strlen() đo độ dài chuỗi.
#include <errno.h> // Thằng này để dùng cái biến errno.

int main () {
    ssize_t ket_qua = write (99, "hello\n", 6); // Hàm write trả về số byte mà nó ghi dc, size_t là đo số byte k âm
                                               // ssize_t là đo số byte có âm, dùng trong trường hợp hàm write() bị lỗi, trả về -1.
    // Bài 2 này mình cố tình làm lỗi bằng cách truyền cổng ra là 99.
    if (ket_qua==-1) {
        char *loi = strerror(errno);       // Lấy chuỗi mô tả lỗi của hệ thống
        write(2, "Loi : ", 6);             // In chữ "Loi : " (6 ký tự)
        write(2, loi, strlen(loi));        // In thông điệp lỗi hệ thống ra màn hình
        write(2, "\n", 1);                 // In ký tự xuống dòng
        //Cách khác : fprintf (stderr, "%s : %s\n", "Loi", strerror(errno)); // Dùng như này để in ra lỗi, thay vì write bất tiện.
        return 1;
    }
    else {
        return 0;
    }
}
