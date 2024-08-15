#!/bin/bash
echo "*******************************************"
echo "**                                       **"
echo "**               SkipAdsTV               **"
echo "**  Tiện ích bỏ qua quảng cáo YoutubeTV  **"
echo "**                                       **"
echo "*******************************************"
echo "*                 Linor                   *"
echo "*******************************************"
sleep 3

if [ ! -f start.py ]; then
    sudo apt-get update
    sudo apt-get --assume-yes upgrade
    sudo apt-get install unzip python3 python3-pip -y
    wget -O skip.zip "https://drive.google.com/uc?id=18G3UizQTfJgVaTsecABF4gV10tVr7tlt&export=download&confirm=yes"
    unzip skip.zip
    rm skip.zip
    mkdir -p ~/.local/share/SkipAdsTV
    python3 -m pip install -r re.txt
fi

if [ ! -f re ]; then
    python3 start.py -s
fi

while [ -f re ]; do
    python3 start.py
    break
done
