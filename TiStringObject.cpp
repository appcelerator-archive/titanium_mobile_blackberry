/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiStringObject.h"

#include "TiGenericFunctionObject.h"
#include "TiMessageStrings.h"
#include <QDate>
#include <QLocale>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QTime>

// Prototypes
static QString formatInt(QString s, Local<Value> arg);
static QString formatUInt(QString s, Local<Value> arg);
static QString formatDouble(QString s, Local<Value> arg);
static QString formatString(QString s, Local<Value> arg);
static QString formatPointer(QString s, Local<Value> arg);

static const char* DATE_FORMAT_SHORT       = "short";
static const char* DATE_FORMAT_MEDIUM      = "medium";
static const char* DATE_FORMAT_LONG        = "long";

TiStringObject::TiStringObject(NativeObjectFactory* objectFactory)
    : TiObject("String")
{
    objectFactory_ = objectFactory;
}

TiStringObject::~TiStringObject()
{
}

void TiStringObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiStringObject* obj = new TiStringObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiStringObject::onCreateStaticMembers()
{
    TiGenericFunctionObject::addGenericFunctionToParent(this, "format", this, _format);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatCurrency", this, _formatCurrency);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatDate", this, _formatDate);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatDecimal", this, _formatDecimal);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "formatTime", this, _formatTime);
}

bool TiStringObject::canAddMembers() const
{
    return false;
}

Handle<Value> TiStringObject::_format(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1 || !args[0]->IsString())   // TODO: support StringObject
    {
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_string));
        return Undefined();
    }

    const String::Utf8Value utf8(args[0]);
    QString str = QString::fromUtf8(*utf8);
    QRegExp rx("%.*([diouxXfFeEgGaAcspCSn%])");
    rx.setMinimal(true);
    QString res;
    QTextStream ts(&res);
    int start = 0, end = 0, i = 0;

    while ((end = rx.indexIn(str, end)) != -1 && ++i < args.Length())
    {
        end += rx.matchedLength();
        switch (rx.cap(1).at(0).toAscii())
        {
            /* Specifiers that don't take an argument */
        case '%':
            --i;
            continue;

            /* %n: doesn't make sense in the JS context */
        case 'n':
            /* rewind end and remove the token from the format string, ignore the associated arg */
            end -= rx.matchedLength();
            str.remove(end, rx.matchedLength());
            continue;

            /* Signed int */
        case 'd':
        case 'i':
        case 'c':
        case 'C':       // same as %lc
            ts << formatInt(str.mid(start, end - start), args[i]);
            break;

            /* Unsigned int */
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            ts << formatUInt(str.mid(start, end - start), args[i]);
            break;

            /* Double */
        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'a':
        case 'A':
            ts << formatDouble(str.mid(start, end - start), args[i]);
            break;

            /* String */
        case 's':
        case 'S':       // same as %ls
            ts << formatString(str.mid(start, end - start), args[i]);
            break;

            /* Pointer */
        case 'p':
            ts << formatPointer(str.mid(start, end - start), args[i]);
            break;

        default:
            ThrowException(String::New(Ti::Msg::INTERNAL__An_error_occurred_while_parsing_the_format_string));
            break;
        }
        start = end;
    }
    ts << str.sprintf(str.mid(start).toLatin1().constData());
    // Warning str contains the result of the sprintf call at this point

    Handle<String> result = String::New(res.toUtf8());
    return (result);
}

