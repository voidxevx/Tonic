#pragma once

#include "ComponentPool.h"

#include<string>
#include<unordered_map>
#include<unordered_set>
#include<bitset>

namespace xenon
{
	struct Entity_Container
	{
		std::bitset<32> components = {};
		const char* script = "";
		bool tickEnabled = false;

		Entity_Container() = default;
		Entity_Container(const char* path)
			: script(path)
		{}

	};

	class registry
	{
	public:
		registry(size_t max)
			: m_MaxEntities(max)
		{}
		
		XenonID CreateEntity()
		{
			XenonID loc = (XenonID)m_Top;
			++m_Top;
			return loc;
		}
		
		template<typename _T>
		void RegisterComponent()
		{
			m_ComponentTypes[typeid(_T).name()] = (unsigned int)m_RegisteredComponents;
			m_Pools[(XenonID)m_RegisteredComponents] = new ComponentPool<_T>((XenonID)m_MaxEntities);
			++m_RegisteredComponents;
		}

		template<typename _T>
		void AddComponent(XenonID entity, _T* component)
		{
			dynamic_cast<ComponentPool<_T>*>(m_Pools[m_ComponentTypes[typeid(_T).name()]])->add(entity, component);
			m_Entities[entity].components.set(m_ComponentTypes[typeid(_T).name()]);
		}

		template<typename _T>
		bool HasComponent(XenonID id)
		{
			return m_Entities[id].components.test(m_ComponentTypes[typeid(_T).name()]);
		}

		template<typename _T>
		_T* GetComponent(XenonID id)
		{
			ComponentPool<_T>* pool = dynamic_cast<ComponentPool<_T>*>(m_Pools[m_ComponentTypes[typeid(_T).name()]]);
			std::optional<_T*> comp = pool->GetComponent(id);
			if (comp.has_value())
				return comp.value();
			else
				return nullptr;
		}

		template<typename _T>
		bool RemoveComponent(XenonID id)
		{
			ComponentPool<_T>* pool = dynamic_cast<ComponentPool<_T>*>(m_Pools[m_ComponentTypes[typeid(_T).name()]]);
			if (pool->contains(id))
			{
				pool->remove(id);
				m_Entities[id].components.flip(m_ComponentTypes[typeid(_T).name()]);
				return true;
			}
			return false;
		}

		void RegisterDestroy(XenonID id)
		{
			m_RegisteredToDestroy.push_back(id);
		}

		void DestroyEntity(XenonID id)
		{
			std::bitset<32> comps = m_Entities[id].components; // destroy components
			for (unsigned int i{}; i < m_RegisteredComponents; ++i)
			{
				if (comps.test(i))
					m_Pools[i]->remove(id);
			}

			XenonID endID = (XenonID)m_Top; // move the top entity to the removed entity location
			comps = m_Entities[endID].components;
			for (unsigned int i{}; i < m_RegisteredComponents; ++i)
			{
				if (comps.test(i))
					m_Pools[i]->move(endID, id);
			}
			m_Entities[id] = m_Entities[endID];
			--m_Top;
		}

		void PostTick()
		{
			for (const XenonID& entity : m_RegisteredToDestroy)
			{
				DestroyEntity(entity);
			}
			m_RegisteredToDestroy.clear();
		}

		void SetTickEnabled(XenonID id, bool val = true)
		{
			m_Entities[id].tickEnabled = val;
		}

		std::unordered_set<XenonID> GetAllEntitiesWithComponents(std::vector<std::string> componentIDs)
		{
			std::bitset<32> set = {};
			for (const std::string& comp : componentIDs)
			{
				set.set(m_ComponentTypes[comp]);
			}

			std::unordered_set<XenonID> entities;
			for (XenonID c_ent{}; c_ent < m_Top; ++c_ent) if (m_Entities[c_ent].components == set)
				entities.emplace(c_ent);

			return entities;
		}

	private:

		size_t m_MaxEntities; // maximum entities
		size_t m_Top = 0; // top of entity stack

		std::unordered_map<unsigned int, IComponentPool*> m_Pools; // maps bit location to component pool
		std::unordered_map<std::string, unsigned int> m_ComponentTypes; // maps component name to bit location
		size_t m_RegisteredComponents = 0; // the total amount of registered components

		std::unordered_map<XenonID, Entity_Container> m_Entities; // maps each entity id to the components it has and its scripts
		std::vector<XenonID> m_RegisteredToDestroy; // the entities marked for distruction at the end of the tick
	};
}