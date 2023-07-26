#!/bin/bash
# Script to upgrade from Debian 10 (Buster) to Debian 11 (Bullseye)

# Update current packages
sudo apt update
sudo apt upgrade -y

# Update sources.list to Bullseye/Bookworm
sudo sed -i 's/buster/bullseye/g' /etc/apt/sources.list

# Update packages to Bullseye
sudo apt update
sudo apt upgrade -y

# Perform dist-upgrade
sudo apt dist-upgrade -y

# Reboot system
sudo reboot