Handle<Value> TiStringObject::_formatCurrency(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1 || (!args[0]->IsNumber() && !args[0]->IsNumberObject()))
    {
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_integer));
        return Undefined();
    }

    Handle<Number> num = Handle<Number>::Cast(args[0]);
    QString strRes = QLocale().toCurrencyString(num->Value());

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> TiStringObject::_formatDate(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1 || !args[0]->IsDate() || !args[0]->IsObject())
    {
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_date));
        return Undefined();
    }

    Local<Value> value = args[0];
    unsigned int year = 0, month = 0, day = 0;

    Local<Object> obj = Object::Cast(*value);
    // Get year property
    Local<Value> getYear_prop = (obj->Get(String::New("getFullYear")));
    if (getYear_prop->IsFunction())
    {
        Local<Function> getYear_func = Function::Cast(*getYear_prop);
        Local<Value> yearValue = getYear_func->Call(obj, 0, NULL);
        year = yearValue->NumberValue();
    }
    // Get month property
    Local<Value> getMonth_prop = (obj->Get(String::New("getMonth")));
    if (getMonth_prop->IsFunction())
    {
        Local<Function> getMonth_func = Function::Cast(*getMonth_prop);
        Local<Value> monthValue = getMonth_func->Call(obj, 0, NULL);
        month = monthValue->NumberValue();
    }
    // Get day property
    Local<Value> getDay_prop = (obj->Get(String::New("getDate")));
    if (getDay_prop->IsFunction())
    {
        Local<Function> getDay_func = Function::Cast(*getDay_prop);
        Local<Value> dayValue = getDay_func->Call(obj, 0, NULL);
        day = dayValue->NumberValue();
    }

    // Defaults to NarrowFormat
    QLocale::FormatType fType = QLocale::NarrowFormat;

    // Try to parse optional format argument
    if (args.Length() == 2 && (args[1]->IsString() || args[1]->IsStringObject()))
    {
        const String::Utf8Value utf8(args[1]);
        QString strFormat = QString::fromUtf8(*utf8);
        if (strFormat.compare(DATE_FORMAT_MEDIUM) == 0)
        {
            fType = QLocale::ShortFormat;
        }
        else if (strFormat.compare(DATE_FORMAT_LONG) == 0)
        {
            fType = QLocale::LongFormat;
        }
        else
        {
            fType = QLocale::NarrowFormat;
        }
    }

    // Adding +1 to month, since it starting from 0
    QDate date(year, month + 1, day);
    QString strRes = QLocale().toString(date, fType);

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> TiStringObject::_formatDecimal(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1 || (!args[0]->IsNumber() && !args[0]->IsNumberObject()))
    {
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_integer));
        return Undefined();
    }

    Handle<Number> num = Handle<Number>::Cast(args[0]);
    QString strRes = QLocale().toString(num->Value());

    // TODO: parse optional parameters: locale & pattern
    // See: http://docs.appcelerator.com/titanium/2.0/index.html#!/api/Global.String

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> TiStringObject::_formatTime(void* userContext, TiObject* caller, const Arguments& args)
{
    if (args.Length() < 1 || !args[0]->IsDate() || !args[0]->IsObject())
    {
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_date));
        return Undefined();
    }

    Local<Value> value = args[0];
    int hours = 0, minutes = 0, seconds = 0, msecs = 0;

    Local<Object> obj = Object::Cast(*value);
    // Get hours property
    Local<Value> getHours_prop = (obj->Get(String::New("getHours")));
    if (getHours_prop->IsFunction())
    {
        Local<Function> getHours_func = Function::Cast(*getHours_prop);
        Local<Value> hoursValue = getHours_func->Call(obj, 0, NULL);
        hours = hoursValue->NumberValue();
    }
    // Get minute property
    Local<Value> getMinutes_prop = (obj->Get(String::New("getMinutes")));
    if (getMinutes_prop->IsFunction())
    {
        Local<Function> getMinutes_func = Function::Cast(*getMinutes_prop);
        Local<Value> minutesValue = getMinutes_func->Call(obj, 0, NULL);
        minutes = minutesValue->NumberValue();
    }
    // Get seconds property
    Local<Value> getSeconds_prop = (obj->Get(String::New("getSeconds")));
    if (getSeconds_prop->IsFunction())
    {
        Local<Function> getSeconds_func = Function::Cast(*getSeconds_prop);
        Local<Value> secondsValue = getSeconds_func->Call(obj, 0, NULL);
        seconds = secondsValue->NumberValue();
    }
    // Get milliseconds property
    Local<Value> getMsecs_prop = (obj->Get(String::New("getMilliseconds")));
    if (getMsecs_prop->IsFunction())
    {
        Local<Function> getMsecs_func = Function::Cast(*getMsecs_prop);
        Local<Value> msecsValue = getMsecs_func->Call(obj, 0, NULL);
        msecs = msecsValue->NumberValue();
    }

    // Defaults to NarrowFormat
    QLocale::FormatType fType = QLocale::NarrowFormat;

    // Try to parse optional format argument
    if (args.Length() == 2 && (args[1]->IsString() || args[1]->IsStringObject()))
    {
        const String::Utf8Value utf8(args[1]);
        QString strFormat = QString::fromUtf8(*utf8);
        if (strFormat.compare(DATE_FORMAT_MEDIUM) == 0)
        {
            fType = QLocale::ShortFormat;
        }
        else if (strFormat.compare(DATE_FORMAT_LONG) == 0)
        {
            fType = QLocale::LongFormat;
        }
        else
        {
            fType = QLocale::NarrowFormat;
        }
    }

    QTime time = QTime(hours, minutes, seconds, msecs);
    QString strRes = QLocale().toString(time, fType);

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}


