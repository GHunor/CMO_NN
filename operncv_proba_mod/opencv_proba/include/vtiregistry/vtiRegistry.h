
#ifndef __vtiRegistry_h
#define __vtiRegistry_h

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VH_REGISTRY_DLL__
#define VH_REG_DLL_EXPORT __declspec(dllexport)
#else
#define VH_REG_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VH_REG_DLL_EXPORT

#endif

#include "vtiRegistryKey.h"
#include "vtiRegistryValue.h"
#include <stdio.h>
#include "FlexLexer.h"
#include "vtiRegistryFileError.h"
#define MAX_PATH          260
#define VTI_REGISTRY_FILE "registry.vrg"

class vtiRegistry
{
	static char	 *ROOT_NAME;
	static char	 *REGISTRY_VERSION_STRING;

	public:
		VH_REG_DLL_EXPORT vtiRegistry();
		VH_REG_DLL_EXPORT virtual ~vtiRegistry();

		VH_REG_DLL_EXPORT vtiRegistryKey  *getRoot() const;
		virtual void	initialize(bool bCreate = false);
		bool			createRoot();
		void			applyChanges();
	//	void			commit();
		void			create();

	private:
		vtiRegistryKey  *m_root;

		bool			m_allowSave;
		yyFlexLexer		*m_lexer;
   
		void			load();
		void			loadKey(vtiRegistryKey *key);
		void			loadValue(vtiRegistryValue *val);

		void			save();
		void			save(vtiRegistryKey *key, FILE *ofile, int indentLevel) const;
		void			save(vtiRegistryValue *val, FILE *ofile, int indentLevel) const;

		void			getRegFileName(char * inout_filename) const;

		enum			{ INDENT_SIZE = 4 };
		
		void			indent(FILE *ofile, int indentLevel) const;
};

#endif
