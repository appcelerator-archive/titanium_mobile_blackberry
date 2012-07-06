/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeStringInterface.h"

#include "NativeMessageStrings.h"
#include "TiMessageStrings.h"
#include <QDate>
#include <QLocale>
#include <QRegExp>
#include <QString>
#include <QTextStream>
#include <QTime>

using namespace v8;

// Prototypes
static QString formatInt(QString s, Local<Value> arg);
static QString formatUInt(QString s, Local<Value> arg);
static QString formatDouble(QString s, Local<Value> arg);
static QString formatString(QString s, Local<Value> arg);
static QString formatPointer(QString s, Local<Value> arg);
static QLocale::FormatType parseFormat(Local<Value> format);

static const char* DATE_FORMAT_SHORT       = "short";
static const char* DATE_FORMAT_MEDIUM      = "medium";
static const char* DATE_FORMAT_LONG        = "long";

static NativeStringInterface* s_theInstance = NULL;

const NativeStringInterface* NativeStringInterface::instance()
{
    if (s_theInstance == NULL)
    {
        s_theInstance = new NativeStringInterface;
    }
    return s_theInstance;
}

Handle<Value> NativeStringInterface::format(const Arguments& args)
{
    if (args.Length() < 1)
    {
        ThrowException(String::New(Native::Msg::Expected_argument_of_type_string));
        return Undefined();
    }

    Local<Value> format = args[0]->ToString();

    const String::Utf8Value utf8(format);
    QString str = QString::fromUtf8(*utf8);
    /* Define a regex to match the % tokens of the format string
     *    cap(0): the whole matched token
     *    cap(1): the 'n$' token if present (numbered args)
     *    cap(2): the 'n' token from the above 'n$' token
     *    cap(3): the specifier char
     */
    QRegExp rx("%((\\d+)\\$)?.*([diouxXfFeEgGaAcspCSn%])");
    rx.setMinimal(true);
    QString res;
    QTextStream ts(&res);
    int start = 0, end = 0, i = 0;

    while ((end = rx.indexIn(str, end)) != -1 && ++i < args.Length())
    {
        end += rx.matchedLength();
        QString tmp = str.mid(start, end - start);
        int argN = i;

        /* Look for numbered argument */
        if (!rx.cap(2).isEmpty())
        {
            bool ok;
            argN = rx.cap(2).toInt(&ok);
            if (!ok)
            {
                ThrowException(String::New(Native::Msg::An_error_occurred_converting_to_int));
                return Undefined();
            }
            if (argN >= args.Length() || argN <= 0)
            {
                ThrowException(String::New(Native::Msg::Numbered_argument_exceeds_the_length_of_provided_arguments));
                return Undefined();
            }

            /* Remove the 'n$' token from the string as qt doesn't do numbered args */
            tmp.remove(rx.cap(1));
            /* Don't consume an argument as with numbered args there can be less args than placeholders
               due to args being allowed to be used more than once */
            --i;
        }

        switch (rx.cap(3).at(0).toAscii())
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
            ts << formatInt(tmp, args[argN]);
            break;

            /* Unsigned int */
        case 'o':
        case 'u':
        case 'x':
        case 'X':
            ts << formatUInt(tmp, args[argN]);
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
            ts << formatDouble(tmp, args[argN]);
            break;

            /* String */
        case 's':
        case 'S':       // same as %ls
            ts << formatString(tmp, args[argN]);
            break;

            /* Pointer */
        case 'p':
            ts << formatPointer(tmp, args[argN]);
            break;

        default:
            ThrowException(String::New(Native::Msg::INTERNAL__An_error_occurred_while_parsing_the_format_string));
            break;
        }
        start = end;
    }
    ts << str.sprintf(str.mid(start).toLatin1().constData());
    // Warning str contains the result of the sprintf call at this point

    Handle<String> result = String::New(res.toUtf8());
    return (result);
}

Handle<Value> NativeStringInterface::formatCurrency(const Arguments& args)
{
    if (args.Length() < 1 || (!args[0]->IsNumber() && !args[0]->IsNumberObject()))
    {
        ThrowException(String::New(Native::Msg::Expected_argument_of_type_integer));
        return Undefined();
    }

    Handle<Number> num = Handle<Number>::Cast(args[0]);
    QString strRes = QLocale().toCurrencyString(num->Value());

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> NativeStringInterface::formatDate(const Arguments& args)
{
    // TODO: Revisit format part when R6 available
    if (args.Length() < 1 || !args[0]->IsDate())
    {
        ThrowException(String::New(Native::Msg::Expected_argument_of_type_date));
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
    if (args.Length() > 1)
    {
        fType = parseFormat(args[1]);
    }

    // Adding +1 to month, since it starting from 0
    QDate date(year, month + 1, day);
    QString strRes = QLocale().toString(date, fType);

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> NativeStringInterface::formatDecimal(const Arguments& args)
{
    if (args.Length() < 1 || (!args[0]->IsNumber() && !args[0]->IsNumberObject()))
    {
        ThrowException(String::New(Native::Msg::Expected_argument_of_type_integer));
        return Undefined();
    }

    Handle<Number> num = Handle<Number>::Cast(args[0]);
    QString strRes = QLocale().toString(num->Value());

    // TODO: parse optional parameters: locale & pattern

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}

Handle<Value> NativeStringInterface::formatTime(const Arguments& args)
{
    // TODO: Revisit format part when R6 available
    if (args.Length() < 1 || !args[0]->IsDate())
    {
        ThrowException(String::New(Native::Msg::Expected_argument_of_type_date));
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
    if (args.Length() > 1)
    {
        fType = parseFormat(args[1]);
    }

    QTime time = QTime(hours, minutes, seconds, msecs);
    QString strRes = QLocale().toString(time, fType);

    Handle<String> result = String::New(strRes.toUtf8());
    return (result);
}


/* Static Helpers */

static QString formatInt(QString s, Local<Value> arg)
{
    if (arg->IsNumber() || arg->IsNumberObject())
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
    ThrowException(String::New(Native::Msg::Expected_argument_of_type_integer));
    return QString();
}

static QString formatUInt(QString s, Local<Value> arg)
{
    if (arg->IsNumber() || arg->IsNumberObject())
    {
        if (s.right(3).startsWith("ll"))
        {
            int64_t v = arg->IntegerValue();
            return s.sprintf(s.toLatin1().constData(), v);
        }
        unsigned int v = arg->Uint32Value();
        return s.sprintf(s.toLatin1().constData(), v);
    }
    ThrowException(String::New(Native::Msg::Expected_argument_of_type_unsigned_integer));
    return QString();
}

static QString formatDouble(QString s, Local<Value> arg)
{
    if (arg->IsNumber() || arg->IsNumberObject())
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
    ThrowException(String::New(Native::Msg::Expected_argument_of_type_double));
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

    arg = arg->ToString();
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
    ThrowException(String::New(Native::Msg::Expected_argument_of_type_object_or_external));
    return QString();
}

static QLocale::FormatType parseFormat(Local<Value> format)
{
    QLocale::FormatType fType = QLocale::NarrowFormat;
    if (!format->IsString())
    {
        format = format->ToString();
    }

    const String::Utf8Value utf8(format);
    QString strFormat = QString::fromUtf8(*utf8);
    if (strFormat.compare(DATE_FORMAT_MEDIUM) == 0)
    {
        fType = QLocale::ShortFormat;
    }
    else if (strFormat.compare(DATE_FORMAT_LONG) == 0)
    {
        fType = QLocale::LongFormat;
    }

    return fType;
}
