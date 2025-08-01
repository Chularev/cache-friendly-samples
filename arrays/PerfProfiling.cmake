set(PERF_STAT_EVENTS
    cycles
    instructions
    l1d-loads
    l1d-load-misses
    branches
    branch-misses
    CACHE STRING "perf stat events to measure"
)

function(add_perf_stat target)
    add_custom_target(perf_stat_${target}
        COMMAND sudo perf stat -e ${PERF_STAT_EVENTS} $<TARGET_FILE:${target}>
        COMMENT "Profiling ${target} with perf stat"
        DEPENDS ${target}
    )
endfunction()

add_perf_stat(simple_linear_array)
add_perf_stat(move_backward_linear_array)
