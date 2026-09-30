#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    int soluong = 0;
    int succhua = 2;
    int n;

    typedef struct {
        int ID;
        char tensinhvien[50];
    }Sinhvien; // => phải có dấu ; ở struct

    Sinhvien *dssv = malloc(succhua*sizeof(Sinhvien)); // => phải xin đất cố định ở ngoài while

while (1) {
    printf ("---Quản lý sinh viên INSA---\n");
    printf ("1. Thêm sinh viên\n");
    printf ("2. Xem danh sách\n");
    printf ("3. Tìm sinh viên\n");
    printf ("4. Thoát\n");
    printf ("Vui lòng chọn chức năng : 1-4\n");

    scanf ("%d", &n);

    if (n==1) {
        if (soluong==succhua) {
            succhua++;
            Sinhvien *t = realloc(dssv,succhua*sizeof(Sinhvien));
            if (t!=NULL){
                dssv=t;
            }
            else {
                printf ("Dung lượng bộ nhớ đầy.\n");
                return 1;
            }

        }
        printf ("Vui lòng điền ID sinh viên : \n");
        int a; 
        scanf ("%d", &a);
        getchar(); // => cần thiết để bỏ dấu \n
        printf ("Vui lòng điền tên sinh viên : \n");
        char s[50];
        fgets (s,sizeof(s),stdin);
        s[strcspn(s,"\n")]='\0';
        
        dssv[soluong].ID=a;
        strcpy(dssv[soluong].tensinhvien,s);
        soluong++;
        printf ("Sinh viên vừa thêm là %s, số ID : %d\n",s,a);
    }

    else if (n==2){
        if (soluong==0) {
            printf ("Danh sách sinh viên trống.\n");
        }
        else {
                printf ("Danh sách sinh viên :\n");
                for (int i=0; i<soluong; i++) {
                    printf ("Mã số ID : %d, tên sinh viên : %s\n", dssv[i].ID, dssv[i].tensinhvien);
                }
             }
    }

    else if (n==3) {

        int idtimkiem;
        int i; 

        printf ("Nhập ID sinh viên cần tìm kiếm :\n");
        scanf ("%d", &idtimkiem);
        
        int timthay = 0;  
        
        for (i=0; i<soluong; i++) {
                if (idtimkiem == dssv[i].ID); {
                printf ("ID sinh viên : %d, Họ và tên : %s.", dssv[i].ID, dssv[i].tensinhvien);
                timthay = 1;
                }
                }
           
        if (timthay==0) {
            printf ("Mã ID chưa tồn tại.\n");
        }       
    }

    else if (n==4) {
        printf ("Đang thoát chương trình...\n");
        return 0;
    }
    else {
        printf ("Lỗi, xin vui lòng chọn giá trị từ 1 đến 4.\n");
    }
}
    return 0;
}