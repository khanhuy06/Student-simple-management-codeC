#include <stdio.h> // Chứa hàm printf()
#include <pwd.h> // Chứa hàm getpwnam() và struct passwd

int main (int argc, char *argv[]) {
    if (argc < 2) {
        printf ("Lỗi, vui lòng nhập theo định dạng \"./bai10 ten_nguoi_dung\"\n"); // Lưu ý k dc có .c nhé.
        return 1;
    }
    struct passwd *p = getpwnam(argv[1]);
    if (p==NULL) {
        printf ("Tên không tồn tại.\n");
        return 1;
    }
    else {
        printf ("Tên người dùng : %s\n", p->pw_name);
        printf("UID: %d\n", p->pw_uid);
        printf("GID: %d\n", p->pw_gid);
        printf ("Home : %s\n", p->pw_dir);
        printf ("Shell : %s\n", p->pw_shell);
    }
    return 0;
}