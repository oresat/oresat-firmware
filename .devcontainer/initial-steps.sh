#!/bin/bash

set -e

if [ ! -d ../docker_cache ]; then
    mkdir ../docker_cache
else
    echo "$0:  Docker cache directory already present"
fi
