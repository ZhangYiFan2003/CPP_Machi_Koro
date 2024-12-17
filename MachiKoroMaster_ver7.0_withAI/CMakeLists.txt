cmake_minimum_required(VERSION 3.16)
project(MachiKoro_master)

set(CMAKE_CXX_STANDARD 14)
set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

include_directories(MachiKoro)

add_executable(MachiKoro_master
        MachiKoro/Bank.cpp
        MachiKoro/Bank.h
        MachiKoro/BlueCard.cpp
        MachiKoro/BlueCard.h
        MachiKoro/Card.cpp
        MachiKoro/Card.h
        MachiKoro/ColorAndIcon.h
        MachiKoro/Deck.cpp
        MachiKoro/Deck.h
        MachiKoro/Game.cpp
        MachiKoro/Game.h
        MachiKoro/GreenCard.cpp
        MachiKoro/GreenCard.h
        MachiKoro/MachiKoro.cpp
        MachiKoro/PurpleCard.cpp
        MachiKoro/PurpleCard.h
        MachiKoro/RedCard.cpp
        MachiKoro/RedCard.h
        MachiKoro/YellowCard.cpp
        MachiKoro/YellowCard.h)