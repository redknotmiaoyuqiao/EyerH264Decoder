include_directories (../)

add_executable(
        Lesson_ReadAnnexB

        Nalu.hpp
        Nalu.cpp

        AnnexBReader.hpp
        AnnexBReader.cpp

        Main.cpp
)

file(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/../demo_video_176x144_baseline.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS Lesson_ReadAnnexB
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)