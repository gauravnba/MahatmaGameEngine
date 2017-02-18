#pragma once

namespace MahatmaGameEngine
{
	/**

	*/
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)

	public:
		//Typedefs used by the Scope Class
		typedef HashMap<std::string, Datum> Table;
		typedef HashMap<std::string, Datum>::Iterator TableIterator;
		typedef Vector<std::pair<std::string, Datum>*> Order;
		typedef std::pair<std::string, Datum> Pair;

		/**
		* Constructor for Scope.
		* @param size of the table if known apriori. Default is 5.
		*/
		Scope(std::uint32_t size = 5);
		
		/**
		* Copy constructor that deep copies the scope to this.
		* @param obj Scope to copy from.
		*/
		Scope(const Scope& obj);

		/**
		* Clears all the heap allocated Scope elements from the Table
		*/
		~Scope();

		/**
		* Assignment operator assigns the Scope on the right hand side to this.
		* @param obj the SCope to assign
		* @return this
		*/
		Scope& operator=(const Scope& obj);

		//TODO -- lookup adding reference to another method
		/**
		* Implements append.
		* @param name with which you search for the Datum
		* @return The found Datum or appends a new Datum
		*/
		Datum& operator[](const std::string& name);

		Datum& operator[](std::uint32_t index);

		bool operator==(const Scope& obj) const;

		bool operator!=(const Scope& obj) const;

		Datum* find(const std::string& name) const;

		Datum* search(const std::string& name, Scope** scope);

		/**
		* Appends a new name, Datum pair to the table.
		* The Datum is default constructed and can be manipulated with the returned value.
		* @param name the key that associates to the Datum.
		* @return returns the address of the Datum assigned.
		* @exception thrown if passed an empty string
		*/
		Datum& append(const std::string& name);

		/**
		* Appends a Scope object to this table with the string key that was passed
		* @param name the key that associates to the Datum that has the scope.
		* @return returns the address of the appended Scope
		*/
		Scope& appendScope(const std::string& name);

		void adopt(const Scope& child, const std::string& name, std::uint32_t index);

		Scope& getParent();

		const Scope& getParent() const;

		void orphan();

		/**
		* 
		*/
		bool equals(const RTTI* obj) const override;

	private:
		void clear();

		HashMap<std::string, Datum> mTable;
		Vector<std::pair<std::string, Datum>*> mOrder;
		Scope* mParent;
	};
}