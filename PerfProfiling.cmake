set(PERF_STAT_EVENTS
    cycles
    instructions
    l1d-loads
    l1d-load-misses
    branches
    branch-misses
    CACHE STRING "perf stat events to measure"
)
string(REPLACE ";" "," perf_events "${PERF_STAT_EVENTS}")

function(add_perf_stat target)
    add_custom_target(perf_stat_${target}
        COMMAND sudo perf stat -e ${perf_events} $<TARGET_FILE:${target}>
        COMMENT "Profiling ${target} with perf stat"
        DEPENDS ${target}
    )
endfunction()

function(add_perf_record target)
    add_custom_target(perf_record_${target}
        COMMAND sudo perf record -e ${perf_events} $<TARGET_FILE:${target}>
        COMMENT "Profiling ${target} with perf stat"
        DEPENDS ${target}
    )
endfunction()

function(perf_profile target)
    add_perf_stat(${target})
    add_perf_record(${target})
endfunction()

add_custom_target(perf_report
    COMMAND sudo perf report --no-children
)
