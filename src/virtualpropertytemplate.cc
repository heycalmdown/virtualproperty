#include <iostream>
#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

class VirtualPropertyTemplate: ObjectWrap
{
private:

public:

	static Persistent<FunctionTemplate> SuperClass;
	static void Init(Handle<Object> target)
	{
		HandleScope scope;

		Local<FunctionTemplate> t = FunctionTemplate::New(New);

		SuperClass = Persistent<FunctionTemplate>::New(t);
		SuperClass->InstanceTemplate()->SetInternalFieldCount(1);
		SuperClass->SetClassName(String::NewSymbol("VirtualPropertyTemplate"));
		NODE_SET_PROTOTYPE_METHOD(SuperClass, "create", CreateTemplate);

		target->Set(String::NewSymbol("VirtualPropertyTemplate"), SuperClass->GetFunction());
	}

	VirtualPropertyTemplate()
	{
	}

	~VirtualPropertyTemplate()
	{
	}

	static Handle<Value> New(const Arguments& args)
	{
		HandleScope scope;
		VirtualPropertyTemplate* hw = new VirtualPropertyTemplate();
		hw->Wrap(args.This());

		return args.This();
	}

	static Handle<Value> GetByName(v8::Local<v8::String> name, const AccessorInfo &info) {
		HandleScope scope;

		// Send real properties untouched
		Local<Value> value =  scope.Close(info.This()->GetRealNamedProperty(name));
		if (!value.IsEmpty()) {
			return value;
		}

		Local<String> getter = String::New("__get__");

		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(getter);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=1;
			Local<Value> argv[1];
			argv[0] = name;
			Local<Value> dynamicProperty = accessorFn->Call(info.This(), argc, argv);
			return dynamicProperty;
		} else {
			return accessor;
		}

		return scope.Close(Handle<Value>(NULL));
	}

	static Handle<Value> GetByIndex(uint32_t index, const AccessorInfo &info) {
		HandleScope scope;

		Local<String> getter = String::New("__get__");
		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(getter);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=1;
			Local<Value> argv[1];
			argv[0] = Number::New(index);
			Local<Value> dynamicProperty = accessorFn->Call(info.This(), argc, argv);
		    String::Utf8Value res2(dynamicProperty->ToString());
			return scope.Close(dynamicProperty);
		} else {
			return scope.Close(accessor);
		}
		return scope.Close(Handle<Value>(NULL));
	}

	static Handle<Array> Enum(const AccessorInfo &info)  {
		HandleScope scope;

		Local<String> enumerator = String::New("__enum__");
		Handle<Value> accessor = info.This()->GetRealNamedPropertyInPrototypeChain(enumerator);
		if (!accessor.IsEmpty() && accessor->IsFunction()) {
			Handle<Function> accessorFn = Handle<Function>(Function::Cast(*accessor));
			int argc=0;
			Local<Value> result = accessorFn->Call(info.This(), argc, NULL);
			return Local<Array>::Cast(result);
		}
		return scope.Close(Handle<Array>(NULL));
	}

	static Handle<Value> CreateTemplate(const Arguments& args)
	{
		HandleScope scope;

		Local<FunctionTemplate> t = FunctionTemplate::New(New);

		SuperClass = Persistent<FunctionTemplate>::New(t);
		SuperClass->InstanceTemplate()->SetInternalFieldCount(2);
		SuperClass->SetClassName(String::NewSymbol("VirtualPropertyTemplate"));
		SuperClass->InstanceTemplate()->SetNamedPropertyHandler(GetByName, NULL, NULL, NULL, NULL);
		SuperClass->InstanceTemplate()->SetIndexedPropertyHandler(GetByIndex, NULL, NULL, NULL, Enum);
		return SuperClass->GetFunction();
	}
};

Persistent<FunctionTemplate> VirtualPropertyTemplate::SuperClass;

extern "C" {
	static void init (Handle<Object> target)
	{
		VirtualPropertyTemplate::Init(target);
	}

	NODE_MODULE(virtualpropertytemplate, init);
}
