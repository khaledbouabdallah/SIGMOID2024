#!/bin/bash

# install python 3.11
sudo apt-get update
sudo apt-get install python3.11

# create virtual environment
python3 -m venv venv

# Activate the virtual environment
source venv/bin/activate

# Install required packages
pip install -r requirements.txt

# Run the application
python3 main.py
