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
		* Move Constructor of Scope.
		* @param obj RValue reference to Scope to move from
		*/
		Scope(Scope&& obj);

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

		/**
		* Move Assignment operator of Scope.
		* @param obj RValue reference to Scope to move from
		* @return Scope reference to this
		*/
		Scope& operator=(Scope&& obj);

		/**
		* Returns the datum entered at the index mentioned, based on the order of append
		* @param index coincides with the order at which the Datum was inserted.
		* @return The found Datum
		* @exception if out of index
		*/
		Datum& operator[](std::uint32_t index);

		/**
		* Implements append.
		* @param name with which you search for the Datum
		* @return The found Datum or appends a new Datum
		* @overload Datum& operator[](std::uint32_t index);
		*/
		Datum& operator[](const std::string& name);

		/**
		* Equality operator for Scope. Structural equality check
		* @param obj The scope to compare to
		* @return true if structurally equal
		*/
		bool operator==(const Scope& obj) const;

		/**
		* Inequality operator for Scope.
		* @param obj The scope to compare to
		* @return false if structurally equal
		*/
		bool operator!=(const Scope& obj) const;

		/**
		* Looks for the Datum, corresponding to the string passed, in the table
		* @param name with which to look up the Datum
		* @return pointer to Datum found, nullptr otherwise
		*/
		Datum* find(const std::string& name) const;

		/**
		* Extension of the find method, but searches for the Datum in parent Scopes as well
		* @param name with which to look up the Datum
		* @param scope output parameter: pointer to the pointer of the scope in which the Datum, nullptr if not found.
		* @return pointer to the Datum found, nullptr otherwise
		*/
		Datum* search(const std::string& name, Scope** scope);

		/**
		* Appends a new name, Datum pair to the table.
		* Note that append should not be used to append a type Scope (table); use appendScope(const string&) instead.
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
		* @exception thrown if trying to append a Scope to a non Scope name.
		*/
		Scope& appendScope(const std::string& name);

		/**
		* Adopts an existing child scope.
		* @param child Scope pointer to the child to adopt
		* @param name to access the child with
		*/
		void adopt(Scope* child, const std::string& name);

		/**
		* Returns the parent Scope of this scope.
		* @return pointer to the parent Scope
		*/
		Scope* getParent();

		/**
		* const version of getParent()
		* @return const pointer to the parent Scope
		*/
		Scope* const getParent() const;

		/**
		* Equals implements the Scope equality operator by casting the RTTI input to Scope.
		* The method is an override to the RTTI equals(const RTTI*) method
		* @param obj the RTTI pointer to be casted to Scope to check for equality
		* @return true if parameter is equal to the contents of this
		*/
		bool equals(const RTTI* obj) const override;

		/**
		* Overrides toString() in RTTI to return as Scope.
		* @return "Scope" to indicate the object the method is called is a Scope.
		*/
		std::string toString() const override;

	private:
		void orphan();

		void clear();

		HashMap<std::string, Datum> mTable;				/**< Table that stores string, Datum pairs. */
		Vector<std::pair<std::string, Datum>*> mOrder;	/**< */
		Scope* mParent;
	};
}