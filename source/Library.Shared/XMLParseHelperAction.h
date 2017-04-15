#pragma once

#include "XMLParseHelper.h"
#include "SharedDataTable.h"

namespace MahatmaGameEngine
{
	class Action;
	/**
	* Parsing helper class for floating point type.
	*/
	class XMLParseHelperAction : public XMLParseHelper
	{
	public:
		/**
		* Default constructor of XMLParseHelperAction.
		*/
		XMLParseHelperAction();

		/**
		* Disallow XMLParseHelperAction copy construction.
		*/
		XMLParseHelperAction(const XMLParseHelperAction&) = delete;

		/**
		* Disallow XMLParseHelperAction move semantics.
		*/
		XMLParseHelperAction(XMLParseHelperAction&&) = delete;

		/**
		* Default destructor of XMLParseHelperAction.
		*/
		virtual ~XMLParseHelperAction() = default;

		/**
		* Initializes the Helper, generally by populating the list of tags the helper can handle
		*/
		virtual void initialize() override {};

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
		* Handles the character data obtained via Action tags. These will generally contain conditions or expressions.
		* @param sharedData the address of the SharedData being used in this parsing.
		* @param value of the character string read from the XML file.
		*/
		virtual void charDataHandler(XMLParseMaster::SharedData* sharedData, const std::string& value) override;

	private:
		/**
		* Handles the type of action read from the file.
		* @param sharedData the SharedDataTable being used by the parser.
		* @param index the index of the element resolved.
		* @param attributesMap the HashMap containing all the attributes of the current tag.
		*/
		void actionStartHandler(SharedDataTable& sharedData, std::uint32_t index, HashMap<std::string, std::string>& attributesMap);

		/**
		* Resolve the type of the table in sharedData currently (World, Sector, Entity or Action) and createAction for that object.
		* @param sharedData the sharedData currently being used for the parsing.
		*/
		void createActionListIf(SharedDataTable& sharedData, const std::string& name);

		/**
		* Call create action on the current type of class that is stored in the sharedData.
		* @param sharedData the current table of contents used by the Parser.
		* @param attributes Hashmap of XML attributes.
		*/
		void createAction(SharedDataTable& sharedData, const HashMap<std::string, std::string>& attributes);

		/**
		* Create Reaction using factory and adopt it to the sharedData table.
		* @param sharedData the current table of contents used by the Parser.
		* @param attributes Hashmap of XML attributes.
		*/
		void createReaction(SharedDataTable& sharedData, const HashMap<std::string, std::string>& attributes);

		/**
		* Create Reaction using factory and adopt it to the sharedData table.
		* @param sharedData the current table of contents used by the Parser.
		* @param attributes Hashmap of XML attributes.
		*/
		void setActionAttributes(Action& temp, const HashMap<std::string, std::string>& attributes);

		/**
		* Handles the mBuffer as filled by the charDataHandler. This is called from the endElementHandler.
		* @param sharedData the sharedData currently being used for the parsing.
		* @param index at which the tag was found.
		*/
		void actionEndHandler(SharedDataTable& sharedData, std::uint32_t index);

		Vector<std::string> mHandledTags;	/**< The list of tags that the helper can handle. */
		std::string mBuffer;				/**< The string buffer into which you read the character data. */
	};
}