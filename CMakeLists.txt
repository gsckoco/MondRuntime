# CMakeList.txt : CMake project for MondRuntime, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("MondRuntime")


option(LUAU_BUILD_CLI "Build CLI" OFF)
option(LUAU_BUILD_TESTS "Build tests" OFF)
option(LUAU_BUILD_WEB "Build Web module" OFF)
option(LUAU_WERROR "Warnings as errors" OFF)
option(LUAU_STATIC_CRT "Link with the static CRT (/MT)" OFF)
add_subdirectory(Lib/luau)
# Add source to this project's executable.
add_executable (MondRuntime "Src/MondRuntime.cpp" "Src/MondRuntime.h" "Src/Html/html.cpp" "Src/Html/html.h")
target_link_libraries(MondRuntime Luau.Compiler)
target_link_libraries(MondRuntime Luau.VM)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MondRuntime PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
