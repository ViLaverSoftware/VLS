cmake_minimum_required(VERSION 3.12)

project(VLS)

option(VLS_NO_INTERNAL_CONAN "Conan is not used to manage VLS packages if ON(Used for development)" ON)

add_subdirectory(Core)
add_subdirectory(Event)
add_subdirectory(Variant)
add_subdirectory(Element)