import qbs

CppApplication{
    name: "QtCenter"

    condition: qbs.targetOS.contains("windows")

    consoleApplication: false


    cpp.defines: [
        "VER=\"6.0.0\"",
        "ORIGIN_TARGET=\"\"",
        "PLUGINTYPE=\"\""
    ]
    cpp.includePaths: [
        "../Api/"
    ]

    Depends {name: "QtCenterAPI"}
    Depends {
        name: "Qt";
        submodules: [
            "core",
            "gui",
            "widgets",
        ]
    }

//    Group {
//        name: "API"
//        prefix: "./../Api/**/*"
//        files: [
//            "*.cpp",
//            "*.h",
//            "*.ui"
//        ]
//    }

    Group {
        name: "Source"
        prefix: "**/*"
        files: [
            "*.cpp",
        ]
    }

    Group {
        name: "Headers"
        prefix: "**/*"
        files: [
            "*.h",
        ]
    }
    Group {
        name: "Forms"
        prefix: "**/*"
        files: [
            "*.ui",
        ]
    }
    Group {
        name: "Resource"
        files:[
            "*.qrc"
        ]
    }
}
