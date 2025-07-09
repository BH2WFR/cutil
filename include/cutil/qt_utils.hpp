/* UTF-8 encoding
* Project URL: https://github.com/BH2WFR/cutil
  Author:		BH2WFR
  Updated:		2 JAN 2025
  License:		MIT License
* You can include this header in header files.
*/
#ifndef CUTIL_QT_UTILS_HPP__
#define CUTIL_QT_UTILS_HPP__
#include <cutil/base.h>
#include <cutil/cpp_base.hpp>

#ifndef CUTIL_CPP14_SUPPORTED
	#error ">= C++14 is required"
#endif


//* ATTENTION: Include Qt Headers previously!
#if defined(__cplusplus) && defined(CUTIL_CPP14_SUPPORTED) && defined(QT_VERSION) //* Qt

// 宏 QT_CORE_LIB, 只要链接了 Qt 库, 都会定义, 不在这里使用, 因为会导致未包含 Qt 头文件时报错
_CUTIL_NAMESPACE_BEGIN
namespace qt{


//===================== Qt Utils ==========================

//* Qt5 high DPI support since Qt5.6, and fractional scaling support since Qt5.14
//  in Qt6, high DPI and fractional scaling support is enabled by default and no need for this macro.
//  pls #include<QApplication> first before #include of this header.
#if ((QT_VERSION >= QT_VERSION_CHECK(5,6,0)) && (QT_VERSION < QT_VERSION_CHECK(5,14,0)))
	#define CUTIL_QT5_HIGH_DPI() 	do { \
			QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
			QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);	 \
		} while(0)
		
#elif ((QT_VERSION >= QT_VERSION_CHECK(5,14,0)) && (QT_VERSION < QT_VERSION_CHECK(6,0,0)))
	#define CUTIL_QT5_HIGH_DPI()	do { \
			QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); \
			QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps); 	 \
			QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough); \
		} while(0)
		
#else // QT_VERSION ( >= 6.0.0 || <= 5.5.0 )
	#define CUTIL_QT5_HIGH_DPI()
	
#endif // QT_VERSION

inline _CUTIL_FUNC_STATIC void set_qt5_high_dpi()
{
	CUTIL_QT5_HIGH_DPI();
}


//* Set QTextCodec default encoding to UTF-8,
//  or cannot correctly print chinese characters via qDebug() if code is saved in UTF-8 encoding;
//  pls #include<QTextCodec> first before #include of this header.
//  in MSVC Compiler, compiler argument "/utf-8" is required if code is saved in UTF-8 encoding;
//  	in CMake, you should add "set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")"
//  In Qt6, QTextCodec module is deleted and contained in Qt5 Compatibility Module.
#if defined(QTEXTCODEC_H)
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)	QTextCodec::setCodecForLocale(QTextCodec::codecForName(_STR))
#else //. !QTEXTCODEC_H
	#define CUTIL_QT5_TEXTCODEC_SET(_STR)
#endif // QTEXTCODEC_H

#define CUTIL_QT5_TEXTCODEC_UTF8()		CUTIL_QT5_TEXTCODEC_SET("UTF-8")
#define CUTIL_QT5_TEXTCODEC_GBK()		CUTIL_QT5_TEXTCODEC_SET("GB18030")
#define CUTIL_QT5_TEXTCODEC_BIG5()		CUTIL_QT5_TEXTCODEC_SET("Big5")
#define CUTIL_QT5_TEXTCODEC_EUCKR()		CUTIL_QT5_TEXTCODEC_SET("EUC-KR")
#define CUTIL_QT5_TEXTCODEC_EUCJP()		CUTIL_QT5_TEXTCODEC_SET("EUC-JP")
#define CUTIL_QT5_TEXTCODEC_JIS()		CUTIL_QT5_TEXTCODEC_SET("Shift-JIS")

inline _CUTIL_FUNC_STATIC void set_qt5_textcodec(const std::string& codecName)
{
#if defined(QTEXTCODEC_H)
	QTextCodec::setCodecForLocale(QTextCodec::codecForName(codecName.c_str()));
#endif
}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_utf8() 	{::cutil::qt::set_qt5_textcodec("UTF-8");}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_gbk() 		{::cutil::qt::set_qt5_textcodec("GB18030");}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_big5() 	{::cutil::qt::set_qt5_textcodec("Big5");}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_euckr() 	{::cutil::qt::set_qt5_textcodec("EUC-KR");}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_eucjp() 	{::cutil::qt::set_qt5_textcodec("EUC-JP");}
inline _CUTIL_FUNC_STATIC void set_qt5_textcodec_jis() 		{::cutil::qt::set_qt5_textcodec("Shift-JIS");}



//* qDebug() without spaces or quotes
//  pls #include<QDebug> first before this header #include
#ifdef QDEBUG_H
	#define CUTIL_QDEBUG_N  qDebug().noquote() 		  	 // qDebug() without quotes
	#define CUTIL_QDEBUG_NN qDebug().nospace().noquote() // qDebug() without spaces and quotes
		// example: CUTIL_QDEBUG_N << "test" << 1;
	
#endif

/*
* example:
	#include <qglobal.h>
	#include <QApplication>
	#include <QDebug>
	#include <QTextCodec> // include Qt headers first
	
	#include <cutil/console_utils.h> // <QtUtil.h> has been wrapped in this header.
	
	int main(int argc, char* argv[])
	{
		CUTIL_QT5_HIGH_DPI(); 	  	//* enable Qt5 high DPI support
		
		CUTIL_CHCP_ENCODING_UTF8();
		CUTIL_QT5_TEXTCODEC_UTF8(); //* set Qt default text encoding to UTF-8
		
		QApplication app(argc, argv); // you must create QCoreApplication after these macros.
		
		return app.exec();
	}
*/


//* get all Items in the TreeModel
template<typename TreeModel_t, typename Item_t>
static inline auto get_treemodel_item_iter(const TreeModel_t* model) -> std::vector<Item_t>
{
	if(model == nullptr){
		return {};
	}
	std::vector<Item_t> items;
	items.reserve(model->rowCount());
	std::function<void(Item_t*)> traverse = [&](Item_t* item){
		if(item == nullptr){
			return;
		}
		items.push_back(item);
		for(int i = 0; i < item->childCount(); ++i){
			traverse(item->childAt(i));
		}
	};
	traverse(model->rootItem());
	return items;
}





} // namespace qt
_CUTIL_NAMESPACE_END
#endif // QT_VERSION
#endif // CUTIL_QT_UTILS_HPP__
