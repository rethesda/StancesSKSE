-- set minimum xmake version
set_xmakever("2.8.2")

-- includes
includes("lib/commonlibsse-ng")
includes("extern/clib-util")

-- set project
set_project("StancesNG")
set_version("2.0.0")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_warnings("allextra")
set_defaultmode("releasedbg")

-- set policies
set_policy("package.requires_lock", true)

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- configs
set_config("rex_toml", true)
add_requires("imgui", {public = true})

-- targets
target("StancesNG")
    -- add dependencies to target
    add_deps("commonlibsse-ng")
    add_deps("clib-util")
    add_packages("imgui")
    -- add commonlibsse-ng plugin
    add_rules("commonlibsse-ng.plugin", {
        name = "StancesNG",
        author = "styyx",
        description = "SKSE based stance mod"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    add_includedirs("extern/clib-util/include", { public = true })
    set_pcxxheader("src/pch.h")

    -- copy build files (dll and pdb) to distr folder
    after_build(function (target)

        local dist_root = path.join(os.projectdir(), "distr")
        local release_root = path.join(os.projectdir(), "upload")
        local plugins = path.join(release_root, "SKSE", "Plugins")

        os.rm(release_root)
        os.mkdir(plugins)

        os.trycp(target:targetfile(), plugins)
        os.trycp(target:symbolfile(), plugins)

        if os.isdir(dist_root) then
            os.trycp(path.join(dist_root, "*"), plugins)
        end
    end)