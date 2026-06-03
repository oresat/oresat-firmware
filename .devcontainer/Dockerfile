# Dockerfile based on zephyrprojectrtos/ci image
# ref: https://github.com/zephyrproject-rtos/docker-image/blob/main/Dockerfile.ci

FROM ubuntu:24.04

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

ARG USERNAME=user
ARG UID=1000
ARG GID=1000
ENV PYTHON_VENV_PATH=/opt/python/venv

# Set default shell during Docker image build to bash
SHELL ["/bin/bash", "-eo", "pipefail", "-c"]

# Install system dependencies (minimal set from zephyr base)

# - DEV 0127 - troubleshoot dot deb packages randomly failing checksum tests.
# References 1.2 and 1.3 seem to solve this problem:

# Ref (1.1) https://github.com/docker/for-mac/issues/7025
# RUN echo 'Acquire::http::Pipeline-Depth 0;\nAcquire::http::No-Cache true;\nAcquire::BrokenProxy true;\n' > /etc/apt/apt.conf.d/99fixbadproxy

# Ref (1.2) https://gist.github.com/trastle/5722089?permalink_comment_id=3714332
RUN touch /etc/apt/apt.conf.d/99fixbadproxy
RUN echo "Acquire::http::Pipeline-Depth 0;Acquire::http::No-Cache true;Acquire::BrokenProxy true;" >> /etc/apt/apt.conf.d/99fixbadproxy

# Ref (1.3) https://askubuntu.com/questions/1524755/apt-upgrade-crashed-installing-python3-3-12-3-0ubuntu2-amd64-deb
RUN dpkg --configure -a
RUN apt -f install

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        git \
        cmake \
        ninja-build \
        gperf \
        ccache \
        dfu-util \
        device-tree-compiler \
        openssh-client \
        openssh-server \
        wget \
        patch \
        python3-dev \
        python3-pip \
        python3-setuptools \
        python3-tk \
        python3-venv \
        python-is-python3 \
        xz-utils \
        file \
        make gcc \
        gcc-multilib \
        g++-multilib \
        libsdl2-dev \
        libmagic1 \
        unzip \
        sudo \
        wget \
        vim \
        tree \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Set up Python virtual environment
RUN <<EOF
    # Initialize virtual environment
    mkdir -p ${PYTHON_VENV_PATH}
    python3 -m venv ${PYTHON_VENV_PATH}

    # Activate virtual environment and install Python packages
    source ${PYTHON_VENV_PATH}/bin/activate

    # Install pip package manager
    pip install --no-cache-dir --upgrade pip setuptools wheel
    pip install --no-cache-dir \
        -r https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/v4.3.0/scripts/requirements-base.txt \
        -r https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/v4.3.0/scripts/requirements-build-test.txt \
        -r https://raw.githubusercontent.com/zephyrproject-rtos/zephyr/v4.3.0/scripts/requirements-run-test.txt \
        protobuf \
        grpcio-tools
EOF

# Make Zephyr Python virtual environment available system-wide
ENV PATH="${PYTHON_VENV_PATH}/bin:${PATH}"

# Install Zephyr SDK 0.17.4
ENV ZEPHYR_SDK_VERSION=0.17.4
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk-${ZEPHYR_SDK_VERSION}
RUN <<EOF
    mkdir -p /opt/toolchains
    cd /opt/toolchains
    wget -q https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
    tar -xf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz -C /opt/toolchains
    rm zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
    cd ${ZEPHYR_SDK_INSTALL_DIR}
    ./setup.sh -t arm-zephyr-eabi -h -c
EOF

# Set environment variables
ENV ZEPHYR_TOOLCHAIN_VARIANT=zephyr

# Create user and add it to plugdev and dialout
# to have proper access to usb devices
RUN userdel -r ubuntu && \
    groupadd -g $UID $USERNAME && \
    useradd -u $UID -g $GID -s /bin/bash -m $USERNAME && \
    usermod -a -G dialout $USERNAME && \
    usermod -a -G plugdev $USERNAME && \
    echo $USERNAME ' ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER $USERNAME
RUN cd ${ZEPHYR_SDK_INSTALL_DIR} && ./setup.sh -c

# Set working directory
WORKDIR /workdir
CMD ["/bin/bash"]
