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

using namespace v8;

namespace titanium {

void DisplayExceptionLine (TryCatch &try_catch) {
  // Prevent re-entry into this function.
  static bool displayed_error = false;

  if (displayed_error) return;
  displayed_error = true;

  HandleScope scope;

  Handle<Message> message = try_catch.Message();

  fprintf(stderr, "\n");

  if (!message.IsEmpty()) {
    // Print (filename):(line number): (message).
    String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = *filename;
    int linenum = message->GetLineNumber();
    fprintf(stderr, "%s:%i\n", filename_string, linenum);
    // Print line of source code.
    String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = *sourceline;

    int start = message->GetStartColumn();
    int end = message->GetEndColumn();

    // fprintf(stderr, "---\nsourceline:%s\noffset:%d\nstart:%d\nend:%d\n---\n", sourceline_string, start, end);

    fprintf(stderr, "%s\n", sourceline_string);
    // Print wavy underline (GetUnderline is deprecated).
    for (int i = 0; i < start; i++) {
      fputc((sourceline_string[i] == '\t') ? '\t' : ' ', stderr);
    }
    for (int i = start; i < end; i++) {
      fputc('^', stderr);
    }
    fputc('\n', stderr);
  }
}

void ReportException(TryCatch &try_catch, bool show_line) {
  HandleScope scope;

  if (show_line) DisplayExceptionLine(try_catch);

  String::Utf8Value trace(try_catch.StackTrace());

  // range errors have a trace member set to undefined
  if (trace.length() > 0 && !try_catch.StackTrace()->IsUndefined()) {
    fprintf(stderr, "%s\n", *trace);
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
    }

    String::Utf8Value msg(!isErrorObject ? er
                         : er->ToObject()->Get(String::New("message")));
    fprintf(stderr, "%s\n", *msg);
  }

  fflush(stderr);
}

QString V8StringToQString(Handle<String> v8Str) {
    QString qStr;
    qStr.resize(v8Str->Length());
    v8Str->Write(reinterpret_cast<uint16_t*>(qStr.data()));
    return qStr;
}

}  // namespace titanium

