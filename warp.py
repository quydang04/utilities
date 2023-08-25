import urllib.request
import json
import datetime
import random
import string
import time
import os
import sys

script_version = '5.0.0'
window_title = f"WARP+ by WinGiaRe.Com (version {script_version})"
os.system('title ' + window_title if os.name == 'nt' else 'PS1="\[\e]0;' +
          window_title + '\a\]"; echo $PS1')
os.system('cls' if os.name == 'nt' else 'clear')
print(
    ' Hỗ trợ Free kích key data WARP+ từ chính key của máy bạn tại https://wingiare.com\n'
)
print(
    "[*] Khắc phục lỗi kích data không nhận 12 triệu data WARP+ trên các thiết bị hỗ trợ tại https://wingiare.com"
)
print("")
print(f"[-] Version: {script_version}")
print("--------")
print("[+] Lưu ý: Chạy tốt nhất trên Chrome, Edge, Safari")
print("[-] Website: https://wingiare.com")
print("[-] Hỗ trợ qua Facebook: https://www.facebook.com/wingiare.com")
print(
    "[+] ID WARP lấy tại app 1.1.1.1: Settings > Advanced > Diagnostics > ID")
print("7090afce-08b0-43a1-9125-a6bb81d679d4")
referrer = input("Nhập WARP ID và nhấn Enter:")


def progressBar():
    animation = [
        "[□□□□□□□□□□]", "[■□□□□□□□□□]", "[■■□□□□□□□□]", "[■■■□□□□□□□]",
        "[■■■■□□□□□□]", "[■■■■■□□□□□]", "[■■■■■■□□□□]", "[■■■■■■■□□□]",
        "[■■■■■■■■□□]", "[■■■■■■■■■□]"
    ]
    progress_anim = 0
    save_anim = animation[progress_anim % len(animation)]
    percent = 0
    while True:
        for i in range(10):
            percent += 1
            sys.stdout.write(f"\r[+] Chờ phản hồi...  " + save_anim +
                             f" {percent}%")
            sys.stdout.flush()
            time.sleep(0.075)
        progress_anim += 1
        save_anim = animation[progress_anim % len(animation)]
        if percent == 100:
            sys.stdout.write("\r[+] Lệnh hoàn thành... [■■■■■■■■■■] 100%")
            break


def genString(stringLength):
    try:
        letters = string.ascii_letters + string.digits
        return ''.join(random.choice(letters) for i in range(stringLength))
    except Exception as error:
        print(error)


def digitString(stringLength):
    try:
        digit = string.digits
        return ''.join((random.choice(digit) for i in range(stringLength)))
    except Exception as error:
        print(error)


url = f'https://api.cloudflareclient.com/v0a{digitString(3)}/reg'


def run():
    try:
        install_id = genString(22)
        body = {
            "key": "{}=".format(genString(43)),
            "install_id": install_id,
            "fcm_token": "{}:APA91b{}".format(install_id, genString(134)),
            "referrer": referrer,
            "warp_enabled": False,
            "tos": datetime.datetime.now().isoformat()[:-3] + "+07:00",
            "type": "Android",
            "locale": "en_EN"
        }
        data = json.dumps(body).encode('utf8')
        headers = {
            'Content-Type': 'application/json; charset=UTF-8',
            'Host': 'api.cloudflareclient.com',
            'Connection': 'Keep-Alive',
            'Accept-Encoding': 'gzip',
            'User-Agent': 'okhttp/3.12.1'
        }
        req = urllib.request.Request(url, data, headers)
        response = urllib.request.urlopen(req)
        status_code = response.getcode()
        return status_code
    except Exception as error:
        print("")
        print(error)


g = 0
b = 0
while True:
    os.system('cls' if os.name == 'nt' else 'clear')
    print("")
    print(
        "Hỗ trợ kích key 12 triệu data WARP+ FREE 100% tại https://wingiare.com"
    )
    print("")
    print(
        "Share key 12 triệu data WARP+ Free tại https://wingiare.com/cach-buff-warp-1-1-1-1-mien-phi-2021.html"
    )
    print("")
    print("[*] Lưu ý: Chạy trên Chrome, Edge, Safari")
    print("")
    sys.stdout.write("\r[+] Đang gửi lệnh...   [□□□□□□□□□□] 0%")
    sys.stdout.flush()
    result = run()
    if result == 200:
        g += 1
        progressBar()
        print(f"\n[-] ID: {referrer}")
        print(f"[:)] Đã +{g}GB data WARP+ vào key WARP của bạn")
        print(f"[#] Kết quả: {g} Ok | {b} No")
        for i in range(20, 0, -1):
            sys.stdout.write(f"\r[*] Sau {i} giây, lệnh sẽ được gửi đi...")
            sys.stdout.flush()
            time.sleep(1)
    else:
        b += 1
        print("[:(] Lỗi kết nối tới máy chủ.")
        print(f"[#] Kết quả: {g} Ok | {b} No")
        for i in range(20, 0, -1):
            sys.stdout.write(f"\r[*] Thử lại trong {i}s...")
            sys.stdout.flush()
            time.sleep(1)
