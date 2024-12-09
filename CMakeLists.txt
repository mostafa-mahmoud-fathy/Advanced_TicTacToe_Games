cmake_minimum_required(VERSION 3.27)
project(Advanced_TicTacToe_Games)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Advanced_TicTacToe_Games
        4x4_Tic_Tac_Toe.h
        5x5_Tic_Tac_Toe.h
        "A2_19_20231085_Game 4.h"
        BoardGame_Classes.h
        FourInARowGame.h
        "Game 2.cpp"
        Misere_TicTacToe.h
        "A2_19_20231085_Game 4.cpp")
