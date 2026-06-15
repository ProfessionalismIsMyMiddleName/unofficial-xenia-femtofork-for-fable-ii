project_root = "../../.."
include(project_root.."/tools/build")

group("src")
project("xenia-f2")
  uuid("f2f7b35b-945f-4f2e-ac71-aa956e4dc32a")
  kind("StaticLib")
  language("C++")
  links({
    "xenia-base",
  })

  local_platform_files()
