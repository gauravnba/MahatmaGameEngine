#pragma once

#include <SDKDDKVer.h>

#include <cstdint>
#include <exception>
#include <string>
#include <cstring>

#define GLM_FORCE_CXX11
#include "glm.hpp"
#include "gtx/string_cast.hpp"

#include "SList.h"
#include "Vector.h"
#include "DefaultHash.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Datum.h"
#include "Attributed.h"
#include "XMLParseMaster.h"
#include "XMLParseHelperAction.h"
#include "XMLParseHelperDatum.h"
#include "XMLParseHelperScope.h"
#include "GameTime.h"
#include "GameClock.h"
#include "Factory.h"
#include "WorldState.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionListIf.h"
#include "ActionSetString.h"
#include "Event.h"
#include "EventPublisher.h"
#include "EventQueue.h"
#include "Reaction.h"
#include "ReactionAttributed.h"
#include "AttributedMessage.h"
#include "ActionEvent.h"