#pragma once

#define GLM_FORCE_CXX11

#include <cstdint>
#include <exception>
#include <string>
#include "glm.hpp"
#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "HashMap.h"
#include "FooDefaultHash.h"
#include "Datum.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			//Create ToString function for the UnitTestLibraryDesktop::Foo class.
			template<>
			std::wstring ToString<UnitTestLibraryDesktop::Foo>(const UnitTestLibraryDesktop::Foo& obj)
			{
				std::uint32_t returnVal = obj.getVar();
				return std::to_wstring(returnVal);
			}

			//Create ToString function for the integer Iterator class.
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<std::int32_t>::Iterator>(const MahatmaGameEngine::SList<std::int32_t>::Iterator& obj)
			{
				try
				{
					std::int32_t returnVal = *obj;
					return std::to_wstring(returnVal);
				}
				catch(std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Created ToString function for the pointer Iterator class.
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<std::int32_t*>::Iterator>(const MahatmaGameEngine::SList<std::int32_t*>::Iterator& obj)
			{
				try
				{
					return std::to_wstring(**obj);
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Created ToString function for the UnitTestLibraryDesktop::Foo Iterator class
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<UnitTestLibraryDesktop::Foo>::Iterator>(const MahatmaGameEngine::SList<UnitTestLibraryDesktop::Foo>::Iterator& obj)
			{
				try
				{
					UnitTestLibraryDesktop::Foo returnVal = *obj;
					return std::to_wstring(returnVal.getVar());
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Create ToString function for the integer Iterator class of Vector.
			template<>
			std::wstring ToString<MahatmaGameEngine::Vector<std::int32_t>::Iterator>(const MahatmaGameEngine::Vector<std::int32_t>::Iterator& obj)
			{
				try
				{
				return std::to_wstring(*obj);
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Created ToString function for the pointer Iterator class of Vector.
			template<>
			std::wstring ToString<MahatmaGameEngine::Vector<std::int32_t*>::Iterator>(const MahatmaGameEngine::Vector<std::int32_t*>::Iterator& obj)
			{
				try
				{
					return std::to_wstring(**obj);
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Created ToString function for the UnitTestLibraryDesktop::Foo Iterator class of Vector.
			template<>
			std::wstring ToString<MahatmaGameEngine::Vector<UnitTestLibraryDesktop::Foo>::Iterator>(const MahatmaGameEngine::Vector<UnitTestLibraryDesktop::Foo>::Iterator& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring((*obj).getVar());
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::HashMap<int32_t, int32_t>::PairType>(const MahatmaGameEngine::HashMap<int32_t, int32_t>::PairType& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring(obj.first);
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::HashMap<int32_t, int32_t>::Iterator>(const MahatmaGameEngine::HashMap<int32_t, int32_t>::Iterator& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring((*obj).first);
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::HashMap<char*, int32_t>::Iterator>(const MahatmaGameEngine::HashMap<char*, int32_t>::Iterator& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring((*obj).second);
				}
				catch (std::exception)
				{
					//return L"Invalid Iterator pointer";
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::HashMap<std::string, int32_t>::Iterator>(const MahatmaGameEngine::HashMap<std::string, int32_t>::Iterator& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring((*obj).second);
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::HashMap<Foo, int32_t>::Iterator>(const MahatmaGameEngine::HashMap<Foo, int32_t>::Iterator& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring((*obj).second);
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<MahatmaGameEngine::DatumType>(const MahatmaGameEngine::DatumType& obj)
			{
				std::wstring returnVal;
				try
				{
					returnVal = std::to_wstring(static_cast<int32_t>(obj));
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<glm::vec4>(const glm::vec4& obj)
			{
				std::wstring returnVal;
				try
				{
					std::string temp;
					sscanf_s("%f, %f, %f, %f", temp.c_str(), obj.x, obj.y, obj.z, obj.w);
					std::wstring tempWString(temp.begin(), temp.end());
					returnVal = tempWString;
				}
				catch (std::exception)
				{
				}
				return returnVal;
			}

			template <>
			std::wstring ToString<glm::mat4x4>(const glm::mat4x4& obj)
			{
				std::wstring returnVal;
				try
				{
					std::string temp;
					sscanf_s("%f, %f, %f, %f\n"
						"%f, %f, %f, %f\n"
						"%f, %f, %f, %f\n"
						"%f, %f, %f, %f", 
						temp.c_str(),
						obj[0].x, obj[0].y, obj[0].z, obj[0].w,
						obj[1].x, obj[1].y, obj[1].z, obj[1].w,
						obj[2].x, obj[2].y, obj[2].z, obj[2].w,
						obj[3].x, obj[3].y, obj[3].z, obj[3].w);
					std::wstring tempWString(temp.begin(), temp.end());
					returnVal = tempWString;
				} 
				catch (std::exception)
				{
				}
				return returnVal;
			}
		}
	}
}