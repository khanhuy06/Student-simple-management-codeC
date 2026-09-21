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