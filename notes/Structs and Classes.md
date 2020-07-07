# Structs and Classes

Imagine trying  to write a course management system  using only primitive types:
built-in types like `int` and `char`, pointers, and arrays. If it's important to
keep track of  every student's name,  major,  and ID number, every function that
deals with a student would have to look something like this:

```cpp
void do_thing(int id, const char* name, const char* major) {
  // Do the thing.
}
```

That's  already pretty ugly,  but now imagine  that you realize  halfway through
that you also need to keep track of every student's GPA. Now you need to go find
every function that deals with a student and add a  `float gpa`  argument.  Then
you need to go find  everywhere  you call any of those functions and add the new
`gpa` argument to the function call.  It's a huge hassle.

The solution  is to create a  custom data type  that bundles up all the data you
need into one **object**. The simplest way to do this is to use a `struct`, like
this:

```cpp
struct Student {
  int   id;
  char* name;
  char* major;
};
```

Now a function that deals with a student can be written as:

```cpp
void do_thing(const Student& student) {
  // Do the thing.
}
```

Need to store more data about your students?  Not a problem: simply add a member
variable to the `Student` type and recompile.

The  `struct`  example above will work (almost) unmodified in plain C.  C++ adds
more power to `struct`s  and calls them `class`es.  The main differences are the
idea of visibility and the ability to add functions to objects.

_Note:  The `struct` and `class` keywords in C++ are almost identical.  The only
difference is the default member visibility - more on that later._


## Member Functions

In addition to member variables, which you can have in C,  C++ allows a class to
have member functions.  These functions define  the actions that  an instance of
your class can perform.

You can't  call a member function  like you can a regular function.  You need an
instance of a class to call it on, and you call it with a dot:

```cpp
void example(const Person& person) {
  // Call Person::yell() on the given person:
  person.yell();
}
```

You declare member functions  inside the class they belong to,  like with member
variables.  Inside the body of a member function, you have access to the class's
member variables by name, as if they were local variables.  You also have access
to an implicit parameter  called `this` - a pointer to  the object that was used
to call the member function.

```cpp
struct Person {
  std::string name;
  int         age;

  // The const suffix is a promise not to change the person.
  void yell() const {
    // The this-> prefix is optional for member variables.
    std::cout << "I'm " << name << " and I'm " << this->age << " years old!\n";
  }

  // Member functions can take arguments just like regular functions.
  void dance(const std::string& style) const {
    std::cout << name << " dances a " << style << ".\n";
  }

  // We can't use const here because we're modifying the person.
  void decrepify() {
    age = 99;
  }
};
```

Once you've defined some member functions, you can use them on your instances in
an intuitive way:

```cpp
// Assume the appropriate constructor exists...
Person alice("Alice", 12);
Person bob("Bob", 500);

alice.yell();       // I'm Alice and I'm 12 years old!
bob.yell();         // I'm Bob and I'm 500 years old!
bob.dance("waltz"); // Bob dances a waltz.
alice.decrepify();
alice.yell();       // I'm Alice and I'm 99 years old!
```

These are also a good way to organize your code. You could always write a global
`add_student_to_course(Student s, Course c)`  function if you really wanted, but
it's much nicer to use a `Course::add(Student s)` member function.


### Constructors and Destructors

Classes also allow you to define a few special member functions. These functions
are the  **constructors**  and  **destructor**  of  the class.  The constructors
define  how to initialize a new instance of your class  when it is created.  The
destructor defines how to  release the resources  held by the an instance of the
class when it goes out of scope.

Constructors have the same name as the class they construct, and they don't have
a return type.  A class can have  multiple constructors  -  as long as they take
different argument types, the compiler will be able to figure out which to use.

```cpp
struct Owl {
  // Member Variables
  // These are pointers so we have an excuse to use a destructor.
  // In real life you'd just use a std::string.
  std::string* name;
  std::string* color;

  // Default Constructor
  // Typical owls are brown owls named Hoobert.
  Owl() {
    name  = new std::string("Hoobert");
    color = new std::string("brown");
  }

  // Copy Constructor
  // How to create one owl by cloning another.
  Owl(const Owl& other) {
    name  = new std::string(*other.name);
    color = new std::string(*other.color);
  }

  // Custom Constructor
  // This lets the user pick a name and color.
  Owl(const std::string& name, const std::string& color) {
    // We need to use "this" to distinguish members from arguments.
    this->name  = new std::string(name);
    this->color = new std::string(color);
  }

  // Destructor
  // Clean up any long-lived resources here.
  ~Owl() {
    delete name;
    delete color;
  }
};
```

A few constructors are special. The constructor that takes no arguments is known
as the  **default constructor**; it needs to exist if you want to make arrays of
your class. The constructor that takes a const reference to the same type is the
**copy constructor**;  it's used  to move  instances of your class  around,  for
example  when you return  your class  from a function  by value.  There's also a
**move constructor** - a sort of optimized copy constructor - that we won't talk
about here.

