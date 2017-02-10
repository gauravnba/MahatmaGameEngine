#pragma once

#include <cstdint>
#include <string>
#include "glm.hpp"
#include "RTTI.h"

namespace MahatmaGameEngine
{
	/**
	* 
	*/
	enum class DatumType
	{
		//Unassigned will go to default in the switch
		Integer,
		Float,
		Vector,
		Matrix,
		Table,
		String,
		RRTIPointer
	};

	class Datum
	{
	public:


		Datum();

		~Datum();

		Datum(const Datum& obj);

		Datum& operator=(const Datum& obj);

		void setType(DatumType datumType);
		
		DatumType type() const;

		void setSize(std::uint32_t numberOfValues);

		std::uint32_t size();

		void clear();

		void setStorage(const DatumType& dataToInsert);

		bool operator==(const DatumType& obj);

		bool operator!=(const DatumType& obj);

		void set(const DatumType& value, std::uint32_t index = 0);

		DatumType get(std::uint32_t index = 0);

		void setFromString(std::string value, std::uint32_t index = 0);

		std::string toString(std::uint32_t index = 0);

	private:
		union DatumValue
		{
			// Unassigned
			std::int32_t* integerType;
			float* floatingType;
			glm::vec4* vectorType;
			glm::mat4x4* matrixType;
			// Table (Scope)
			std::string* stringType;
			Library::RTTI* rttiType;
		};
		
		DatumType mType;			/**< The type of element in this Datum. */
		std::uint32_t mSize;		/**< The number of elements in the datum if it is not a scalar value. */
		std::uint32_t mCapacity;	/**< The number of elements the datum can hold at the moment. */
	};
}