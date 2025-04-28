add_requires("boost", "eigen", {system = false})
-- Create the IR project
add_headerfiles("Shared/(**.h**)")
add_headerfiles("../external/redsvd/(**.h**)")
includes("boolean_src")
includes("vector_src")

