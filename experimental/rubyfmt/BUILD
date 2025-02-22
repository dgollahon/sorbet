config_setting(
    name = "enable_rubyfmt",
    values = {
        "define": "rubyfmt=true",
    },
    visibility = ["//visibility:public"],
)

config_setting(
    name = "enable_rubyfmt_darwin",
    values = {
        "define": "rubyfmt=true",
        "host_cpu": "darwin",
    },
    visibility = ["//visibility:public"],
)

# NOTE: If a target depends on this, that target **must** cargo cult the linkopts
# from `rubyfmt_test`! Otherwise, it will not compile+link properly.
cc_library(
    name = "rubyfmt",
    srcs = select({
        ":enable_rubyfmt": ["rubyfmt.cc"],
        "//conditions:default": ["rubyfmt-noop.cc"],
    }),
    hdrs = [
        "rubyfmt.h",
    ],
    features = ["fully_static_link"],
    linkstatic = True,
    visibility = ["//visibility:public"],
    deps = select({
        "//conditions:default": [],
        ":enable_rubyfmt": [
            "@sorbet_ruby_2_6//:rubyfmt-static-deps",
            "@rubyfmt//:librubyfmt",
            "@rubyfmt//:rubyfmt_macro_wrappers",
            "@com_google_absl//absl/synchronization",
        ],
    }),
    alwayslink = True,
)

cc_test(
    name = "rubyfmt_test",
    size = "small",
    srcs = glob([
        "test/*.cc",
    ]),
    linkopts = select({
        "//conditions:default": [],
        ":enable_rubyfmt": [
            "-lcrypt",
            "-lrt",
            "-lz",
            "-lgmp",
        ],
        ":enable_rubyfmt_darwin": [
            "-framework Foundation",
        ],
    }),
    linkstatic = select({
        "//tools/config:linkshared": 0,
        "//conditions:default": 1,
    }),
    visibility = ["//tools:__pkg__"],
    deps = [
        "//experimental/rubyfmt",
        "@doctest",
        "@doctest//:doctest_main",
    ],
)
