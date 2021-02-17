cmake_minimum_required(VERSION 3.9)

project(srndtool VERSION 1.0.0 DESCRIPTION "SRND Tool to use Simple RND OpenSSL Engine")

set(SOURCE src/main.c)

find_package(OpenSSL REQUIRED)

if(MSVC)
    list(APPEND
        SOURCE
            ${OPENSSL_INCLUDE_DIR}/openssl/applink.c
    )
endif()

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(
    ${PROJECT_NAME}
        OpenSSL::SSL
        OpenSSL::Crypto
)
