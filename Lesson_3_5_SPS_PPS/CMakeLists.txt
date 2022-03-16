include_directories (../)

add_executable(
        Lesson_3_5_SPS_PPS

        RBSP.hpp
        RBSP.cpp

        EBSP.hpp
        EBSP.cpp

        Nalu.hpp
        Nalu.cpp

        AnnexBReader.hpp
        AnnexBReader.cpp

        BitStream.hpp
        BitStream.cpp

        NaluSPS.hpp
        NaluSPS.cpp

        NaluPPS.hpp
        NaluPPS.cpp

        Main.cpp
)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/../demo_video_176x144_baseline.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS Lesson_3_5_SPS_PPS
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)