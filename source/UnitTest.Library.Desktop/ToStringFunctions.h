#pragma once

#include <cstdint>
#include <exception>
#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"
#include "HashMap.h"
#include "FooDefaultHash.h"

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
					//return L"Invalid Iterator pointer";
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
					//return L"Invalid Iterator pointer";
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
					//return L"Invalid Iterator pointer";
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
					//return L"Invalid Iterator pointer";
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
					//return L"Invalid Iterator pointer";
				}
				return returnVal;
			}
		}
	}
}