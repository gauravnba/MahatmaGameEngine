#pragma once

#include "XMLParseHelper.h"
#include <string>

namespace MahatmaGameEngine
{
	/**
	* Parsing helper class for Matrix type.
	*/
	class XMLParseHelperMatrix : public XMLParseHelper
	{
	public:
		/**
		* Default constructor of XMLParseHelperInteger.
		*/
		XMLParseHelperMatrix() = default;

		/**
		* Disallow XMLParseHelperInteger copy construction.
		*/
		XMLParseHelperMatrix(const XMLParseHelperMatrix&) = delete;

		/**
		* Disallow XMLParseHelperInteger move semantics.
		*/
		XMLParseHelperMatrix(XMLParseHelperMatrix&&) = delete;

		/**
		* Default destructor of XMLParseHelperInteger.
		*/
		virtual ~XMLParseHelperMatrix() = default;

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

		/**
		* Called via XML_CharDataHandler. Attempts to handle the character data between the start and end tags.
		* @param buffer character buffer passed by expat parser. This is the data between the tags
		* @param length of the string of data passed
		*/
		virtual void charDataHandler(XMLParseMaster::SharedData* sharedData, const char* buffer, std::uint32_t length) override;

	private:
		const std::string mHandledTag = "Matrix";
	};
}