#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/ModuleLoader.hpp>
#include <GarrysMod/InterfacePointers.hpp>

#include <icvar.h>
#include <convar.h>

GarrysMod::Lua::ILuaBase* _LUA = nullptr;

LUA_FUNCTION(Set) {
    LUA->CheckString(1);
    const int type = LUA->GetType(2);
    const char* convar_str = LUA->GetString(1);
    const float new_value = LUA->GetNumber(2);

    ICvar *icvar = InterfacePointers::Cvar();
    ConVar *found_cvar = icvar->FindVar(convar_str);
    if (!found_cvar) {
        LUA->ThrowError("Could not find convar");
    }

    if (type == GarrysMod::Lua::Type::Number) {
        found_cvar->SetValue(static_cast<float>(new_value));
    }
    else if ( type == GarrysMod::Lua::Type::String ) {
        found_cvar->SetValue(static_cast<char>(new_value));
    }
    else {
        LUA->ArgError(2,"Invalid value type input");
    }

    return 0;
}

LUA_FUNCTION(Get) {

    return 0;
}

GMOD_MODULE_OPEN() {
    _LUA = LUA;

    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
    LUA->CreateTable();
        LUA->PushCFunction(Set);
        LUA->SetField(-2, "Set");

        LUA->PushCFunction(Get);
        LUA->SetField(-2, "Get");
    LUA->SetField(-2, "icvar");
    LUA->Pop();

    return 0;
}
