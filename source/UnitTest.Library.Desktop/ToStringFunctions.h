#pragma once

#include <cstdint>
#include <exception>
#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"
#include "Vector.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			//Create ToString function for the Foo class.
			template<>
			std::wstring ToString<Foo>(const Foo& obj)
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
					std::int32_t* returnVal = *obj;
					return std::to_wstring(*returnVal);
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}

			//Created ToString function for the Foo Iterator class
			template<>
			std::wstring ToString<MahatmaGameEngine::SList<Foo>::Iterator>(const MahatmaGameEngine::SList<Foo>::Iterator& obj)
			{
				try
				{
					Foo returnVal = *obj;
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

			//Created ToString function for the Foo Iterator class of Vector.
			template<>
			std::wstring ToString<MahatmaGameEngine::Vector<Foo>::Iterator>(const MahatmaGameEngine::Vector<Foo>::Iterator& obj)
			{
				try
				{
					Foo returnVal = *obj;
					return std::to_wstring(returnVal.getVar());
				}
				catch (std::runtime_error e)
				{
					return L"Invalid Iterator pointer";
				}
			}
		}
	}
}