#pragma once

#include <cstdint>
#include "RTTI.h"
#include "Vector.h"
#include "expat.h"

namespace MahatmaGameEngine
{
	class XMLParseHelper;
	/**
	* Wrapper class for the expat library in C++
	*/
	class XMLParseMaster final
	{
	public:
		/**
		* This class represents data that all helpers share with each other and with the master parser.
		*/
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)
		public:

			/**
			* Initializes the SharedData object by setting the current depth to 0. 
			*/
			virtual void initialize();

			/**
			* Clones this object, ready to accept another file to parse, and returns an address to it.
			* @return address of the clone copy
			*/
			virtual SharedData* clone() = 0;

			/**
			* Setter for XMLParseMaster of SharedData
			* @param xmlParseMaster the address of the XMLParseMaster to be set
			*/
			void setXMLParseMaster(XMLParseMaster* xmlParseMaster);

			/**
			* Getter for the associated XMLParseMaster
			* @return address of the XMLParseMaster
			*/
			XMLParseMaster* getXMLParseMaster();

			/**
			* Const getter for the associated XMLParseMaster
			* @return address of the XMLParseMaster
			*/
			XMLParseMaster* const getXMLParseMaster() const;

			/**
			* Increases the depth at which the xml is being read
			*/
			void incrementDepth();

			/**
			* Decreases the depth at which the xml is being read
			*/
			void decrementDepth();

			/**
			* Returns the current depth at which the xml is at.
			*/
			std::uint32_t depth();

		private:
			XMLParseMaster* mXMLParseMaster;	/**< The associated XMLParseMaster of this shared data. */
			std::uint32_t mDepth;				/**< The depth at which the xml parsing currently is at.*/
		};

		/**
		* Constructor using a SharedData object. This constructor sets up the association to SharedData and creates an XML_Parser.
		* @param obj is the address of the SharedData object to associate to the XMLParseMaster
		*/
		XMLParseMaster(SharedData* obj);

		/**
		* Destructor destroys member variables.
		* Deletes XMLParseHelpers if this is cloned, because in that case, user does not have ownership of the Helpers.
		*/
		~XMLParseMaster();

		/**
		* Initialize the XMLParseMaster for a new parsing routine
		*/
		void initialize();

		/**
		* Creates a copy of this on the heap.
		* @return address to XMLParseMaster
		*/
		XMLParseMaster* clone();

		/**
		* Adds new helper to the list of helper methods of this master.
		* Note that you can't add new Helper objects to a cloned Master.
		* @param parseHelper the address of Helper object to add
		*/
		void addHelper(XMLParseHelper* parseHelper);

		/**
		* Removes a helper from tne list of the helper methods of this master.
		* @param parseHelper the address of the Helper object to remove.
		*/
		void removeHelper(XMLParseHelper* parseHelper);

		/**
		* Parses the data passed and triggers expat callbacks.
		* @param data character string of the data to be parsed
		* @param length of the data passed
		* @param isLast true if it is the last block passed
		*/
		void parse(const char* data, std::uint32_t length, bool isLast);

		/**
		* Parses the data from an XML file. Basically creates a string of data from the file and calls the parse method with it.
		* @param fileName the string value of the path to the file
		*/
		void parseFromFile(const std::string& fileName);

		/**
		* Getter for the fileName being used to parse the data from.
		* @return the string value with the Name and location of file
		*/
		std::string& getFileName();

		/**
		* Associates a different SharedData object to this.
		* @param sharedData address to the SharedData object
		*/
		void setSharedData(SharedData* sharedData);

		/**
		* Getter for the SharedData object associated with this.
		* @return address of the SharedData object
		*/
		SharedData* getSharedData();

	private:
		/**
		* The method registered with the XML_StartElementHandler callback from expat. It's static because it has to be called from a C library.
		* @param userData in our case, we are using this as a pointer to this XMLParseMaster object
		* @param element the character string value of the XML element returned by the parser
		* @param attributes array of attribute strings. The even numbers are the attribute names and the odd numbers are attribute values
		*/
		static void startElementHandler(void* userData, const char* element, const char** attributes);

		/**
		* The method registered with the XML_EndElementHandler callback from expat. It's static because it has to be called from a C library.
		* @param userData in our case, we are using this as a pointer to this XMLParseMaster object
		* @param element the character string value of the XML element returned by the parser
		*/
		static void endElementHandler(void* userData, const char* element);

		/**
		* The method registered with the XML_CharacterDataHandler callback from expat. It's static because it has to be called from a C library.
		* @param userData in our case, we are using this as a pointer to this XMLParseMaster object
		* @param value of the character string in between the start and end tags
		* @param length of the character string value
		*/
		static void charDataHandler(void* userData, const char* value, int length);

		SharedData* mSharedData;				/**< The address of the associated SharedData object */
		XML_Parser mParser;						/**< The parser of this object */
		std::string mFileName;					/**< Name of the file and path that was most recently parsed. */
		Vector<XMLParseHelper*> mHelpers;		/**< List of XMLParseHelpers the master can pass responsibility to. */
		bool mIsCloned;							/**< Flag to check if object is a clone. */
		std::int32_t mResponsibleHelperIndex;	/**< Index of the XMLParseHelper in mHelpers that has the current responsibility. */
	};
}