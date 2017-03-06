#pragma once

#include "Attributed.h"
#include <cstdint>

namespace MahatmaGameEngine
{
	class AttributedFoo : protected Attributed
	{
	public:
		AttributedFoo();

		~AttributedFoo();

	private:
		std::int32_t mIntAttribute;
		float mFloatAttribute;
		Scope* mTableAttribute;
	};
}