load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all",
    srcs = glob(["**"]),
)

cmake(
    name = "c-blosc",
    build_args = ["--parallel"],
    cache_entries = {
        "DEACTIVATE_ZLIB": "ON",
        "DEACTIVATE_LZ4": "OFF",
        "PREFER_EXTERNAL_ZSTD": "ON",
        "BUILD_TESTS": "OFF",
        "BUILD_SHARED": "OFF",
        "BUILD_FUZZERS": "OFF",
        "BUILD_BENCHMARKS": "OFF",
    },
    lib_source = ":all",
    out_static_libs = ["libblosc.a"],
    deps = [
        "@zstd",
    ],
)
