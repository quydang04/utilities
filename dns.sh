#!/bin/bash

# Tạo thư mục /etc/systemd/resolved.conf.d nếu chưa tồn tại
sudo mkdir -p /etc/systemd/resolved.conf.d

# Tạo file adguardhome.conf với nội dung cấu hình
sudo bash -c 'cat <<EOF > /etc/systemd/resolved.conf.d/adguardhome.conf
[Resolve]
DNS=127.0.0.1
DNSStubListener=no
EOF'

# Sao lưu file resolv.conf hiện tại
sudo mv /etc/resolv.conf /etc/resolv.conf.backup

# Tạo liên kết tượng trưng (symlink) đến file resolv.conf mới
sudo ln -s /run/systemd/resolve/resolv.conf /etc/resolv.conf

# Khởi động lại dịch vụ systemd-resolved
sudo systemctl reload-or-restart systemd-resolved

echo "Đã thực hiện các thay đổi thành công."
