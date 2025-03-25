add_requires("boost", {system = false})
-- Create the IR project
add_headerfiles("Shared/(**.h**)")
includes("boolean_src")
includes("vector_src")

