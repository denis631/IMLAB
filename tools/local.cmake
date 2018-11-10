# ---------------------------------------------------------------------------
# IMLAB
# ---------------------------------------------------------------------------

include("${CMAKE_SOURCE_DIR}/tools/schemac/local.cmake")
include("${CMAKE_SOURCE_DIR}/tools/queryc/local.cmake")

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

file(GLOB_RECURSE TOOLS_SRC "tools/imlabdb.cc")

# ---------------------------------------------------------------------------
# Executables
# ---------------------------------------------------------------------------

add_executable(imlabdb tools/imlabdb.cc tools/queryc/queryc.cc tools/queryc/queryParser.cc ${INCLUDE_H})
target_link_libraries(imlabdb imlab gflags Threads::Threads)

# ---------------------------------------------------------------------------
# Linting
# ---------------------------------------------------------------------------

add_cpplint_target(lint_tools "${TOOLS_SRC}")
list(APPEND lint_targets lint_tools)

