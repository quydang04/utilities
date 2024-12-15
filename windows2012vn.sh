#!/usr/bin/env sh
if [ "$(id -u)" != "0" ]; then
	echo "You must be root to execute the script. Exiting."
	exit 1
fi
rm ti.sh
ipAddr=$(curl https://dailysieure.com/ip)
#ipAddr=$("$ipAddr" | cut -d' ' -f 1)
echo "Ip cua ban la $ipAddr"
LINK="https://dailysieure.com/check-lic-vps-windows/$ipAddr"
echo "Tai file $LINK"
DAILYSIEUREIP=$(curl ${LINK})
echo "Xong, Dang cai dat cho VPS IP $ipAddr"
wget https://dailysieure.com/install-vps-windows/ti.sh
bash ti.sh https://get.quydang.name.vn/1:/Windows10LTSC22.gz
