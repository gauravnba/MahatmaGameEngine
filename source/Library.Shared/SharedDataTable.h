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
		SharedDataTable() = default;

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

		virtual void initialize() override;

		virtual XMLParseMaster::SharedData* clone() override;

		Scope mSharedTable;
	};
}