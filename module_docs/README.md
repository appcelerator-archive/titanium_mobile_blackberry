# Extending Titanium BB


## The *TiProxy* class
A TiProxy is a native class exposed to the JS. You will use some helper macros and specific function calls to hook it up with the JS engine. At the same time, you will not work with the JS engine directly.
To create one of these, please take a look at [ExamleProxy.h](ExamleProxy.h) and [ExamleProxy.cpp](ExamleProxy.cpp) for details
### Exposing a setter
To create a setter you will need _four_ main parts:

1. Function declaration in class definition
```void setExampleProperty(Ti::TiValue);```
2. Exposure macro  in class definition ```EXPOSE_SETTER(MyProxy, setExampleProperty)```
3. Hook to the JS engine in class constructor ```createPropertySetter("exampleProperty", _setExampleProperty);```
4. Declare the setter function ```void MyProxy::setExampleProperty(Ti::TiValue value) { ... }```

### Exposing a getter
To create getter you will need _four_ main parts as well, the process is almost identical to the setter:

1. Function declaration in class definition
```Ti::TiValue getExampleProperty();```
2. Exposure macro in class definition ```EXPOSE_GETTER(MyProxy, getExampleProperty)```
3. Hook to the JS engine in class constructor ```createPropertyGetter("exampleProperty", _getExampleProperty);```
4. Declare the setter function ```Ti::TiValue MyProxy::getExampleProperty() { ... }```

### Exposing a method
Again, _four_ parts are required to expose a method to the JS

1. Function declaration in class definition
```Ti::TiValue exampleMethod(Ti::TiValue);```
2. Exposure macro in class definition ```EXPOSE_METHOD(MyProxy, exampleMethod)```
3. Hook to the JS engine in class constructor ```createPropertyFunction("exampleMethod", _exampleMethod);```
4. Declare the method function ```Ti::TiValue MyProxy::exampleMethod(Ti::TiValue value) { ... }```

### Events
Adding events and firing them is very simple
To fire an event you need to create an instance of the TiEventParameters (on the stack) and fire it

    {
        TiEventParameters params;
        params.addParam("some_string_key", "some_value");
        params.addParam("some_int_key", 12);
        params.addParam("some_double_key", 12.32);
        params.addParam("some_proxy_key", this); // `this` is proxy

        // the `e.source` is included
         fireEvent("my_event", params);
    }

To know which events has been added, you can check with the function `onEventAdded(QString)` (make sure you add it as a virtual function in the class definition.

    void MyProxy::onEventAdded(QString eventName)
    {
        if(eventName == "my_event")
        {
            // do something if needed
        }
    }

## The _TiValue_ container
The TiValue class is a simple, yet powerful, class. It's a tiny bridge between the JS types and the native types. The purpose for this is that you, as a module developer, should not be directly touching the JS engine. There are _three_ initializers. The one you need to know about is the 3rd one.

1. ```TiValue( JS Object )```
2. ```TiValue( JS Arguments )```
3. ```TiValue()```

### WARNING!
Always instantiate on the stack:

    TiValue myValue;  
    myValue.setString("Hello World!");

### Functions
You can get native types from a TiValue created from JS. This is for function, setter, getters, etc..

<table>
   <tr> <td>toString() </td>                  <td>QString </td> </tr> 
   <tr> <td>toColor() </td>                   <td>bb::cascades::Color </td> </tr> 
   <tr> <td>toJSValue() </td>                 <td>Handle < Value > (JS Value) </td> </tr> 
   <tr> <td>toProxy() </td>                   <td>TiProxy* </td> </tr> 
   <tr> <td>toBool() </td>                    <td>bool </td> </tr> 
   <tr> <td>toNumber() </td>                  <td>double </td> </tr> 
   <tr> <td>toList() </td>                    <td>QList<TiValue> </td> </tr> 
   <tr> <td>setString(QString) </td>          <td>void </td> </tr>
   <tr> <td>setNumber(double) </td>           <td>void </td> </tr> 
   <tr> <td>setBool(bool) </td>               <td>void </td> </tr> 
   <tr> <td>setProxy(Ti::TiProxy*) </td>      <td>void </td> </tr> 
   <tr> <td>setList(QList<Ti::TiValue>) </td> <td>void </td> </tr> 
   <tr> <td>isList() </td>                    <td>bool </td> </tr> 
   <tr> <td>isNull </td>                      <td>bool </td> </tr> 
   <tr> <td>isList() </td>                    <td>bool </td> </tr> 
   <tr> <td>isUndefined() </td>               <td>bool </td> </tr> 
   <tr> <td>isProxy() </td>                   <td>bool </td> </tr> 
   <tr> <td>isNumber() </td>                  <td>bool </td> </tr> 
</table>

### Getting types from and to JavaScript

For example, to return a `String` to JavaScript you would do this

    TiValue returnValue;
    returnValue.setString("Something cool");
    return returnValue;

To get a `String` from JavaScript, this can be in a setter function, you would do this

    void MyProxy::setMyCustomProperty(TiValue value)
    {
        QString str = value.toString()
        // more code
    }

If you're expecting a JavaScript array, first check for the correct type, the `QList<TiValue>`

    void MyProxy::setMyCustomProperty(TiValue value)
    {
        if(value.isList())
        {
            QList<TiValue> array = value.toList()
            // Now you can loop and get all the values
        }
    }
