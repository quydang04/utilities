create database QLGH
use QLGH

create table Product (
    ProductID NVARCHAR(20) not null PRIMARY KEY,
    ProductName NVARCHAR(100) not null,
    Unit NVARCHAR(20) not null,
    BuyPrice DECIMAL(18, 2) null,
    SellPrice DECIMAL(18, 2) null
);
create table Invoice (
    InvoiceNo NVARCHAR(20) not null PRIMARY KEY,
    OrderDate DATETIME not null,
    DeliveryDate DATETIME not null,
    Note NVARCHAR(255) null
);
CREATE TABLE [Order] (
    InvoiceNo NVARCHAR(20) not null,
    [No] INT not null,
    ProductID NVARCHAR(20) not null,
    ProductName NVARCHAR(100) null,
    Unit NVARCHAR(20) null,
    Price DECIMAL(18, 2) not null,
    Quantity INT not null,
    PRIMARY KEY (InvoiceNo, [No]),
    CONSTRAINT FK_Order_Invoice FOREIGN KEY (InvoiceNo) REFERENCES Invoice(InvoiceNo),
    CONSTRAINT FK_Order_Product FOREIGN KEY (ProductID) REFERENCES Product(ProductID)
);

insert into Product (ProductID, ProductName, Unit, BuyPrice, SellPrice) values
('P001', N'Sản phẩm A', N'Cái', 100000, 120000),
('P002', N'Sản phẩm B', N'Hộp', 200000, 250000),
('P003', N'Sản phẩm C', N'Chiếc', 50000, 75000);

insert into Invoice (InvoiceNo, OrderDate, DeliveryDate, Note) values
('I001', '2024-12-01', '2024-12-03', N'Giao hàng trước 10h sáng'),
('I002', '2024-12-02', '2024-12-04', N'Giao hàng trong ngày');

insert into [Order] (InvoiceNo, [No], ProductID, ProductName, Unit, Price, Quantity) values
('I001', 1, 'P001', N'Sản phẩm A', N'Cái', 120000, 2),
('I001', 2, 'P003', N'Sản phẩm C', N'Chiếc', 75000, 5),
('I002', 1, 'P002', N'Sản phẩm B', N'Hộp', 250000, 3);

select * from Product
select * from Invoice
select * from [Order]