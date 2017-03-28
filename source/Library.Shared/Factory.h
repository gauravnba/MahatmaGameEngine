#pragma once

#include "HashMap.h"
#include <string>

namespace MahatmaGameEngine
{
	/**
	* Factory class uses a Factory pattern to create objects based on the name of their type
	* i.e. the class will create objects based on the class name as a string parameter passed as argument.
	*/
	template <typename AbstractProductT>
	class Factory
	{
	public:
		//typedef HashMap<std::string, Factory<AbstractProductT>> HashMap<std::string, Factory<AbstractProductT>>;

		/**
		* The name of the class as the Factory knows it
		* @return string of the name of the class
		*/
		virtual const std::string className() = 0;

	private:
		/**
		* Create new instance of the class in Factory
		* @return Address to the factory class of object 
		*/
		virtual AbstractProductT* create() = 0;

	public:
		/**
		* 
		*/
		static Factory<AbstractProductT>* find(const std::string& className);

		/**
		* 
		*/
		static AbstractProductT* create(const std::string& className);

		/**
		* 
		*/
		static typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator begin();

		/**
		* 
		*/
		static typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator end();

	protected:
		/**
		* 
		*/
		static void add(Factory<AbstractProductT>* factory);

		/**
		* 
		*/
		static void remove(Factory<AbstractProductT>* factory);

	private:
		static HashMap<std::string, Factory<AbstractProductT>*> mFactoryTable;		/**< List of factory products that can be created by the Factory. */
	};
}

#define CONCRETE_FACTORY(AbstractProductT, ConcreteProductT)								\
	class ConcreteProductT ## Factory : public MahatmaGameEngine::Factory<AbstractProductT>		\
	{																							\
	public:																						\
		ConcreteProductT ## Factory() { add(this); };											\
																								\
		~ConcreteProductT ## Factory() { remove(this); };										\
																								\
		virtual const std::string className() override											\
		{																						\
			return #ConcreteProductT;															\
		};																						\
																								\
		virtual AbstractProductT* create() override												\
		{																						\
			return new ConcreteProductT;														\
		};																						\
	};

#include "Factory.inl"