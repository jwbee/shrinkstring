workspace(name = "jwbee_shrinkstring")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "com_google_googletest",
    strip_prefix = "googletest-b73f27fd164456fea9aba56163f5511355a03272",
    urls = ["https://github.com/google/googletest/archive/b73f27fd164456fea9aba56163f5511355a03272.zip"],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "b8a1527901774180afc798aeb28c4634bdccf19c4d98e7bdd1ce79d1fe9aaad7",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.4.1/bazel-skylib-1.4.1.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.4.1/bazel-skylib-1.4.1.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-d6a45e95ab515b55a2437835fdd5873c6572131d",
    urls = ["https://github.com/abseil/abseil-cpp/archive/d6a45e95ab515b55a2437835fdd5873c6572131d.zip"],
)

http_archive(
    name = "com_github_google_benchmark",
    strip_prefix = "benchmark-bd721f9859e50b261b7afe8a262a11c25b292aa5",
    urls = ["https://github.com/google/benchmark/archive/bd721f9859e50b261b7afe8a262a11c25b292aa5.zip"],
)

http_archive(
    name = "rules_foreign_cc",
    sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
    strip_prefix = "rules_foreign_cc-0.9.0",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/tags/0.9.0.tar.gz",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.9.0/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()

http_archive(
    name = "libpfm",
    build_file = "@com_github_google_benchmark//tools:libpfm.BUILD.bazel",
    sha256 = "5da5f8872bde14b3634c9688d980f68bda28b510268723cc12973eedbab9fecc",
    strip_prefix = "libpfm-4.11.0",
    type = "tar.gz",
    urls = ["https://sourceforge.net/projects/perfmon2/files/libpfm4/libpfm-4.11.0.tar.gz/download"],
)

load("@com_github_google_benchmark//:bazel/benchmark_deps.bzl", "benchmark_deps")

benchmark_deps()

http_archive(
    name = "rules_fuzzing",
    sha256 = "d9002dd3cd6437017f08593124fdd1b13b3473c7b929ceb0e60d317cb9346118",
    strip_prefix = "rules_fuzzing-0.3.2",
    urls = ["https://github.com/bazelbuild/rules_fuzzing/archive/v0.3.2.zip"],
)

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()

git_repository(
    name = "com_google_tcmalloc",
    branch = "master",
    recursive_init_submodules = True,
    remote = "https://github.com/google/tcmalloc.git",
)

http_archive(
    name = "hedron_compile_commands",
    strip_prefix = "bazel-compile-commands-extractor-d3afb5dfadd4beca48bb027112d029f2d34ff0a0",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/d3afb5dfadd4beca48bb027112d029f2d34ff0a0.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

http_archive(
    name = "zstd",
    build_file = "@//:zstd.BUILD",
    sha256 = "35ad983197f8f8eb0c963877bf8be50490a0b3df54b4edeb8399ba8a8b2f60a4",
    strip_prefix = "zstd-1.5.4",
    url = "https://github.com/facebook/zstd/archive/v1.5.4.tar.gz",
)

http_archive(
    name = "lz4",
    build_file = "@//:lz4.BUILD",
    sha256 = "37e63d56fb9cbe2e430c7f737a404cd4b98637b05e1467459d5c8fe1a4364cc3",
    strip_prefix = "lz4-1.9.4",
    url = "https://github.com/lz4/lz4/archive/refs/tags/v1.9.4.zip",
)

http_archive(
    name = "bitshuffle",
    build_file = "@//:bitshuffle.BUILD",
    sha256 = "59912a41c7d8e71f307e8c40da9beda80c4649c791f2aa33332c8390ee79b0bc",
    strip_prefix = "bitshuffle-0.5.1",
    url = "https://github.com/kiyo-masui/bitshuffle/archive/refs/tags/0.5.1.zip",
)

http_archive(
    name = "c-blosc",
    build_file = "@//:c-blosc.BUILD",
    sha256 = "a1dd1fa4bad3b97d1fd8a1f20923dd8161028ccf674a07da62662891c3219aa4",
    strip_prefix = "c-blosc-1.21.2",
    url = "https://github.com/Blosc/c-blosc/archive/refs/tags/v1.21.2.zip",
)
