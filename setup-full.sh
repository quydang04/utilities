#!/bin/bash
# Script to upgrade from Debian 10 (Buster) to Debian 11 (Bullseye)

# Update current packages
sudo apt update
sudo apt full-upgrade -y

# Update sources.list to Bullseye/Bookworm
sudo sed -i 's/bullseye/bookworm/g' /etc/apt/sources.list

# Update packages to bookworm
sudo apt update
sudo apt full-upgrade -y

# Perform dist-upgrade
sudo apt dist-upgrade -y

#Setup swap

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

# Install AdguardHome
curl -s -S -L https://raw.githubusercontent.com/AdguardTeam/AdGuardHome/master/scripts/install.sh | sh -s -- -v

#Setup DNS
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

#Setup TinyCP
sudo apt install apt-transport-https dirmngr gnupg ca-certificates -y
sudo apt-key adv --fetch-keys http://repos.tinycp.com/debian/conf/gpg.key
sudo echo "deb http://repos.tinycp.com/debian all main" | sudo tee /etc/apt/sources.list.d/tinycp.list
sudo apt-get update -y
TINYCP_USER="quydang" TINYCP_PASS="Quydang@1122" TINYCP_PORT="2222" sudo apt-get install tinycp -y
# Reboot system
sudo reboot
