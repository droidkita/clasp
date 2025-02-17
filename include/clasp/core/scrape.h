
/**
 * \defgroup DEFUN Functions that are exposed to Clasp Common Lisp
 */

/**
 * \defgroup DEFUN-SETF Setf functions that are exposed to Clasp Common Lisp
 */

/**
 * \defgroup DEFMETHOD C++ methods that are exposed to Clasp Common Lisp
 */

#define DOCGROUP(...)

#ifdef SCRAPING
#define BEGIN_TAG BEGIN_TAG_bfc54f90bafadf5
#define END_TAG END_TAG_bfc54f90bafadf5
#define GC_MANAGED_TYPE(...) BEGIN_TAG GC_MANAGED_TYPE_TAG ( :FILE __FILE__ :LINE __LINE__ :TYPE #__VA_ARGS__ )
#define CL_BEGIN_ENUM(type,symbol,desc) BEGIN_TAG CL_BEGIN_ENUM_TAG ( :FILE __FILE__ :LINE __LINE__ :TYPE #type :SYMBOL #symbol :DESCRIPTION desc )
#define CL_VALUE_ENUM(symbol,value) BEGIN_TAG CL_VALUE_ENUM_TAG ( :FILE __FILE__ :LINE __LINE__ :SYMBOL #symbol :VALUE #value )
#define CL_END_ENUM(symbol) BEGIN_TAG CL_END_ENUM_TAG ( :FILE __FILE__ :LINE __LINE__ :SYMBOL #symbol )
#define CL_NAME(...) BEGIN_TAG CL_NAME_TAG ( :FILE __FILE__ :LINE __LINE__ :CL-NAME #__VA_ARGS__ )
#define CL_LISPIFY_NAME(...) BEGIN_TAG CL_LISPIFY_NAME_TAG ( :FILE __FILE__ :LINE __LINE__ :CL-NAME #__VA_ARGS__ )
#define CL_PKG_NAME(pkg,name) BEGIN_TAG CL_PKG_NAME_TAG ( :FILE __FILE__ :LINE __LINE__ :CL-PKG #pkg :CL-NAME #name )
#define CL_LAMBDA(...) BEGIN_TAG CL_LAMBDA_TAG ( :FILE __FILE__ :LINE __LINE__ :LAMBDA-LIST  #__VA_ARGS__ )
#define CL_DECLARE(...) BEGIN_TAG CL_DECLARE_TAG ( :FILE __FILE__ :LINE __LINE__ :DECLARE #__VA_ARGS__ )
#define CL_DOCSTRING(...) BEGIN_TAG CL_DOCSTRING_TAG ( :FILE __FILE__ :LINE __LINE__ )  __VA_ARGS__ END_TAG
#define CL_DOCSTRING_LONG(...) BEGIN_TAG CL_DOCSTRING_LONG_TAG ( :FILE __FILE__ :LINE __LINE__ )  __VA_ARGS__ END_TAG
#define CL_UNWIND_COOP(...) BEGIN_TAG CL_UNWIND_COOP_TAG ( :FILE __FILE__ :LINE __LINE__ :COOP #__VA_ARGS__ ) END_TAG
#define CL_PRIORITY(...) BEGIN_TAG CL_PRIORITY_TAG ( :FILE __FILE__ :LINE __LINE__ )  __VA_ARGS__ END_TAG
#define CL_PRE_GC_STARTUP BEGIN_TAG CL_PRE_GC_STARTUP_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_INITIALIZER BEGIN_TAG CL_INITIALIZER_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_EXPOSE BEGIN_TAG CL_EXPOSE_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_TERMINATOR BEGIN_TAG CL_TERMINATOR_TAG ( :FILE __FILE__ :LINE __LINE__ )
DOCGROUP(clasp)
#define CL_DEFUN BEGIN_TAG CL_DEFUN_TAG ( :FILE __FILE__ :LINE __LINE__ )
DOCGROUP(clasp)
#define CL_DEFUN_SETF BEGIN_TAG CL_DEFUN_SETF_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_DEFMETHOD BEGIN_TAG CL_DEFMETHOD_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_DEFMETHOD BEGIN_TAG CL_DEFMETHOD_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_METHOD_OVERLOAD
// BEGIN_TAG CL_METHOD_OVERLOAD_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_DEF_CLASS_METHOD BEGIN_TAG CL_DEF_CLASS_METHOD_TAG ( :FILE __FILE__ :LINE __LINE__ )
#define CL_EXTERN_DEFMETHOD(type,pointer) BEGIN_TAG CL_EXTERN_DEFMETHOD_TAG (:FILE __FILE__ :LINE __LINE__ :TYPE #type :POINTER #pointer ) 
#define CL_EXTERN_DEFUN(pointer) BEGIN_TAG CL_EXTERN_DEFUN_TAG (:FILE __FILE__ :LINE __LINE__ :POINTER #pointer ) 
#define SYMBOL_SC_(pkg,name) BEGIN_TAG SYMBOL_INTERNAL ( :FILE __FILE__ :LINE __LINE__ :PACKAGE #pkg :NAME #name )
#define SYMBOL_EXPORT_SC_(pkg,name) BEGIN_TAG SYMBOL_EXTERNAL ( :FILE __FILE__ :LINE __LINE__  :PACKAGE #pkg :NAME #name )
//! Ensure that the symbol is present within the package - acts like CL:SHADOW
#define SYMBOL_SHADOW_EXPORT_SC_(pkg,name) BEGIN_TAG SYMBOL_SHADOW_EXTERNAL ( :FILE __FILE__ :LINE __LINE__  :PACKAGE #pkg :NAME #name )
#define DETAILED_SYMBOL_EXPORT_SC_(pkg,cxxname,name) BEGIN_TAG DETAILED_SYMBOL_EXTERNAL ( :FILE __FILE__ :LINE __LINE__  :PACKAGE #pkg :CXX-NAME #cxxname :NAME name )
#define INTERN_(ns,name) BEGIN_TAG SYMBOL_INTERN ( :FILE __FILE__ :LINE __LINE__ :NAMESPACE #ns :NAME #name )
#define PACKAGE_USE(name_str) BEGIN_TAG PACKAGE_USE_TAG ( :FILE __FILE__ :LINE __LINE__ :NAME name_str)
#define PACKAGE_NICKNAME(name_str) BEGIN_TAG PACKAGE_NICKNAME_TAG ( :FILE __FILE__ :LINE __LINE__ :NAME name_str)
#define PACKAGE_SHADOW(name_str) BEGIN_TAG PACKAGE_SHADOW_TAG ( :FILE __FILE__ :LINE __LINE__ :NAME name_str)
#define NAMESPACE_PACKAGE_ASSOCIATION(ns,pkg,pkgname) BEGIN_TAG NAMESPACE_PACKAGE_ASSOCIATION_TAG ( :FILE __FILE__ :LINE __LINE__ :NAMESPACE #ns :PACKAGE #pkg :PACKAGE-NAME pkgname )
#define LISP_META_CLASS(...) BEGIN_TAG META_CLASS_TAG ( :FILE __FILE__ :LINE __LINE__ :META-CLASS  #__VA_ARGS__ )
#define LISP_CLASS(n,p,c,s,b) BEGIN_TAG LISP_CLASS_TAG ( :FILE __FILE__ :LINE __LINE__ :NAMESPACE #n :PACKAGE #p :CLASS #c :CLASS-SYMBOL s :BASE #b) \
       DETAILED_SYMBOL_EXPORT_SC_(p,c,s)
