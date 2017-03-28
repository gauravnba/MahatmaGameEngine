namespace MahatmaGameEngine
{
	template <typename AbstractProductT>
	HashMap<std::string, Factory<AbstractProductT>*> Factory<AbstractProductT>::mFactoryTable;

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::add(Factory<AbstractProductT>* factory)
	{
		mFactoryTable[factory->className()] = factory;
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::remove(Factory<AbstractProductT>* factory)
	{
		mFactoryTable.remove(factory->className());
	}

	template <typename AbstractProductT>
	typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::begin()
	{
		return mFactoryTable.begin();
	}

	template <typename AbstractProductT>
	typename HashMap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::end()
	{
		return mFactoryTable.end();
	}

	template <typename AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::find(const std::string& className)
	{
		HashMap<std::string, Factory<AbstractProductT>*>::Iterator temp = mFactoryTable.find(className);
		if (mFactoryTable.find(className) == mFactoryTable.end())
		{
			return nullptr;
		}
		return temp->second;
	}

	template <typename AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::create(const std::string& className)
	{
		return mFactoryTable[className]->create();
	}
}