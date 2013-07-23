// Portions of this code have been copied from the Node.js project.
//
// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "V8Utils.h"
#include  <string>

using namespace v8;

namespace titanium {

void DisplayExceptionLine (TryCatch &try_catch, std::string& err_msg) {
  // Prevent re-entry into this function.
  static bool displayed_error = false;

  if (displayed_error) return;
  displayed_error = true;

  HandleScope scope;

  Handle<Message> message = try_catch.Message();

  fprintf(stderr, "\n");
  err_msg = "JavaScript Exception\n\n";

  if (!message.IsEmpty()) {
    // Print (filename):(line number): (message).
    String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = *filename;
    int linenum = message->GetLineNumber();
    fprintf(stderr, "%s:%i\n", filename_string, linenum);
    err_msg += filename_string;
    err_msg += ":";
    char num_conv[10];
    sprintf(num_conv, "%i", linenum);
    err_msg += num_conv;
    err_msg += "\n";
    // Print line of source code.
    String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = *sourceline;

    int start = message->GetStartColumn();
    int end = message->GetEndColumn();

    // fprintf(stderr, "---\nsourceline:%s\noffset:%d\nstart:%d\nend:%d\n---\n", sourceline_string, start, end);

    fprintf(stderr, "%s\n", sourceline_string);
    err_msg += sourceline_string;
    err_msg += "\n";
    // Print wavy underline (GetUnderline is deprecated).
    for (int i = 0; i < start; i++) {
      fputc((sourceline_string[i] == '\t') ? '\t' : ' ', stderr);
    }
    for (int i = start; i < end; i++) {
      fputc('^', stderr);
    }
    fputc('\n', stderr);
    err_msg += "\n";
  }
}

void ReportException(TryCatch &try_catch, bool show_line, std::string& err_msg) {
  HandleScope scope;

  if (show_line) DisplayExceptionLine(try_catch, err_msg);

  String::Utf8Value trace(try_catch.StackTrace());

  // range errors have a trace member set to undefined
  if (trace.length() > 0 && !try_catch.StackTrace()->IsUndefined()) {
    fprintf(stderr, "%s\n", *trace);
    err_msg +=  *trace;
    err_msg +=  "\n";
  } else {
    // this really only happens for RangeErrors, since they're the only
    // kind that won't have all this info in the trace, or when non-Error
    // objects are thrown manually.
    Local<Value> er = try_catch.Exception();
    bool isErrorObject = er->IsObject() &&
      !(er->ToObject()->Get(String::New("message"))->IsUndefined()) &&
      !(er->ToObject()->Get(String::New("name"))->IsUndefined());

    if (isErrorObject) {
      String::Utf8Value name(er->ToObject()->Get(String::New("name")));
      fprintf(stderr, "%s: ", *name);
      err_msg += *name;
      err_msg += ": ";
    }

    String::Utf8Value msg(!isErrorObject ? er
                         : er->ToObject()->Get(String::New("message")));
    fprintf(stderr, "%s\n", *msg);
    err_msg += *msg;
    err_msg += "\n";
  }

  fflush(stderr);
}

QString V8StringToQString(Handle<String> v8Str) {
    QString qStr;
    qStr.resize(v8Str->Length());
    v8Str->Write(reinterpret_cast<uint16_t*>(qStr.data()));
    return qStr;
}

Local<Value> CallV8ObjectProperty(Handle<Object> object,
                                  const char* propertyName,
                                  int argc,
                                  Handle<Value> argv[]) {
    HandleScope scope;

    // Lookup a property by name on the object.
    // If the property is undefined or not a function then
    // return an empty handle to indicate the error.
    Local<Value> property = object->Get(String::NewSymbol(propertyName));
    if (property.IsEmpty() || !property->IsFunction()) {
        return Local<Value>();
    }

    Local<Function> callback = Local<Function>::Cast(property);
    Local<Value> result = callback->Call(object, argc, argv);
    return scope.Close(result);
}

}  // namespace titanium

