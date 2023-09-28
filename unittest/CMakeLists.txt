add_definitions(-DFLOATING_POINT -DVAR_ARRAYS)
include_directories(../src)

codec2_add_executable(TARGET tfdmdv SOURCES tfdmdv.c ../src/kiss_fft.c ../src/octave.c)
codec2_add_executable(TARGET tcohpsk SOURCES tcohpsk.c ../src/cohpsk.c ../src/octave.c)
codec2_add_executable(TARGET tfsk NO_LINK_CODEC2 LINK_M SOURCES tfsk.c ../src/kiss_fft.c ../src/kiss_fftr.c ../src/octave.c ../src/modem_probe.c)
codec2_add_executable(TARGET tfreedv_data_channel NO_LINK_CODEC2 SOURCES tfreedv_data_channel.c ../src/freedv_data_channel.c)
codec2_add_executable(TARGET tfmfsk SOURCES tfmfsk.c ../src/octave.c ../src/modem_probe.c)


add_definitions(-DMODEMPROBE_ENABLE -DXXXXX)

codec2_add_executable(TARGET tofdm SOURCES tofdm.c ../src/octave.c)
codec2_add_executable(TARGET tofdm_acq LINK_M SOURCES tofdm_acq.c ../src/octave.c)

if(UNIX) # Uses pthreads
    add_executable(tfifo tfifo.c ../src/codec2_fifo.c)
    target_link_libraries(tfifo codec2 ${CMAKE_THREAD_LIBS_INIT})
endif()

add_definitions(-D__UNITTEST__)

set(CODEBOOKS
        ${CMAKE_BINARY_DIR}/src/codebook.c
        ${CMAKE_BINARY_DIR}/src/codebookd.c
        ${CMAKE_BINARY_DIR}/src/codebookge.c
        ${CMAKE_BINARY_DIR}/src/codebookjmv.c
        ${CMAKE_BINARY_DIR}/src/codebooknewamp1.c
        ${CMAKE_BINARY_DIR}/src/codebooknewamp1_energy.c
)

codec2_add_executable(TARGET tnewamp1 SOURCES tnewamp1.c ../src/quantise.c ../src/newamp1.c ../src/mbest.c ../src/kiss_fft.c ../src/sine.c ../src/nlp.c ../src/dump.c ../src/octave.c  ${CODEBOOKS})

add_executable(compare_ints compare_ints.c)
include_getopt(compare_ints)
add_executable(compare_floats compare_floats.c)
include_getopt(compare_floats)
add_executable(tvq_mbest tvq_mbest.c)


codec2_add_executable(TARGET tfreedv_800XA_rawdata SOURCES tfreedv_800XA_rawdata.c)
codec2_add_executable(TARGET tfreedv_2400A_rawdata SOURCES tfreedv_2400A_rawdata.c)
codec2_add_executable(TARGET tfreedv_2400B_rawdata SOURCES tfreedv_2400B_rawdata.c)
codec2_add_executable(TARGET tfsk_llr LINK_M SOURCES tfsk_llr.c)
codec2_add_executable(TARGET thash LINK_M SOURCES thash.c)
codec2_add_executable(TARGET tqam16 LINK_M SOURCES tqam16.c)
codec2_add_executable(TARGET t16_8 LINK_M SOURCES t16_8.c ../src/kiss_fft.c)
codec2_add_executable(TARGET t16_8_short SOURCES t16_8_short.c ../src/kiss_fft.c)
codec2_add_executable(TARGET t48_8 SOURCES t48_8.c ../src/kiss_fft.c)
codec2_add_executable(TARGET t48_8_short SOURCES t48_8_short.c ../src/kiss_fft.c)
codec2_add_executable(TARGET tquisk_filter SOURCES tquisk_filter.c)

# Build CML as part of unit test setup
find_program(OCTAVE_CMD octave-cli REQUIRED)
message("Octave command: ${OCTAVE_CMD}")

set(MSVC_CML_BUILD_COMMAND ${CMAKE_SOURCE_DIR}/octave/cml.bat )

if (NOT MSVC)
    include(ExternalProject)
    set(CML_PATH ${CMAKE_CURRENT_BINARY_DIR}/../cml)
    ExternalProject_Add(cml
            GIT_REPOSITORY https://github.com/drowe67/cml.git
            SOURCE_DIR ${CML_PATH}
            BUILD_IN_SOURCE 1
            CONFIGURE_COMMAND "" # No configuration required
            BUILD_COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/../cml && $<IF:$<BOOL:${MSVC}>,${MSVC_CML_BUILD_COMMAND},make>
            BUILD_ALWAYS False
            INSTALL_COMMAND "" # No installation required
    )
endif ()

# Create fading files (used for channel simulation) as part of unit test setup
add_custom_target(fading_files ALL
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/fast_fading_samples.float
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/faster_fading_samples.float
  )
add_custom_command(
  OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/fast_fading_samples.float
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/faster_fading_samples.float
  COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && $<IF:$<BOOL:${MSVC}>,"fading_files.bat","./fading_files.sh"> ${CMAKE_CURRENT_BINARY_DIR}
)

codec2_add_executable(TARGET freedv_700d_comptx SOURCES freedv_700d_comptx.c)
codec2_add_executable(TARGET freedv_700d_comprx SOURCES freedv_700d_comprx.c)


if(LPCNET AND lpcnetfreedv_FOUND)
    target_link_libraries(freedv_700d_comptx lpcnetfreedv)
    target_link_libraries(freedv_700d_comprx lpcnetfreedv)
endif()

add_executable(golay23 ../src/golay23.c)
target_compile_options(golay23 PUBLIC -DGOLAY23_UNITTEST)

add_executable(golay23_runtime_tables ../src/golay23.c)
target_compile_options(golay23_runtime_tables PUBLIC -DGOLAY23_UNITTEST -DRUN_TIME_TABLES)

codec2_add_executable(TARGET mksine NO_LINK_CODEC2 SOURCES mksine.c)
codec2_add_executable(TARGET vq_mbest SOURCES vq_mbest.c)
codec2_add_executable(TARGET tesno_est SOURCES tesno_est.c)