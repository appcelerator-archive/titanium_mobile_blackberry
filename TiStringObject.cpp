/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiStringObject.h"

#include "TiGenericFunctionObject.h"
#include "TiMessageStrings.h"
#include <QRegExp>
#include <QString>
#include <QTextStream>

// Prototypes
static QString formatInt(QString s, Local<Value> arg);
static QString formatUInt(QString s, Local<Value> arg);
static QString formatDouble(QString s, Local<Value> arg);
static QString formatString(QString s, Local<Value> arg);
static QString formatPointer(QString s, Local<Value> arg);


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
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatDate(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatDecimal(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
    return Undefined();
}

Handle<Value> TiStringObject::_formatTime(void* userContext, TiObject* caller, const Arguments& args)
{
    // TODO: Implement
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
