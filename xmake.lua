set_project("MidnightMovies")
set_version("0.1.0")

add_repositories("gf-repo https://github.com/GamedevFramework/xmake-repo")

add_requires("gamedevframework1", "nlohmann_json", "sfml", "icu4c")
add_requires("boost", { configs = { locale = true }})

add_rules("mode.debug", "mode.releasedbg", "mode.release")

set_policy("build.warning", true)
set_warnings("allextra")
set_languages("cxx17")
set_encodings("utf-8")

if is_plat("windows") then
  add_cxflags("/wd4251") -- Disable warning: class needs to have dll-interface to be used by clients of class blah blah blah
  add_defines("NOMINMAX", "_CRT_SECURE_NO_WARNINGS")
end

set_configdir("$(buildir)/config")
set_configvar("GAME_DATADIR", "$(projectdir)/data/MidnightMovies")
set_configvar("GAME_LOCALEDIR", "$(projectdir)/data/raw/i18n")
add_configfiles("code/config.h.in", {pattern = "@(.-)@"})

target("MidnightMovies")
    set_kind("binary")
    add_files("code/main.cc")
    add_files("code/bits/*.cc")
    add_includedirs("$(buildir)/config")
    add_packages("gamedevframework1", "nlohmann_json")
    add_packages("sfml", {components = "audio"})
    add_packages("boost", "icu4c")

target("MidnightMoviesGenerator")
    set_kind("binary")
    add_files("code/generate.cc")
    add_packages("gamedevframework1")

target("MidnightMoviesCheck")
    set_kind("binary")
    add_files("code/check.cc")
    add_files("code/bits/MovieData.cc")
    add_includedirs("$(buildir)/config")
    add_packages("gamedevframework1", "nlohmann_json")
    add_packages("boost", "icu4c")

target("MidnightMoviesLevel")
    set_kind("binary")
    add_files("code/level.cc")
    add_files("code/bits/MovieData.cc")
    add_includedirs("$(buildir)/config")
    add_packages("gamedevframework1", "nlohmann_json")
    add_packages("boost", "icu4c")
