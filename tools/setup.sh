#!/bin/bash -e
# Ideally this installation would be handled by devcontainer features, but I
# can't seem to get them to work. I'm not investing more time, since this works
# FOR NOW.
#
# TODO: Add conon and xmake as devcontainer features

command -v curl
command -v gcc

# https://docs.conan.io/en/1.46/installation.html#install-with-pip-recommended
pip install conan

# https://xmake.io/#/getting_started?id=installation
bash <(curl -fsSL https://xmake.io/shget.text)
