#pragma once


namespace MahatmaGameEngine
{
	template <typename T>
	typename Datum& Attributed::appendExternalAttribute(const std::string& name, T* attribute, std::uint32_t numberOfElements /* = 1 */)
	{
		Datum& temp = append(name);
		temp.setStorage(attribute, numberOfElements);

	}
}