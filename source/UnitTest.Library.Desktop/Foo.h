#pragma once
#include <cstdint>
#include "RTTI.h"
#include "DefaultHash.h"

namespace UnitTestLibraryDesktop
{
	class Foo : public MahatmaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI)
	public:
		Foo();
		Foo(std::uint32_t data);
		~Foo();
		Foo(const Foo& obj);
		Foo& operator= (const Foo& obj);
		bool operator== (const Foo& obj) const;
		bool operator!= (const Foo& obj) const;
		void setVar(std::uint32_t var);
		std::uint32_t getVar() const;

	private:
		std::uint32_t* mVar;
	};
}