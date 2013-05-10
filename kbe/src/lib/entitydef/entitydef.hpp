/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2012 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __ENTITYDEF_H__
#define __ENTITYDEF_H__
#include "cstdkbe/cstdkbe.hpp"
#include "cstdkbe/md5.hpp"
#if KBE_PLATFORM == PLATFORM_WIN32
#pragma warning (disable : 4910)
#pragma warning (disable : 4251)
#endif
// common include
#include "method.hpp"	
#include "property.hpp"
#include "math/math.hpp"
#include "pyscript/scriptobject.hpp"
#include "xmlplus/xmlplus.hpp"	
#include "cstdkbe/smartpointer.hpp"
//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif

namespace KBEngine{

class ScriptDefModule;
typedef SmartPointer<ScriptDefModule> ScriptDefModulePtr;

class EntityDef
{
public:
	typedef std::vector<ScriptDefModulePtr> SCRIPT_MODULES;	
	typedef std::map<std::string, ENTITY_SCRIPT_UID> SCRIPT_MODULE_UID_MAP;	

	EntityDef();
	~EntityDef();
	
	/** 
		初始化
	*/
	static bool initialize(const std::string entitiesPath, 
		std::vector<PyTypeObject*>& scriptBaseTypes, 
		COMPONENT_TYPE loadComponentType);

	static bool finalise(void);

	/** 
		加载相关描述
	*/
	static bool loadAllScriptModule(std::string entitiesPath, 
		std::vector<PyTypeObject*>& scriptBaseTypes);

	static bool loadAllDefDescription(const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	static bool loadDefPropertys(const std::string& moduleName, 
		XmlPlus* xml, 
		TiXmlNode* defPropertyNode, 
		ScriptDefModule* scriptModule);

	static bool loadDefCellMethods(const std::string& moduleName, 
		XmlPlus* xml, 
		TiXmlNode* defMethodNode, 
		ScriptDefModule* scriptModule);

	static bool loadDefBaseMethods(const std::string& moduleName, 
		XmlPlus* xml, 
		TiXmlNode* defMethodNode, 
		ScriptDefModule* scriptModule);

	static bool loadDefClientMethods(const std::string& moduleName, 
		XmlPlus* xml, 
		TiXmlNode* defMethodNode, 
		ScriptDefModule* scriptModule);

	static bool loadInterfaces(const std::string& defFilePath, 
		const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	static bool loadParentClass(const std::string& defFilePath, 
		const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	static bool loadDefInfo(const std::string& defFilePath, 
		const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	static bool loadDetailLevelInfo(const std::string& defFilePath, 
		const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	static bool loadVolatileInfo(const std::string& defFilePath, 
		const std::string& moduleName, 
		XmlPlus* defxml, 
		TiXmlNode* defNode, 
		ScriptDefModule* scriptModule);

	/** 
		是否加载这个脚本模块 
	*/
	static bool isLoadScriptModule(ScriptDefModule* scriptModule);

	/** 
		根据当前组件类别设置是否有cell 或者base 
	*/
	static void setScriptModuleHasComponentEntity(ScriptDefModule* scriptModule, bool has);

	/** 
		检查脚本模块中被定义的方法是否存在 
	*/
	static bool checkDefMethod(ScriptDefModule* scriptModule, PyObject* moduleObj, 
		const std::string& moduleName);
	
	/** 
		通过标记来寻找到对应的脚本模块对象 
	*/
	static ScriptDefModule* findScriptModule(ENTITY_SCRIPT_UID utype);
	static ScriptDefModule* findScriptModule(const char* scriptName);

	static bool installScript(PyObject* mod);
	static bool uninstallScript();

	static const SCRIPT_MODULES& getScriptModules(){ 
		return EntityDef::__scriptModules; 
	}

	static KBE_MD5& md5(){ return __md5; }

	static bool initializeWatcher();
private:
	static SCRIPT_MODULES __scriptModules;										// 所有的扩展脚本模块都存储在这里

	static SCRIPT_MODULE_UID_MAP __scriptTypeMappingUType;						// 脚本类别映射utype

	static COMPONENT_TYPE __loadComponentType;									// 所需关系的组件类别的相关数据		

	static KBE_MD5 __md5;														// defs-md5
};

}

#ifdef CODE_INLINE
#include "entitydef.ipp"
#endif
#endif
