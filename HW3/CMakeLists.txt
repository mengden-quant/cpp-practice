cmake_minimum_required(VERSION 3.12)

project(02.guess_number)

add_executable(guess_number 
    main.cpp
    guess.cpp
    rnd.cpp
    leaderboard.cpp
)

set_target_properties(guess_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
