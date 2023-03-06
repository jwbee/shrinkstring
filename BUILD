cc_binary(
    name = "benchmark",
    srcs = ["benchmark.cc"],
    malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@bitshuffle",
        "@c-blosc",
        "@com_github_google_benchmark//:benchmark_main",
        "@lz4",
        "@lz4//:lz4_hc",
        "@zstd",
    ],
)