#define LISP_ABSTRACT_CLASS(n,p,c,s,b) BEGIN_TAG LISP_CLASS_TAG ( :FILE __FILE__ :LINE __LINE__ :NAMESPACE #n :PACKAGE #p :CLASS #c :CLASS-SYMBOL s :BASE #b ) \
       DETAILED_SYMBOL_EXPORT_SC_(p,c,s)
#define LISP_EXTERNAL_CLASS(n,p,l,c,s,b) BEGIN_TAG LISP_EXTERNAL_CLASS_TAG ( :FILE __FILE__ :LINE __LINE__ :NAMESPACE #n :PACKAGE #p :CXXCLASS #l :CLASS #c :CLASS-SYMBOL s :BASE #b ) \
       DETAILED_SYMBOL_EXPORT_SC_(p,c,s)
#else
#define CL_INITIALIZE
DOCGROUP(clasp)
#define CL_DEFUN
DOCGROUP(clasp)
#define CL_DEFUN_SETF
#define CL_DEFMETHOD
#define CL_DEFMETHOD
#define CL_METHOD_OVERLOAD 
#define CL_DEF_CLASS_METHOD
#define CL_BEGIN_ENUM(type,symbol,desc)
#define CL_VALUE_ENUM(symbol,value)
#define CL_END_ENUM(symbol)
#define CL_NAME(...)
#define CL_LISPIFY_NAME(...)
#define CL_PKG_NAME(pkgid,name)
#define CL_LAMBDA(...)
#define CL_DECLARE(...)
#define CL_DOCSTRING(...)
#define CL_DOCSTRING_LONG(...)
#define CL_UNWIND_COOP(...)
#define CL_PRIORITY(...)
#define CL_TYPE(...)
#define CL_EXTERN_DEFMETHOD(type,pointer)
#define CL_EXTERN_DEFUN(pointer)
#define GC_MANAGED_TYPE(...)
#define CL_PRE_GC_STARTUP
#define CL_INITIALIZER
#define CL_EXPOSE
#define CL_TERMINATOR
#define SYMBOL_SC_(pkg,name)
#define SYMBOL_EXPORT_SC_(pkg,name)
#define SYMBOL_SHADOW_EXPORT_SC_(pkg,name)
#define INTERN_(ns,name) (ns::_sym_##name)
#define PACKAGE_USE(name_str)
#define PACKAGE_NICKNAME(name_str)
#define PACKAGE_SHADOW(name_str)
#define NAMESPACE_PACKAGE_ASSOCIATION(x, y, z) \
  static const char* /*std::string*/ y = z;              \
  namespace x {                                \
    static const char* /*std::string*/ CurrentPkg = z;     \
  }
#endif

// Define a translator for the enum
#define CL_ENUM_TRANSLATOR(_sym_,_type_) \
namespace translate { \
template <> struct to_object<_type_> \
{								 \
  typedef	_type_	GivenType;	 \
  static core::T_sp convert(const GivenType& val) \
  {_G(); \
    core::SymbolToEnumConverter_sp converter = _sym_->symbolValue().as<core::SymbolToEnumConverter_O>(); \
    return (converter->symbolForEnum(val)); \
  } \
}; \
template <> \
struct from_object<_type_> \
{								 \
  typedef	_type_ 	ExpectedType; \
  typedef	ExpectedType 	DeclareType; \
  DeclareType _v; \
  from_object(gctools::smart_ptr<core::T_O> o) { \
    core::SymbolToEnumConverter_sp converter = _sym_->symbolValue().as<core::SymbolToEnumConverter_O>(); \
    _v = converter->enumForSymbol<_type_>(o.as<core::Symbol_O>()); \
  } \
}; \
};

