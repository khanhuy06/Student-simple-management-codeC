#include <unistd.h>

int main () {
    ssize_t ket_qua = write (99, "hello\n", 6); // Hàm write trả về số byte mà nó ghi dc, size_t là đo số byte k âm
                                               // ssize_t là đo số byte có âm, dùng trong trường hợp hàm write() bị lỗi, trả về -1.
    // Bài 2 này mình cố tình làm lỗi bằng cách truyền cổng ra là 99.
    if (ket_qua==-1) {
        write(2, "loi\n", 4); // Cổng 2 cũng xuất ra terminal, nma nó báo lỗi
        return 1;
    }
    else {
        return 0;
    }
}