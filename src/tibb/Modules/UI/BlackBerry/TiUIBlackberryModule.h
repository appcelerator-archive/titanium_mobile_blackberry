/**
 * TiUIBlackberry.h
 *
 *
 */

#ifndef NATIVE_TiUIBlackberry_MODULE
#define NATIVE_TiUIBlackberry_MODULE

#include "TiCore.h"

namespace TiUI
{
    enum KeyboardType {
        KEYBOARD_TYPE_DEFAULT,
        KEYBOARD_TYPE_ASCII,
        KEYBOARD_TYPE_EMAIL,
        KEYBOARD_TYPE_NAMEPHONE_PAD,
        KEYBOARD_TYPE_NUMBERS_PUNCTUATION,
        KEYBOARD_TYPE_PHONE_PAD,
        KEYBOARD_TYPE_URL,
        KEYBOARD_TYPE_CHAT
    };
};

class TiUIBlackberryModule : public Ti::TiModule
{
public:
	CREATE_MODULE(TiUIBlackberryModule);
	TiUIBlackberryModule(const char*);
	virtual ~TiUIBlackberryModule();

	virtual Ti::TiValue getModuleId();
	virtual Ti::TiValue getModuleVersion();
	virtual Ti::TiValue getModuleName();
};

#endif
