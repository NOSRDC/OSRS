cmake_minimum_required(VERSION 3.20)

set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")

set(PLATFORM "" CACHE STRING "Target platform: windows, macos or linux")
set_property(CACHE PLATFORM PROPERTY STRINGS windows macos linux)

if(PLATFORM STREQUAL "")
    message(FATAL_ERROR "PLATFORM is not set. Use -DPLATFORM=windows, macos or linux")
endif()

if(PLATFORM STREQUAL "macos")
    project(unreal-studio LANGUAGES CXX OBJCXX)
else()
    project(unreal-studio LANGUAGES CXX)
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

set(VCPKG_APPLOCAL_DEPS ON)
set(VCPKG_APPLOCAL_DEPS_INSTALL ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(elfio CONFIG REQUIRED)
find_package(LibArchive REQUIRED)
find_package(lz4 CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(FILAMENT_BASE "${CMAKE_SOURCE_DIR}/assets/filament-platform")

if(PLATFORM STREQUAL "macos")
    set(FILAMENT_ROOT "${FILAMENT_BASE}/macOS/filament")
elseif(PLATFORM STREQUAL "windows")
    set(FILAMENT_ROOT "${FILAMENT_BASE}/win32/filament")
elseif(PLATFORM STREQUAL "linux")
    set(FILAMENT_ROOT "${FILAMENT_BASE}/linux/filament")
else()
    message(FATAL_ERROR "Unknown PLATFORM='${PLATFORM}'. Use windows or macos or linux")
endif()

set(FILAMENT_INCLUDE_DIR "${FILAMENT_ROOT}/include")
set(FILAMENT_BIN_DIR     "${FILAMENT_ROOT}/bin")

if(PLATFORM STREQUAL "macos")
    set(FILAMENT_LIB_DIR "${FILAMENT_ROOT}/lib/arm64")

elseif(PLATFORM STREQUAL "linux")
    set(FILAMENT_LIB_DIR "${FILAMENT_ROOT}/lib/x86_64")

elseif(PLATFORM STREQUAL "windows")
    set(FILAMENT_LIB_DIR_RELEASE "${FILAMENT_ROOT}/lib/x86_64/md")
    set(FILAMENT_LIB_DIR_DEBUG   "${FILAMENT_ROOT}/lib/x86_64/mdd")
endif()

if(NOT EXISTS "${FILAMENT_INCLUDE_DIR}")
    message(FATAL_ERROR "Filament include dir not found: ${FILAMENT_INCLUDE_DIR}")
endif()

if(PLATFORM STREQUAL "windows")
    if(NOT EXISTS "${FILAMENT_LIB_DIR_RELEASE}")
        message(FATAL_ERROR "Filament lib dir (Release) not found: ${FILAMENT_LIB_DIR_RELEASE}")
    endif()
    if(NOT EXISTS "${FILAMENT_LIB_DIR_DEBUG}")
        message(FATAL_ERROR "Filament lib dir (Debug) not found: ${FILAMENT_LIB_DIR_DEBUG}")
    endif()
else()
    if(NOT EXISTS "${FILAMENT_LIB_DIR}")
        message(FATAL_ERROR "Filament lib dir not found: ${FILAMENT_LIB_DIR}")
    endif()
endif()

set(FILAMENT_IMPORTED_TARGETS "")

if(PLATFORM STREQUAL "windows")
    file(GLOB FILAMENT_LIB_FILES_RELEASE "${FILAMENT_LIB_DIR_RELEASE}/*.lib")
    file(GLOB FILAMENT_LIB_FILES_DEBUG   "${FILAMENT_LIB_DIR_DEBUG}/*.lib")

    if(FILAMENT_LIB_FILES_RELEASE STREQUAL "" OR FILAMENT_LIB_FILES_DEBUG STREQUAL "")
        message(FATAL_ERROR "No Filament .lib found in md/mdd folders.")
    endif()

    set(_filament_names "")
    foreach(libfile IN LISTS FILAMENT_LIB_FILES_RELEASE)
        get_filename_component(fname "${libfile}" NAME_WE)
        list(APPEND _filament_names "${fname}")
    endforeach()
    list(REMOVE_DUPLICATES _filament_names)

    message(STATUS "Filament libs found (Windows):")
    foreach(name IN LISTS _filament_names)
        message(STATUS "  ${name}.lib")

        set(tgt "filament_${name}")

        add_library(${tgt} STATIC IMPORTED GLOBAL)
        set_target_properties(${tgt} PROPERTIES
                IMPORTED_LOCATION_RELEASE "${FILAMENT_LIB_DIR_RELEASE}/${name}.lib"
                IMPORTED_LOCATION_RELWITHDEBINFO "${FILAMENT_LIB_DIR_RELEASE}/${name}.lib"
                IMPORTED_LOCATION_MINSIZEREL "${FILAMENT_LIB_DIR_RELEASE}/${name}.lib"
                IMPORTED_LOCATION_DEBUG "${FILAMENT_LIB_DIR_DEBUG}/${name}.lib"
        )

        list(APPEND FILAMENT_IMPORTED_TARGETS ${tgt})
    endforeach()

else()
    file(GLOB FILAMENT_LIB_FILES "${FILAMENT_LIB_DIR}/*.a")

    if(FILAMENT_LIB_FILES STREQUAL "")
        message(FATAL_ERROR "No Filament libs found in: ${FILAMENT_LIB_DIR}")
    endif()

    message(STATUS "Filament libs found:")
    foreach(libfile IN LISTS FILAMENT_LIB_FILES)
        message(STATUS "  ${libfile}")
    endforeach()

    foreach(libfile IN LISTS FILAMENT_LIB_FILES)
        get_filename_component(fname "${libfile}" NAME_WE)
        string(REGEX REPLACE "^lib" "" fname "${fname}")
        string(REPLACE "-" "_" safe "${fname}")

        set(tgt "filament_${safe}")

        add_library(${tgt} STATIC IMPORTED GLOBAL)
        set_target_properties(${tgt} PROPERTIES
                IMPORTED_LOCATION "${libfile}"
        )

        list(APPEND FILAMENT_IMPORTED_TARGETS ${tgt})
    endforeach()
endif()

add_library(filament_all INTERFACE)
target_include_directories(filament_all INTERFACE "${FILAMENT_INCLUDE_DIR}")
target_link_libraries(filament_all INTERFACE ${FILAMENT_IMPORTED_TARGETS})

set(APP_NAME "unreal-studio")

set(SOURCES
        # core
        Application/core/sources/boot.cpp
        Application/core/sources/modules/interface.cpp
        Application/core/sources/modules/phases.cpp
        Application/core/file/file.cpp
        Application/core/file/binary/BinaryFormat.cpp
        Application/core/file/xml/XmlFormat.cpp
        Application/core/filamentclasses/filamentclasses.cpp
        Application/core/qtclasses/qtclasses.cpp
        Application/core/sumerrors/sumerrors.cpp
        Application/core/lang/languages.cpp

        # interface
        Application/interface/widgets/widget.cpp
        Application/interface/windows/windowmanager.cpp

        # programme-language
        Application/programme-language/languagemanager.cpp
        Application/programme-language/luau/luau.cpp
        Application/programme-language/luau/command-line/commandline.cpp
        Application/programme-language/luau/logic/logic.cpp
        Application/programme-language/cpp/cpp.cpp
        Application/programme-language/cpp/resolver/resolver.cpp
        Application/programme-language/cpp/blox/blox.cpp

        # ram
        Application/ram/rammanager.cpp
        Application/ram/optimization/optimization.cpp

        # render
        Application/render/rendermanager.cpp
        Application/render/3d/3d.cpp
        Application/render/3d/sub/file3d.cpp
        Application/render/cam/cam.cpp
        Application/render/cam/player/playercam.cpp
        Application/render/cam/studio/studiocam.cpp
        Application/render/light/light.cpp
        Application/render/physics/physics.cpp
        Application/render/cframe/cframemanager.cpp
        Application/render/cframe/position/position.cpp
        Application/render/cframe/orientation/orientation.cpp

        # auth
        Application/web/auth.cpp
)

if(PLATFORM STREQUAL "macos")
    message(STATUS "Configuring for macOS bundle")

    set(MACOS_ICON "${CMAKE_SOURCE_DIR}/assets/macos/icon.icns")
    set(MACOSX_BUNDLE_ICON_FILE "icon.icns")

    set_source_files_properties(${MACOS_ICON} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
    )

    add_executable(${APP_NAME} MACOSX_BUNDLE
            ${SOURCES}
            ${MACOS_ICON}
    )

    set_target_properties(${APP_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME}"
            MACOSX_BUNDLE_GUI_IDENTIFIER "com.neemaxon.unreal-studio"
            MACOSX_BUNDLE_ICON_FILE "icon.icns"
            MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
            MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
    )

    target_link_libraries(${APP_NAME} PRIVATE
            filament_all
            "-framework Cocoa"
            "-framework Metal"
            "-framework QuartzCore"
            "-framework CoreVideo"
            elfio::elfio
            LibArchive::LibArchive
            cpr::cpr
            lz4::lz4
            Qt6::Widgets
    )

    install(TARGETS ${APP_NAME}
            BUNDLE DESTINATION .
    )

elseif(PLATFORM STREQUAL "windows")
    message(STATUS "Configuring for Windows executable")

    set(LUNE_BIN "${CMAKE_SOURCE_DIR}/StableFrameworks/platform-lune/windows/lune.exe")
    set(WIN_ICON_RC "${CMAKE_SOURCE_DIR}/assets/windows/app.rc")

    add_executable(${APP_NAME} WIN32
            ${SOURCES}
            ${WIN_ICON_RC}
    )

    target_link_libraries(${APP_NAME} PRIVATE
            filament_all
            opengl32
            gdi32
            user32
            shell32
            elfio::elfio
            LibArchive::LibArchive
            cpr::cpr
            Qt6::Widgets
            lz4::lz4
    )

    install(TARGETS ${APP_NAME}
            RUNTIME DESTINATION .
    )

elseif(PLATFORM STREQUAL "linux")
    message(STATUS "Configuring for Linux build")

    add_executable(${APP_NAME}
            ${SOURCES}
    )

    target_link_options(${APP_NAME} PRIVATE "-Wl,--start-group")

    target_link_libraries(${APP_NAME} PRIVATE
            filament_all
            dl pthread m
            X11 Xi Xrandr Xcursor
            GL
            elfio::elfio
            LibArchive::LibArchive
            cpr::cpr
            Qt6::Widgets
            lz4::lz4
    )

    target_link_options(${APP_NAME} PRIVATE "-Wl,--end-group")

    install(TARGETS ${APP_NAME}
            RUNTIME DESTINATION bin
    )
endif()
