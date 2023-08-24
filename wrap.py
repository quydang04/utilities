import urllib.request
import json
import datetime
import random
import string
import time
import os
import sys

script_version = '4.1.0'
window_title = f"WARP-PLUS-CLOUDFLARE By Navaneeth K M (version {script_version})"

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_about():
    print("[+] ABOUT SCRIPT:")
    print("[-] With this script, you can obtain unlimited WARP+ referral data.")
    print(f"[-] Version: {script_version}")
    print("--------")
    print("[+] By Navaneeth K M")
    print("[-] My Website: https://navaneethkm.ml")
    print("[-] TELEGRAM: navaneethkm004")
    print("--------")

def progress_bar(percent):
    animation = ["[□□□□□□□□□□]", "[■□□□□□□□□□]", "[■■□□□□□□□□]", "[■■■□□□□□□□]", "[■■■■□□□□□□]",
                 "[■■■■■□□□□□]", "[■■■■■■□□□□]", "[■■■■■■■□□□]", "[■■■■■■■■□□]", "[■■■■■■■■■□]"]
    progress_anim = percent // 10
    return f"\r[+] Waiting response... {animation[progress_anim]} {percent}%"

def gen_string(string_length):
    letters = string.ascii_letters + string.digits
    return ''.join(random.choice(letters) for _ in range(string_length))

def digit_string(string_length):
    digit = string.digits
    return ''.join(random.choice(digit) for _ in range(string_length))

def run(referrer):
    try:
        install_id = gen_string(22)
        body = {
            "key": f"{gen_string(43)}=",
            "install_id": install_id,
            "fcm_token": f"{install_id}:APA91b{gen_string(134)}",
            "referrer": referrer,
            "warp_enabled": False,
            "tos": f"{datetime.datetime.now().isoformat()[:-3]}+02:00",
            "type": "Android",
            "locale": "es_ES",
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
        return response.getcode()
    except Exception as error:
        print("\n" + str(error))

def main():
    clear_screen()
    print_about()
    referrer = input("[#] Enter the User ID:")

    g = 0
    b = 0
    while True:
        clear_screen()
        sys.stdout.write("\r[+] Sending request... " + progress_bar(0))
        sys.stdout.flush()
        result = run(referrer)
        if result == 200:
            g += 1
            for percent in range(0, 101, 10):
                sys.stdout.write(progress_bar(percent))
                sys.stdout.flush()
                time.sleep(0.075)
            print(f"\n[-] WORK ON ID: {referrer}")
            print(f"[:)] {g} GB has been successfully added to your account.")
            print(f"[#] Total: {g} Good {b} Bad")
            for i in range(18, 0, -1):
                sys.stdout.write(f"\r[*] After {i} seconds, a new request will be sent.")
                sys.stdout.flush()
                time.sleep(1)
        else:
            b += 1
            print("[:(] Error when connecting to the server.")
            print(f"[#] Total: {g} Good {b} Bad")
            for i in range(10, 0, -1):
                sys.stdout.write(f"\r[*] Retrying in {i}s...")
                sys.stdout.flush()
                time.sleep(1)

if __name__ == "__main__":
    while True:
        main()
        time.sleep(10)  # Delay for 10 seconds before running the loop again
