#include "interface.h"

///////////////////////////////////////////////////////////////////////////////
// private functions headers
///////////////////////////////////////////////////////////////////////////////
static void Interface_Check_Args(const interfaceConfig_t config, const void *classImpl, const char *prefix);
static char *Interface_Resolve_FuncName(const char *ifunc, const char *append,
                                        const enum interfaceAppendType_t type);
static void Interface_Resolve_Func_Addr(void *interface, const interfaceConfig_t config,
                                        const char *prefix, const enum interfaceAppendType_t type);



///////////////////////////////////////////////////////////////////////////////
// private functions
///////////////////////////////////////////////////////////////////////////////
static void Interface_Check_Args(const interfaceConfig_t config, const void *classImpl, const char *prefix) {
	if(config.func == NULL) { Error("INTERFACE ERROR CHECK"); }
	
	if(config.numFunc < 1) { Error("INTERFACE ERROR CHECK"); }
	
	if(config._sizeof < (sizeof(void*) + config.numFunc*sizeof(void*(*)()))) { Error("INTERFACE ERROR CHECK"); }
	
	if(config.addr == NULL) { Error("INTERFACE ERROR CHECK"); }
	
	for(int i=0; i < config.numFunc +1; ++i) {
		if(config.func[i] == NULL && i < config.numFunc) {
			Error("INTERFACE ERROR CHECK");
		}
		
		if(config.addr[i] == NULL) {
			Error("INTERFACE ERROR CHECK");
		}
	}
	
	if(classImpl == NULL) { Error("INTERFACE ERROR CHECK"); }
	
	if(prefix == NULL) { Error ("INTERFACE ERROR CHECK"); }
}

static char *Interface_Resolve_FuncName(const char *ifunc,
                                        const char *append,
                                        const enum interfaceAppendType_t type) {
	if((strlen(append) + strlen(ifunc)) >= INTERFACE_MAX_NAME_FUNC_IMPL) {
		Error("INTERFACE ERROR FUNCTION NAME");
	}
	
	static char funcImpl[INTERFACE_MAX_NAME_FUNC_IMPL]; // recebe o nome da função que será chamada
	
	// constroi o nome da função que será chamada
	if(type == Prefix) {
		sprintf(funcImpl, "%s%s", append, ifunc);
	} else if (type == Posfix) {
		sprintf(funcImpl, "%s%s", ifunc, append);
	} else {
		Error("INTERFACE ERROR FUNCTION NAME");
	}
	
	return funcImpl;
}

static void Interface_Resolve_Func_Addr(void *interface, 	// insert the functions in interface
                                        const interfaceConfig_t config,
                                        const char *append,
                                        const enum interfaceAppendType_t type) {
	void *handle = dlopen(NULL, RTLD_LAZY);
  if (!handle) {
  	fprintf(stderr, "INTERFACE ERROR CALL: function:%s | line: %d\n Error dlopen: \"%s\"\n", __func__, __LINE__, dlerror());
    abort();
  }
  dlerror(); /* Clear any existing error */
  
	for(int i=0; i < config.numFunc; ++i) { // insere as funções na interface
		char *funcImpl = Interface_Resolve_FuncName(config.func[i], append, type);
		
		void *func = dlsym(handle, funcImpl); // recebe o endereço da função
		char *error = dlerror(); // get error if occurred
		if (error != NULL)  {
			fprintf(stderr, "INTERFACE ERROR CALL: function:%s | line: %d\n Error dlsym: \"%s\"\n",
  			__func__, __LINE__, error);
			abort();
  	}
  	  	
		void **addr = interface + (size_t)(config.addr[i+1] - config.addr[0]); // calcula o endereço onde a função deve estar na estrutura da interface
		*addr = func; // insere a função no lugar onde ela deve estar na estrutura da interface
	}
	
	dlclose(handle); // finaliza o handle
}

///////////////////////////////////////////////////////////////////////////////
// construct
///////////////////////////////////////////////////////////////////////////////
void *Interface_New(const interfaceConfig_t config,
                    const char *prefix,
                    const void *classImpl) {
	
	Interface_Check_Args(config, classImpl, prefix);
	
	void *interface = MM_Malloc(config._sizeof);
	if(interface == NULL) {
		Error("INTERFACE ERROR CREATE");
	}
	
	Interface_Resolve_Func_Addr(interface, config, prefix, Prefix);
	void **interface_classImpl = interface;
	*interface_classImpl = (void*)classImpl;
	
	return interface;
}

void *Interface_New_Posfix(const interfaceConfig_t config,
						   const char *posfix,
                    	   const void *classImpl) {
	Interface_Check_Args(config, classImpl, posfix);
	
	void *interface = MM_Malloc(config._sizeof);
	if(interface == NULL) {
		Error("INTERFACE ERROR CREATE");
	}
	
	Interface_Resolve_Func_Addr(interface, config, posfix, Posfix);
	void **interface_classImpl = interface;
	*interface_classImpl = (void*)classImpl;
	
	return interface;
}
  

  


///////////////////////////////////////////////////////////////////////////////
// public functions
///////////////////////////////////////////////////////////////////////////////






























