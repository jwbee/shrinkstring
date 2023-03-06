load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "zstd",
    cache_entries = {
        "ZSTD_MULTITHREAD_SUPPORT": "0",
        "ZSTD_LEGACY_SUPPORT": "1",
        "ZSTD_BUILD_STATIC": "1",
        "ZSTD_BUILD_SHARED": "0",
        "ZSTD_PROGRAMS_LINK_SHARED": "0",
        "ZSTD_BUILD_PROGRAMS": "0",
        "ZSTD_BUILD_CONTRIB": "0",
        "CMAKE_C_FLAGS": "-Wno-error",
    },
    build_args = ["--parallel"],
    lib_source = ":all",
    working_directory = "build/cmake",
    out_static_libs = ["libzstd.a"],
)

# vim: ft=bzl
