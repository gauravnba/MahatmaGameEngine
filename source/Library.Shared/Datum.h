#pragma once

#define GLM_FORCE_CXX11

#include <cstdint>
#include <string>
#include "glm.hpp"
#include "RTTI.h"

namespace MahatmaGameEngine
{
	//Forward declaration of the class scope as a hint to the compiler.
	class Scope;

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
		* Datum destructor. Does nothing if data is marked external.
		*/
		~Datum();

		/**
		* Copy constructor of Datum.
		* @param obj Datum to deep-copy from.
		*/
		Datum(const Datum& obj);

		/**
		* Move constructor for Datum.
		* @param obj Rvalue reference to Datum to be moved from.
		*/
		Datum(Datum&& obj);

#pragma region ASSIGNMENT_OPERATOR_DECLARATIONS

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
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(int32_t obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(const float& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(const glm::vec4& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(const glm::mat4x4& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj Scope to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(Scope& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(const std::string& obj);

		/**
		* Scalar assignment operator assigns the parameter to this at index 0.
		* @param obj vec4 to assign
		* @return Reference to this
		* @overload Datum& operator=(const Datum& obj);
		*/
		Datum& operator=(RTTI* obj);
#pragma endregion

		/**
		* Move assignment operator for Datum.
		* @param obj RValue reference to the Datum to move from
		* @return Datum reference to this
		*/
		Datum& operator=(Datum&& obj);

#pragma region EQUALITY_OPERATOR_DECLARATIONS

		/**
		* Equality operator for Datum 
		* @param obj reference to Datum to be compared with
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const Datum& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks 
		if the first element in Datum is equal to passed parameter.
		* @param obj integer to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(int32_t obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj float to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const float& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj vector to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const glm::vec4& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj 4x4 matrix to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const glm::mat4x4& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj Scope pointer to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const Scope& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj string to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const std::string& obj) const;

		/**
		* Overloaded equality operator for scalar values i.e. checks
		if the first element in Datum is equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean true if equal
		* @overload bool operator==(const Datum& obj) const;
		*/
		bool operator==(const RTTI* obj) const;
#pragma endregion

#pragma region INEQUALITY_OPERATOR_DECLARATIONS

		/**
		* Equality operator for Datum
		* @param obj reference to Datum to be compared with
		* @return boolean true if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const Datum& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(int32_t obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const float& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const glm::vec4& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const glm::mat4x4& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const Scope& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const std::string& obj) const;

		/**
		* Overloaded inequality operator for scalar values i.e. checks
		if the first element in Datum is not-equal to passed parameter.
		* @param obj RTTI pointer to compare to
		* @return boolean false if equal
		* @overload bool operator!=(const Datum& obj) const;
		*/
		bool operator!=(const RTTI* obj) const;
#pragma endregion

#pragma region SET_STORAGE_DECLARATIONS

		/**
		* Sets the union to point to an external array passed as parameter. Overload for integer.
		* @param externalArray of type integer to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(int32_t* externalArray, uint32_t numberOfElements);

		/**
		* Sets the union to point to an external array passed as parameter. Overload for floating point.
		* @param externalArray of type float to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(float* externalArray, uint32_t numberOfElements);

		/**
		* Sets the union to point to an external array passed as parameter. Overload for vector.
		* @param externalArray of type vector to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(glm::vec4* externalArray, uint32_t numberOfElements);

		/**
		* Sets the union to point to an external array passed as parameter. Overload for matrix.
		* @param externalArray of type matrix to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(glm::mat4x4* externalArray, uint32_t numberOfElements);

		/**
		* Sets the union to point to an external array passed as parameter. Overload for string.
		* @param externalArray of type string to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(std::string* externalArray, uint32_t numberOfElements);

		/**
		* Sets the union to point to an external array passed as parameter. Overload for RTTI pointer.
		* @param externalArray of type RTTI pointer to be assigned from.
		* @param numberOfElements to set the size of the datum Array
		* @overload void setStorage(int32_t* externalArray, uint32_t numberOfElements);
		*/
		void setStorage(RTTI** externalArray, uint32_t numberOfElements);
#pragma endregion

#pragma region SET_DECLARATIONS

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
		* @overload void set(const float& value, std::uint32_t index = 0);
		*/
		void set(const glm::vec4& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		* @overload void set(const float& value, std::uint32_t index = 0);
		*/
		void set(const glm::mat4x4& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index in the Datum array at which the value will be assigned. The default is 0.
		* @overload void set(const float& value, std::uint32_t index = 0);
		*/
		void set(Scope& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index in the Datum array at which the value will be assigned. The default is 0.
		* @overload void set(const float& value, std::uint32_t index = 0);
		*/
		void set(const std::string& value, std::uint32_t index = 0);

		/**
		* Sets the value at the given index in the Datum
		* @param value is the const reference to the value to be assigned.
		* @param index is the index in the Datum array at which the value will be assigned. The default is 0.
		* @overload void set(const float& value, std::uint32_t index = 0);
		*/
		void set(RTTI* value, std::uint32_t index = 0);
#pragma endregion

#pragma region GET_DECLARATIONS

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
		* Template specialization of the get method for Scope Table
		* @param index where the element to be obtained is.
		* @return Scope reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		Scope*& get<Scope*>(std::uint32_t index);

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
		RTTI*& get<RTTI*>(std::uint32_t index);
#pragma endregion

#pragma region CONST_GET_DECLARATIONS
		/**
		* Templated method get returns the value at index (default = 0)
		* @param index where the element to be obtained is.
		* @return type T of the type of Datum it is.
		* @exception thrown if mType is not set.
		*/
		template <typename T>
		const T& get(std::uint32_t index = 0) const;

		/**
		* Template specialization of the get method for integer type
		* @param index where the element to be obtained is.
		* @return int32_t reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		const std::int32_t& get<int32_t>(std::uint32_t index) const;

		/**
		* Template specialization of the get method for floating type
		* @param index where the element to be obtained is.
		* @return float reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		const float& get<float>(std::uint32_t index) const;

		/**
		* Template specialization of the get method for glm vector type
		* @param index where the element to be obtained is.
		* @return vec4 reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		const glm::vec4& get<glm::vec4>(std::uint32_t index) const;

		/**
		* Template specialization of the get method for glm matrix type
		* @param index where the element to be obtained is.
		* @return mat4x4 reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		const glm::mat4x4& get<glm::mat4x4>(std::uint32_t index) const;

		/**
		* Const version of the template specialization of the get method for Scope Table
		* @param index where the element to be obtained is.
		* @return Scope reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		Scope* const& get<Scope*>(std::uint32_t index) const;

		/**
		* Template specialization of the get method for string type
		* @param index where the element to be obtained is.
		* @return string reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		const std::string& get<std::string>(std::uint32_t index) const;

		/**
		* Template specialization of the const get method for integer type
		* @param index where the element to be obtained is.
		* @return RTTI pointer reference.
		* @exception thrown if index is out of range.
		*/
		template <>
		RTTI* const& get<RTTI*>(std::uint32_t index) const;
#pragma endregion

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
		std::uint32_t size() const;

		/**
		* Returns the number of elements the Datum can hold.
		* @return Unsigned integer of the capacity of Datum
		*/
		std::uint32_t capacity() const;

		/**
		* Clears all the elements in the Datum
		* @exception if the type of the datum is undetermined
		*/
		void clear();

		/**
		* Removes the element from the datum array.
		* @param scope at which the element to remove is present. Default is zero.
		* @return true if table removed.
		*/
		bool removeTable(const Scope* scope);

		/**
		* Sets data into the Datum from a string value at specified index.
		* Note that the type of the Datum needs to be set before this method.
		* @param value is the string value to set from
		* @param index at which the value needs to be set
		* @exception thrown if DatumType not set
		*/
		void setFromString(std::string value, std::uint32_t index = 0);

		/**
		* Returns a string value of the item at the index
		* @param index where the item is located (default is 0)
		* @return value converted to string type
		*/
		std::string toString(std::uint32_t index = 0);

	private:
		/**
		* Clears the Datum and frees the memory allocated to the Union.
		*/
		void emptyOut();

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
		void removeRecursively(T* datumVal, std::uint32_t size = 0);

		/**
		* Converts string passed to the method to a vector
		* @param vectorValue string to be converted to vector
		* @return the converted vector
		*/
		glm::vec4 stringToVector(std::string vectorString);

		union DatumValue
		{
			std::int32_t* integerType;
			float* floatingType;
			glm::vec4* vectorType;
			glm::mat4x4* matrixType;
			Scope** tableType;
			std::string* stringType;
			RTTI** rttiType;
			void* genericType;
		};
		
		DatumValue mDatumVal;		/**< The Union that holds the array of the Datum values. */
		DatumType mType;			/**< The type of element in this Datum. */
		std::uint32_t mSize;		/**< The number of elements in the datum if it is not a scalar value. */
		std::uint32_t mCapacity;	/**< The number of elements the datum can hold at the moment. */
		bool mIsExternal;			/**< Whether the data is external or not. */
	};
}

#include "Datum.inl"