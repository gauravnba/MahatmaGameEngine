#define SCOPE_TEST_DATA_DECLARATION											\
		string intType = "integer";											\
		int32_t iA = 10;													\
																			\
		string floatType = "float";											\
		float fA = 10.5f;													\
		float fB = 20.5f;													\
		float fC = 30.5f;													\
		float fD = 40.5f;													\
																			\
		string vecType = "vector";											\
		vec4 vA = vec4(vec3(fA), fB);										\
		vec4 vB = vec4(vec3(fB), fA);										\
		vec4 vC = vec4(vec3(fC), fD);										\
		vec4 vD = vec4(vec3(fD), fC);										\
																			\
		string matrixType = "matrix";										\
		mat4x4 mA = mat4x4(vA, vB, vC, vD);									\
		mat4x4 mB = mat4x4(vB, vC, vD, vA);									\
		mat4x4 mC = mat4x4(vC, vD, vA, vB);									\
		mat4x4 mD = mat4x4(vD, vA, vB, vC);									\
																			\
		string stringType = "string";										\
		string sA = "test";													\
		string sB = "anotherTest";											\
																			\
		string tableType = "table";											\
		Scope childScope;													\

//Requires SCOPE_TEST_DATA_DECLARATION before it

#define POPULATE_TEST_SCOPE													\
		Scope testScope;													\
		Datum* integer = &(testScope.append(intType));						\
		integer->set(iA);													\
		Datum* floatingPoint = &(testScope.append(floatType));				\
		floatingPoint->set(fA);												\
		floatingPoint->set(fB);												\
		Datum* vector4 = &(testScope.append(vecType));						\
		vector4->set(vA);													\
		vector4->set(vB);													\
		Datum* matrix4x4 = &(testScope.append(matrixType));					\
		matrix4x4->set(mA);													\
		matrix4x4->set(mB);													\
		Datum* stringDatum = &(testScope.append(stringType));				\
		stringDatum->set(sA);												\
		stringDatum->set(sB);												\
		Scope* childTable = &(testScope.appendScope(tableType));			\

