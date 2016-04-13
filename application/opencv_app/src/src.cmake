

set(SOURCES
    main.cpp
)

find_package( OpenCV REQUIRED )

set(DEPENDENCIES
    ${OpenCV_LIBS}
)