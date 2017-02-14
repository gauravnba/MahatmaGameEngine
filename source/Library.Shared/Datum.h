#pragma once

#define GLM_FORCE_CXX11

#include <cstdint>
#include <string>
#include "glm.hpp"
#include "RTTI.h"

namespace MahatmaGameEngine
{
	/**
	* Strong enum of possible types of Datum, including Unknown for before the Datum is assigned.
	*/
	enum class DatumType
	{
		UNKNOWN, //will go to default in the switch
		INTEGER,
		FLOAT,
		VECTOR,
		MATRIX,
		TABLE,
		STRING,
		RTTI_POINTER
	};
	class Datum
	{
	public:
		/**
		* Datum constructor. Initializes the variables but not the DatumType, nor assigns value on the heap
		*/
		Datum();

		/**
		* Datum destructor.
		*/
		~Datum();

		/**
		* Copy constructor of Datum.
		* @param obj Datum to deep-copy from.
		*/
		Datum(const Datum& obj);

		/**
		* Assignment operator assigns the parameter datum to this.
		* @param obj Datum to deep copy from
		* @return Reference to Datum
		*/
		Datum& operator=(const Datum& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(int32_t obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(const float& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(const glm::vec4& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(const glm::mat4x4& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(const std::string& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		*/
		Datum& operator=(Library::RTTI* obj);

		/**
		* Equality operator for Datum 
		* @param obj reference to Datum to be compared with
		* @return boolean true if equal
		*/
		bool operator==(const Datum& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks 
		if the first element in Datum is equal to passed parameter.
		* @param obj integer to compare to
		* @return boolean true if equal
		*/
		bool operator==(int32_t obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj float to compare to
		* @return boolean true if equal
		*/
		bool operator==(const float& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj vector to compare to
		* @return boolean true if equal
		*/
		bool operator==(const glm::vec4& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj 4x4 matrix to compare to
		* @return boolean true if equal
		*/
		bool operator==(const glm::mat4x4& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj string to compare to
		* @return boolean true if equal
		*/
		bool operator==(const std::string& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean true if equal
		*/
		bool operator==(const Library::RTTI* obj) const;

		/**
		* Equality operator for Datum
		* @param obj reference to Datum to be compared with
		* @return boolean true if equal
		*/
		bool operator!=(const Datum& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(int32_t obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(const float& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(const glm::vec4& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(const glm::mat4x4& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(const std::string& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		*/
		bool operator!=(const Library::RTTI* obj) const;

		/**
		* Sets the type of the Datum
		* @param datumType is the type of the Datum
		* @exception thrown if trying to set an already set Datum
		*/
		void setType(DatumType datumType);
		
		/**
		* Gets the type of the Datum
		* @return enum value of the type of the Datum
		*/
		DatumType type() const;

		/**
		* Sets the number of values the Datum will store
		* @param numberOfValues is the number of values of the DatumType to be constructed
		* @exception if Datum type is undetermined.
		*/
		void setSize(std::uint32_t numberOfValues);

		/**
		* Returns the number of elements in the Datum.
		* @return Unsigned integer of the size of Datum
		*/
		std::uint32_t size();

		/**
		* Returns the number of elements the Datum can hold.
		* @return Unsigned integer of the capacity of Datum
		*/
		std::uint32_t capacity();

		/**
		* Clears all the elements in the Datum
		* @exception if the type of the datum is undetermined
		*/
		void clear();

		/**
		* 
		*/
		void setStorage(const DatumType* dataToInsert, uint32_t numberOfElements);

		/**
		* Sets the value at the given index in the Datum
		* @param value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(int32_t value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(const float& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(const glm::vec4& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(const glm::mat4x4& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(const std::string& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		*/
		void set(Library::RTTI* value, std::uint32_t index = 0);

		/**
		* Templated method get returns the value at index (default = 0)
		* @param index where the element to be obtained is.
		* @return type T of the type of Datum it is.
		* @exception thrown if mType is not set.
		*/
		template <typename T>
		T& get(std::uint32_t index = 0);

		/**
		* Template specialization of the get method for integer type
		* @param index where the element to be obtained is.
		* @return int32_t reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		std::int32_t& get<int32_t>(std::uint32_t index);

		/**
		* Template specialization of the get method for floating type
		* @param index where the element to be obtained is.
		* @return float reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		float& get<float>(std::uint32_t index);

		/**
		* Template specialization of the get method for glm vector type
		* @param index where the element to be obtained is.
		* @return vec4 reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		glm::vec4& get<glm::vec4>(std::uint32_t index);

		/**
		* Template specialization of the get method for glm matrix type
		* @param index where the element to be obtained is.
		* @return mat4x4 reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		glm::mat4x4& get<glm::mat4x4>(std::uint32_t index);

		/**
		* Template specialization of the get method for string type
		* @param index where the element to be obtained is.
		* @return string reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		std::string& get<std::string>(std::uint32_t index);

		/**
		* Template specialization of the get method for integer type
		* @param index where the element to be obtained is.
		* @return RTTI pointer reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		Library::RTTI*& get<Library::RTTI*>(std::uint32_t index);

		void setFromString(std::string value, std::uint32_t index = 0);

		std::string toString(std::uint32_t index = 0);

	private:

		/**
		* Reserves the DatumVal array of length of capacity
		* @param datumVal is the pointer to the data to be allocated to.
		* @param capacity is the amount of memory of size of T to be created.
		*/
		template <typename T>
		void reserve(T* datumVal, uint32_t capacity);

		/**
		* Instantiates objects in the mDatumVal array to length of size
		* @param datumVal is the pointer to the data to be instantiated at.
		* @param size is the amount of objects to be created.
		*/
		template <typename T>
		void instantiateSize(T* datumVal, std::uint32_t size);

		/**
		* Deletes objects in the mDatumVal array to length of size
		* @param datumVal is the pointer to the data to be destroyed
		* @param size is the amount of objects (from mSize to size) to be destroyed
		*/
		template <typename T>
		void removeRecursively(T* datumVal, std::uint32_t size);

		union DatumValue
		{
			std::int32_t* integerType;
			float* floatingType;
			glm::vec4* vectorType;
			glm::mat4x4* matrixType;
			// Table (Scope)
			std::string* stringType;
			Library::RTTI** rttiType;
			void* genericType;
		};
		
		DatumValue mDatumVal;		/**< The */
		DatumType mType;			/**< The type of element in this Datum. */
		std::uint32_t mSize;		/**< The number of elements in the datum if it is not a scalar value. */
		std::uint32_t mCapacity;	/**< The number of elements the datum can hold at the moment. */
		bool mIsExternal;			/**< Whether the data is external or not. */
	};
}

#include "Datum.inl"