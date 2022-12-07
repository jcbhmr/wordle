#!/bin/bash -e
command -v curl
command -v gcc
# https://docs.conan.io/en/1.46/installation.html#install-with-pip-recommended
pip install conan
# https://xmake.io/#/getting_started?id=installation
bash <(curl -fsSL https://xmake.io/shget.text)
