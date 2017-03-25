#pragma once

#include "XMLParseHelper.h"
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
		const std::string mHandledTag = "Scope";
	};
}