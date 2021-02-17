cmake_minimum_required(VERSION 3.9)

project(SRndEngine VERSION 1.0.0 DESCRIPTION "Simple RND OpenSSL Engine")

include(GNUInstallDirs)

set(SOURCE src/engine.c)

add_library(${PROJECT_NAME} MODULE ${SOURCE})

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
    install(TARGETS dummyengine LIBRARY
      DESTINATION /usr/lib/x86_64-linux-gnu/engines-1.1
    )
endif()

add_subdirectory(app)
