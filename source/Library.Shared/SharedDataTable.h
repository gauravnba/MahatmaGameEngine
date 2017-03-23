#pragma once

#include "XMLParseMaster.h"
#include "RTTI.h"
#include "Scope.h"

namespace MahatmaGameEngine
{
	/**
	* SharedDataTable holds the data that is parsed from the XML file.
	*/
	class SharedDataTable : public XMLParseMaster::SharedData
	{
		RTTI_DECLARATIONS(SharedDataTable, XMLParseMaster::SharedData)

	public:

		SharedDataTable() = default;

		virtual ~SharedDataTable() = default;

		SharedDataTable(const SharedDataTable& obj) = delete;

		SharedDataTable(SharedDataTable&& obj) = delete;

		virtual void initialize() override;

		virtual XMLParseMaster::SharedData* clone() override;

		Scope mSharedTable;
	};
}