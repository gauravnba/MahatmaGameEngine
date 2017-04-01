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
		* Looks for the factory in the list of Factories, and then returns the found object.
		* @param className string parameter with the class name to search with.
		* @return address of the found Factory class and nullptr if not found.
		*/
		static Factory<AbstractProductT>* find(const std::string& className);

		/**
		* Creates the class of type by invoking the create override of the derived factory class.
		* @param className string parameter to create the product of type className.
		* return address to the created product.
		*/
		static AbstractProductT* create(const std::string& className);

		/**
		* Returns an iterator to the beginning of the list of Factories.
		* @return iterator at begin of list of Factories
		*/
		static typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator begin();

		/**
		* Returns an iterator to the beginning of the list of Factories.
		* @return iterator at begin of list of Factories
		*/
		static typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator end();

	protected:
		/**
		* Adds a Factory to the list of factories.
		* @param factory the Factory object to insert into HashMap.
		*/
		static void add(Factory<AbstractProductT>* factory);

		/**
		* Removes a Factory from the list of factories.
		* @param factory the Factory object to remove from HashMap.
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