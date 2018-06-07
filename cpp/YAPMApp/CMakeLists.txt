#find_package( Qt5Widgets REQUIRED )
#set( CMAKE_AUTOMOC ON )


add_executable( YAPM
    src/qtMain.cpp)

target_compile_features(YAPM PRIVATE cxx_std_17)

#set_target_properties( YAPM PROPERTIES CMAKE_AUTOMOC ON )
#target_link_libraries( YAPM Qt5::Widgets MetricsLib DataServiceLib)
#target_compile_features( YAPM PUBLIC cxx_nullptr cxx_lambdas )
