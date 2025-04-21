load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def clean_dep(dep):
    return str(Label(dep))

def jsonrpc_workspace(path_prefix = "", tf_repo_name = "", **kwargs):

    io_opentelemetry_cpp_ver = kwargs.get("io_opentelemetry_cpp_ver", "1.8.1")
    io_opentelemetry_cpp_sha256 = kwargs.get("io_opentelemetry_cpp_sha256", "3d640201594b07f08dade9cd1017bd0b59674daca26223b560b9bb6bf56264c2")
    io_opentelemetry_cpp_urls = [
        "https://mirrors.tencent.com/github.com/open-telemetry/opentelemetry-cpp/archive/v{ver}.tar.gz".format(ver = io_opentelemetry_cpp_ver),
        "https://github.com/open-telemetry/opentelemetry-cpp/archive/v{ver}.tar.gz".format(ver = io_opentelemetry_cpp_ver),
    ]
    http_archive(
        name = "io_opentelemetry_cpp",
        sha256 = io_opentelemetry_cpp_sha256,
        strip_prefix = "opentelemetry-cpp-{ver}".format(ver = io_opentelemetry_cpp_ver),
        urls = io_opentelemetry_cpp_urls,
    )

    github_nlohmann_json_ver = kwargs.get("github_nlohmann_json_ver", "3.6.1")
    github_nlohmann_json_sha256 = kwargs.get("github_nlohmann_json_sha256", "2a515568e5b09babf7277f7d9ff2e2ae8ad6c94ec647e38e8b174628733dc2f5")
    github_nlohmann_json_urls = [
        "https://mirrors.tencent.com/github.com/nlohmann/json/archive/refs/tags/{ver}.tar.gz".format(ver = github_nlohmann_json_ver),
        "https://github.com/nlohmann/json/archive/refs/tags/{ver}.tar.gz".format(ver = github_nlohmann_json_ver),
    ]
    http_archive(
        name = "github_nlohmann_json",
        sha256 = github_nlohmann_json_sha256,
        strip_prefix = "json-{ver}".format(ver = github_nlohmann_json_ver),
        build_file = clean_dep("@io_opentelemetry_cpp//bazel:nlohmann_json.BUILD"),
        urls = github_nlohmann_json_urls,
    )