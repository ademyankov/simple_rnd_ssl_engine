cmake_minimum_required(VERSION 3.9)

project(srndengine VERSION 1.0.0 DESCRIPTION "Simple RND OpenSSL Engine")

include(GNUInstallDirs)
find_package(OpenSSL REQUIRED)

set(SOURCE
    src/engine.c
    src/rnd.c
    src/engine.h
)

add_library(${PROJECT_NAME} MODULE ${SOURCE})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(
    ${PROJECT_NAME}
        OpenSSL::SSL
        OpenSSL::Crypto
)

if(UNIX)
    install(TARGETS srndengine LIBRARY
      DESTINATION /usr/lib/x86_64-linux-gnu/engines-1.1
    )
endif()

add_subdirectory(app)

#add_dependencies(srndtool ${PROJECT_NAME})
