#include <unistd.h> // Thư viện này có hàm write().

int main() {
    write(1, "hello\n", 6); // Ghi 6 bytes của chuỗi "hello\n" ra màn hình (cổng 1).
    return 0;
}