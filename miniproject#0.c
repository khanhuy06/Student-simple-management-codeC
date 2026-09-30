//KHUNG MASTER PROMPT (Copy dùng mãi mãi):

//*"Tôi đang xây dựng hệ thống Backend bằng FastAPI và PostgreSQL (SQLAlchemy ORM). Dự án của tôi là: [Điền tên dự án: ví dụ Web Bán Quần Áo / Đặt Phòng Khách Sạn].

//Yêu cầu kiến trúc chuẩn kỹ sư:

//1.Cấu trúc thư mục: Chia chuẩn 4 file riêng biệt (database.py, models.py, schemas.py, crud.py, main.py).
//2. Thiết kế Database (models.py):
//Hỗ trợ [Liệt kê các bảng, ví dụ: User, Product cha, ProductVariant con, Order, OrderItem].
//Áp dụng kỹ thuật Soft Delete (is_deleted: bool = False) cho mọi bảng dữ liệu quan trọng.
//Lưu dấu vết thời gian (created_at, updated_at).
//Sử dụng DECIMAL(10, 2) cho mọi trường tiền tệ và có ràng buộc CHECK (price >= 0).
//Đánh index=True cho các trường tìm kiếm thường xuyên như: email, SKU, mã đơn.
//3. Xử lý CRUD (crud.py):
//Sử dụng with_for_update() khi trừ tồn kho để chống Race Condition.
//Có đầy đủ khối try ... except: db.rollback() để đảm bảo tính an toàn giao dịch.
//4. API Endpoints (main.py):
//Sử dụng Depends(get_db) để quản lý session an toàn.
//Tạo đầy đủ các endpoint CRUD chuẩn RESTful."*



// MASTER PROMPT: THIẾT KẾ HỆ THỐNG XÁC THỰC & PHÂN QUYỀN CHUẨN DOANH NGHIỆP

// Bạn là một Chuyên gia Kiến trúc Hệ thống và Kỹ sư An toàn Thông tin Cấp cao (Senior Backend & Application Security Engineer). 
//Hãy xây dựng module Xác thực (Authentication) và Phân quyền (Authorization - RBAC) cho ứng dụng FastAPI của tôi, tuân thủ nghiêm ngặt các tiêu chuẩn bảo mật sau:

//1. KIẾN TRÚC MẬT MÃ & HASHING:
//- Dùng `passlib` với thuật toán `Bcrypt` (rounds/cost factor tối thiểu 12), bắt buộc tự động sinh Salt ngẫu nhiên. Tuyệt đối không dùng MD5, SHA-1 hoặc SHA-256 thô.
//- Hàm kiểm tra mật khẩu phải dùng cơ chế so sánh chống tấn công đo thời gian (Timing-Attack resistant).

//2. XÁC THỰC BẰNG JWT (OAUTH2 PASSWORD BEARER FLOW):
//- Triển khai chuẩn `OAuth2PasswordBearer` để tích hợp mượt mà với Swagger UI (`/docs`).
//- Tách biệt rõ 2 loại Token:
//  + `Access Token`: Thuật toán HS256, ký bằng `SECRET_KEY` (lấy từ biến môi trường `.env`), thời gian sống ngắn (30 phút). Payload chỉ chứa `sub` (user_id/username), `role` và `exp`. Tuyệt đối không lưu dữ liệu nhạy cảm vào Payload.
//  + `Refresh Token`: Thời gian sống 7 ngày, lưu mã băm an toàn trong Database để có thể thu hồi (Revoke).

//3. CHỐT GÁC BẢO VỆ (DEPENDENCY INJECTION):
//- Viết Dependency `get_current_user`: Tự động trích xuất Bearer token, giải mã chữ ký, xử lý lỗi `401 Unauthorized` nếu token giả, hết hạn hoặc không hợp lệ.
//- Viết Dependency phân quyền RBAC `require_roles(["admin", "staff"])`: Kiểm tra quyền hạn của `current_user`, nếu không đủ quyền phải ném lỗi `403 Forbidden`.

//4. PHÒNG VỆ CHỦ ĐỘNG TRƯỚC CÁC ĐẠI LỖ HỔNG (OWASP TOP 10):
//- Chống IDOR: Mọi câu truy vấn dữ liệu nhạy cảm phải luôn ràng buộc điều kiện quyền sở hữu của `current_user`.
//- Chống Mass Assignment: Dùng các Pydantic Schemas riêng biệt (`UserCreate`, `UserUpdate`, `UserResponse`) với cấu hình cấm trường lạ.
//- Chống SQLi: 100% dùng SQLAlchemy ORM truy vấn tham số hóa.
//- Chống Brute-force: Cài đặt middleware Rate Limiting (tối đa 5 lần đăng nhập sai/phút).
//- Chống CORS: Cấu hình `CORSMiddleware` với danh sách whitelist cụ thể, không dùng `allow_origins=["*"]`.

//Hãy viết mã nguồn rõ ràng, tách file module hóa chuẩn (`auth.py`, `models.py`, `schemas.py`, `main.py`), kèm theo chú thích giải thích lý do bảo mật cho từng quyết định kỹ thuật!