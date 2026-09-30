#include <stdio.h>
#include <stdlib.h>

int main (){
    typedef struct {
        char ten[50];
        int mssv;
        float diem;
    } S;

    //Ta phải đọc file để đếm số lượng sinh viên trước, nếu chưa có file thì slsv = 0
    FILE *test = fopen ("quanlysinhvieninsa.txt", "r"); //thử đọc file trước xem nó đã tồn tại hay chưa
    int soluongsinhvien = 0; //Phải khai báo ở ngoài vì nếu đặt trong if nó sẽ biến mất khi hết if
    if (test == NULL) { //break không dùng trong if, chỉ dùng cho vòng lặp
        soluongsinhvien = 0; //Không có ý nghĩa gì nma cứ bỏ vậy
    }
    else { //Khi file đã có, đọc để biết soluongsinhvienhientai và gán nó bằng soluongsinhvien để chạy chương trình
        int temp = 0;
        char tentam[50]; //Khởi tạo để biết kiểu dữ liệu đọc => lúc khai báo là đã xin đất rồi, k cần malloc => fscanf chạy xong 1 lần là 1 data mới đè vào địa chỉ này
        int mssvtam; //Khởi tạo để biết kiểu dữ liệu đọc => lúc khai báo là đã xin đất rồi, k cần malloc => fscanf chạy xong 1 lần là 1 data mới đè vào địa chỉ này
        float diemtam; //Khởi tạo để biết kiểu dữ liệu đọc => lúc khai báo là đã xin đất rồi, k cần malloc => fscanf chạy xong 1 lần là 1 data mới đè vào địa chỉ này
        while (fscanf(test,"%s, %d, %f", tentam, &mssvtam, &diemtam)==3){ //Ở đây, nó chỉ đọc các kiểu dữ liệu cần đọc mà ta đã khai báo, ta k cần quan tâm đến giá trị
        temp ++;
    } 

    soluongsinhvien = temp; //Sau khi thoát else, soluongsinhvien sẽ được cập nhật, còn temp sẽ biến mất
    fclose (test); //Nếu file tồn tại, và đã đọc xong file, ta phải đóng file ở trong else
    }

    int soluongsinhvienhientai = soluongsinhvien; //Gán soluongsinhvienhientai, dùng cho ý n==4, phải gán ở ngoài else để k biến mất

    S *sinhvien = malloc(soluongsinhvien * sizeof(S)); //Xin RAM cho từng đó sinh viên trong file
                                                       //malloc chính là hàm xin mảng để lưu trữ rồi
                                                       //Bây giờ RAM đã bị cắt 1 đoạn, giao cho con trỏ sinhvien giam giữ

    //Bây giờ ta cần nạp đống sinh viên vừa đọc vào RAM (sau khi đã xin RAM bằng malloc)
    if (soluongsinhvien != 0) {
        FILE *f = fopen ("quanlysinhvieninsa.txt","r"); //Mở file phải mở ở ngoài vòng lặp for
        for (int i = 0; i < soluongsinhvien; i++) { //Phải khai báo i ở trong for
            fscanf(f,"%s, %d, %f", sinhvien[i].ten, &sinhvien[i].mssv, &sinhvien[i].diem); //sinhvien[i] lúc này nó không còn là 1 con trỏ nữa nên phải dùng "."
            // fscanf là đọc dữ liệu của "f" ở trong ổ cứng, ghi đè "nó" vào "các địa chỉ mình đã gán" ở trên RAM
        }
        fclose (f);
    }

    //Lưu ý, sinhvien là 1 con trỏ, nhưng sinhvien[i] thì lại là 1 Ngôi nhà thật sự số thứ tự i
    while (1) {
        printf ("---Quản lý danh sách sinh viên INSA---\n");
        printf ("1. Thêm sinh viên\n");
        printf ("2. Xem danh sách\n");
        printf ("3. Tìm sinh viên\n");
        printf ("4. Lưu dữ liệu và thoát\n");
        printf ("Vui lòng chọn chức năng : 1-4\n");

        int n;
        scanf ("%d", &n); //Phải có dấu "&"

        //Đây mới chỉ là trường hợp cơ bản, khi dữ liệu nhập vào đủ cả 3 yếu tố
        if (n==1) {
            printf ("Vui lòng điền Mã số sinh viên\n");
            int a;
            scanf ("%d", &a);
            soluongsinhvien++;
            
            S *temp = realloc(sinhvien, soluongsinhvien * sizeof(S));
            if (temp != NULL) {
                sinhvien = temp;
            }
            else {
                printf ("Không đủ bộ nhớ để thêm sinh viên\n");
                return 1;    //return 1 phải để sau lệnh in chứ không phải trước lệnh in
            }
            sinhvien[soluongsinhvien-1].mssv = a;

            printf ("Vui lòng điền tên sinh viên\n");
            int aa;
            while ((aa=getchar())!= '\n' && (aa!=EOF))
            fgets (sinhvien[soluongsinhvien-1].ten, sizeof(sinhvien[soluongsinhvien-1].ten), stdin); //fgets là lấy chuỗi, nên lưu vào file sẽ là %s
            //fgets sẽ nuốt luôn \n
            sinhvien[soluongsinhvien-1].ten[strcspn(sinhvien[soluongsinhvien-1].ten, "\n")] = '\0'; // vì fgets lấy luôn \n, nên ta phải dùng lệnh này để bỏ \n, đổi nó thành \0.
            // scanf thì thấy dấu cách [ ] là dừng lại.

            printf ("Vui lòng điền điểm sinh viên\n");
            scanf ("%f",&sinhvien[soluongsinhvien-1].diem);
        }
        else if (n==2) {
            printf ("Danh sách sinh viên:\n");
            for (int i=0; i<soluongsinhvien; i++) {
                printf ("Mã số sinh viên: %d\n", sinhvien[i].mssv);
                printf ("Tên sinh viên: %s\n", sinhvien[i].ten);
                printf ("Điểm sinh viên: %f\n", sinhvien[i].diem);
            }
        }
        else if (n==3) {
            printf ("Vui lòng điền Mã số sinh viên\n");
            int c;
            scanf ("%d",&c);
            int timthay = 0; //dành cho trường hợp mssv không tồn tại
            for (int i=0; i<soluongsinhvien; i++) {
                if (sinhvien[i].mssv == c) {
                    timthay = 1;
                    printf ("Mã số sinh viên: %d\n", sinhvien[i].mssv);
                    printf ("Tên sinh viên: %s\n", sinhvien[i].ten);
                    printf ("Điểm sinh viên: %f\n", sinhvien[i].diem);
                    break; //break để thoát vòng lặp for
                }
            }
            if (timthay == 0) {
                printf ("Không tìm thấy sinh viên\n");
            }
        }
        else if (n==4) {
            
            FILE *test = fopen ("quanlysinhvieninsa.txt", "r"); //thử đọc file trước xem nó đã tồn tại hay chưa            
            
            if (test != NULL) { //trường hợp đã có file và muốn ghi nối
                fclose (test); //đóng file test
            FILE *f = fopen ("quanlysinhvieninsa.txt", "a"); //mở file để ghi nối
            for (int i = soluongsinhvienhientai; i < soluongsinhvien; i++) { //phải có soluongsinhvienhientai để biết ghi nối từ đâu 
                fprintf (f, "%d %s %f\n", sinhvien[i].mssv, sinhvien[i].ten, sinhvien[i].diem);
                //Ghi vào file "f" các "kiểu dữ liệu" đã được xác định, dùng data từ các biến được liệt kê, k cần "&"
            }
            fclose (f);
            }
            
            else {
            FILE *f = fopen ("quanlysinhvieninsa.txt", "w"); //trường hợp tạo lần đầu
            if (f == NULL) {
                printf ("Không thể lưu file\n");
            }
            for (int i = 0; i < soluongsinhvien; i++) {
                fprintf (f, "%d %s %f\n", sinhvien[i].mssv, sinhvien[i].ten, sinhvien[i].diem); //Đọc từ RAM ghi vào file
            }
            fclose (f);
            }

            break; //thoát khỏi while
        }
        else {
            printf ("Vui lòng chọn chức năng từ 1 đến 4\n");
        }
    }
    return 0;
}