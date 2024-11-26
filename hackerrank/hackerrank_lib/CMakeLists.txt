project(hackerrank)

set(HEADER_FILES
        common_child.h
        fradulent_activity.h
        frequency_queries.h
        counting_inversions.h
        triplets.h
)

set(SOURCE_FILES
        common_child.cpp
        fraudulent_activity.cpp
        frequency_queries.cpp
        counting_inversions.cpp
        triplets.cpp
)

add_library(hackerrank_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})