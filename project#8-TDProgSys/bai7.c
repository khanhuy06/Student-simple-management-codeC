#include <string.h> // Để dùng hàm strlen
#include <stdlib.h> // Để dùng hàm getenv

int main (int argc, char *argv[]) {
    if (argc < 2) {
        write (1, "Loi dinh dang", 13);
        write (1,"\n",1);
        write (1, "Cach dung: ./bai7 <ten_bien_moi_truong>", 38);
        write (1,"\n",1);
    }
    char *value = getenv(argv[1]);
    if (value == NULL) {
        write (1, "Bien moi truong khong ton tai", 29);
        write (1,"\n",1);
    }
    else {
        write (1, value, strlen(value));
        write (1,"\n",1);
    }
    return 0;
} 
