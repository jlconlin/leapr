
add_executable( coldh.coldh_util.betaLoop_util.test
                bt.test.cpp
                jprimeLoop.test.cpp )
target_compile_options( coldh.coldh_util.betaLoop_util.test PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${strict}>:${${PREFIX}_strict_flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_time_optimization}>:${${PREFIX}_link_time_optimization_flags}>
$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags}>>

${CXX_appended_flags} ${leapr_appended_flags} )
target_link_libraries( coldh.coldh_util.betaLoop_util.test PUBLIC leapr ) 
add_test( NAME coldh.coldh_util.betaLoop_util COMMAND coldh.coldh_util.betaLoop_util.test )