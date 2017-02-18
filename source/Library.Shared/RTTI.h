#pragma once

#include <Windows.h>
#include <string>
#include <cstdint>

namespace MahatmaGameEngine
{
	class RTTI
	{
	public:
		virtual ~RTTI() = default;
		
		virtual std::uint64_t typeIdInstance() const = 0;
		
		virtual RTTI* queryInterface(const std::uint64_t id) const
		{
			UNREFERENCED_PARAMETER(id);
			return nullptr;
		}

		virtual bool is(std::uint64_t id) const
		{
			UNREFERENCED_PARAMETER(id);
			return false;
		}

		virtual bool is(const std::string& name) const
		{
			UNREFERENCED_PARAMETER(name);
			return false;
		}

		template <typename T>
		T* as() const
		{
			if (is(T::typeIdClass()))
			{
				return (T*)this;
			}

			return nullptr;
		}

		virtual std::string toString() const
		{
			return "RTTI";
		}

		virtual bool equals(const RTTI* rhs) const
		{
			return this == rhs;
		}
	};

#define RTTI_DECLARATIONS(Type, parentType)																	 \
		public:                                                                                              \
			typedef parentType Parent;                                                                       \
			static std::string typeName() { return std::string(#Type); }                                     \
			static std::uint64_t typeIdClass() { return sRunTimeTypeId; }                                    \
			virtual std::uint64_t typeIdInstance() const override { return Type::typeIdClass(); }            \
			virtual MahatmaGameEngine::RTTI* queryInterface(const std::uint64_t id) const override                     \
            {                                                                                                \
                if (id == sRunTimeTypeId)                                                                    \
					{ return (RTTI*)this; }                                                                  \
                else                                                                                         \
					{ return Parent::queryInterface(id); }                                                   \
            }                                                                                                \
			virtual bool is(std::uint64_t id) const override                                                 \
			{                                                                                                \
				if (id == sRunTimeTypeId)                                                                    \
					{ return true; }                                                                         \
				else                                                                                         \
					{ return Parent::is(id); }                                                               \
			}                                                                                                \
			virtual bool is(const std::string& name) const override                                          \
			{                                                                                                \
				if (name == typeName())                                                                      \
					{ return true; }                                                                         \
				else                                                                                         \
					{ return Parent::is(name); }                                                             \
			}                                                                                                \
			private:                                                                                         \
				static std::uint64_t sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type) std::uint64_t Type::sRunTimeTypeId = reinterpret_cast<std::uint64_t>(&Type::sRunTimeTypeId);
}