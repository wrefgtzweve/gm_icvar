PROJECT_GENERATOR_VERSION = 3

local options = {
    trigger = "gmcommon",
    description = "Sets the path to the garrysmod_common (https://github.com/danielga/garrysmod_common) directory",
    value = "path to garrysmod_common directory"
}
local filesToInclude = {
    "src/**.cpp",
    "src/**.hpp",
    "src/**.h"
}
local workspace = { name = "icvar" }

newoption( options )

local gmcommon = assert( _OPTIONS.gmcommon or os.getenv( "GARRYSMOD_COMMON" ), "you didn't provide a path to your garrysmod_common (https://github.com/danielga/garrysmod_common) directory" )
include( gmcommon )

CreateWorkspace( workspace )

CreateProject( { serverside = true } )
    IncludeLuaShared()
    IncludeHelpersExtended()

    IncludeSDKCommon()
    IncludeSDKTier0()
    IncludeSDKTier1()

    files( filesToInclude )

CreateProject( { serverside = false } )
    IncludeLuaShared()
    IncludeHelpersExtended()

    IncludeSDKCommon()
    IncludeSDKTier0()
    IncludeSDKTier1()

    files( filesToInclude )
