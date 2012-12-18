/**********************************************

License: BSD
Project Webpage: http://cajun-jsonapi.sourceforge.net/
Author: Terry Caton

***********************************************/

#include "elements.h"

#include "visitor.h"
#include "reader.h"
#include <cassert>
#include <algorithm>
#include <map>

/*  

TODO:
* better documentation

*/

namespace json
{


Exception::Exception(const std::string& sMessage) :
   std::runtime_error(sMessage) {}


/////////////////////////
// UnknownElement members

class UnknownElement::Imp
{
public:
   virtual ~Imp() {}
   virtual Imp* Clone() const = 0;

   virtual bool Compare(const Imp& imp) const = 0;

   virtual void Accept(ConstVisitor& visitor) const = 0;
   virtual void Accept(Visitor& visitor) = 0;
};


template <typename ElementTypeT>
class UnknownElement::Imp_T : public UnknownElement::Imp
{
public:
   Imp_T(const ElementTypeT& element) : m_Element(element) {}
   virtual Imp* Clone() const { return new Imp_T<ElementTypeT>(*this); }

   virtual void Accept(ConstVisitor& visitor) const { visitor.Visit(m_Element); }
   virtual void Accept(Visitor& visitor) { visitor.Visit(m_Element); }

   virtual bool Compare(const Imp& imp) const
   {
      ConstCastVisitor_T<ElementTypeT> castVisitor;
      imp.Accept(castVisitor);
      return castVisitor.m_pElement &&
             m_Element == *castVisitor.m_pElement;
   }

private:
   ElementTypeT m_Element;
};


class UnknownElement::ConstCastVisitor : public ConstVisitor
{
   virtual void Visit(const Array& array) {}
   virtual void Visit(const Object& object) {}
   virtual void Visit(const Number& number) {}
   virtual void Visit(const String& string) {}
   virtual void Visit(const Boolean& boolean) {}
   virtual void Visit(const Null& null) {}
};

template <typename ElementTypeT>
class UnknownElement::ConstCastVisitor_T : public ConstCastVisitor
{
public:
   ConstCastVisitor_T() : m_pElement(0) {}
   virtual void Visit(const ElementTypeT& element) { m_pElement = &element; } // we don't know what this is, but it overrides one of the base's no-op functions
   const ElementTypeT* m_pElement;
};


class UnknownElement::CastVisitor : public Visitor
{
protected:
   virtual void Visit(Array& array) {}
   virtual void Visit(Object& object) {}
   virtual void Visit(Number& number) {}
   virtual void Visit(String& string) {}
   virtual void Visit(Boolean& boolean) {}
   virtual void Visit(Null& null) {}
};

template <typename ElementTypeT>
class UnknownElement::CastVisitor_T : public CastVisitor
{
public:
   CastVisitor_T() : m_pElement(0) {}
   virtual void Visit(ElementTypeT& element) { m_pElement = &element; } // we don't know what this is, but it overrides one of the base's no-op functions
   ElementTypeT* m_pElement;
};




UnknownElement::UnknownElement() :                               m_pImp( new Imp_T<Null>( Null() ) ) {}
UnknownElement::UnknownElement(const UnknownElement& unknown) :  m_pImp( unknown.m_pImp->Clone()) {}
UnknownElement::UnknownElement(const Object& object) :           m_pImp( new Imp_T<Object>(object) ) {}
UnknownElement::UnknownElement(const Array& array) :             m_pImp( new Imp_T<Array>(array) ) {}
UnknownElement::UnknownElement(const Number& number) :           m_pImp( new Imp_T<Number>(number) ) {}
UnknownElement::UnknownElement(const Boolean& boolean) :         m_pImp( new Imp_T<Boolean>(boolean) ) {}
UnknownElement::UnknownElement(const String& string) :           m_pImp( new Imp_T<String>(string) ) {}
UnknownElement::UnknownElement(const Null& null) :               m_pImp( new Imp_T<Null>(null) ) {}

UnknownElement::~UnknownElement()   { delete m_pImp; }

UnknownElement::operator const Object& () const    { return CastTo<Object>(); }
UnknownElement::operator const Array& () const     { return CastTo<Array>(); }
UnknownElement::operator const Number& () const    { return CastTo<Number>(); }
UnknownElement::operator const Boolean& () const   { return CastTo<Boolean>(); }
UnknownElement::operator const String& () const    { return CastTo<String>(); }
UnknownElement::operator const Null& () const      { return CastTo<Null>(); }

UnknownElement::operator Object& ()    { return ConvertTo<Object>(); }
UnknownElement::operator Array& ()     { return ConvertTo<Array>(); }
UnknownElement::operator Number& ()    { return ConvertTo<Number>(); }
UnknownElement::operator Boolean& ()   { return ConvertTo<Boolean>(); }
UnknownElement::operator String& ()    { return ConvertTo<String>(); }
UnknownElement::operator Null& ()      { return ConvertTo<Null>(); }

UnknownElement& UnknownElement::operator = (const UnknownElement& unknown) 
{
   delete m_pImp;
   m_pImp = unknown.m_pImp->Clone();
   return *this;
}

UnknownElement& UnknownElement::operator[] (const std::string& key)
{
   // the people want an object. make us one if we aren't already
   Object& object = ConvertTo<Object>();
   return object[key];
}

const UnknownElement& UnknownElement::operator[] (const std::string& key) const
{
   // throws if we aren't an object
   const Object& object = CastTo<Object>();
   return object[key];
}

UnknownElement& UnknownElement::operator[] (size_t index)
{
   // the people want an array. make us one if we aren't already
   Array& array = ConvertTo<Array>();
   return array[index];
}

const UnknownElement& UnknownElement::operator[] (size_t index) const
{
   // throws if we aren't an array
   const Array& array = CastTo<Array>();
   return array[index];
}


template <typename ElementTypeT>
const ElementTypeT& UnknownElement::CastTo() const
{
   ConstCastVisitor_T<ElementTypeT> castVisitor;
   m_pImp->Accept(castVisitor);
   if (castVisitor.m_pElement == 0)
      throw Exception("Bad cast");
   return *castVisitor.m_pElement;
}



template <typename ElementTypeT>
ElementTypeT& UnknownElement::ConvertTo() 
{
   CastVisitor_T<ElementTypeT> castVisitor;
   m_pImp->Accept(castVisitor);
   if (castVisitor.m_pElement == 0)
   {
      // we're not the right type. fix it & try again
      *this = ElementTypeT();
      m_pImp->Accept(castVisitor);
   }

   return *castVisitor.m_pElement;
}


void UnknownElement::Accept(ConstVisitor& visitor) const { m_pImp->Accept(visitor); }
void UnknownElement::Accept(Visitor& visitor)            { m_pImp->Accept(visitor); }


bool UnknownElement::operator == (const UnknownElement& element) const
{
   return m_pImp->Compare(*element.m_pImp);
}



//////////////////
// Object members


Object::Member::Member(const std::string& nameIn, const UnknownElement& elementIn) :
   name(nameIn), element(elementIn) {}

bool Object::Member::operator == (const Member& member) const 
{
   return name == member.name &&
          element == member.element;
}

class Object::Finder : public std::unary_function<Object::Member, bool>
{
public:
   Finder(const std::string& name) : m_name(name) {}
   bool operator () (const Object::Member& member) {
      return member.name == m_name;
   }

private:
   std::string m_name;
};



Object::iterator Object::begin() { return m_Members.begin(); }
Object::iterator Object::end() { return m_Members.end(); }
Object::const_iterator Object::begin() const { return m_Members.begin(); }
Object::const_iterator Object::end() const { return m_Members.end(); }

size_t Object::Size() const { return m_Members.size(); }
bool Object::Empty() const { return m_Members.empty(); }

Object::iterator Object::Find(const std::string& name) 
{
   return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
}

Object::const_iterator Object::Find(const std::string& name) const 
{
   return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
}

Object::iterator Object::Insert(const Member& member)
{
   return Insert(member, end());
}

Object::iterator Object::Insert(const Member& member, iterator itWhere)
{
   iterator it = Find(member.name);
   if (it != m_Members.end())
      throw Exception("Object member already exists: " + member.name);

   it = m_Members.insert(itWhere, member);
   return it;
}

Object::iterator Object::Erase(iterator itWhere) 
{
   return m_Members.erase(itWhere);
}

UnknownElement& Object::operator [](const std::string& name)
{

   iterator it = Find(name);
   if (it == m_Members.end())
   {
      Member member(name);
      it = Insert(member, end());
   }
   return it->element;      
}

const UnknownElement& Object::operator [](const std::string& name) const 
{
   const_iterator it = Find(name);
   if (it == end())
		 assert(false);
      //throw Exception("Object member not found: " + name);
   return it->element;
}

void Object::Clear() 
{
   m_Members.clear(); 
}

bool Object::operator == (const Object& object) const 
{
   return m_Members == object.m_Members;
}


/////////////////
// Array members

Array::iterator Array::begin()  { return m_Elements.begin(); }
Array::iterator Array::end()    { return m_Elements.end(); }
Array::const_iterator Array::begin() const  { return m_Elements.begin(); }
Array::const_iterator Array::end() const    { return m_Elements.end(); }

Array::iterator Array::Insert(const UnknownElement& element, iterator itWhere)
{ 
   return m_Elements.insert(itWhere, element);
}

Array::iterator Array::Insert(const UnknownElement& element)
{
   return Insert(element, end());
}

Array::iterator Array::Erase(iterator itWhere)
{ 
   return m_Elements.erase(itWhere);
}

void Array::Resize(size_t newSize)
{
   m_Elements.resize(newSize);
}

size_t Array::Size() const  { return m_Elements.size(); }
bool Array::Empty() const   { return m_Elements.empty(); }

UnknownElement& Array::operator[] (size_t index)
{
   size_t nMinSize = index + 1; // zero indexed
   if (m_Elements.size() < nMinSize)
      m_Elements.resize(nMinSize);
   return m_Elements[index]; 
}

const UnknownElement& Array::operator[] (size_t index) const 
{
   if (index >= m_Elements.size())
      throw Exception("Array out of bounds");
   return m_Elements[index]; 
}

void Array::Clear() {
   m_Elements.clear();
}

bool Array::operator == (const Array& array) const
{
   return m_Elements == array.m_Elements;
} 



//////////////////
// Null members

bool Null::operator == (const Null& trivial) const
{
   return true;
}



} // End namespace
