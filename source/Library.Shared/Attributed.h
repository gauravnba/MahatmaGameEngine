#pragma once

#include "Scope.h"
#include "HashMap.h"
#include "Datum.h"
#include <string>
#include <cstdint>

namespace MahatmaGameEngine
{
	/**
	* Attributed is a class created to make it easy to define attributes for Entities.
	*/
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)

	public:
		/**
		* @typedef Standard Pair of RTTI type ID and a Vector of string names of PrescribedAttributes.
		*/
		typedef std::pair<uint64_t, Vector<std::string>> PrescribedAttributesPair;

		/**
		* The constructor for the Attributed class just adds this class to the Scope with the string "This".
		* This is added to the static hashmap of prescribed attributes
		*/
		Attributed();

		/**
		* Destructor for Attributed class
		*/
		virtual ~Attributed();

		/**
		* Copy constructor for the Attributed class
		* @param obj the Attributed object to be copied from
		*/
		Attributed(const Attributed& obj);

		/**
		* Move Constructor for the Attributed class
		* @param obj the Attributed Rvalue object to be moved
		*/
		Attributed(Attributed&& obj);

		/**
		* Copy assignment operator for the Attributed class
		* @param obj the Attributed object to be copied from
		* @return The Attributed reference of the this object that just got copied to
		*/
		Attributed& operator=(const Attributed& obj);

		/**
		* Move assignment operator for the Attributed class
		* @param obj the Attributed Rvalue object to be moved
		* @return The Attributed reference of the this object that just got moved to
		*/
		Attributed& operator=(Attributed&& obj);

		/**
		* Checks if an attribute of passed name exists
		* @param name of Attribute to check for existence
		* @return True if the attribute exists in this Scope
		*/
		bool isAttribute(const std::string& name) const;

		/**
		* Checks if the name passed is a prescribed attribute
		* @param name string name of the attribute
		* @return true if the name belongs to a prescribed attribute
		*/
		bool isPrescribedAttribute(const std::string& name) const;

		/**
		* Checks if the name passed is an auxiliary attribute
		* @param name string name of the attribute
		* @return true if the name belongs to an auxiliary attribute
		*/
		bool isAuxiliaryAttribute(const std::string& name) const;

		/**
		* Append an auxiliary attribute to this Scope.
		* @param name of the attribute to append
		* @return Datum that was just appended to the scope
		* @exception thrown if a prescribed attribute of the same name exists
		*/
		Datum& appendAuxiliaryAttribute(const std::string& name);

		/**
		* Returns the number of Prescribed attributes in the Scope.
		* @return unsigned int32 number of prescribed attributes. Or the number after which the Auxiliary attributes are populated.
		*/
		std::uint32_t auxiliaryBegin();

	protected:
		/**
		* Adds an extant nested Scope to the table.
		* @param name string name of the scope once added.
		* @param scope the scope to add.
		* @return a Datum of the Scope appended.
		*/
		Datum& addNestedScope(const std::string& name, Scope& scope);

#pragma region APPEND_INTERNAL_OVERLOADS
		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, std::int32_t value, uint32_t numberOfElements = 1);

		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, float value, uint32_t numberOfElements = 1);

		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, glm::vec4 value, uint32_t numberOfElements = 1);

		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, glm::mat4x4 value, uint32_t numberOfElements = 1);

		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, std::string value, uint32_t numberOfElements = 1);

		/**
		* Appends an internal attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param value of the Datum to set
		* @param numberOfElements the size of the Datum.
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendInternalAttribute(const std::string& name, RTTI* value, uint32_t numberOfElements = 1);
#pragma endregion

#pragma region APPEND_EXTERNAL_OVERLOADS
		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, std::int32_t* attribute, std::uint32_t numberOfElements = 1);

		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, float* attribute, std::uint32_t numberOfElements = 1);

		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, glm::vec4* attribute, std::uint32_t numberOfElements = 1);

		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, glm::mat4x4* attribute, std::uint32_t numberOfElements = 1);

		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, std::string* attribute, std::uint32_t numberOfElements = 1);

		/**
		* Appends an external attribute to the scope and returns the named Datum
		* @param name string to name the Datum with
		* @param attribute to be set as the Datum to set
		* @param numberOfElements the number of Elements in the attribute
		* @return Datum reference of the named Datum that was appended.
		*/
		Datum& appendExternalAttribute(const std::string& name, RTTI** attribute, std::uint32_t numberOfElements = 1);
#pragma endregion

		/**
		* Initializes the this signature in the Scope from derived class. Note that this method appends the this of child class in a heirarchy.
		*/
		void setTheThisAttribute();

		/**
		* Adds the name of a prescribed attribute to the static hashmap of Prescribed Attributes.
		* @param name string value name of the Datum.
		*/
		void addToPrescribed(const std::string& name);

		static HashMap<std::uint64_t, Vector<std::string>> mPrescribedAttributes;	/**< static Hashmap of RTTI type ID and list of string names of its prescribed attributes. */

	private:
		template <typename T>
		Datum& addInternalAttribute(const std::string& name, T value, std::uint32_t numberOfElements);

		template <typename T>
		Datum& addExternalAttribute(const std::string& name, T* attribute, std::uint32_t numberOfElements);
	};
}