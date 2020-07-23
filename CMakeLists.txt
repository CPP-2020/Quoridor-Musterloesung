cmake_minimum_required(VERSION 3.15)
project(Hackathon)

add_subdirectory(extern/googletest)

add_library(GraphLib
    STATIC
    Graph/Edge.cpp
    Graph/Edge.h
    Graph/Vertex.cpp
    Graph/Vertex.h
    Graph/Graph.cpp
    Graph/Graph.h
    Graph/Graph-commons.h
    Graph/PointerIteratorWrapper.h
    Graph/SimpleRange.h
    Graph/GraphMaps.h
    Graph/Algorithm/BreadthFirstSearch.cpp
    Graph/Algorithm/BreadthFirstSearch.h
    Graph/VertexVector.h)

add_library(LoggerLib
        STATIC
        Logger/Logger.h
        Logger/LogPolicyInterface.h
        Logger/FileLogPolicy.cpp
        Logger/FileLogPolicy.h
        Logger/CoutLogPolicy.cpp
        Logger/CoutLogPolicy.h
        Logger/LogLevel.cpp
        Logger/LogLevel.h
        Logger/Log.h)

add_library(GameLib
    STATIC
    GameLib/ConsoleUtils.h
    GameLib/ConsoleUtils.cpp
    GameLib/GameField.h
    GameLib/GameField.cpp
    GameLib/Position.h
    GameLib/Position.cpp
    GameLib/Coordinate.h
    GameLib/Coordinate.cpp
    GameLib/HumanPlayer.h
    GameLib/HumanPlayer.cpp
        GameLib/Ui.cpp GameLib/Ui.h GameLib/GameHost.cpp GameLib/GameHost.h GameLib/Player.cpp GameLib/Player.h GameLib/GameRules.cpp GameLib/GameRules.h GameLib/GameDecision.cpp GameLib/GameDecision.h GameLib/PlaceBorderDecision.cpp GameLib/PlaceBorderDecision.h GameLib/MovePlayerDecision.cpp GameLib/MovePlayerDecision.h GameLib/DummyPlayer.cpp GameLib/DummyPlayer.h)

add_executable(
    Hackathon
    main.cpp
)

if(UNIX)
    target_link_libraries(GameLib -lcurses)
endif(UNIX)

target_link_libraries(Hackathon GameLib GraphLib LoggerLib)

