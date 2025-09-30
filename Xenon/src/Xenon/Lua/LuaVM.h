#pragma once

#include "../../../../Lua/include/lua.hpp"

#pragma comment(lib, "../lua/lua.lib")

#include <functional>
#include <cstdarg>

#define lua_function [](struct lua_State* L) -> int

namespace xenon
{

	enum LuaType
	{
		Float = 0,
		Int = 1,
		String = 2,
		Bool = 3,
	};

	struct LuaTableElement
	{
		const char* Key;
		LuaType Type;
		union
		{
			float f;
			int i;
			const char* s;
			bool b;
		};

		LuaTableElement(LuaType type, const char* key, float fval)
			: Key(key)
			, Type(type)
			, f(fval)
		{}

		LuaTableElement(LuaType type, const char* key, int ival)
			: Key(key)
			, Type(type)
			, i(ival)
		{}

		LuaTableElement(LuaType type, const char* key, const char* sval)
			: Key(key)
			, Type(type)
			, s(sval)
		{}

		LuaTableElement(LuaType type, const char* key, bool bval)
			: Key(key)
			, Type(type)
			, b(bval)
		{}
	};

	struct LuaTable
	{
		std::vector<LuaTableElement> table;

		LuaTable(std::vector<LuaTableElement> elements)
			: table(elements)
		{}
	};

	struct LuaFunctionInput
	{
		LuaType Type;
		union
		{
			float f;
			int i;
			const char* s;
			bool b;
		};

		LuaFunctionInput(LuaType type, float fval)
			: Type(type)
			, f(fval)
		{}
		LuaFunctionInput(LuaType type, int ival)
			: Type(type)
			, i(ival)
		{}
		LuaFunctionInput(LuaType type, const char* sval)
			: Type(type)
			, s(sval)
		{}
		LuaFunctionInput(LuaType type, bool bval)
			: Type(type)
			, b(bval)
		{}
	};

	template<typename _T>
	void lua_push(lua_State* L, _T val)
	{}

	template<>
	void lua_push<std::string>(lua_State* L, std::string val)
	{
		lua_pushstring(L, val.c_str());
	}

	template<>
	void lua_push<const char*>(lua_State* L, const char* val)
	{
		lua_pushstring(L, val);
	}

	template<>
	void lua_push<int>(lua_State* L, int val)
	{
		lua_pushnumber(L, val);
	}

	template<>
	void lua_push<float>(lua_State* L, float val)
	{
		lua_pushnumber(L, val);
	}

	template<>
	void lua_push<bool>(lua_State* L, bool val)
	{
		lua_pushboolean(L, val);
	}

	template<typename _T>
	void lua_push_tableElement(lua_State* L, const char* name, _T val)
	{
		lua_pushstring(L, name);
		lua_push<_T>(L, val);
		lua_settable(L, -3);
	}

	void lua_push_table(lua_State* L, LuaTable table)
	{
		lua_newtable(L);
		for (const LuaTableElement& element : table.table)
		{
			switch (element.Type)
			{
			case LuaType::Float:
				lua_push_tableElement(L, element.Key, element.f);
				break;
			case LuaType::Int:
				lua_push_tableElement(L, element.Key, element.i);
				break;
			case LuaType::String:
				lua_push_tableElement(L, element.Key, element.s);
				break;
			case LuaType::Bool:
				lua_push_tableElement(L, element.Key, element.b);
			}
		}
	}

	class LuaVM
	{
	public:
		LuaVM()
		{
			instance = luaL_newstate();
			luaL_openlibs(instance);
		}
		~LuaVM()
		{
			lua_close(instance);
		}

		void loadScript(std::string path) const
		{
			int success = luaL_dofile(instance, path.c_str());
			if (success != LUA_OK)
				std::cout << lua_tostring(instance, -1) << std::endl;
		}

		void function(std::string name, lua_CFunction callback) const
		{
			lua_register(instance, name.c_str(), callback);
		}

		bool call(std::string name) const
		{
			lua_getglobal(instance, name.c_str());
			if (lua_isfunction(instance, -1))
			{
				lua_pcall(instance, 0, 0, 0);
				return true;
			}
			else return false;
		}

		bool call(const char* name, unsigned int returnCount, std::initializer_list<LuaFunctionInput> inputs)
		{

			lua_getglobal(instance, name);
			if (lua_isfunction(instance, -1))
			{

				for (const LuaFunctionInput in : inputs)
				{
					switch (in.Type)
					{
					case LuaType::Float:
						lua_push<float>(instance, (float)in.f);
						break;
					case LuaType::Int:
						lua_push<int>(instance, (int)in.i);
						break;
					case LuaType::String:
						lua_push<std::string>(instance, in.s);
						break;
					}
				}

				lua_pcall(instance, (int)inputs.size(), returnCount, 0);
				return true;

			}
			else return false;
		}
		
		lua_State* instance;
	};


	
}