#include <unistd.h>
#include <stdio.h>

int main () {
    ssize_t ket_qua = write (99, "hello\n", 6); // Hàm write trả về số byte mà nó ghi dc, size_t là đo số byte k âm
                                               // ssize_t là đo số byte có âm, dùng trong trường hợp hàm write() bị lỗi, trả về -1.
    // Bài 2 này mình cố tình làm lỗi bằng cách truyền cổng ra là 99.
    if (ket_qua==-1) {
        perror ("Loi"); // Hàm perror sẽ đi tìm lỗi, và sau đó xuất thông báo lỗi ra màn hình, thông qua cổng 2.
        return 1;
    }
    else {
        return 0;
    }
}

// Gói gọn trong 1 dòng lệnh : int main () { if(write(99, "hello\n", 6)==-1){perror("Loi");return 1;} return 0; }