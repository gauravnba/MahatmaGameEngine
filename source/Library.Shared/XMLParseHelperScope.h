#pragma once

#include "XMLParseHelper.h"
#include "SharedDataTable.h"
#include <string>

namespace MahatmaGameEngine
{
	/**
	* Parsing helper class for integer type.
	*/
	class XMLParseHelperScope : public XMLParseHelper
	{
	public:
		/**
		* Default constructor of XMLParseHelperInteger.
		*/
		XMLParseHelperScope() = default;

		/**
		* Disallow XMLParseHelperInteger copy construction.
		*/
		XMLParseHelperScope(const XMLParseHelperScope&) = delete;

		/**
		* Disallow XMLParseHelperInteger move semantics.
		*/
		XMLParseHelperScope(XMLParseHelperScope&&) = delete;

		/**
		* Default destructor of XMLParseHelperInteger.
		*/
		virtual ~XMLParseHelperScope() = default;

		/**
		* Initializes the Helper, generally by populating the list of tags the helper can handle
		*/
		virtual void initialize() override;

		/**
		* Clones the Helper and returns the address of it.
		* @return Address of the cloned object
		*/
		virtual XMLParseHelper* clone() override;

		/**
		* Called via the XML_StartElementHandler. Attempts to handle the element at start.
		* @param name of the element to be handled
		* @param attributesMap Hashmap of attribute-value pairs
		* @return boolean true if helper is responsible for handling the element
		*/
		virtual bool startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<std::string, std::string>& attributesMap) override;

		/**
		* Called via the XML_EndElementHandler. Attempts to handle the element at end.
		* @param name of the element to be handled
		* @return boolean true if helper is responsible for handling the element
		*/
		virtual bool endElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name) override;

	private:
		/**
		* Handles scope type tags.
		* @param index the index type for the switch statement.
		
		KEY:
		0 = Scope;
		1 = World;
		2 = Sector;
		3 = Entity;

		* @param sharedData the sharedDataTable value casted from the sharedData that startElementHandler received.
		* @param attributesMap the Hashmap of attributes received by startElementHandler.
		*/
		void scopeStartHandler(std::uint32_t index, SharedDataTable& sharedData, HashMap<std::string, std::string>& attributesMap);

		Vector<std::string> mHandledTags;					/**< The list of tags handled by this Helper.*/
	};
}