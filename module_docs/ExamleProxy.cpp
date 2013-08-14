// TODO: Remove the Ti namespace from all the TiCore classes
//
// ==================================================================================================
// Proxy Implementation

#include "ExampleProxy.h"

// You MUST pass in the `name` of the constructor to the base class
ExampleProxy::ExampleProxy(const char* name) :
	Ti::TiProxy(name)
{
	// Create a setter and getter for the same property
	// Note: the setter and getter *MUST* start with `_`
	createPropertySetterGetter("exampleProperty", _setExampleProperty, _getExampleProperty);

	/* Or create them individually, first approach is recommended if
	 * both, setter and getter, exist
	 *
	 * createPropertySetter("exampleProperty", _setExampleProperty);
	 * createPropertyGetter("exampleProperty", _getExampleProperty);
	 * 
	 */

	// Create a method, it also has to start with `_`
	createPropertyFunction("example", _example);

}

ExampleProxy::~ExampleProxy()
{
	// delete instatiated pointers
}

void ExampleProxy::setExampleProperty(Ti::TiValue value)
{

	// Note, some values will be undefined
	// Check with:
	value.isList();
	value.isProxy();

	// To get a QString
	QString val = value.toString();

	// To get a number (double)
	double num = value.toNumber();

	// To get a boolean
	bool flag = value.toBool();

	// To get a list
	QList<Ti::TiValue> list = value.toList()

	// To get a proxy, is this takes a proxy
	Ti::TiProxy *proxy = value.toProxy();

	// To get the actual JavaScript value
	Handle<Value> val = value.toJSValue()

	// To get a color, if this takes a color, otherwise returns bb::cascades::Color::Yellow
	// #include <bb/cascades/Color>
	bb::cascades::Color color = value.toColor();
}

Ti::TiValue ExampleProxy::getExampleProperty()
{
	// Warning!!! do not "new" a Ti::TiValue, instatiate it on the stack!!
	Ti::TiValue value;

	// Caution! use only one of these

	// Creates a JS String()
	value.setString("some string");
	// Creates a JS Number()
	value.setNumber(12.54);
	// Create a JS Bool()
	value.setBool(true);
	// Returns a proxy
	value.setProxy(this);

	// Createa a JS Array() with TiValues
	QList<Ti::Value> list;
	{
		Ti::TiValue value1;
		value1.setString("one");
		list.append(value1);

		Ti::TiValue value2;
		value2.setNumber(2);
		list.append(value2);

		Ti::TiValue value3;
		value3.setBool(true);
		list.append(value3);
	}
	value.setList(list);

	// Return the created value
	return value;
}

Ti::TiValue ExampleProxy::exampleMethod(Ti::TiValue value)
{
	// Now you can call functions in this class
	// Get the value from `value`
	QString str = value.toString();
	str.prepend("Something added to ");

	// Call local function
	// doSomethingWith(str) <---- this would be a local function to this class

	// Create a return value
	Ti::TiValue returnValue;
	returnValue.setString(str);

	// Can also be null or undefined
	returnValue.setUndefined()
	// or
	returnValue.setNull()
	
	return returnValue;
}
// ==================================================================================================