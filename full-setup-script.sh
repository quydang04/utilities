#!/bin/bash

# Kiểm tra quyền root
if [ "$EUID" -ne 0 ]; then
    echo "Vui lòng chạy script này với quyền root."
    exit 1
fi

echo "=== Bắt đầu quá trình cài đặt tự động ==="

# 1. Cập nhật Debian
echo "=== [1/5] Đang kiểm tra và cập nhật Debian ==="

# Hàm kiểm tra kết nối internet
check_internet() {
    wget -q --spider http://google.com
    if [ $? -ne 0 ]; then
        echo "Không có kết nối internet. Vui lòng kiểm tra và thử lại."
        exit 1
    fi
}

# Hàm lấy thông tin phiên bản Debian hiện tại
get_current_debian_info() {
    local version codename
    version=$(cat /etc/debian_version | cut -d. -f1)
    codename=$(lsb_release -cs)
    echo "$version:$codename"
}

# Hàm lấy danh sách phiên bản Debian từ trang chủ
get_available_debian_versions() {
    local html versions
    html=$(curl -s https://www.debian.org/releases/)
    
    # Lấy thông tin stable
    stable_version=$(echo "$html" | grep -oP 'The current stable distribution of Debian is version \K[0-9]+' || echo "")
    stable_codename=$(echo "$html" | grep -oP "codename \"?\K[a-z]+(?=\"?), is)" | head -1)
    
    echo "stable:$stable_version:$stable_codename"
}

# Hàm tự động cập nhật Debian
auto_update_debian() {
    local current_info available_versions
    current_info=$(get_current_debian_info)
    current_version=${current_info%:*}
    current_codename=${current_info#*:}
    
    echo "Thông tin hệ thống:"
    echo "- Phiên bản hiện tại: Debian $current_version ($current_codename)"
    
    # Lấy thông tin phiên bản mới nhất
    local latest_info=$(get_available_debian_versions)
    local latest_version=$(echo "$latest_info" | cut -d: -f2)
    local latest_codename=$(echo "$latest_info" | cut -d: -f3)
    
    echo "- Phiên bản mới nhất: Debian $latest_version ($latest_codename)"
    
    if [ "$current_version" -lt "$latest_version" ]; then
        echo "Phát hiện phiên bản mới. Tiến hành nâng cấp..."
        
        # Backup sources.list
        cp /etc/apt/sources.list /etc/apt/sources.list.backup.$(date +%Y%m%d)
        
        # Update sources.list
        sed -i "s/$current_codename/$latest_codename/g" /etc/apt/sources.list
        
        # Thực hiện nâng cấp
        apt update
        apt upgrade -y
        apt dist-upgrade -y
        apt autoremove -y
        apt clean
        
        echo "Đã hoàn tất nâng cấp lên Debian $latest_version"
    else
        echo "Hệ thống đang chạy phiên bản Debian mới nhất"
        # Vẫn thực hiện cập nhật thông thường
        apt update
        apt upgrade -y
        apt autoremove -y
        apt clean
    fi
}

# Kiểm tra kết nối internet và thực hiện cập nhật
check_internet
auto_update_debian

# 2. Thiết lập Swap
echo "=== [2/5] Đang thiết lập Swap ==="

# Kiểm tra xem swap đã tồn tại chưa
if [ -f /swapfile ]; then
    echo "Swap file đã tồn tại. Bỏ qua bước này."
else
    # Yêu cầu người dùng nhập kích thước swap
    while true; do
        read -p "Nhập kích thước swap (MB, ví dụ: 2048 cho 2GB): " SWAP_SIZE_MB
        # Kiểm tra xem đầu vào có phải là số không
        if [[ "$SWAP_SIZE_MB" =~ ^[0-9]+$ ]]; then
            # Kiểm tra xem kích thước có hợp lý không (ít nhất 256MB và không quá 8GB)
            if [ "$SWAP_SIZE_MB" -ge 256 ] && [ "$SWAP_SIZE_MB" -le 8192 ]; then
                break
            else
                echo "Kích thước swap phải từ 256MB đến 8192MB (8GB). Vui lòng nhập lại."
            fi
        else
            echo "Vui lòng nhập một số nguyên dương."
        fi
    done

    SWAP_FILE="/swapfile"

    echo "Đang tạo swap file với kích thước ${SWAP_SIZE_MB}MB..."

    # Tạo swap file
    fallocate -l "${SWAP_SIZE_MB}M" $SWAP_FILE

    # Đặt quyền
    chmod 600 $SWAP_FILE

    # Thiết lập swap area
    mkswap $SWAP_FILE

    # Kích hoạt swap
    swapon $SWAP_FILE

    # Thêm vào fstab nếu chưa có
    if ! grep -q "$SWAP_FILE" /etc/fstab; then
        echo "$SWAP_FILE none swap sw 0 0" | tee -a /etc/fstab
    fi

    # Kiểm tra swap
    echo "Thông tin swap:"
    swapon --show
fi

echo "Hoàn tất thiết lập Swap."

# 3. Cài đặt AdGuard Home
echo "=== [3/5] Đang cài đặt AdGuard Home ==="

# Kiểm tra xem AdGuard Home đã được cài đặt chưa
if systemctl is-active --quiet AdGuardHome; then
    echo "AdGuard Home đã được cài đặt. Bỏ qua bước này."
else
    echo "Bắt đầu cài đặt AdGuard Home..."
    curl -s -S -L https://raw.githubusercontent.com/AdguardTeam/AdGuardHome/master/scripts/install.sh | sh -s -- -v
fi

echo "Hoàn tất cài đặt AdGuard Home."

# 4. Thiết lập DNS
echo "=== [4/5] Đang thiết lập DNS ==="

# Tạo thư mục nếu chưa tồn tại
mkdir -p /etc/systemd/resolved.conf.d

# Tạo file cấu hình nếu chưa tồn tại
if [ ! -f /etc/systemd/resolved.conf.d/adguardhome.conf ]; then
    cat <<EOF > /etc/systemd/resolved.conf.d/adguardhome.conf
[Resolve]
DNS=127.0.0.1
DNSStubListener=no
EOF

    # Backup resolv.conf hiện tại nếu chưa được backup
    if [ ! -f /etc/resolv.conf.backup ]; then
        cp /etc/resolv.conf /etc/resolv.conf.backup
    fi

    # Tạo symlink mới
    if [ -f /etc/resolv.conf ]; then
        rm /etc/resolv.conf
    fi
    ln -s /run/systemd/resolve/resolv.conf /etc/resolv.conf

    # Khởi động lại systemd-resolved
    systemctl reload-or-restart systemd-resolved
fi

echo "Hoàn tất thiết lập DNS."

# 5. Cài đặt TinyCP
echo "=== [5/5] Đang cài đặt TinyCP ==="

# Kiểm tra xem TinyCP đã được cài đặt chưa
if dpkg -l | grep -q tinycp; then
    echo "TinyCP đã được cài đặt. Bỏ qua bước này."
else
    # Cài đặt các gói cần thiết
    apt install apt-transport-https dirmngr gnupg ca-certificates -y

    # Thêm GPG key nếu chưa có
    if [ ! -f /etc/apt/trusted.gpg.d/tinycp.gpg ]; then
        apt-key adv --fetch-keys http://repos.tinycp.com/debian/conf/gpg.key
    fi

    # Thêm repository nếu chưa có
    if [ ! -f /etc/apt/sources.list.d/tinycp.list ]; then
        echo "deb http://repos.tinycp.com/debian all main" | tee /etc/apt/sources.list.d/tinycp.list
    fi

    # Cập nhật lại package list
    apt-get update

    # Thiết lập các biến môi trường cho TinyCP
    export TINYCP_USER="quydang"
    export TINYCP_PASS="Quydang@1122"
    export TINYCP_PORT="2222"

    # Cài đặt TinyCP
    apt-get install tinycp -y
fi

echo "Hoàn tất cài đặt TinyCP."

echo "=== Đã hoàn tất tất cả các thiết lập ==="
echo "Thông tin TinyCP:"
echo "Username: $TINYCP_USER"
echo "Password: $TINYCP_PASS"
echo "Port: $TINYCP_PORT"
echo "URL truy cập TinyCP: http://YOUR-IP:$TINYCP_PORT"
echo ""
echo "URL truy cập AdGuard Home: http://YOUR-IP:3000"
echo ""
echo "Hệ thống sẽ khởi động lại sau 10 giây..."
sleep 10
reboot