# C-Emulating-Vtables

Description
-----------
This C program simulates the work that a C++ compiler performs to transform
virtual method calls into vtable lookups. Structs are used to store a 
pointer to a vtable so we can achieve polymorphism and dynamic dispatch.
The purpose of this program is to explore the dynamic binding mechanism
of virtual functions in object-oriented languages.