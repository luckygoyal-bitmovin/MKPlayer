// swift-tools-version: 5.8
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "MKPlayer",
    platforms: [
        .iOS(.v12),
        .tvOS(.v12)
    ],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "MKPlayer",
            targets: ["MKPlayerPackage"]),
    ],
    dependencies: [
        .package(url: "https://github.com/mkplayer-ios/OMSDK_Mediakind.git", exact: "0.0.2"),
        .package(url: "https://github.com/bitmovin/player-ios.git",
                    exact:"3.34.1"),
        .package(url: "https://github.com/bitmovin/bitmovin-analytics-collector-ios",
                 exact:"2.9.2")
    ],
    
    targets: [
        .target(name: "MKPlayerPackage",
                dependencies: ["MKPlayerPackageWrapper"],
                cSettings: [
                    .define("BUILD_LIBRARY_FOR_DISTRIBUTION", to: "YES")
                ]
        ),
        
        .target(name: "MKPlayerPackageWrapper",
                dependencies: [ "Alamofire", "OMSDK_Mediakind", "MKPlayer", "GoogleCast", "asid_ott_sdk",
                    .product(name: "BitmovinPlayer", package: "player-ios"),
                    .product(name: "BitmovinPlayerCollector", package: "bitmovin-analytics-collector-ios"),
                    ],
                cSettings: [
                    .define("BUILD_LIBRARY_FOR_DISTRIBUTION", to: "YES")
                ]
               ),
        
        .binaryTarget(name:"MKPlayer" , url: "https://mkplayer.blob.core.windows.net/$web/ios_tvos_rc_build/MKPlayer-1.0.0.99.zip", checksum: "8cb91f5ab71166f25617f3bd209c992a6b662a52b68c7de6f7caa632bae1f199"),
        .binaryTarget(
          name: "GoogleCast",
          path: "./GoogleCast.xcframework"
        ),
        .binaryTarget(
          name: "asid_ott_sdk",
          path: "./asid_ott_sdk.xcframework"
        ),
        .binaryTarget(
          name: "Alamofire",
          path: "./Alamofire.xcframework"
        ),
    ]
)
