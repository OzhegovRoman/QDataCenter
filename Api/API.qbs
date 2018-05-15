import qbs

StaticLibrary{
    name: "QtCenterAPI"

    condition: qbs.targetOS.contains("windows")

    cpp.defines: [
        "VER=\"6.0.0\"",
        "ORIGIN_TARGET=\"\"",
        "PLUGINTYPE=\"\""
    ]
    cpp.includePaths: [
        "../Api/"
    ]

    Depends {
        name: "Qt";
        submodules: [
            "core",
            "gui",
            "widgets",
        ]
    }

    Group {
        name: "API"
        prefix: "**/*"
        files: [
            "*.cpp",
            "*.h",
            "*.ui"
        ]
    }
}
