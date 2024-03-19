USE master

CREATE DATABASE quanlysinhvienct6

USE quanlysinhvienct6

CREATE TABLE lop (

   MaLop varchar(8) not null,

   TenLop nvarchar(30),

   SiSo tinyint,

)

ALTER TABLE lop

ADD CONSTRAINT PK_MaLop primary key(MaLop)

ALTER TABLE lop

ADD CONSTRAINT CHK_LOP_SISO_CHECK CHECK (SiSo > 0);

INSERT INTO lop (MaLop, TenLop, SiSo) VALUES

  ('18DTH01', N'CNTT Khoá 18, Lớp 1', 50),

  ('18DTH02', N'CNTT Khoá 18, Lớp 2', 45),

  ('19DTH01', N'CNTT Khoá 19, Lớp 1', 55),

  ('19DTH02', N'CNTT Khoá 19, Lớp 2', 50),

  ('19DTH03', N'CNTT Khoá 19, Lớp 3', 40);

-- Bang mon hoc

CREATE TABLE monhoc (

  MAMH varchar(6) not null,

  TenMH nvarchar(50),

  TCLT tinyint,

  TCTH tinyint,

)

ALTER TABLE monhoc

ADD CONSTRAINT PK_MaMH primary key(MaMH)

INSERT INTO monhoc (MAMH, TenMH, TCLT, TCTH) VALUES

  ('COS201', N'Kỹ thuật lập trình', 2, 1),

  ('COS202', N'Lý thuyết đồ thị', 2, 1),

  ('COS203', N'CSDL và quản trị CSDL', 3, 0),

  ('COS204', N'Phân tích thiết kế hệ thống', 3, 0),

  ('COS205', N'CSDL phân tán', 3, 0);

-- Bang sinh vien

CREATE TABLE sinhvien (

  MSSV varchar(6) not null,

  MaLop varchar(8),

  HoTen nvarchar(50),

  NTNS date,

  Phai bit,

)

ALTER TABLE sinhvien

ADD CONSTRAINT PK_SinhVien primary key(MSSV)

ALTER TABLE sinhvien

ADD CONSTRAINT FK_MaLopSV foreign key(MaLop) references lop(MaLop)

ALTER TABLE sinhvien 

ADD CONSTRAINT CHK_SINH_VIEN_PHAI CHECK (PHAI = 0 OR PHAI = 1), 

CONSTRAINT DEF_SINHVIEN_PHAI DEFAULT 1 FOR PHAI

INSERT INTO sinhvien(MSSV, HoTen, NTNS, Phai, MaLop) values ('170001', N'Lê Hoài An', '1999/10/12', 1, '18DTH01'),

('180002', N'Nguyễn Thị Hoà Bình', '2000/11/20', 1, '18DTH01'),

('180003', N'Phạm Tường Châu', '2000/06/07', 0, '18DTH02'),

('180004', N'Trần Công Danh', '2000/01/31', 0, '19DTH01')    



-- Bang diem sinh vien

CREATE TABLE diemsv (

  MSSV varchar(6) not null,

  MAMH varchar(6) not null,

  Diem decimal(3,1),

)

ALTER TABLE diemsv

ADD CONSTRAINT PK_DiemSV primary key(MSSV, MAMH)

ALTER TABLE diemsv 

ADD CONSTRAINT FK_DiemSV_MaMH FOREIGN KEY (MAMH) REFERENCES monhoc(MAMH)

ALTER TABLE diemsv

ADD CONSTRAINT FK_DiemSV_MSSV foreign key (MSSV) REFERENCES sinhvien(MSSV)

ALTER TABLE diemsv 

ADD CONSTRAINT CHK_DIEMSV_DIEM CHECK (Diem>=0 AND Diem<=10),

CONSTRAINT DEF_DIEMSV_DIEM DEFAULT NULL FOR Diem

INSERT INTO diemsv(MSSV, MAMH, Diem) VALUES

('170001', 'COS201', 10),

('170001', 'COS202', 10),

('170001', 'COS203', 10),

('170001', 'COS204', 10),

('170001', 'COS205', 10),

('180002', 'COS201', 3.5),

('180002', 'COS202', 7),

('180003', 'COS201', 8.5),

('180003', 'COS202', 2),

('180003', 'COS203', 6.5),

('180004', 'COS201', 8),

('180004', 'COS204', NULL);

--- Cau 1: Them mot dong moi vao bang

INSERT INTO sinhvien(MSSV, HoTen, NTNS, Phai, MaLop) values ('190001', N'Đào Thị Tuyết Hoa', '2001/03/08', 0, '19DTH02')

select * from sinhvien

--- Cau 2: Doi ten mon hoc Ly Thuyet Do thi sang Toan Roi Rac

UPDATE monhoc

SET TenMH = N'Toán rời rạc'

