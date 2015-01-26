set(GAME_SOURCES main.cpp game.cpp gamemodel.cpp)

qt5_add_resources(RESOURCES qml.qrc)

add_executable(Game ${GAME_SOURCES} ${RESOURCES})

target_link_libraries(Game PUBLIC
    Qt5::Core
    Qt5::Quick
)