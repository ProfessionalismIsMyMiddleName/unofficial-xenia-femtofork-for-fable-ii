add_library(xenia-f2 STATIC)

target_sources(xenia-f2 PRIVATE
    features.cc
    features.h
    hacks.h
)

target_link_libraries(xenia-f2 PUBLIC
    xenia-base
)

xe_target_defaults(xenia-f2)