.PHONY: build clean

mac:
	@rm -rf build WD CMakeFiles CMakeCache.txt && cmake -S . -B build -G Ninja -DPLATFORM=macos -DCMAKE_INSTALL_PREFIX=$PWD/dist -DCMAKE_PREFIX_PATH="/opt/homebrew/opt/qt" -DCMAKE_TOOLCHAIN_FILE=/Users/neemaxon/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build build && cmake --install build && /opt/homebrew/opt/qt/bin/macdeployqt WD/dist/rbxmk-studio.app -verbose=2 && codesign --force --deep --sign - WD/dist/rbxmk-studio.app
win:
	@rm -rf build WD CMakeFiles CMakeCache.txt && docker compose up --build win

lin:
	@rm -rf build WD CMakeFiles CMakeCache.txt && docker compose up --build linux
