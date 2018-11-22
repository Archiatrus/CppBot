# All the source files for the bot.
file(GLOB BOT_SOURCES "*.cpp" "*.h")

include_directories(SYSTEM "${SC2Api_INCLUDE_DIRS}")

# Show more warnings at compiletime.
if (MSVC)
    # FIXME: put Windows specific options here.
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif ()

# Create the executable.
add_executable(CppBot ${BOT_SOURCES})
target_link_libraries(CppBot ${SC2Api_LIBRARIES})

if (APPLE)
    target_link_libraries(CppBot "-framework Carbon")
endif ()

# Linux specific.
if (UNIX AND NOT APPLE)
    target_link_libraries(CppBot pthread dl)
endif ()
