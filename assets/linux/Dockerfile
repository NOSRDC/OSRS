FROM --platform=linux/amd64 ubuntu:24.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    git ca-certificates curl zip unzip tar pkg-config \
    build-essential ninja-build cmake python3 python3-pip \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    mesa-common-dev libgl1-mesa-dev \
    patchelf file \
    && rm -rf /var/lib/apt/lists/*

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics

ENV CMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

WORKDIR /app

COPY vcpkg.json /app/vcpkg.json
RUN $VCPKG_ROOT/vcpkg install --triplet x64-linux

COPY . /app

RUN cmake -S . -B build -G Ninja \
    -DPLATFORM=linux \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE \
    -DVCPKG_TARGET_TRIPLET=x64-linux \
    && cmake --build build

CMD ["bash", "-lc", "ls -la /dist/linux && echo 'Linux build finished.'"]
