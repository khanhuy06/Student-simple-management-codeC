#include <unistd.h> // Cái này để dùng write()
#include <string.h> // Cái này để dùng strlen()

extern char **environ; // Gọi biến môi trường.

int main () // Lệnh thực thi bắt buộc luôn phải nằm trong hàm.
{
    for (int i=0; environ[i] != NULL; i++) { 
            write (1, environ[i], strlen(environ[i]));
            write (1, "\n", 1); // Cái này để xuống dòng.
    }
}