WHERE TenMH = N'Lý thuyết đồ thị';

select * from monhoc

--- Cau 3: Hien thi cac ten mon hoc khong co thuc hanh

SELECT TenMH

FROM monhoc

WHERE TCLT > 0 AND TCTH = 0

--- Cau 4: Hien thi cac ten vua co ly thuyet va vua co thuc hanh

SELECT TenMH

FROM monhoc

WHERE TCLT > 0 AND TCTH = 1

--- Cau 5: In ra ten cac mon hoc co ky tu dau la C

SELECT TenMH

FROM monhoc

WHERE TenMH like 'C%'

--- Cau 6: Liet ke thong tin nhung sinh vien chua chi Thị

SELECT HoTen

FROM sinhvien

WHERE HoTen like N'%Thị%'

--- Cau 7: In ra 2 lop co si so dong nhat

SELECT top 2 with ties MaLop, TenLop, SiSo

FROM lop

ORDER BY SiSo DESC

--- Cau 8: In ra danh sach theo tung lop

SELECT MSSV, HoTen, NTNS, CASE WHEN Phai = 1 THEN N'Nam' ELSE N'Nữ' END AS Phai

FROM sinhvien

ORDER BY MaLop

--- Cau 9: Cho biet nhung sinh vien co tuoi >= 20

SELECT HoTen, NTNS, DATEDIFF(YEAR, NTNS, GETDATE()) AS Tuoi

FROM sinhvien

WHERE DATEDIFF(YEAR, NTNS, GETDATE()) >= 20;

--- Cau 10: Liet ke ten cac mon hoc SV da du thi nhung chua co diem

SELECT TenMH

FROM monhoc

WHERE MAMH = (SELECT MAMH FROM diemsv WHERE Diem IS NULL)

--- Cau 11: Liet ke ket qua hoc tap sinh vien co ma so 170001. Hien thi: MSSV, HoTen, TenMH, Diem

SELECT sv.MSSV, sv.HoTen, mh.TenMH, ds.Diem

FROM sinhvien sv, diemsv ds, monhoc mh

WHERE sv.MSSV = ds.MSSV AND ds.MAMH = mh.MAMH AND sv.MSSV = '170001';

--- Cau 12: Liet ke ten sinh vien va ma mon hoc ma sinh vien do dang ki tren 7 diem

SELECT sv.HoTen, ds.MAMH

FROM sinhvien sv, diemsv ds

WHERE sv.MSSV = ds.MSSV AND ds.Diem > 7

--- Cau 13: Liet ke ten mon hoc cung voi so luong sinh vien da hoc va co diem

SELECT mh.TenMH, count(sv.MSSV) as N'Số lượng sinh viên'

FROM monhoc mh, diemsv sv

WHERE mh.MAMH = sv.MAMH and sv.Diem IS NOT NULL

GROUP BY mh.TenMH

--- Cau 14: Liet ke ten SV va diem trung binh do

SELECT sv.HoTen, AVG(ds.Diem) as N'Điểm trung bình của sinh viên'

FROM sinhvien sv, diemsv ds 

WHERE sv.MSSV = ds.MSSV

GROUP BY sv.HoTen

--- Cau 15: Liet ke sinh vien dat diem cao nhat mon Ky Thuat Lap Trinh

SELECT top 1 sv.HoTen

FROM sinhvien sv, diemsv ds, monhoc mh

WHERE sv.MSSV = ds.MSSV AND ds.MAMH = mh.MAMH AND mh.TenMH = N'Kỹ Thuật Lập Trình'

GROUP BY sv.HoTen

--- Cau 16: Liet ke ten SV co diem trung binh cao nhat 

SELECT top 1 with ties sv.HoTen, AVG(ds.Diem) as N'Điểm trung bình cao nhất'

FROM sinhvien sv, diemsv ds

WHERE sv.MSSV = ds.MSSV

GROUP BY sv.HoTen

ORDER BY AVG(ds.Diem) DESC

--- Cau 17: Liet ke ten sinh vien chua hoc mon Toan Roi Rac

SELECT HoTen

FROM sinhvien WHERE MSSV not in ( 

SELECT sv.MSSV

FROM sinhvien sv, monhoc mh, diemsv ds

WHERE sv.MSSV = ds.MSSV AND mh.MAMH = ds.MAMH AND mh.TenMH = N'Toán Rời Rạc'

)

--- Cau 18: Cho biet sinh vien co nam sinh cung voi ten 'Danh'

--- Skip

--- Cau 19: Cho biet tong so sinh vien va tong so sinh vien nu

SELECT COUNT(*) as N'Tổng sinh viên', SUM(CASE WHEN Phai = 0 THEN 1 ELSE 0 END) as N'Tổng sinh viên nữ'

FROM sinhvien;
