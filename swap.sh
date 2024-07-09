#!/bin/bash

# Kiểm tra nếu người dùng là root
if [ "$EUID" -ne 0 ]; then
  echo "Vui lòng chạy script này với quyền root."
  exit 1
fi

# Yêu cầu người dùng nhập dung lượng swap (đơn vị MB)
read -p "Nhập dung lượng swap mong muốn (đơn vị MB, ví dụ: 2048 cho 2GB): " SWAP_SIZE_MB

# Đường dẫn tới swap file
SWAP_FILE="/swapfile"

# Tạo swap file với kích thước đã định
fallocate -l "${SWAP_SIZE_MB}M" $SWAP_FILE

# Đặt quyền truy cập cho swap file
chmod 600 $SWAP_FILE

# Thiết lập swap area
mkswap $SWAP_FILE

# Kích hoạt swap file
swapon $SWAP_FILE

# Thêm swap file vào /etc/fstab để tự động kích hoạt sau mỗi lần khởi động lại
echo "$SWAP_FILE none swap sw 0 0" | tee -a /etc/fstab

# Kiểm tra lại tình trạng swap
swapon --show

echo "Swap file đã được tạo và kích hoạt thành công."

exit 0
