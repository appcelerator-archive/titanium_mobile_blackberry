/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeStringInterface.h"

#include "TiMessageStrings.h"
#include <QRegExp>
#include <QString>
#include <QTextStream>

using namespace v8;

// Prototypes
static QString formatInt(QString s, Local<Value> arg);
static QString formatUInt(QString s, Local<Value> arg);
static QString formatDouble(QString s, Local<Value> arg);
static QString formatString(QString s, Local<Value> arg);
static QString formatPointer(QString s, Local<Value> arg);


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
        ThrowException(String::New(Ti::Msg::Expected_argument_of_type_string));
        return Undefined();
    }

    Local<Value> format = args[0];
    if (!(format->IsString() || format->IsStringObject()))
    {
        format = format->ToString();
    }

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
                ThrowException(String::New(Ti::Msg::An_error_occurred_converting_to_int));
                return Undefined();
            }
            if (argN >= args.Length() || argN <= 0)
            {
                ThrowException(String::New(Ti::Msg::Numbered_argument_exceeds_the_length_of_provided_arguments));
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

Handle<Value> NativeStringInterface::formatCurrency(const Arguments& args)
{
    // TODO: Implement
    Q_UNUSED(args);
    return Undefined();
}

Handle<Value> NativeStringInterface::formatDate(const Arguments& args)
{
    // TODO: Implement
    Q_UNUSED(args);
    return Undefined();
}

Handle<Value> NativeStringInterface::formatDecimal(const Arguments& args)
{
    // TODO: Implement
    Q_UNUSED(args);
    return Undefined();
}

Handle<Value> NativeStringInterface::formatTime(const Arguments& args)
{
    // TODO: Implement
    Q_UNUSED(args);
    return Undefined();
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

    if (!(arg->IsString() || arg->IsStringObject()))
    {
        arg = arg->ToString();
    }
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
    ThrowException(String::New(Ti::Msg::Expected_argument_of_type_object_or_external));
    return QString();
}
