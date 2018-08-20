find_package(Qt5 REQUIRED COMPONENTS Core Widgets Qml Quick)

qt5_add_resources(QT_RESOURCE
    resource/qml.qrc)

add_executable( YAPM
    src/qtMain.cpp
    ${QT_RESOURCE})

target_compile_features(YAPM PRIVATE cxx_std_17)

set_target_properties( YAPM PROPERTIES CMAKE_AUTOMOC ON )
set_target_properties( YAPM PROPERTIES CMAKE_AUTORCC ON )
set_target_properties( YAPM PROPERTIES CMAKE_AUTOUIC ON )

target_link_libraries( YAPM Qt5::Widgets Qt5::Qml Qt5::Quick metricsLib dataservicelib)
target_compile_features( YAPM PUBLIC cxx_nullptr cxx_lambdas )
