#pragma once

#include "XMLParseHelper.h"
#include "Vector.h"
#include "Datum.h"
#include <string>

namespace MahatmaGameEngine
{
	/**
	* Parsing helper class for floating point type.
	*/
	class XMLParseHelperDatum : public XMLParseHelper
	{
	public:
		/**
		* Default constructor of XMLParseHelperDatum.
		*/
		XMLParseHelperDatum();

		/**
		* Disallow XMLParseHelperDatum copy construction.
		*/
		XMLParseHelperDatum(const XMLParseHelperDatum&) = delete;

		/**
		* Disallow XMLParseHelperDatum move semantics.
		*/
		XMLParseHelperDatum(XMLParseHelperDatum&&) = delete;

		/**
		* Default destructor of XMLParseHelperDatum.
		*/
		virtual ~XMLParseHelperDatum() = default;

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
		* Private helper method that sets the type of the Datum based on what type of element was found in the XML.
		* @param name of the element obtained from XML i.e. tag
		* @param setTypeOf the Datum whose type needs to be set.
		*/
		void setDatumType(const uint32_t index, Datum& setTypeOf);

		Vector<std::string> mHandledTags; /**< The list of tags that the helper can handle. */
	};
}