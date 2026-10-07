#include <stdio.h>
#include <sys/types.h>
#include <pwd.h> // Để dùng struct passwd
#include <grp.h> // Để dùng struct group và getgrgid()
#include <sys/stat.h> // Để dùng struct stat và hàm stat()

int main (int argc, char *argv[]) {
    if (argc<2) {
        printf ("Sai dinh dang.\n");
        printf ("Cach nhap : my_stat \"ten_file\" ");
        return 1;
    }
    struct stat hop_dung;
    int ref = stat(argv[1], &hop_dung);
    if (ref == -1) {
        perror("stat failed"); // Làm như này để biết lỗi gì.
        // printf ("Khong the lay thong tin file %s\n", argv[1]); // Làm nnay cũng dc nma k dc max điểm.
        return 1;
    }
    printf ("Thong tin file %s:\n", argv[1]);
    printf ("-So hieu I-node : %ld.\n", hop_dung.st_ino);
    if (S_ISREG(hop_dung.st_mode)) {
        printf ("-Loai file : Regular file.\n");
    }
    else if (S_ISDIR(hop_dung.st_mode)) {
        printf ("-Loai file : Directory.\n");
    }
    else if (S_ISLINK(hop_dung.st_mode)) {
        printf ("-Loai file : Link.\n");
    }
    else {
        printf ("-Loai file : Khong xac dinh.\n");
    }
    printf ("-Quyen han : \n");
    int quyen = 0;
    if (hop_dung.st_mode & S_IRUSR) {
        printf ("+User có quyen doc file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IWUSR) {
        printf ("+User có quyen ghi file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IXUSR) {
        printf ("+User có quyen chay file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IRGRP) {
        printf ("+Group có quyen doc file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IWGRP) {
        printf ("+Group có quyen ghi file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IXGRP) {
        printf ("+Group có quyen chay file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IROTH) {
        printf ("+Other có quyen doc file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IWOTH) {
        printf ("+Other có quyen ghi file.\n");
        quyen = 1;
    }
    if (hop_dung.st_mode & S_IXOTH) {
        printf ("+Other có quyen chay file.\n");
        quyen = 1;
    }
    if (quyen == 0) {
        printf ("+Khong co bat cu quyen nao.\n");
    }
    printf ("-So luong lien ket : %ld.\n", hop_dung.st_nlink);
    printf ("-Dung luong : %ld.\n", hop_dung.st_size);
    // Bây giờ trả về tên người sở hữu và nhóm sở hữu, phần khó nhất.
    uid_t uid = hop_dung.st_uid;
    gid_t gid = hop_dung.st_gid;
    struct group *tro_nhom = getgrgid (gid);
    struct passwd *tro_ca_nhan = getpwuid (uid);
    // Bây giờ, ta cần đề phòng trường hợp mà file còn, nhưng người tạo file thì đã bị xóa.
    if (tro_ca_nhan != NULL) {
    printf("-Ten nguoi so huu : %s\n", tro_ca_nhan->pw_name);
    } else {
    printf("-Ten nguoi so huu : %d (UID)\n", uid);
    }
    if (tro_nhom != NULL) {
    printf("-Ten nhom so huu : %s\n", tro_nhom->gr_name);
    } else {
    printf("-Ten nhom so huu : %d (GID)\n", gid);
    }
    return 0;
}