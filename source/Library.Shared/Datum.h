#pragma once

#include <cstdint>
#include <string>
//#include "glm.hpp"

namespace MahatmaGameEngine
{
	class Datum
	{
		enum class DatumType
		{
			Unassigned,
			Integer,
			Float,
			Vector,
			Matrix,
			Table,
			String,
			Pointer
		};

	public:
		Datum() = default;

		~Datum();

		Datum(const Datum& obj);

		Datum& operator=(const Datum& obj);

		DatumType setType();
		
		DatumType type();

		void setSize(std::uint32_t numberOfValues);

		std::uint32_t size();

		void clear();

		void setStorage(const DatumType& dataToInsert);

		bool operator==(const Datum& obj);

		bool operator!=(const Datum& obj);

		void set(Datum value, std::uint32_t index = 0);

		Datum get(std::uint32_t index = 0);

		void setFromString(std::string value, std::uint32_t index = 0);

		std::string toString(std::uint32_t index = 0);

	private:
		DatumType* mArray;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
	};
}