#pragma once

#include "XMLParseMaster.h"
#include "RTTI.h"
#include "Scope.h"

namespace MahatmaGameEngine
{
	/**
	* SharedDataTable holds the data that is parsed from the XML file. It is an RTTI type and derived from SharedData.
	*/
	class SharedDataTable : public XMLParseMaster::SharedData
	{
		RTTI_DECLARATIONS(SharedDataTable, XMLParseMaster::SharedData)

	public:
		/**
		* Default constructor for SharedData.
		*/
		SharedDataTable();

		/**
		* Default destructor for SharedData.
		*/
		virtual ~SharedDataTable() = default;

		/**
		* Disallow copy construction.
		*/
		SharedDataTable(const SharedDataTable& obj) = delete;

		/**
		* Disallow move construction.
		*/
		SharedDataTable(SharedDataTable&& obj) = delete;

		/**
		* Initialize the SharedTable. This clears the Scope and resets the depth to zero.
		* @override initialize in the SharedData abstract class.
		*/
		virtual void initialize() override;

		/**
		* Clone creates a new object in the same state as this and then returns it.
		* @return address to the SharedData of this hierarchy.
		* @override clone in the SharedData abstract class.
		*/
		virtual XMLParseMaster::SharedData* clone() override;

		/**
		* @override the equals method of the RTTI.
		* @param rhs is the RTTI* to compare with.
		* @return true if the RTTI belongs to this chain of inheritance
		*/
		virtual bool equals(const RTTI* rhs) const override;

		Scope* mCurrentTable;			/**< Address of the Scope the SharedData is currently in. */
	};
}