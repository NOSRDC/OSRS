FROM --platform=linux/amd64 ubuntu:24.04
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    git ca-certificates curl zip unzip tar pkg-config \
    build-essential ninja-build cmake python3 \
    libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
    mesa-common-dev libgl1-mesa-dev \
    software-properties-common \
    file patchelf \
    && rm -rf /var/lib/apt/lists/*

RUN add-apt-repository universe \
    && add-apt-repository multiverse \
    && dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
        wine-stable wine64 wine32:i386 \
        winbind \
    && rm -rf /var/lib/apt/lists/*

ENV WINEDEBUG=-all
ENV WINEPREFIX=/opt/wineprefix
ENV WINEDLLOVERRIDES=mscoree,mshtml=
RUN wineboot --init || true

RUN apt-get update && apt-get install -y --no-install-recommends \
    mingw-w64 \
    && rm -rf /var/lib/apt/lists/*

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics

ENV CMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake

WORKDIR /app

COPY vcpkg.json /app/vcpkg.json

ENV VCPKG_DEFAULT_TRIPLET=x64-mingw-static
RUN $VCPKG_ROOT/vcpkg install --triplet $VCPKG_DEFAULT_TRIPLET

COPY . /app

RUN wine ./assets/cmake-4.2.1-windows-x86_64/bin/cmake.exe -S . -B build -G Ninja \
        -DPLATFORM=windows \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE \
        -DVCPKG_TARGET_TRIPLET=$VCPKG_DEFAULT_TRIPLET \
    && cmake --build build \
    && mkdir -p /dist/windows \
    && cp -v build/rbxmk-studio.exe /dist/windows/rbxmk-studio.exe

CMD ["bash", "-lc", "ls -la /dist/windows && echo 'Windows build finished.'"]
