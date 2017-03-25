#pragma once

#include <string>
#include "HashMap.h"
#include "XMLParseMaster.h"

namespace MahatmaGameEngine
{
	/**
	* Abstract base class for an XMLParseHelper to inherit from.
	*/
	class XMLParseHelper
	{
	public:
		/**
		* Destructor default
		*/
		virtual ~XMLParseHelper() = default;

		/**
		* Initializes the Helper, generally by populating the list of tags the helper can handle
		*/
		virtual void initialize() = 0;

		/**
		* Clones the Helper and returns the address of it.
		* @return Address of the cloned object
		*/
		virtual XMLParseHelper* clone() = 0;

		/**
		* Called via the XML_StartElementHandler. Attempts to handle the element at start.
		* @param name of the element to be handled
		* @param attributesMap Hashmap of attribute-value pairs
		* @return boolean true if helper is responsible for handling the element
		*/
		virtual bool startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<std::string, std::string>& attributesMap) = 0;
		
		/**
		* Called via the XML_EndElementHandler. Attempts to handle the element at end.
		* @param name of the element to be handled
		* @return boolean true if helper is responsible for handling the element
		*/
		virtual bool endElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name) = 0;

		/**
		* Called via XML_CharDataHandler. Attempts to handle the character data between the start and end tags.
		* @param buffer character buffer passed by expat parser. This is the data between the tags
		* @param length of the string of data passed
		*/
		virtual void charDataHandler(XMLParseMaster::SharedData* sharedData, const char* buffer, std::uint32_t length)
		{
			UNREFERENCED_PARAMETER(sharedData);
			UNREFERENCED_PARAMETER(buffer);
			UNREFERENCED_PARAMETER(length);
		};
	};	 
}		 