/* Static Helpers */

static QString formatInt(QString s, Local<Value> arg)
{
    if (arg->IsNumber())
    {
        if (s.endsWith('C'))
        {
            // QString::sprintf doesn't support %C
            s.replace(s.size() - 1, 1, "lc");
        }
        if (s.right(3).startsWith("ll"))
        {
            int64_t v = arg->IntegerValue();
            return s.sprintf(s.toLatin1().constData(), v);
        }
        int v = arg->Int32Value();
        return s.sprintf(s.toLatin1().constData(), v);
    }
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_integer));
    return QString();
}

static QString formatUInt(QString s, Local<Value> arg)
{
    if (arg->IsNumber())
    {
        if (s.right(3).startsWith("ll"))
        {
            int64_t v = arg->IntegerValue();
            return s.sprintf(s.toLatin1().constData(), v);
        }
        unsigned int v = arg->Uint32Value();
        return s.sprintf(s.toLatin1().constData(), v);
    }
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_unsigned_integer));
    return QString();
}

static QString formatDouble(QString s, Local<Value> arg)
{
    if (arg->IsNumber())
    {
        if (s.right(2).startsWith('L'))
        {
            // cast to long double to match the specifier although V8 only has double precision
            long double v = static_cast<long double>(arg->NumberValue());
            return s.sprintf(s.toLatin1().constData(), v);
        }
        double v = arg->NumberValue();
        return s.sprintf(s.toLatin1().constData(), v);
    }
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_double));
    return QString();
}

static QString formatString(QString s, Local<Value> arg)
{
    if (s.endsWith('S'))
    {
        // QString::sprintf doesn't support %S
        s.replace(s.size() - 1, 1, "ls");
    }
    bool longChar = s.endsWith("ls");

    if (arg->IsString())
    {
        if (longChar)
        {
            String::Value utf16(arg);
            return s.sprintf(s.toLatin1().constData(), *utf16);
        }
        else
        {
            String::Utf8Value utf8(arg);
            return s.sprintf(s.toLatin1().constData(), *utf8);
        }
    }
    else if (arg->IsStringObject())
    {
        printf("\t%s (%d): NYI arg is StringObject\n", __FUNCTION__, __LINE__);
    }
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_string));
    return QString();
}

static QString formatPointer(QString s, Local<Value> arg)
{
    if (arg->IsObject() && s.endsWith('p'))
    {
        s.replace(s.size() - 1, 1, "i");
        return s.sprintf(s.toLatin1().constData(), arg->ToObject()->GetIdentityHash());
    }
    else if (arg->IsExternal())
    {
        return s.sprintf(s.toLatin1().constData(), External::Unwrap(arg));
    }
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_object_or_external));
    return QString();
}
