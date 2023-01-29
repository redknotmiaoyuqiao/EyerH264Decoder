INCLUDE_DIRECTORIES (../)

ADD_EXECUTABLE(
        EyerH264Decoder

        Main.cpp

        AnnexBReader.cpp
        AnnexBReader.hpp

        Nalu.hpp
        Nalu.cpp
)

FILE(COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/../demo_video_176x144_baseline.h264
        DESTINATION
        ${CMAKE_CURRENT_BINARY_DIR}/
        )

INSTALL(
        TARGETS EyerH264Decoder
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)