Any  other constructors  simply provide you  convenient ways  to initialize your
class.  They can take whatever arguments make your code cleanest.

Finally,  your destructor  defines how to  clean up  the resources  used by your
class.  The class's member variables have their destructors called automatically
after your destructor runs, but if you have anything that needs to be explicitly
freed, do it here:  if you're holding any dynamically allocated memory, `delete`
it, and if you're holding any open files or sockets, close them.

Your destructor will be called automatically when  any instance of your class is
destroyed.  For dynamically allocated objects,  this happens when you explicitly
`delete` them.  For local variables, this happens automatically when they go out
of scope.

```cpp
void owlstuff() {
  // Use a custom constructor to create a new owl.
  Owl hoolio_sr("Hoolio", "blue");

  // Use the copy constructor to duplicate the owl.
  Owl hoolio_jr(hoolio_sr);

  // Both owls' destructors are called as they go out of scope.
}

```


## Visibility

Every member variable or function of a class has its own visibility level. There
are  three options,  and the different default visibility is the only difference
between a `struct` and a `class`:

- A `public` member is accessible from anywhere. This is the default for members
  of `struct`s.
- A `private` member is accessible only from inside member functions of the same
  class.  This is the default for members of `class`es.
- A `protected` member is  like a `private` member,  but is also accessible from
  member functions of subclasses of the object where it's defined.

The nuances here won't make sense  until we talk about inheritance, but the main
difference is the difference between `public` and `private`.  That is, do we let
non-member functions access the member or not?  This is easiest to explain  with
an example.

```cpp
class Thing {
  // Default class visibility is private:
  std::string name;

public:
  // Everything in this section is public:
  float price;

  void examine() {
    // Member functions can access private members.
    std::cout << "It's a " << name << ".\n";
  }

private:
  // Things here are private again:
  void secret() {
    // Do stuff.
  }
};

void not_a_member_function(Thing& thing) {
  thing.name  = "widget"; // Compile error!
  thing.price = 14.50;    // This works fine.

  thing.examine(); // Also fine.
  thing.secret();  // Compile error!
}

```

The different  visibility levels  let you separate your members  into two roles.
Public membersare the interface of your class - people using your class will use
these to control it.  Private members are implementation details that your users
don't need to worry about - your member functions manage these for them.


### Getters and Setters

A very common pattern is to have  all of the member variables  of a class marked
private  while most or all of the member functions are marked public.  This lets
the author of the class ensure that no one can  arbitrarily modify the class and
possibly get it into an invalid state.

For example, imagine that you had a `Person` class that stored both the person's
birthday  and their age.  On a valid  `Person`  object,  the two variables would
always agree,  but if a programmer could modify the member variables  they could
change one without changing the other, and the `Person` would become invalid.

Writing  **getters**  and  **setters**  - public functions  that grant access to
private members - lets you control access to  your objects and  ensure that they
stay internally consistent. In the birthday example above, this could look like:

```cpp
class Person {
  // Private Members
  // Assume these types are defined somewhere...
  // I use the m prefix so I can use the nice names for the getters.
  Date mBirthday;
  Age  mAge;

public:
  // Constructor
  Person(const Date& birthday) {
    // Use the setter for safety.
    setBirthday(birthday);
  }

  // A getter for age.
  const Age& age() const {
    return mAge;
  }

  // A getter for birthday.
  const Date& birthday() const {
    return mBirthday;
  }

  // The setter for birthday also updates age.
  void setBirthday(const Date& date) {
    mAge = calculate_age(date);
    mBirthday = date;
  }
};
```

The getters for `age` and `birthday` return const references,  so there's no way
for users to modify a `Person` using those. The setter for `birthday` makes sure
that  `age` is updated correctly  if `birthday` ever changes.  And the lack of a
setter for `age` means that a user can never modify it directly. This class will
never be internally inconsistent.


## Refactoring

It's possible to  split classes  into multiple files  when they grow large.  The
member variables and functions  need to be _declared_ in a `.h` file - these are
needed to compile  other code  that uses your class - but the implementations of
the member functions  can be written in a  separate `.cpp` file.  This keeps the
class definition in the header file short and readable, which is important - the
header file is essentially the user's manual for your class.

```cpp
// MyThing.h
class MyThing {
  int mValue;
public:
  MyThing(int value);

  int squared() const;
  int value()   const;
};
```

```cpp
// MyThing.cpp
MyThing::MyThing(int value) {
  mValue = value;
}

int MyThing::squared() const {
  return mValue * mValue;
}

int MyThing::value() const {
  return mValue;
}
```

This multi-file setup also speeds up compile times for big projects. Your member
functions can now be compiled once  into a single `.o` file instead of having to
be recompiled every time your header is included in another `.cpp` file.
