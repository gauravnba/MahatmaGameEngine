#pragma once

#include "XMLParseHelper.h"

namespace MahatmaGameEngine
{
	/**
	*/
	class XMLParseHelperInteger : public XMLParseHelper
	{
	public:
		XMLParseHelperInteger() = default;

		XMLParseHelperInteger(const XMLParseHelperInteger&) = delete;

		XMLParseHelperInteger(XMLParseHelperInteger&&) = delete;

		virtual ~XMLParseHelperInteger() = default;
	};
}